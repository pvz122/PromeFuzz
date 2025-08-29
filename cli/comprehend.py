"""
Comprehender command line interface.
"""

import click
from loguru import logger
from pathlib import Path
from enum import StrEnum, auto
import traceback
import pickle
import sys

from src import vars as global_vars
from src.utils import setup_default_config, setup_llm
from src.preprocessor.information import InfoRepository
from src.preprocessor.api import APICollection
from src.comprehender.knowledge import Knowledge
from src.comprehender.comprehender import (
    GeneralComprehender,
    FuncRelevanceComprehender,
    FuncUsageComprehender,
)


class TaskOptions(StrEnum):
    """
    Enum for the comprehension task
    """

    ALL = auto()
    LIBPURP = auto()
    FUNCPURP = auto()
    FUNCREL = auto()


@click.command(help="Use LLM to comprehend the library.")
@click.option(
    "-L",
    "--library",
    "library_name",
    default=None,
    help="The name of the library to comprehend. You should have it configured in the libraries.toml.",
    show_default=True,
)
@click.option(
    "--task",
    "task",
    type=click.Choice([t for t in TaskOptions]),
    help="The task to perform, either comprehend the library purpose, function purpose and usage, or function relevance.",
    default=TaskOptions.ALL,
    show_default=True,
)
@click.option(
    "--pool-size",
    "pool_size",
    type=int,
    help="The parallel pool size for the comprehension tasks.",
    default=5,
    show_default=True,
)
def comprehend(
    library_name: str,
    task: str,
    pool_size: int,
):
    """
    PromeFuzz Comprehender CLI
    """
    # setup the default configuration
    setup_default_config(library_name)

    # set configs
    comprehender_config = global_vars.config["comprehender"]
    Knowledge.RETRIEVE_TOP_K = comprehender_config["retrieve_top_k"]
    FuncRelevanceComprehender.FUNCTION_BATCH_SIZE = comprehender_config[
        "function_batch_size"
    ]
    FuncUsageComprehender.COMPREHEND_FROM_DOC = global_vars.library_config[
        "document_has_api_usage"
    ]
    DUMP_CSV = global_vars.config["preprocessor"]["dump_relevance_as_csv"]

    # load API functions, info repository
    preprocess_path = Path(global_vars.library_config["output_path"]) / "preprocessor"
    try:
        api_collection = APICollection.load(preprocess_path / "api.pkl")
        info_repo = InfoRepository.load(preprocess_path / "info.pkl")
    except Exception as e:
        logger.critical(
            f"Failed to load libray preprocessing results, please run preprocessor first: {e}"
        )
        traceback.print_exc()
        sys.exit(1)

    # setup the llm
    try:
        llm_client = setup_llm(comprehender_config["comprehension_llm"])
    except Exception as e:
        logger.critical(f"Failed to setup the LLM client: {e}")
        traceback.print_exc()
        sys.exit(1)

    # setup the knowledge retriever
    try:
        knowledge = Knowledge.from_config(
            global_vars.config, global_vars.library_config
        )
    except Exception as e:
        logger.critical(f"Failed to setup the knowledge retriever: {e}")
        traceback.print_exc()
        sys.exit(1)

    # set task flags
    GeneralComprehender.DO_LIBRARY_PURPOSE = (
        task == TaskOptions.LIBPURP or task == TaskOptions.ALL
    )
    GeneralComprehender.DO_FUNC_USAGE = (
        task == TaskOptions.FUNCPURP or task == TaskOptions.ALL
    )
    GeneralComprehender.DO_FUNC_RELEVANCE = (
        task == TaskOptions.FUNCREL or task == TaskOptions.ALL
    )

    # create the output path
    comprehend_path = Path(global_vars.library_config["output_path"]) / "comprehender"
    comprehend_path.mkdir(parents=True, exist_ok=True)

    comprehender = GeneralComprehender(
        llm_client,
        knowledge,
        api_collection,
        info_repo,
        pool_size=pool_size,
    )
    # load last comprehension if exists
    if (comprehend_path / "comp.pkl").exists():
        logger.info("Loading last comprehension.")
        with open(comprehend_path / "comp.pkl", "rb") as f:
            comp = pickle.load(f)
        comprehender.lib_comprehension = comp

    # do comprehension
    comprehender.comprehend()

    # dump the results
    comprehender.dump(
        (
            (comprehend_path / "comp.pkl")
            if GeneralComprehender.DO_LIBRARY_PURPOSE
            or GeneralComprehender.DO_FUNC_USAGE
            else None
        ),
        (
            comprehend_path / "semantic_relev.pkl"
            if GeneralComprehender.DO_FUNC_RELEVANCE
            else None
        ),
    )
    comprehender.dump_to_json_csv(
        (
            comprehend_path / "comp.json"
            if GeneralComprehender.DO_LIBRARY_PURPOSE
            or GeneralComprehender.DO_FUNC_USAGE
            else None
        ),
        (
            comprehend_path / "semantic_relev.csv"
            if GeneralComprehender.DO_FUNC_RELEVANCE and DUMP_CSV
            else None
        ),
    )
