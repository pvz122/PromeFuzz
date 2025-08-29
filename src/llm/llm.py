"""
A wrapper for the OpenAI API and Ollama API
"""

from openai import OpenAI
from ollama import Client as Ollama
from loguru import logger
from enum import Enum
from abc import ABC, abstractmethod
import threading
import tiktoken
import time
import atexit
import sys
from typing import Union
from dataclasses import dataclass

from src import vars as global_vars


class LLM_TYPES(Enum):
    OLLAMA = "ollama"
    OPENAI = "openai"
    OLLAMA_REASONING = "ollama-reasoning"
    OPENAI_REASONING = "openai-reasoning"


@dataclass
class QueryStats:
    """
    Query statistics
    """

    count: int
    """
    The number of queries made
    """

    tokens: dict[int, tuple[int, int]]
    """
    Query tokens, Query ID -> (query tokens, response tokens)
    """

    time: dict[int, float]
    """
    Query elapsed time, Query ID -> elapsed time
    """

    total_tokens: tuple[int, int]
    """
    Total tokens of the queries, (query tokens, response tokens)
    """

    @classmethod
    def from_empty(cls):
        """
        Create an empty QueryStats
        """
        return cls(0, {}, {}, (0, 0))


class QueryLogger:
    """
    Logger for the LLM query
    """

    def __init__(self):
        """
        Initialize the query logger
        """
        # thread lock
        self.lock = threading.Lock()

        # create the query stats
        self.stats = QueryStats.from_empty()

        # temporary dict to calculate the elapsed time
        self.query_start_time: dict[int, float] = {}

        # whether to log the query, controled by the LLM client
        self.enable_log = True

        # register the start and exit functions
        atexit.register(self._at_exit)

    def _at_start(self):
        if not hasattr(self, "_started"):
            self._started = True
            # print the start log
            cmdline_str = " ".join(sys.argv)
            start_log = f"LLM query logger started for program `{cmdline_str}`"
            self._print_log(start_log)

    def _at_exit(self):
        if hasattr(self, "_started"):
            # print the total tokens
            cmdline_str = " ".join(sys.argv)
            exit_log = f"Program `{cmdline_str}` exited.\nTotal query times: {self.stats.count}, total tokens: {self.stats.total_tokens[0]} -> {self.stats.total_tokens[1]}"
            self._print_log(exit_log)
        # close the log file
        if hasattr(self, "log_file") and not self.log_file.closed:
            self.log_file.close()

    def _new_query_id(self):
        """
        Generate a new query ID
        """
        with self.lock:
            self.stats.count += 1
            new_query_id = self.stats.count
        return new_query_id

    def _print_log(self, content: str):
        """
        Print the content to the log file and the logger
        """
        with self.lock:
            if not hasattr(self, "log_file"):
                self.log_file = open(
                    global_vars.promefuzz_path / "logs" / "llm.log", "a"
                )
            self.log_file.write(
                time.strftime("%Y-%m-%d %H:%M:%S") + "\n" + content + "\n"
            )
            self.log_file.flush()
        logger.debug(content)

    @staticmethod
    def _message_to_str(message: dict) -> str:
        """
        Print a message to string
        """
        return f"{message['role']}:\n---\n{message['content']}"

    @staticmethod
    def _messages_to_str(messages: list) -> str:
        """
        Print messages to string
        """
        return "\n===\n".join(
            [QueryLogger._message_to_str(message) for message in messages]
        )

    def log_tokens(self, query_id: int, query_tokens: int, response_tokens: int):
        """
        Log the tokens of the query and response

        :param query_id: Query ID
        :param query_tokens: Query token count
        :param response_tokens: Response token count
        """
        # add the tokens to the total tokens
        with self.lock:
            self.stats.total_tokens = (
                self.stats.total_tokens[0] + query_tokens,
                self.stats.total_tokens[1] + response_tokens,
            )
            self.stats.tokens[query_id] = (query_tokens, response_tokens)

        # print the tokens log
        token_log = "Tokens for query {}: {} -> {}\nTotal tokens: {} -> {}".format(
            query_id,
            query_tokens,
            response_tokens,
            self.stats.total_tokens[0],
            self.stats.total_tokens[1],
        )
        self._print_log(token_log)

    def log_messages(self, query_id: int, messages: list):
        """
        Log the messages

        :param query_id: Query ID
        :param messages: Messages
        """
        with self.lock:
            self.query_start_time[query_id] = time.time()
        message_log = "Messages for query {}:\n{}".format(
            query_id, self._messages_to_str(messages)
        )
        self._print_log(message_log)

    def log_response(self, query_id: int, response: str):
        """
        Log the response

        :param query_id: Query ID
        :param response: Response
        """
        elapsed_time = time.time() - self.query_start_time[query_id]
        with self.lock:
            self.stats.time[query_id] = elapsed_time
        response_log = "Response for query {} after {:.2f}s:\n{}".format(
            query_id, elapsed_time, response
        )
        self._print_log(response_log)

    def log_reasoning(self, query_id: int, reasoning: str):
        """
        Log the reasoning

        :param query_id: Query ID
        :param reasoning: Reasoning
        """
        reasoning_log = "Reasoning for query {}:\n{}".format(query_id, reasoning)
        self._print_log(reasoning_log)

    def with_log(self, func):
        """
        Decorator to log the query

        :param func: The `query_with_messages` function
        :return: `query_with_messages` function with logging
        """
        # the self in the wrapper is the LLMClient instance
        # so we need to pass the QueryLogger instance to the wrapper
        _self = self

        def wrapper(self, *args, **kwargs):
            # check if the client is a reasoning client
            is_reasoning_client = isinstance(self, ReasoningLLMClient)

            # check if the logger is enabled
            if not _self.enable_log:
                return func(self, *args, **kwargs)
            _self._at_start()

            # generate a new query ID
            query_id = _self._new_query_id()

            # get the arguments
            # function is like:
            # def query_with_messages(
            #     self, messages: list[dict[str, str]], return_tokens: bool = False
            # ) -> Union[str, tuple[str, int, int], None]:
            arg_messages = args[0]
            arg_return_tokens = args[1] if len(args) > 1 else False

            # log messages
            _self.log_messages(query_id, arg_messages)

            # invoke the function
            # set `return_tokens` to True to log the tokens
            ret = func(self, arg_messages, True)
            if ret is None:
                # log the query failed
                _self._print_log(f"Query {query_id} failed")
                return None
            else:
                if is_reasoning_client:
                    response, reasoning, query_tokens, response_tokens = ret
                    # log reasoning
                    _self.log_reasoning(query_id, reasoning)
                else:
                    response, query_tokens, response_tokens = ret

            # log response
            _self.log_response(query_id, response)

            # log tokens
            _self.log_tokens(query_id, query_tokens, response_tokens)

            # return the response
            if arg_return_tokens:
                return ret
            else:
                return (response, reasoning) if is_reasoning_client else response

        return wrapper


