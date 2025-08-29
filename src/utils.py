"""
Global utility functions and classes
"""

import sys
from pathlib import Path
from loguru import logger
from functools import cache
from tqdm import tqdm
from typing import Callable
from chardet import detect as charset_detect
from tqdm import tqdm
import json

from src import vars as global_vars
from src.llm import llm as LLM
from src.llm import rag as RAG


def deep_merge(dist_dict: dict, src_dict: dict) -> dict:
    """
    Merge two dict deeply, if the key is the same, the value of dist_dict will be replaced by src_dict.
    dist_dict will not be changed.

    :param dist_dict: The destination dict.
    :param src_dict: The source dict.
    """
    merged_dict = dist_dict.copy()
    for key, value in src_dict.items():
        if key in dist_dict and isinstance(value, dict):
            merged_dict[key] = deep_merge(dist_dict[key], value)
        else:
            merged_dict[key] = value
    return merged_dict


def add_hints_to_comprehension(comprehension, hints: dict[str, str]):
    """
    Add API hints to the function comprehension

    :param comprehension: The comprehension from comprehender
    :param hints: The API hints dict
    """
    func_comprehension: dict[str, str] = comprehension.functions
    for func_name, hint in hints.items():
        hint_str = f"HINT: {hint}"
        if func_name in func_comprehension:
            if not func_comprehension[func_name].endswith(hint_str):
                func_comprehension[func_name] += f"\n{hint_str}"
        elif func_name == "ALL":
            if not comprehension.purpose:
                comprehension.purpose = hint_str
            elif not comprehension.purpose.endswith(hint_str):
                comprehension.purpose += f" {hint_str}"
        else:
            func_comprehension[func_name] = "HINT: " + hint


def setup_default_config(library_name: str | None):
    """
    Setup the default configuration for the library.

    :param library_name: The name of the library.
    """
    # get library name
    if library_name is None:
        if len(global_vars.libraries.keys()) == 1:
            library_name = list(global_vars.libraries.keys())[0]
        else:
            logger.critical("Please specify the library name with the -L option")
            sys.exit(1)

    # check if the library is in the libraries.toml
    if library_name not in global_vars.libraries.keys():
        logger.critical(f"Library {library_name} not found in the libraries.toml.")
        sys.exit(1)

    # load the library configuration template as default value
    global_vars.libraries[library_name] = deep_merge(
        global_vars.libraries_template["a_cpp_library"],
        global_vars.libraries[library_name],
    )

    # load the PromeFuzz configuration template as default value
    global_vars.config = deep_merge(global_vars.config_template, global_vars.config)

    # set the library configuration at the global_vars
    global_vars.library_name = library_name
    global_vars.library_config = global_vars.libraries[library_name]

    # resolve some path for latter process
    # use `strict=False` here to tolerate output_path not exist
    _path = Path(global_vars.library_config.get("output_path")).resolve(strict=False)
    global_vars.library_config["output_path"] = str(_path)

    # set library language
    if global_vars.library_config["language"] in ["c", "C"]:
        global_vars.library_language = global_vars.SupportedLanguages.C
    elif global_vars.library_config["language"] in [
        "c++",
        "C++",
        "cpp",
        "CPP",
        "cxx",
        "CXX",
    ]:
        global_vars.library_language = global_vars.SupportedLanguages.CPP
    elif global_vars.library_config["language"] in ["rust", "Rust", "RUST"]:
        global_vars.library_language = global_vars.SupportedLanguages.RUST
    else:
        logger.critical(
            f"Language {global_vars.library_config['language']} is not supported."
        )
        sys.exit(1)


