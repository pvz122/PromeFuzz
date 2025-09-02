"""
LLM configuration utilities.

This module provides utilities for working with LLM configurations,
including displaying information, masking API keys, and finding usage patterns.
"""

from typing import Dict, Any
import sys
import click
from loguru import logger


def get_llm_instances(llm_config: Dict[str, Any]) -> Dict[str, Dict[str, Any]]:
    """Extract LLM instances from LLM configuration."""
    llm_instances = {}
    for key, value in llm_config.items():
        if isinstance(value, dict) and "llm_type" in value:
            llm_instances[key] = value
    return llm_instances


def validate_llm_exists(llm_config: Dict[str, Any], llm_name: str) -> None:
    """Validate that an LLM configuration exists and is valid.

    Args:
        llm_config: The LLM configuration dictionary
        llm_name: Name of the LLM to validate

    Raises:
        SystemExit: If LLM doesn't exist or is invalid
    """
    if llm_name not in llm_config or not isinstance(llm_config[llm_name], dict):
        llm_instances = get_llm_instances(llm_config)
        available_llms = ", ".join(llm_instances.keys()) if llm_instances else "None"
        logger.critical(
            f"LLM '{llm_name}' not found in configuration. Available LLMs: {available_llms}"
        )
        sys.exit(1)

    if llm_name in llm_config and "llm_type" not in llm_config[llm_name]:
        logger.critical(
            f"'{llm_name}' is not a valid LLM configuration - missing llm_type"
        )
        sys.exit(1)


def mask_api_key(api_key: str) -> str:
    """Mask API key for security display."""
    if not api_key:
        return "Not set"
    if len(api_key) > 12:
        return api_key[:8] + "..." + api_key[-4:]
    else:
        return "***"


def get_modules_using_llm(
    config_data: Dict[str, Any], llm_name: str, is_default: bool
) -> list[str]:
    """Get list of modules that use a specific LLM."""
    modules_using_this_llm = []

    # Check each module configuration
    for section in ["comprehender", "generator", "analyzer"]:
        if section in config_data:
            section_config = config_data[section]
            for key, value in section_config.items():
                if key.endswith("_llm") and value == llm_name:
                    modules_using_this_llm.append(f"{section}.{key}")

    # Check if it's the default LLM
    if is_default:
        modules_using_this_llm.append("default_llm (fallback for unspecified modules)")

    return modules_using_this_llm


def display_llm_details(
    llm_name: str,
    llm_config: Dict[str, Any],
    config_data: Dict[str, Any] = None,
    is_default: bool = False,
    indent: str = "",
) -> None:
    """Display detailed information for a single LLM configuration."""
    llm_type = llm_config.get("llm_type", "unknown")
    model = llm_config.get("model", "unknown")

    click.echo(f"{indent}Type: {llm_type}")
    click.echo(f"{indent}Model: {model}")

    # Type-specific configuration
    if llm_type in ["openai", "openai-reasoning"]:
        click.echo(f"{indent}")
        click.echo(f"{indent}OpenAI Configuration:")
        base_url = llm_config.get("base_url", "https://api.openai.com/v1/")
        click.echo(f"{indent}  Base URL: {base_url}")

        api_key = llm_config.get("api_key", "")
        masked_key = mask_api_key(api_key)
        if api_key:
            click.echo(f"{indent}  API Key: {masked_key}")
        else:
            click.echo(f"{indent}  API Key: {click.style('Not set', fg='red')}")

        temperature = llm_config.get("temperature", "Not set")
        click.echo(f"{indent}  Temperature: {temperature}")

    elif llm_type in ["ollama", "ollama-reasoning"]:
        click.echo(f"{indent}")
        click.echo(f"{indent}Ollama Configuration:")
        host = llm_config.get("host", "localhost")
        port = llm_config.get("port", 11434)
        click.echo(f"{indent}  Host: {host}")
        click.echo(f"{indent}  Port: {port}")
        click.echo(f"{indent}  Full URL: http://{host}:{port}")

    # Common configuration
    click.echo(f"{indent}")
    click.echo(f"{indent}Common Settings:")
    max_tokens = llm_config.get("max_tokens", "Not set")
    if max_tokens == -1:
        max_tokens = "Auto (provider default)"
    click.echo(f"{indent}  Max Tokens: {max_tokens}")

    timeout = llm_config.get("timeout", "Not set")
    click.echo(f"{indent}  Timeout: {timeout}s")

    retry_times = llm_config.get("retry_times", "Not set")
    click.echo(f"{indent}  Retry Times: {retry_times}")

    # Show which modules use this LLM if config_data is provided
    if config_data:
        click.echo(f"{indent}")
        click.echo(f"{indent}Used by modules:")
        modules_using_this_llm = get_modules_using_llm(
            config_data, llm_name, is_default
        )

        if modules_using_this_llm:
            for module in modules_using_this_llm:
                click.echo(f"{indent}  - {module}")
        else:
            click.echo(
                f"{indent}  {click.style('Not used by any module', fg='yellow')}"
            )