class LLMClient(ABC):
    """
    LLM client, abstract class
    """

    # whether to enable the query logger
    ENABLE_LOG = True

    query_logger: QueryLogger = QueryLogger()

    @abstractmethod
    def __init__(self):
        if not self.ENABLE_LOG:
            self.query_logger.enable_log = False

    @abstractmethod
    def query_with_messages(
        self, messages: list[dict[str, str]], return_tokens: bool = False
    ) -> Union[str, tuple[str, int, int], None]:
        """
        Query with messages list

        :param messages: Messages
        :param return_tokens: Whether to return the tokens of the query and response
        :return: Response text, or tuple of response text and tokens, or None if the query failed
        """
        ...

    def query_once(self, user_prompt: str, system_prompt: str = "") -> str:
        """
        Query once with system prompt and user prompt

        :param system_prompt: System prompt
        :param user_prompt: User prompt
        :return: Response
        """
        return (
            self.query_with_messages(
                [
                    {"role": "user", "content": user_prompt},
                ]
            )
            if system_prompt == ""
            else self.query_with_messages(
                [
                    {"role": "system", "content": system_prompt},
                    {"role": "user", "content": user_prompt},
                ]
            )
        )

    @property
    def is_available(self) -> bool:
        """
        Test the LLM client availability by sending a test request

        :return: True if the client is available, False otherwise
        """
        try:
            response = self.query_once('say "pong"')
            if response:
                return True
        except Exception as e:
            logger.error("LLM client test exception: " + str(e))
        return False

    @classmethod
    def with_retry(cls, func):
        """
        Decorator to retry the query
        """

        def wrapper(self, *args, **kwargs):
            for i in range(self.retry_times):
                if ret := func(self, *args, **kwargs):
                    return ret
                else:
                    logger.warning(
                        f"Query attempt {i + 1} failed, {'retrying' if i + 1 < self.retry_times else 'aborting'}"
                    )
            return None

        return wrapper


