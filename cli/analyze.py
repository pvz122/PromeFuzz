"""
Crash analyzer command line interface.
"""

import re
import click
from loguru import logger
from pathlib import Path
from enum import StrEnum, auto
from tqdm import tqdm
from concurrent.futures import ThreadPoolExecutor

from src.utils import setup_default_config, setup_llm
from src import vars as global_vars
from src.analyzer.asan import AsanError
from src.analyzer.report import CrashReportComposer
from src.preprocessor.information import InfoRepository
from src.preprocessor.api import APICollection
from src.comprehender.comprehender import LibraryComprehension
from src.llm.prompter import CrashAnalysisPrompter
from src.llm.llm import LLMChat


class TaskOption(StrEnum):
    """
    Task options for the analysis.
    """

    GLANCE = auto()
    ANALYZE = auto()
    ALL = auto()


@click.command(help="Analyzes the crash and generates a report.")
@click.option(
    "-L",
    "--library",
    "library_name",
    default=None,
    help="The name of the library where the crash happened. You should have it configured in the libraries.toml.",
    show_default=True,
)
@click.option(
    "-O",
    "--output",
    "output_path",
    default=Path("."),
    type=click.Path(path_type=Path, resolve_path=True),
    help="The directory to save the analysis report.",
    show_default=True,
)
@click.option(
    "-T",
    "--task",
    "task_option",
    type=click.Choice([t for t in TaskOption]),
    default=TaskOption.ALL.value,
    help='The task to perform, default is all. "glance" for a quick glance of the crashes,'
    ' "analyze" for a full analysis using LLM, "all" for both.',
    show_default=True,
)
@click.option(
    "--pool-size",
    "pool_size",
    type=int,
    default=5,
    help="The pool size to query the LLM.",
    show_default=True,
)
@click.argument(
    "crash_files",
    type=click.Path(path_type=Path, exists=True, dir_okay=False),
    nargs=-1,
    required=True,
)
def analyze(
    library_name: str,
    output_path: Path,
    task_option: str,
    pool_size: int,
    crash_files: tuple[Path],
):
    """
    PromeFuzz Analyzer CLI
    """
    # setup the default configuration
    setup_default_config(library_name)

    # load the crash messages
    logger.info(f"Found {len(crash_files)} crash files, parsing them...")
    valid_filenames: list[str] = []
    err_signatures: list[str] = []
    asan_errors: list[AsanError] = []
    TP_crash_signatures: list[str] = []
    for crash_file in tqdm(
        crash_files, desc="Parsing crashes", unit="crash", leave=False, colour="yellow"
    ):
        try:
            asan_error = AsanError(crash_file.read_text())
        except Exception as e:
            logger.debug(f"No crash found for {crash_file}, skipping: {e}")
            continue
        if asan_error.signature in err_signatures and not (
            asan_error.signature.endswith("unknown")
            or asan_error.signature.endswith("driver")
        ):
            logger.debug(
                f"Crash {asan_error.signature} for {crash_file} is duplicated, skipping."
            )
            continue
        valid_filenames.append(crash_file.name)
        err_signatures.append(asan_error.signature)
        asan_errors.append(asan_error)

    # perform the task
    if task_option == TaskOption.ANALYZE.value or task_option == TaskOption.ALL.value:
        output_path.mkdir(parents=True, exist_ok=True)
        analysis_reports = task_analyze(asan_errors, pool_size)
        for filename, err_sig, analysis_report in zip(
            valid_filenames, err_signatures, analysis_reports
        ):
            # LLM output example:
            # The crash is a Misuse in fuzz driver / Bug in library, below is the explanation.
            pattern = r"The crash is a .*(Misuse in fuzz driver|Bug in library).* below is the explanation"
            if re.search(pattern, analysis_report):
                crash_type = re.search(pattern, analysis_report).group(1)
                if crash_type == "Bug in library":
                    crash_type = "TP"
                    TP_crash_signatures.append(err_sig)
                elif crash_type == "Misuse in fuzz driver":
                    crash_type = "FP"
                    logger.debug(f"Detected crash type: {crash_type}")
            else:
                crash_type = "UN"
            logger.debug(f"Detected crash type: {crash_type}")
            output_file = (
                output_path / f"{crash_type}-{err_sig.replace('/', '_')}-{filename}.md"
            )
            output_file.write_text(analysis_report)
        logger.success(f"Analysis reports are saved to {output_path}.")

    if task_option == TaskOption.GLANCE.value or task_option == TaskOption.ALL.value:
        driver_crashes, unknown_crashes, library_crashes, TP_crashes = task_glance(
            asan_errors, crash_files, TP_crash_signatures
        )
        if driver_crashes:
            logger.warning(
                f"{len(driver_crashes)} driver crashes found:\n"
                + "\n\n".join(driver_crashes)
            )
        if unknown_crashes:
            logger.warning(
                f"{len(unknown_crashes)} unknown crashes found:\n"
                + "\n\n".join(unknown_crashes)
            )
        logger.info(
            f"{len(library_crashes)} library crashes found:\n"
            + "\n\n".join(library_crashes)
        )
        if TP_crashes:
            logger.success(
                f"{len(TP_crashes)} true positive crashes found:\n"
                + "\n\n".join(TP_crashes)
            )