def setup_llm(llm_name: str) -> LLM.LLMClient:
    """
    Load the LLM configuration and setup the LLM client

    :param llm_name: The name of the LLM configuration
    :return: The LLM client
    """
    # get the LLM configurations
    llm_config = global_vars.config["llm"]

    # set LLM options
    LLM.LLMClient.ENABLE_LOG = llm_config["enable_log"]

    # get the selected LLM configuration
    if not llm_name:
        llm_name = llm_config["default_llm"]
    if llm_name not in llm_config.keys():
        raise ValueError(f"LLM {llm_name} not found in the LLM configuration.")
    selected_llm = llm_config[llm_name]
    llm_type = selected_llm["llm_type"]

    # set default options for the selected LLM
    if (
        llm_type == LLM.LLM_TYPES.OLLAMA.value
        or llm_type == LLM.LLM_TYPES.OLLAMA_REASONING.value
    ):
        selected_llm = deep_merge(
            global_vars.config_template["llm"]["local_llm"],
            selected_llm,
        )
    elif (
        llm_type == LLM.LLM_TYPES.OPENAI.value
        or llm_type == LLM.LLM_TYPES.OPENAI_REASONING.value
    ):
        selected_llm = deep_merge(
            global_vars.config_template["llm"]["cloud_llm"],
            selected_llm,
        )
        # set the OpenAI API key
        if selected_llm["api_key"] == "":
            import os

            selected_llm["api_key"] = os.getenv("OPENAI_API_KEY")
            if selected_llm["api_key"] is None:
                raise ValueError(
                    "OpenAI API key is neither provided nor found in the environment"
                )
    else:
        raise ValueError(f"Unsupported LLM type: {llm_type}")

    # create the LLM client
    match llm_type:
        case LLM.LLM_TYPES.OLLAMA.value:
            llm_client = LLM.OllamaClient(
                selected_llm["host"],
                selected_llm["port"],
                selected_llm["model"],
                selected_llm["max_tokens"],
                selected_llm["timeout"],
                selected_llm["retry_times"],
            )
        case LLM.LLM_TYPES.OPENAI.value:
            llm_client = LLM.OpenAIClient(
                selected_llm["base_url"],
                selected_llm["api_key"],
                selected_llm["model"],
                selected_llm["temperature"],
                selected_llm["max_tokens"],
                selected_llm["timeout"],
                selected_llm["retry_times"],
            )
        case LLM.LLM_TYPES.OLLAMA_REASONING.value:
            llm_client = LLM.OllamaReasoningClient(
                selected_llm["host"],
                selected_llm["port"],
                selected_llm["model"],
                selected_llm["max_tokens"],
                selected_llm["timeout"],
                selected_llm["retry_times"],
            )
        case LLM.LLM_TYPES.OPENAI_REASONING.value:
            llm_client = LLM.OpenAIReasoningClient(
                selected_llm["base_url"],
                selected_llm["api_key"],
                selected_llm["model"],
                selected_llm["temperature"],
                selected_llm["max_tokens"],
                selected_llm["timeout"],
                selected_llm["retry_times"],
            )

    # validate the LLM client
    if global_vars.config["llm"]["validate_llm"]:
        logger.info(f"Validating the LLM client...")
        if not llm_client.is_available:
            raise ValueError(f"LLM client is not available.")

    logger.success(f"The LLM client {llm_name} has been setup.")

    return llm_client


def setup_rag(
    llm_name: str,
    database_path: Path = None,
) -> RAG.RAGRetriever:
    """
    Load the LLM configuration and setup the RAG retriever

    :param llm_name: The name of the LLM configuration
    :param database_path: Path to store the vector database, default not store
    :return: The RAG retriever
    """

    # maybe download the nltk data
    try:
        setup_nltk_requiements()
    except Exception as e:
        logger.critical(
            f"Failed to download the required nltk data, please check your network connection: \n{e}"
        )
        sys.exit(1)

    # get the LLM configurations
    llm_config = global_vars.config["llm"]

    # get the selected LLM configuration
    if llm_name not in llm_config.keys():
        raise ValueError(f"LLM {llm_name} not found in the LLM configuration.")
    selected_llm = llm_config[llm_name]
    llm_type = selected_llm["llm_type"]

    # set default options for the selected LLM
    if llm_type == LLM.LLM_TYPES.OLLAMA.value:
        selected_llm = deep_merge(
            global_vars.config_template["llm"]["local_llm"],
            selected_llm,
        )
    elif llm_type == LLM.LLM_TYPES.OPENAI.value:
        selected_llm = deep_merge(
            global_vars.config_template["llm"]["cloud_llm"],
            selected_llm,
        )
        # set the OpenAI API key
        if selected_llm["api_key"] == "":
            import os

            selected_llm["api_key"] = os.getenv("OPENAI_API_KEY")
            if selected_llm["api_key"] is None:
                raise ValueError(
                    "OpenAI API key is neither provided nor found in the environment"
                )
    else:
        raise ValueError(f"Unsupported LLM type: {llm_type}")

    # create database path
    if database_path is not None:
        database_path.mkdir(parents=True, exist_ok=True)

    # create the RAG retriever
    if llm_type == LLM.LLM_TYPES.OLLAMA.value:
        rag_retriever = RAG.OllamaRetriever(
            selected_llm["host"],
            selected_llm["port"],
            selected_llm["model"],
            selected_llm["max_tokens"],
            database_path=database_path,
        )
    elif llm_type == LLM.LLM_TYPES.OPENAI.value:
        rag_retriever = RAG.OpenAIRetriever(
            selected_llm["base_url"],
            selected_llm["api_key"],
            selected_llm["model"],
            selected_llm["max_tokens"],
            database_path=database_path,
        )

    logger.success(f"The RAG retriever {llm_name} has been setup.")

    return rag_retriever