class ReasoningLLMClient(LLMClient):
    """
    The reasoning LLM client, like OpenAI o1 and DeepSeek R1
    """

    @abstractmethod
    def __init__(self):
        super().__init__()

    @abstractmethod
    def query_with_messages(
        self, messages: list[dict[str, str]], return_tokens: bool = False
    ) -> Union[tuple[str, str], tuple[str, str, int, int], None]:
        """
        Query with messages list

        :param messages: Messages
        :param return_tokens: Whether to return the tokens of the query and response
        :return: A tuple of response text and reasoning;
        or a tuple of response text, reasoning, and tokens;
        or None if the query failed
        """
        ...

    def query_once(self, user_prompt: str, system_prompt: str = "") -> tuple[str, str]:
        """
        Query once with system prompt and user prompt

        :param system_prompt: System prompt
        :param user_prompt: User prompt
        :return: Response and reasoning
        """
        return super().query_once(user_prompt, system_prompt)


class OpenAIClient(LLMClient):
    """
    OpenAI compatible LLM client
    """

    def __init__(
        self,
        base_url: str = "https://api.openai.com/v1/",
        api_key: str = "",
        model: str = "gpt-4o",
        temperature: float = 0.9,
        max_tokens: int = -1,
        timeout: int = 80,
        retry_times: int = 3,
    ):
        """
        Initialize the OpenAI compatible LLM client

        :param base_url: Base URL of the LLM API, default is the OpenAI API
        :param api_key: API key for the LLM API, default is the OPENAI_API_KEY environment variable
        :param model: Model to use, default is gpt-4o
        :param temperature: Temperature of the LLM, default is 0.9
        :param max_tokens: Maximum tokens of the LLM, default is -1(unlimited)
        :param timeout: Timeout for API requests, default is 80 seconds
        :param retry_times: Number of times to retry the API requests, default is 3
        """
        try:
            self.client = OpenAI(
                api_key=api_key,
                base_url=base_url,
                timeout=timeout,
                max_retries=0,
            )
        except Exception as e:
            raise ValueError("OpenAI API initialization failed") from e
        self.temperature = temperature
        self.model = model
        self.max_tokens = max_tokens
        self.retry_times = retry_times

        super().__init__()

    @LLMClient.with_retry
    @LLMClient.query_logger.with_log
    def query_with_messages(
        self, messages: list[dict[str, str]], return_tokens: bool = False
    ) -> Union[str, tuple[str, int, int], None]:
        """
        Query with messages list

        :param messages: Messages
        :param return_tokens: Whether to return the tokens of the query and response
        :return: Response text, or tuple of response text and tokens, or None if the query failed
        """
        try:
            # Though OpenAI deprecated the `max_tokens` parameter,
            # other LLM APIs like DeepSeek still use it.
            # Use max_completion_tokens for newer OpenAI API, fallback to max_tokens for compatibility
            api_params = {
                "model": self.model,
                "messages": messages,
                "temperature": self.temperature,
            }

            if self.max_tokens != -1:
                # Try max_completion_tokens first (newer OpenAI API)
                if "gpt" in self.model or "o1" in self.model:
                    api_params["max_completion_tokens"] = self.max_tokens
                else:
                    # Fallback to max_tokens for other APIs
                    api_params["max_tokens"] = self.max_tokens

            completion = self.client.chat.completions.create(**api_params)
            response = completion.choices[0].message.content
        except Exception as e:
            logger.error(f"OpenAI API exception: {e}")
            return None

        if not return_tokens:
            return response
        else:
            return (
                response,
                completion.usage.prompt_tokens,
                completion.usage.completion_tokens,
            )


class OllamaClient(LLMClient):
    """
    Ollama compatible LLM client
    """

    def __init__(
        self,
        host: str,
        port: int,
        model: str,
        max_tokens: int = -1,
        timeout: int = 80,
        retry_times: int = 3,
    ):
        """
        Initialize the Ollama compatible LLM client

        :param host: Host of the Ollama API
        :param port: Port of the Ollama API
        :param model: Model to use
        :param max_tokens: Maximum tokens of the Ollama input
        :param timeout: The timeout seconds for each query
        :param retry_times: Number of times to retry the query
        """
        self.client = Ollama(f"{host}:{port}", timeout=timeout)
        self.model = model
        self.max_tokens = max_tokens
        self.retry_times = retry_times

        super().__init__()

    @LLMClient.with_retry
    @LLMClient.query_logger.with_log
    def query_with_messages(
        self, messages: list[dict[str, str]], return_tokens: bool = False
    ) -> Union[str, tuple[str, int, int], None]:
        """
        Query with messages list

        :param messages: Messages
        :param return_tokens: Whether to return the tokens of the query and response
        :return: Response text, or tuple of response text and tokens, or None if the query failed
        """
        # query the Ollama API
        try:
            response = self.client.chat(
                model=self.model,
                messages=messages,
                options={"num_ctx": self.max_tokens} if self.max_tokens != -1 else None,
            )
            response = response["message"]["content"]
        except Exception as e:
            logger.error("Ollama API exception: " + str(e))
            return None

        if not return_tokens:
            return response
        else:
            return response, self.count_tokens(messages), self.count_tokens(response)

    @classmethod
    def count_tokens(cls, message: str | list) -> int:
        """
        Count the tokens of the query message or response message

        :param messages: Query message list or response message text
        :return: Token count
        """
        if isinstance(message, str):
            return len(tiktoken.get_encoding("cl100k_base").encode(message))
        elif isinstance(message, list):
            return sum([cls.count_tokens(m["content"]) for m in message])


