"""
File I/O operations for TOML configuration files.

This module provides functions for loading and saving TOML configuration files
without comment preservation for cleaner, simpler configuration management.
"""

import sys
import tomllib
import tomlkit
from pathlib import Path
from typing import Dict, Any
from loguru import logger


def load_config_file(config_path: Path) -> Dict[str, Any]:
    """Load and parse a TOML configuration file.

    :param config_path: Path to the configuration file
    :return: Dict[str, Any]: Configuration data
    :raises SystemExit: If configuration file cannot be loaded
    """
    try:
        with open(config_path, "rb") as f:
            return tomllib.load(f)
    except FileNotFoundError:
        logger.error(f"Configuration file not found: {config_path}")
        logger.info("Run './PromeFuzz.py configure init' to create a configuration file")
        sys.exit(1)
    except tomllib.TOMLDecodeError as e:
        logger.error(f"Invalid TOML syntax in {config_path}: {e}")
        sys.exit(1)


def save_config_file(config_path: Path, config_data: Dict[str, Any]) -> bool:
    """Save configuration data to a TOML file without comments."""
    try:
        # Create clean TOML document
        doc = tomlkit.document()

        # Convert dict to tomlkit document
        def dict_to_tomlkit(data, doc_section=None):
            if doc_section is None:
                doc_section = doc

            for key, value in data.items():
                if isinstance(value, dict):
                    table = tomlkit.table()
                    dict_to_tomlkit(value, table)
                    doc_section[key] = table
                else:
                    doc_section[key] = value

        dict_to_tomlkit(config_data)

        with open(config_path, "w", encoding="utf-8") as f:
            tomlkit.dump(doc, f)
        return True

    except Exception as e:
        logger.error(f"Failed to save configuration file {config_path}: {e}")
        return False
