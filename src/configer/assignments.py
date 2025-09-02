"""
Module assignment utilities for configuration management.

This module provides utilities for managing LLM assignments to different
modules and binary path assignments.
"""

import sys
from pathlib import Path
from typing import Dict, Any
from loguru import logger
from .constants import MODULE_MAPPINGS

from .file_io import load_config_file, save_config_file
from .llm_utils import get_llm_instances


def set_module_llm(config_path: Path, module: str, llm_name: str) -> None:
    """Helper function to set LLM for a module."""
    # Check if config file exists
    if not config_path.exists():
        logger.error(f"Configuration file not found: {config_path}")
        logger.info("Run './PromeFuzz.py config init' to create a configuration file")
        sys.exit(1)

    # Load current configuration
    config_data = load_config_file(config_path)
    if not config_data:
        sys.exit(1)

    # Check if the LLM exists
    llm_config = config_data.get("llm", {})
    if (
        llm_name not in llm_config or not isinstance(llm_config[llm_name], dict)
    ) and llm_name != "":
        logger.error(f"LLM '{llm_name}' not found in configuration")
        logger.info("Available LLMs:")
        llm_instances = get_llm_instances(llm_config)
        for key in llm_instances.keys():
            logger.info(f"  - {key}")
        sys.exit(1)

    # Use shared module mappings
    section_name, param_name = MODULE_MAPPINGS[module]

    # Ensure section exists
    if section_name not in config_data:
        config_data[section_name] = {}

    # Get old value and set new value
    old_value = config_data[section_name].get(param_name, "Not set")
    config_data[section_name][param_name] = llm_name

    # Save configuration
    if save_config_file(config_path, config_data):
        logger.success(f"Set {module} LLM to '{llm_name}' (was: {old_value})")
    else:
        sys.exit(1)
