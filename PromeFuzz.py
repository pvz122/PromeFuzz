#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
PromeFuzz CLI
"""

import sys
import tomllib
import click
import importlib
from pathlib import Path
from loguru import logger
import datetime
import tqdm
import sys

from src import vars as global_vars

SUBCOMMANDS = (
    # add commands here.
    "config",
    "preprocess",
    "comprehend",
    "generate",
    "analyze",
    "test",
    "stats",
)


def setup_subcommands():
    """
    Import command-line module and add the right command.
    """
    for cmd in SUBCOMMANDS:
        module = importlib.import_module(f"cli.{cmd}")
        method = getattr(module, cmd)
        butler.add_command(method)


def get_command_from_argv():
    """
    Extract the actual command name from sys.argv, handling Click options properly.
    Returns the command name or None if not found.
    """
    if len(sys.argv) <= 1:
        return None

    # Skip global options and find the actual command
    for arg in sys.argv[1:]:
        if not arg.startswith("-") and arg in SUBCOMMANDS:
            return arg
    return None


def setup_logger(debug: bool):
    """
    Setup logging level.

    :param debug: If True, set the logging level to DEBUG.
    """
    logger.remove()
    level = "DEBUG" if debug else "INFO"
    logger.add(
        sink=tqdm.tqdm.write,
        level=level,
        format="<green>{time:YYYY-MM-DD HH:mm:ss}</green> | <magenta>{thread.name}</magenta> <level>{level}</level> | <cyan>{name}</cyan>:<cyan>{function}</cyan>:<cyan>{line}</cyan> | <level>{message}</level>",
        colorize=True,
    )
    Path("logs").mkdir(exist_ok=True)
    log_filename = f"logs/{datetime.datetime.now().strftime('%Y%m%d%H%M%S')}_{"_".join(sys.argv).replace(' ', '_').replace('/', '_')}.log"
    if len(log_filename) > 255:
        log_filename = log_filename[:200] + ".log"
    logger.add(
        log_filename,
        level=level,
        enqueue=True,
        format="{time} | {thread.name} {level} | {name}:{function}:{line} | {message}",
        colorize=False,
    )
    logger.info(
        f"Logger set up with level {level}, log will be saved to {log_filename}"
    )


def load_config(config_path: Path, library_path: Path):
    """
    Load the config.toml and libraries.toml

    :param config_path: The path to the PromeFuzz config file.
    :param library_path: The path to the library config file.
    """
    try:
        if not config_path.exists():
            command = get_command_from_argv()
            is_config_init_command = (
                command == "config"
                and len(sys.argv) >= 3
                and any(arg in ["init", "setup"] for arg in sys.argv[2:])
            )
            if is_config_init_command:
                global_vars.config = {}
                global_vars.config_template = {}
                global_vars.libraries = {}
                return
            else:
                logger.error(f"Configuration file not found: {config_path}")
                logger.info(
                    "Run './PromeFuzz.py config init/setup' to create a configuration file"
                )
                sys.exit(1)
        if not library_path.exists():
            logger.error(f"Library configuration file not found: {library_path}")
            sys.exit(1)

        global_vars.config = tomllib.loads(config_path.read_text())
        global_vars.config_template = tomllib.loads(
            (Path(__file__).resolve().parent / "config.template.toml").read_text()
        )
        global_vars.libraries = tomllib.loads(library_path.read_text())
        global_vars.libraries_template = tomllib.loads(
            (Path(__file__).resolve().parent / "libraries.template.toml").read_text()
        )
    except Exception as e:
        logger.critical(f"Toml load error when loading config: {e}")
        sys.exit(1)

    global_vars.promefuzz_path = Path(__file__).resolve().parent

    def _set_bin_path(bin_name):
        """
        Because the path of the preprocessor binary may be relative to the PromeFuzz path,
        we need to set the path of the preprocessor binary here.
        """
        bin_path = global_vars.config.get(
            "bin", global_vars.config_template["bin"]
        ).get(bin_name, global_vars.config_template["bin"][bin_name])
        if r"{PROMEFUZZ_PATH}" in bin_path:
            bin_path = bin_path.format(PROMEFUZZ_PATH=global_vars.promefuzz_path)
        global_vars.config.setdefault("bin", dict())[bin_name] = bin_path

    _set_bin_path("preprocessor")
    _set_bin_path("cgprocessor")


@click.group()
@click.option("-D", "is_debug", help="Output debug information.", flag_value=True)
@click.option(
    "--config",
    "config",
    help="Specify the config file.",
    type=click.Path(dir_okay=False, path_type=Path),
    default=str(Path(__file__).resolve().parent / "config.toml"),
    show_default=True,
)
@click.option(
    "-F",
    "--lib-config",
    "lib_config",
    help="Specify the library config file.",
    type=click.Path(dir_okay=False, path_type=Path),
    default=str(Path(__file__).resolve().parent / "libraries.toml"),
    show_default=True,
)
def butler(
    is_debug: bool,
    config: Path,
    lib_config: Path,
):
    """PromeFuzz CLI"""
    setup_logger(is_debug)
    load_config(config, lib_config)


def main():
    setup_subcommands()
    butler()


if __name__ == "__main__":
    main()