class OpenAIReasoningClient(ReasoningLLMClient):
    """
    OpenAI compatible reasoning LLM client
    """

    def __init__(
        self,
        base_url: str = "https://api.openai.com/v1/",
        api_key: str = "",
        model: str = "o1",
        temperature: float = 0.9,
        max_tokens: int = -1,
        timeout: int = 600,
        retry_times: int = 3,
    ):
        """
        Initialize the OpenAI compatible LLM client

        :param base_url: Base URL of the LLM API, default is the OpenAI API
        :param api_key: API key for the LLM API, default is the OPENAI_API_KEY environment variable
        :param model: Model to use, default is o1
        :param temperature: Temperature of the LLM, default is 0.9
        :param max_tokens: Maximum tokens of the LLM, default is -1(unlimited)
        :param timeout: Timeout for API requests, default is 600 seconds
        :param retry_times: Number of times to retry the API requests, default is 3
        """
        try:
            self.client = OpenAI(
                api_key=api_key,
                base_url=base_url,
                timeout=timeout,
                max_retries=0,
            )
        except Exception as e:
            raise ValueError("OpenAI API initialization failed") from e
        self.temperature = temperature
        self.model = model
        self.max_tokens = max_tokens
        self.retry_times = retry_times

        super().__init__()

    @LLMClient.with_retry
    @LLMClient.query_logger.with_log
    def query_with_messages(
        self, messages: list[dict[str, str]], return_tokens: bool = False
    ) -> Union[tuple[str, str], tuple[str, str, int, int], None]:
        """
        Query with messages list

        :param messages: Messages
        :param return_tokens: Whether to return the tokens of the query and response
        :return: A tuple of response text and reasoning;
        or a tuple of response text, reasoning, and tokens;
        or None if the query failed
        """
        try:
            # Though OpenAI deprecated the `max_tokens` parameter,
            # other LLM APIs like DeepSeek still use it.
            # Use max_completion_tokens for newer OpenAI API, fallback to max_tokens for compatibility
            api_params = {
                "model": self.model,
                "messages": messages,
                "temperature": self.temperature,
            }

            if self.max_tokens != -1:
                # Try max_completion_tokens first (newer OpenAI API)
                if "gpt" in self.model or "o1" in self.model:
                    api_params["max_completion_tokens"] = self.max_tokens
                else:
                    # Fallback to max_tokens for other APIs
                    api_params["max_tokens"] = self.max_tokens

            completion = self.client.chat.completions.create(**api_params)
            response = completion.choices[0].message.content

            # parse the reasoning content
            if hasattr(completion.choices[0].message, "reasoning_content"):
                # DeepSeek API uses the reasoning_content field
                reasoning = completion.choices[0].message.reasoning_content
            elif "</think>" in response:
                # Local reasoning model uses <think> </think> tags
                reasoning = response.split("</think>")[0].removeprefix("<think>")
                response = response.split("</think>")[1]
            elif "Reasoned for a couple of seconds" in response:
                # OpenAI API uses the "Reasoning" and "Reasoned for a couple of seconds" tags
                reasoning, response = response.split("Reasoned for a couple of seconds")
            else:
                logger.warning(
                    "No reasoning content found in the reasoning LLM response:\n"
                    + response
                )
                reasoning = ""
        except Exception as e:
            logger.error(f"OpenAI API exception: {e}")
            return None

        if not return_tokens:
            return response, reasoning
        else:
            try:
                reasoning_tokens = (
                    completion.usage.completion_tokens_details.reasoning_tokens
                )
            except:
                reasoning_tokens = 0
            return (
                response,
                reasoning,
                completion.usage.prompt_tokens,
                completion.usage.completion_tokens + reasoning_tokens,
            )