def task_glance(
    asan_errors: list[AsanError],
    valid_filenames: list[str],
    TP_crash_signatures: list[str] = [],
) -> tuple[list[str], list[str], list[str], list[str]]:
    """
    Glances at the crashes.

    :param asan_errors: The list of ASan errors.
    :param valid_filenames: The list of valid filenames.
    :param TP_crash_signatures: The list of true positive crash signatures.
    :return: The list of glancing for driver crashes, unknown crashes, library crashes and true positive crashes.
    """
    # filter the crashes
    driver_crashes = []
    unknown_crashes = []
    library_crashes = []
    TP_crashes = []
    trivial_crash_sigs = set()
    for asan_error, filename in zip(asan_errors, valid_filenames):
        glance = f"========== {filename}({asan_error.signature}) ==========\n{asan_error.readable}"
        if asan_error.signature.endswith("driver"):
            if asan_error.signature not in trivial_crash_sigs:
                trivial_crash_sigs.add(asan_error.signature)
                driver_crashes.append(glance)
        elif asan_error.signature.endswith("unknown"):
            if asan_error.signature not in trivial_crash_sigs:
                trivial_crash_sigs.add(asan_error.signature)
                unknown_crashes.append(glance)
        else:
            library_crashes.append(glance)
            if asan_error.signature in TP_crash_signatures:
                TP_crashes.append(glance)

    return driver_crashes, unknown_crashes, library_crashes, TP_crashes


def task_analyze(asan_errors: list[AsanError], pool_size: int = 5) -> list[str]:
    """
    Analyzes the crashes and generates analysis reports.

    :param asan_errors: The list of ASan errors.
    :param pool_size: The pool size for the thread pool.
    :return: The list of analysis reports.
    """
    # setup llm client
    llm_client = setup_llm(global_vars.config["analyzer"]["analysis_llm"])

    # load information
    preprocessor_out_path = (
        Path(global_vars.library_config["output_path"]) / "preprocessor"
    )
    comprehender_out_path = (
        Path(global_vars.library_config["output_path"]) / "comprehender"
    )
    info_repo = InfoRepository.load(preprocessor_out_path / "info.pkl")
    api_collection = APICollection.load(preprocessor_out_path / "api.pkl")
    try:
        comprehension = LibraryComprehension.load(comprehender_out_path / "comp.pkl")
    except:
        # it is optional
        comprehension = LibraryComprehension("", {})

    # create progress bar
    progress_bar = tqdm(
        total=len(asan_errors),
        desc="Analyzing crashes",
        unit="crash",
        leave=False,
        colour="blue",
    )

    def _single_task_analyze(asan_error: AsanError) -> str:
        # compose the crash report
        composer = CrashReportComposer(info_repo, api_collection)
        crash_report = composer.compose_with_inferred_fuzz_driver_code(asan_error)
        logger.debug(f"Crash report for {asan_error.signature}:\n{crash_report}")

        if asan_error.signature.endswith("unknown") or asan_error.signature.endswith(
            "driver"
        ):
            progress_bar.update(1)
            return crash_report + "\n\n# No analysis for unknown or driver crashes."

        # prompt the LLM for analysis
        logger.info(f"Prompting the LLM for analyzing {asan_error.signature}...")
        prompter = CrashAnalysisPrompter(LLMChat(llm_client))
        analysis, reasoning = prompter.prompt(
            crash_report, comprehension.purpose, global_vars.library_name
        )
        if not analysis:
            logger.error(f"No analysis from LLM for {asan_error.signature}.")
            progress_bar.update(1)
            return crash_report + "\n\n# No analysis from LLM."

        # print the analysis and add to the list
        if reasoning:
            logger.info(f"Reasoning Process for {asan_error.signature}:\n\n{reasoning}")
        logger.info(f"Analysis from LLM for {asan_error.signature}:\n\n{analysis}")
        analysis_report = crash_report + "\n\n# Analysis from LLM\n\n" + analysis
        if reasoning:
            analysis_report += "\n\n# Reasoning Process\n\n" + reasoning
        progress_bar.update(1)
        return analysis_report

    # analyze each crash
    if pool_size == 1:
        # for debugging
        analysis_reports = [
            _single_task_analyze(asan_error) for asan_error in asan_errors
        ]
    else:
        with ThreadPoolExecutor(max_workers=pool_size) as executor:
            analysis_reports = list(executor.map(_single_task_analyze, asan_errors))

    return analysis_reports
