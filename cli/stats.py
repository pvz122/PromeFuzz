"""
Show statistics of a generation.
"""

import click
from pathlib import Path
from loguru import logger
import sys

from src.stats.statistics import StatsReport
from src.preprocessor.api import APICollection
from src.generator.worker import GenerationState
from src.utils import setup_default_config
from src import vars as global_vars


@click.command(help="Show statistics of a generation.")
@click.option(
    "-L",
    "--library",
    "library_name",
    default=None,
    help="The name of the library for statistics. You should have it configured in the libraries.toml. \
If the libraries.toml contains only one library, you can omit this option.",
    show_default=True,
)
@click.option(
    "-O",
    "--output",
    "output_path",
    default=None,
    help="The path to save the statistics report. If not specified, \
the statistics will be saved to the configured output path of the library.",
    type=click.Path(exists=False, dir_okay=True, path_type=Path),
)
def stats(
    library_name: str | None,
    output_path: Path | None,
):
    """
    PromeFuzz Stats CLI
    """
    # setup the default configuration
    setup_default_config(library_name)

    # set save file
    lib_output_path = Path(global_vars.library_config["output_path"])
    if output_path is None:
        save_file = lib_output_path / f"statistics_for_{global_vars.library_name}.xlsx"
    else:
        save_file = output_path / f"statistics_for_{global_vars.library_name}.xlsx"
    save_file.parent.mkdir(parents=True, exist_ok=True)

    # load api collection
    try:
        api_collection = APICollection.load(
            lib_output_path / "preprocessor" / "api.pkl"
        )
    except Exception as e:
        logger.critical(f"Failed to load the API collection: {e}")
        sys.exit(1)

    # load the generation state
    if not (state_path := lib_output_path / "generator" / "state.pkl").is_file():
        logger.critical(
            f"The generation state file is not found in {state_path}, please run the generator first."
        )
        sys.exit(1)
    state = GenerationState.load(state_path)

    # synthesize the report
    report = StatsReport(state, api_collection, lib_output_path / "fuzz_driver")

    # save the report
    report.save_report(save_file)
    logger.success(f"Statistics report saved to {save_file}")