def setup_nltk_requiements():
    """
    The langchain unstructured requires the nltk package, this function will download the required nltk data.
    """
    import nltk

    try:
        nltk.data.find("tokenizers/punkt_tab")
        nltk.data.find("taggers/averaged_perceptron_tagger_eng")
    except:
        logger.info("Downloading the required nltk data...")
        nltk.download("punkt_tab", raise_on_error=True)
        nltk.download(
            "averaged_perceptron_tagger_eng",
            raise_on_error=True,
        )


def path_in_paths(p: Path, paths: list[Path]) -> bool:
    """
    Check if the path is in the paths or part of the paths.

    :param p: The path to check.
    :param paths: The paths to check.
    """
    for path in paths:
        if path in p.parents:
            return True
    return False


def is_source_file(file: Path) -> bool:
    """
    Check if the file is a source file.

    :param file: The file
    :return: True if the file is a source file, False otherwise
    """
    if file is None:
        return False
    if hasattr(is_source_file, "source_files"):
        return file.resolve() in is_source_file.source_files
    else:
        try:
            source_files = json.loads(
                (
                    Path(global_vars.library_config["output_path"])
                    / "preprocessor"
                    / "sources.json"
                ).read_text()
            )
        except Exception as e:
            logger.error(
                f"Failed to load source files from sources.json, error: {e}, you should re-run the preprocessor."
            )
            return False
        # FIXME: currently, we only consider those source files in the compile_commands.json
        #        and those header files specified in the library configuration.
        #        This is not a perfect solution, we should consider all the source files and
        #        all the header files included in the source files, which is a little bit complex.
        is_source_file.source_files = [Path(f).resolve() for f in source_files]
        return is_source_file(file)


def parse_location(location_line: str) -> tuple[str | None, int, int]:
    """
    Parse the location line in the meta file

    :param location_line: The location line
    :return: The parsed location tuple, like: (file, line, col), file set to None if not found
    """
    from parse import parse

    # a location line is like:
    # "file:line:col"
    result = parse("{file}:{line:d}:{col:d}", location_line)
    if result is None:
        return (None, -1, -1)
    return (result["file"], result["line"], result["col"])


def filter_typename(t: str) -> str:
    """
    Filter the type name, make it a valid composite type name.
    """
    # remove the pointer, reference, and const
    t = t.replace("*", "").replace("&", "").replace("const", "")
    # remove array
    t = t.split("[")[0] if "[" in t else t
    # remove the space
    t = t.strip()
    return t


def remove_template_parts_in_name(name: str) -> str:
    """
    Remove the template parts in the name, like: "std::vector<int>" -> "std::vector"
    """
    if "<" not in name:
        return name
    # find the first "<" and the corresponding ">" in the name
    start = name.find("<")
    end = start
    count = 1
    for i, c in enumerate(name[start + 1 :], start + 1):
        if c == "<":
            count += 1
        elif c == ">":
            count -= 1
        if count == 0:
            end = i
            break
    # remove the template part
    processed_name = name[:start] + name[end + 1 :]
    # there may be not only one template part in the name
    return remove_template_parts_in_name(processed_name)


# remove the duplicated elements in a list
deduplicate_list: Callable[[list], list] = lambda l: list(dict.fromkeys(l))


# concatenate excerpts list into human readable string
concat_excerpts: Callable[[list[RAG.RAGExcerpt]], str] = lambda excerpts: "\n\n".join(
    f"{i + 1}. Excerpt from {excerpt.location}:\n```\n{excerpt.content}\n```"
    for i, excerpt in enumerate(excerpts)
)


class ProgressTitle:
    """
    A progress bar title
    Use it with the `with` statement to show the progress bar title
    """

    def __init__(self, title: str):
        self.title = title

    def __enter__(self):
        self.progress = tqdm(desc=self.title, bar_format="{desc}", leave=False)
        return self.progress

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.progress.close()


def with_progress_update(func):
    """
    Decorator to update the progress bar after each function call
    The named argument `progress` should be the progress bar
    """

    def wrapper(*args, **kwargs):
        progress: tqdm = kwargs.pop("progress", None)
        result = func(*args, **kwargs)
        if progress is not None:
            progress.update(1)
        return result

    return wrapper


