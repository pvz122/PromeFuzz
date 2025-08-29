"""
Test command.
"""

import click
from loguru import logger
from pathlib import Path

from src import vars as global_vars
from src.utils import setup_default_config
from PromeFuzz import setup_logger


@click.command(help="Run tests.")
@click.option(
    "-T",
    "--task",
    "task",
    help="The task to run. 'all' for all tasks.",
)
@click.option(
    "--list",
    "do_list",
    is_flag=True,
    help="List all tests.",
)
@click.argument(
    "args",
    nargs=-1,
    type=click.UNPROCESSED,
)
def test(task: str, do_list: bool, args: list):
    """
    Run tests.
    """
    # setup logger to debug
    setup_logger(debug=True)

    # load dummy configs
    global_vars.libraries = global_vars.libraries_template
    setup_default_config("a_c_library")

    # get tests
    test_dir = Path("src/tests").resolve()
    test_files = list(test_dir.glob("test_*.py"))
    test_files = [str(f.name).split("test_")[-1][:-3] for f in test_files]

    if do_list:
        tests = "Tests:\n"
        for test_name in test_files:
            tests += f"  {test_name}\n"
        logger.info(tests)
        return
    else:
        if not task:
            logger.critical("Please specify a task using -T/--task.")
            return

    # run tests
    def run_test(test_name: str):
        logger.info(f"Running test {test_name}...")
        # import test module
        test_module =  __import__(f"src.tests.test_{test_name}", fromlist=["run"])
        # run test
        test_module.run(*args)
        logger.info(f"Test {test_name} done.")

    if task == "all":
        for test_name in test_files:
            run_test(test_name)
    else:
        if task not in test_files:
            logger.error(f"Test {task} not found.")
            return
        run_test(task)