class OllamaReasoningClient(ReasoningLLMClient):
    """
    Ollama compatible reasoning LLM client
    """

    def __init__(
        self,
        host: str,
        port: int,
        model: str,
        max_tokens: int = -1,
        timeout: int = 80,
        retry_times: int = 3,
    ):
        """
        Initialize the Ollama compatible LLM client

        :param host: Host of the Ollama API
        :param port: Port of the Ollama API
        :param model: Model to use
        :param max_tokens: Maximum tokens of the Ollama input
        :param timeout: The timeout seconds for each query
        :param retry_times: Number of times to retry the query
        """
        self.client = Ollama(f"{host}:{port}", timeout=timeout)
        self.model = model
        self.max_tokens = max_tokens
        self.retry_times = retry_times

        super().__init__()

    @LLMClient.with_retry
    @LLMClient.query_logger.with_log
    def query_with_messages(
        self, messages: list[dict[str, str]], return_tokens: bool = False
    ) -> Union[tuple[str, str], tuple[str, str, int, int], None]:
        """
        Query with messages list

        :param messages: Messages
        :param return_tokens: Whether to return the tokens of the query and response
        :return: A tuple of response text and reasoning;
        or a tuple of response text, reasoning, and tokens;
        or None if the query failed
        """
        # query the Ollama API
        try:
            response = self.client.chat(
                model=self.model,
                messages=messages,
                options={"num_ctx": self.max_tokens} if self.max_tokens != -1 else None,
            )
            response: str = response["message"]["content"]
        except Exception as e:
            logger.error("Ollama API exception: " + str(e))
            return None

        # parse the reasoning content inside <think> </think> tags
        reasoning = ""
        if "</think>" in response:
            reasoning = response.split("</think>")[0].removeprefix("<think>")
            response = response.split("</think>")[1]
        else:
            logger.warning(
                "No reasoning content found in the reasoning LLM response:\n" + response
            )

        if not return_tokens:
            return response, reasoning
        else:
            return (
                response,
                reasoning,
                OllamaClient.count_tokens(messages),
                OllamaClient.count_tokens(reasoning + response),
            )


class LLMChat:
    """
    A LLM Chat is a continuous conversation with preserved contexts
    """

    def __init__(
        self,
        client: LLMClient,
        system_prompt: str = "",
    ):
        """
        Initialize a LLM chat

        :param client: The LLM client.
        :param system_prompt: The system prompt of the LLM
        """
        self.client = client
        self._history = (
            [{"role": "system", "content": system_prompt}]
            if system_prompt != ""
            else []
        )

    def query_reasoning(self, prompt: str) -> tuple[str, str]:
        """
        Query the LLM chat with a prompt and get the reasoning

        :param prompt: Prompt to query the LLM chat with
        :return: Response and reasoning from the LLM chat
        """
        # create the messages
        messages = self._history + [{"role": "user", "content": prompt}]
        # query the LLM
        if isinstance(self.client, ReasoningLLMClient):
            response, reasoning = self.client.query_with_messages(messages)
        else:
            response = self.client.query_with_messages(messages)
            reasoning = ""

        # update the history
        if response:
            self._history = messages + [{"role": "assistant", "content": response}]
            return response, reasoning
        else:
            return "", ""

    def query(self, prompt: str) -> str:
        """
        Query the LLM chat with a prompt

        :param prompt: Prompt to query the LLM chat with
        :return: Response from the LLM chat
        """
        return self.query_reasoning(prompt)[0]

    @property
    def history(self) -> list:
        """
        :return: History of the LLM chat
        """
        return self._history

    @property
    def history_str(self) -> str:
        """
        Print the LLM chat history to string
        """
        return self.client._messages_to_str(self._history)

    @history.setter
    def history(self, history: list):
        """
        Update history of the LLM chat

        :param history: New history
        """
        self._history = history

    def remove_last_message(self) -> dict[str, str]:
        """
        Remove the last message from the history

        :return: The last message
        """
        if len(self._history) > 0:
            return self._history.pop()

    def remove_last_query(self) -> tuple[dict[str, str], dict[str, str]]:
        """
        Remove the last query from the history

        :return: The last query and response, or None if the last message is not a query
        """
        if self._history[-1]["role"] == "assistant":
            response = self._history.pop()
            query = self._history.pop()
            return query, response
        else:
            return None, None

    @property
    def system_prompt(self) -> str:
        """
        :return: System prompt of the LLM chat
        """
        if len(self._history) > 0 and self._history[0]["role"] == "system":
            return self._history[0]["content"]
        else:
            return ""

    @system_prompt.setter
    def system_prompt(self, system_prompt: str):
        """
        Update system prompt of the LLM chat

        :param system_prompt: New system prompt
        """
        if len(self._history) > 0 and self._history[0]["role"] == "system":
            self._history[0]["content"] = system_prompt
        else:
            self._history.insert(0, {"role": "system", "content": system_prompt})