class FilePos:
    """
    The class to represent the position in a text file
    """

    @staticmethod
    @cache
    def _open_file_cached(file: Path) -> tuple[str, list[int]]:
        """
        Open file cached version
        """
        return FilePos._open_file(file)

    @staticmethod
    def _open_file(file: Path) -> tuple[str, list[int]]:
        """
        Open the file and get the content and line length list

        :param file: The file path
        :return: The content and line length list, for example:
        ```
        ("this is a line\nanother line\n", [15, 13])
        ```
        """
        # For some annoying libraries not written in utf-8, we need to detect the encoding
        with open(file, "rb") as f:
            content = f.read()
            encoding = charset_detect(content)["encoding"]
            if encoding is None:
                logger.warning(
                    f"Unable to detect encoding for {file}, trying reading it as UTF-8..."
                )
                encoding = "utf-8"
            content = content.decode(encoding)
        lines = [
            len(line) + 1 for line in content.split("\n")
        ]  # plus 1 for the newline char
        return content, lines

    def __init__(self, file: Path, line: int, col: int, reload_file: bool = False):
        """
        Initialize the file position

        :param file: The source file path
        :param line: The line number, index start from 1
        :param col: The column number, index start from 1
        :param reload_file: Whether to reload the file content
        """
        file = file.resolve()
        self.file = file
        self.content, self.lines_length = (
            FilePos._open_file(file) if reload_file else FilePos._open_file_cached(file)
        )
        self._line = line
        self._col = col
        try:
            self._index = self.pos_to_index(line, col)
        except IndexError:
            raise ValueError(f"Invalid line {line} or column {col} in file {file}")

    @staticmethod
    def from_location_line(location_line: str, reload_file: bool = False) -> "FilePos":
        """
        Create the source file position from the location line

        :param location_line: The location line
        :param reload_file: Whether to reload the file content
        :return: The source file position
        """
        file, line, col = parse_location(location_line)
        if file is None:
            raise ValueError(f"Invalid location line: {location_line}")
        try:
            new_pos = FilePos(Path(file), line, col, reload_file=reload_file)
        except Exception as e:
            raise ValueError(
                f"Failed to create FilePos from location line {location_line}: {e}"
            )
        return new_pos

    # These setters are used to update the index when line or col is changed or vice versa
    @property
    def line(self) -> int:
        return self._line

    @line.setter
    def line(self, value: int):
        self._index = self.pos_to_index(value, self.col)
        self._line = value

    @property
    def col(self) -> int:
        return self._col

    @col.setter
    def col(self, value: int):
        self._index = self.pos_to_index(self.line, value)
        self._col = value

    @property
    def index(self) -> int:
        return self._index

    @index.setter
    def index(self, value: int):
        self._line, self._col = self.index_to_pos(value)
        self._index = value

    def index_to_pos(self, index: int) -> tuple[int, int]:
        """
        Convert the char index of the file to the line and column number

        :param index: The char index
        :return: The line and column number tuple
        """
        line = 1
        index += 1  # index starts from 0, but line and col starts from 1
        while index > self.lines_length[line - 1]:
            index -= self.lines_length[line - 1]
            line += 1
        return line, index

    def pos_to_index(self, line: int, col: int) -> int:
        """
        Convert the line and column number to the char index of the file

        :param line: The line number
        :param col: The column number
        :return: The char index
        """
        return sum(self.lines_length[: line - 1]) + col - 1

    @property
    def cur_char(self) -> str:
        """
        Get the current char content
        """
        return self.content[self.index]

    @property
    def cur_line(self) -> str:
        """
        Get the current line content
        """
        line_start_index = self.pos_to_index(self.line, 1)
        line_end_index = line_start_index + self.lines_length[self.line - 1] - 1
        return self.content[line_start_index:line_end_index]

    def set_to_start_of_file(self):
        """
        Set the position to the start of the file
        """
        self.index = 0

    def set_to_end_of_file(self):
        """
        Set the position to the end of the file
        """
        self.index = len(self.content) - 1

    def set_to_start_of_line(self):
        """
        Set the position to the start of the line
        """
        self.col = 1

    def set_to_end_of_line(self):
        """
        Set the position to the end of the line
        """
        self.col = self.lines_length[self.line - 1]

    def is_in_same_line(self, other: "FilePos") -> bool:
        """
        Check if the two positions are in the same line

        :param other: The other position
        :return: True if in the same line, False otherwise
        """
        return self.file == other.file and self.line == other.line

    def set_forward(self, step: int):
        """
        Move the position forward by the step

        :param step: The step to move forward
        """
        try:
            self.index += step
        except IndexError:
            self.set_to_end_of_file()

    def set_backward(self, step: int):
        """
        Move the position backward by the step

        :param step: The step to move backward
        """
        try:
            self.index -= step
        except IndexError:
            self.set_to_start_of_file()

    def set_to_next_char(self):
        """
        Move the position to the next char
        """
        self.set_forward(1)

    def set_to_prev_char(self):
        """
        Move the position to the previous char
        """
        self.set_backward(1)

    def walk(self, is_backward: bool = False, until: "FilePos" = None):
        """
        Walk forward or backward by one char

        :param is_backward: True if walk backward, False otherwise
        :param until: The end position, include the end position
        :return: The next position generator, include the current position
        """
        yield self
        walk_pos = self
        while True:
            if until is not None and walk_pos == until:
                break
            try:
                if is_backward:
                    walk_pos -= 1
                else:
                    walk_pos += 1
                yield walk_pos
            except ValueError:
                break

    def walk_line(self, is_backward: bool = False, until: "FilePos" = None):
        """
        Walk forward or backward by one line, each position returned is the start of the line

        :param is_backward: True if walk backward, False otherwise
        :param until: The end position, include the end position
        :return: The next position generator, include the current position
        """
        yield self
        walk_pos = self
        while True:
            if until is not None and walk_pos.is_in_same_line(until):
                break
            try:
                if is_backward:
                    walk_pos = FilePos(walk_pos.file, walk_pos.line - 1, 1)
                    walk_pos.set_to_end_of_line()
                else:
                    walk_pos = FilePos(walk_pos.file, walk_pos.line + 1, 1)
                yield walk_pos
            except ValueError:
                break

    def find_str(self, target: str, is_backward: bool = False) -> "FilePos":
        """
        Find the target string from the current position

        :param target: The target string
        :param is_backward: True if find backward, False otherwise
        :return: The first char position of the target string, None if not found
        """
        if is_backward:
            str_index = self.content.rfind(target, 0, self.index)
        else:
            str_index = self.content.find(target, self.index)
        if str_index == -1:
            return None
        return FilePos(self.file, *self.index_to_pos(str_index))

    def get_content_till_pos(self, end_pos: "FilePos") -> str:
        """
        Get the contents from the current position to the end position, current position can be after the end position

        :param end_pos: The end position
        :return: The content string, include the current position and end position
        """
        if self.file != end_pos.file:
            raise ValueError("Can not get content from different files")

        if self == end_pos:
            return ""
        elif self > end_pos:
            start_pos, end_pos = end_pos, self
        else:
            start_pos = self

        start_index = start_pos.index
        end_index = end_pos.index
        return self.content[start_index:end_index]

    def copy(self) -> "FilePos":
        """
        Copy the current position

        :return: The copied position
        """
        return FilePos(self.file, self.line, self.col)

    def __add__(self, other):
        if isinstance(other, int):
            new_index = self.index + other
            try:
                new_line, new_col = self.index_to_pos(new_index)
            except IndexError:
                raise ValueError(f"{self} + {other} is out of range")
            return FilePos(self.file, new_line, new_col)
        else:
            raise ValueError("Can only add int to SourceFilePos")

    def __sub__(self, other):
        if isinstance(other, int):
            return self + (-other)
        elif isinstance(other, FilePos):
            if self.file != other.file:
                raise ValueError(
                    "Can not subtract the SourceFilePos from different files"
                )
            if self < other:
                raise ValueError("Can not subtract the SourceFilePos from larger one")
            return self.index - other.index

    def __eq__(self, other: "FilePos"):
        return self.file == other.file and self.index == other.index

    def __lt__(self, other: "FilePos"):
        if self.file != other.file:
            raise ValueError("Can not compare the SourceFilePos from different files")
        if self.index < other.index:
            return True
        else:
            return False

    def __le__(self, other: "FilePos"):
        return self < other or self == other

    def __gt__(self, other: "FilePos"):
        return not self <= other

    def __ge__(self, other: "FilePos"):
        return not self < other

    def __str__(self):
        return f"{self.file}:{self.line}:{self.col}"

    @property
    def human_str(self) -> str:
        """
        Print the position in human readable format
        """
        human = str(self)
        human += f"\n{self.cur_line}"
        human += f"\n{' ' * (self.col - 1)}^"
        return human


class SinglePool:
    """
    Single-threaded pool executor, for debugging
    """

    def __init__(self): ...

    def submit(self, func):
        """
        Submit the function to the pool
        """
        func()

    def shutdown(self, wait): ...