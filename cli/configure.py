"""
Configuration management command line interface.
"""

import shutil
import sys
from pathlib import Path
import click
from loguru import logger
from src.configurer import (
    load_config_file,
    save_config_file,
    get_llm_instances,
    get_modules_using_llm,
    display_llm_details,
    create_minimal_config,
    set_module_llm,
    validate_llm_exists,
)
from src.configurer.constants import (
    get_display_mapping,
    VALIDATION_MODULES,
    MODULE_DESCRIPTIONS,
    get_assignment_options,
)


def config_path_option(exists=False):
    if exists:
        return click.option(
            "--config-path",
            type=click.Path(exists=True, path_type=Path),
            default=Path("config.toml"),
            help="Path to the configuration file (default: config.toml)",
        )
    else:
        return click.option(
            "--config-path",
            type=click.Path(path_type=Path),
            default=Path("config.toml"),
            help="Path to the main configuration file (default: config.toml)",
        )


@click.group(help="Manage PromeFuzz configuration files.")
def config():
    """Configuration management commands."""
    pass


@config.command(help="Initialize empty configuration file with basic structure.")
@config_path_option()
@click.option("--force", is_flag=True, help="Overwrite existing configuration file")
@click.option("--quiet", is_flag=True, help="Skip next steps suggestions")
def init(config_path: Path, force: bool, quiet: bool):
    """Initialize empty configuration file with basic structure."""
    # Copy the libraries.template.toml to libraries.toml
    path_lib_config = Path("libraries.toml")
    path_lib_template = Path("libraries.template.toml")
    if not path_lib_config.exists():
        shutil.copy(path_lib_template, path_lib_config)
    # Initialize config.toml
    if config_path.exists() and not force:
        logger.warning(
            f"Configuration file {config_path} already exists. Use --force to overwrite."
        )
    else:
        try:
            empty_config = create_minimal_config()
            with open(config_path, "w", encoding="utf-8") as f:
                f.write(empty_config)

            logger.success(
                f"Initialized {config_path} with empty configuration structure"
            )
            if not quiet:
                click.echo("Next steps:")
                click.echo(
                    f"  1. Add LLM configurations: ./PromeFuzz.py configure llm add <name>"
                )
                click.echo(f"  2. View current config: ./PromeFuzz.py configure llm list")
        except Exception as e:
            logger.error(f"Failed to initialize {config_path}: {e}")
            sys.exit(1)


@config.group(help="Manage LLM configurations.")
def llm():
    """LLM configuration management commands."""
    pass


@llm.command(help="List all configured LLMs.")
@config_path_option(exists=True)
@click.option("--verbose", "-v", is_flag=True, help="Show detailed LLM configurations")
def list(config_path: Path, verbose: bool):
    """List all configured LLMs with their basic information."""
    config_data = load_config_file(config_path)

    llm_config = config_data.get("llm", {})

    if not llm_config:
        logger.warning("No LLM configuration found in the config file")
        return

    # Get default LLM and LLM instances
    default_llm = llm_config.get("default_llm", "Not set")
    llm_instances = get_llm_instances(llm_config)

    # Display header
    click.echo(f"Default LLM: {click.style(default_llm, fg='green', bold=True)}")
    click.echo()
    click.echo("Configured LLMs:")

    if not llm_instances:
        logger.warning("No LLM instances found in the configuration")
        return

    # Display LLM list
    for name, config in llm_instances.items():
        llm_type = config.get("llm_type", "unknown")
        model = config.get("model", "unknown")

        # Mark default LLM
        is_default = name == default_llm
        name_style = (
            click.style(name, fg="green", bold=True)
            if is_default
            else click.style(name, fg="cyan")
        )
        default_mark = " (default)" if is_default else ""

        if verbose:
            # Verbose mode - show more details
            click.echo(f"  {name_style}{default_mark}:")
            display_llm_details(name, config, config_data, is_default, indent="    ")
            click.echo()
        else:
            # Simple mode - one line per LLM
            click.echo(f"  {name_style}: {llm_type} ({model}){default_mark}")


@llm.command(help="Show detailed configuration for a specific LLM.")
@config_path_option(exists=True)
@click.argument("name")
def show(config_path: Path, name: str):
    """Show detailed configuration for a specific LLM."""
    config_data = load_config_file(config_path)

    llm_config = config_data.get("llm", {})

    if not llm_config:
        logger.critical("No LLM configuration found in the config file")
        sys.exit(1)

    # Validate LLM exists and is valid
    validate_llm_exists(llm_config, name)
    llm_instance = llm_config[name]

    # Get default LLM for marking
    default_llm = llm_config.get("default_llm", "")
    is_default = name == default_llm

    # Display header
    name_style = (
        click.style(name, fg="green", bold=True)
        if is_default
        else click.style(name, fg="cyan", bold=True)
    )
    default_mark = " (default)" if is_default else ""
    click.echo(f"LLM Configuration: {name_style}{default_mark}")
    click.echo("=" * (len(name) + 18 + len(default_mark)))

    display_llm_details(name, llm_instance, config_data, is_default)


@llm.command(help="Set LLM configuration parameters.")
@config_path_option()
@click.option("--model", "-m", help="Set the model name")
@click.option("--temperature", "-t", type=float, help="Set the temperature (0.0-2.0)")
@click.option("--max-tokens", type=int, help="Set max tokens (-1 for auto)")
@click.option("--timeout", type=int, help="Set timeout in seconds")
@click.option("--retry-times", type=int, help="Set maximum retry times")
@click.option("--api-key", help="Set API key (for OpenAI-type LLMs)")
@click.option("--base-url", help="Set base URL (for OpenAI-type LLMs)")
@click.option("--host", help="Set host (for Ollama-type LLMs)")
@click.option("--port", type=int, help="Set port (for Ollama-type LLMs)")
@click.argument("name", required=True)
def set(config_path: Path, name: str, **kwargs):
    """Set LLM configuration parameters.

    Examples:
        ./PromeFuzz.py configure llm set mycloud --model gpt-4o --temperature 0.3
    """
    config_data = load_config_file(config_path)

    # Ensure llm section exists
    if "llm" not in config_data:
        config_data["llm"] = {}

    llm_config = config_data["llm"]

    # Validate LLM exists and is valid
    validate_llm_exists(llm_config, name)
    llm_instance = llm_config[name]
    llm_type = llm_instance.get("llm_type", "")
    changes_made = []

    # Update parameters based on options
    for param, value in kwargs.items():
        if value is None:
            continue

        param_key = param.replace("_", "_")

        # Validate parameter based on LLM type
        if param in ["api_key", "base_url"] and not llm_type.startswith("openai"):
            logger.warning(
                f"Parameter '{param}' is only applicable to OpenAI-type LLMs, but '{name}' is type '{llm_type}'"
            )
            continue

        if param in ["host", "port"] and not llm_type.startswith("ollama"):
            logger.warning(
                f"Parameter '{param}' is only applicable to Ollama-type LLMs, but '{name}' is type '{llm_type}'"
            )
            continue

        # Validate temperature range
        if param == "temperature" and not (0.0 <= value <= 2.0):
            logger.critical(
                f"Invalid temperature value {value}. Temperature must be between 0.0 and 2.0"
            )
            sys.exit(1)

        config_key = param.replace("-", "_")

        # Update the configuration
        old_value = llm_instance.get(config_key, "Not set")
        llm_instance[config_key] = value
        changes_made.append(f"{config_key}: {old_value} -> {value}")

    if changes_made:
        logger.info(f"Updating LLM '{name}':")
        for change in changes_made:
            logger.info(f"  {change}")

        if save_config_file(config_path, config_data):
            logger.success(f"Successfully updated LLM '{name}'")
        else:
            sys.exit(1)
    else:
        logger.info("No parameters provided to update")


@llm.command(help="Add a new LLM configuration interactively.")
@config_path_option()
@click.option("--quiet", is_flag=True, help="Skip next steps suggestions")
@click.argument("name")
def add(config_path: Path, name: str, quiet: bool):
    """Add a new LLM configuration interactively.

    Examples:
        ./PromeFuzz.py configure llm add myopenai
    """
    # Load and validate configuration
    config_data = load_config_file(config_path)

    # Ensure llm section exists
    if "llm" not in config_data:
        config_data["llm"] = {}

    llm_config = config_data["llm"]

    # Check if LLM already exists
    if name in llm_config and isinstance(llm_config[name], dict):
        if not click.confirm(f"LLM '{name}' already exists. Overwrite?"):
            logger.info("Operation cancelled")
            return

    click.echo(
        f"\n{click.style('Adding new LLM configuration:', fg='green', bold=True)} {click.style(name, fg='cyan', bold=True)}"
    )
    click.echo("=" * (len(name) + 30))

    # Choose LLM type
    click.echo("\n1. Select LLM Type:")
    llm_types = [
        ("openai", "OpenAI API (GPT-4, GPT-5-nano, etc.)"),
        ("openai-reasoning", "OpenAI Reasoning API (o1 models)"),
        ("ollama", "Local Ollama server"),
        ("ollama-reasoning", "Local Ollama server with reasoning support"),
    ]

    for i, (type_key, description) in enumerate(llm_types, 1):
        click.echo(f"  {i}. {click.style(type_key, fg='cyan')}: {description}")

    while True:
        try:
            choice = click.prompt("\nSelect type", type=int)
            if 1 <= choice <= len(llm_types):
                llm_type = llm_types[choice - 1][0]
                break
            else:
                click.echo(f"Please enter a number between 1 and {len(llm_types)}")
        except (ValueError, click.Abort):
            click.echo("Please enter a valid number")

    click.echo(f"Selected: {click.style(llm_type, fg='green')}")

    llm_instance = {"llm_type": llm_type}

    # Configure model
    click.echo("\n2. Model Configuration:")
    if llm_type.startswith("openai"):
        default_models = {
            "openai": [
                "gpt-4o",
                "gpt-5-mini",
                "gpt-5-nano",
                "text-embedding-3-small",
            ],
            "openai-reasoning": ["o1", "o1-mini", "o1-preview"],
        }
        models = default_models.get(llm_type, default_models["openai"])

        click.echo("Common models:")
        for model in models:
            click.echo(f"  - {model}")

        model = click.prompt(
            "Enter model name (press Enter for default)", default=models[0]
        )
    else:  # ollama
        click.echo("Common Ollama models:")
        common_ollama_models = [
            "deepseek-r1:70b",
            "llama3.2:latest",
            "qwen2.5:latest",
            "codellama:latest",
        ]
        for model in common_ollama_models:
            click.echo(f"  - {model}")

        model = click.prompt(
            "Enter model name (press Enter for default)", default="deepseek-r1:70b"
        )

    llm_instance["model"] = model

    # Type-specific configuration
    if llm_type.startswith("openai"):
        click.echo(f"\n3. {click.style('OpenAI Configuration:', fg='yellow')}")

        # Base URL
        base_url = click.prompt(
            "Base URL (press Enter for default)", default="https://api.openai.com/v1/"
        )
        llm_instance["base_url"] = base_url

        # API Key
        api_key = click.prompt(
            "API Key (press Enter to use OPENAI_API_KEY environment variable)",
            default="",
            show_default=False,
        )
        if api_key:
            llm_instance["api_key"] = api_key
        else:
            llm_instance["api_key"] = ""
            click.echo("Will use OPENAI_API_KEY environment variable")

        # Temperature (for non-reasoning models)
        if not llm_type.endswith("-reasoning"):
            temperature = click.prompt(
                "Temperature (0.0-2.0, press Enter for default)",
                default=0.5,
                type=float,
            )
            if 0.0 <= temperature <= 2.0:
                llm_instance["temperature"] = temperature
            else:
                click.echo("Temperature out of range, using default 0.5")
                llm_instance["temperature"] = 0.5

    else:  # ollama
        click.echo(f"\n3. {click.style('Ollama Configuration:', fg='yellow')}")

        # Host
        host = click.prompt(
            "Ollama host (press Enter for default)", default="localhost"
        )
        llm_instance["host"] = host

        # Port
        port = click.prompt(
            "Ollama port (press Enter for default)", default=11434, type=int
        )
        llm_instance["port"] = port

        click.echo(f"Will connect to: http://{host}:{port}")

    click.echo(f"\n4. {click.style('Common Settings:', fg='yellow')}")

    # Max tokens with type-specific defaults and guidance
    if llm_type.startswith("ollama"):
        if llm_type == "ollama-reasoning":
            default_max_tokens = 6144
            click.echo(
                "For Ollama reasoning models, be careful about GPU memory usage."
            )
            click.echo("Recommended values: 6144 (70B models), 8192 (smaller models)")
        else:
            default_max_tokens = -1
            click.echo("For regular Ollama models, -1 uses the model's preset limit.")

        max_tokens = click.prompt(
            f"Max tokens (press Enter for default)",
            default=default_max_tokens,
            type=int,
        )
    else:  # OpenAI
        default_max_tokens = -1
        click.echo("For OpenAI models, -1 uses the provider's default limit.")
        max_tokens = click.prompt(
            f"Max tokens (press Enter for default)",
            default=default_max_tokens,
            type=int,
        )

    llm_instance["max_tokens"] = max_tokens

    # Timeout with type-specific defaults
    if llm_type.startswith("ollama"):
        if llm_type == "ollama-reasoning":
            default_timeout = 600
            click.echo("Reasoning models may take longer to respond.")
        else:
            default_timeout = 30
    else:  # OpenAI
        default_timeout = 80

    timeout = click.prompt(
        f"Timeout seconds (press Enter for default)", default=default_timeout, type=int
    )
    llm_instance["timeout"] = timeout

    retry_times = click.prompt(
        "Retry times (press Enter for default)", default=3, type=int
    )
    llm_instance["retry_times"] = retry_times

    click.echo(f"\n{click.style('Preview:', fg='yellow', bold=True)}")
    click.echo("=" * 8)
    display_llm_details(name, llm_instance, indent="")

    if click.confirm(f"\nAdd this LLM configuration?", default=True):
        llm_config[name] = llm_instance
        if save_config_file(config_path, config_data):
            logger.success(f"Successfully added LLM '{name}'")

            if not quiet:
                click.echo("Next steps:")
                click.echo(f"  - View: ./PromeFuzz.py configure llm show {name}")
                click.echo(f"  - Test: ./PromeFuzz.py test -T LittleChat {name}")
                click.echo(f"  - List all: ./PromeFuzz.py configure llm list")
        else:
            sys.exit(1)
    else:
        logger.info("Operation cancelled")


@llm.command(help="Remove an LLM configuration.")
@config_path_option(exists=True)
@click.option("--force", "-f", is_flag=True, help="Force removal without confirmation")
@click.argument("name")
def remove(config_path: Path, name: str, force: bool):
    """Remove an LLM configuration.

    Examples:
        ./PromeFuzz.py configure llm remove old-llm
        ./PromeFuzz.py configure llm remove test-llm --force
    """
    # Load current configuration
    config_data = load_config_file(config_path)

    llm_config = config_data.get("llm", {})

    if not llm_config:
        logger.critical("No LLM configuration found in the config file")
        sys.exit(1)

    # Validate LLM exists and is valid
    validate_llm_exists(llm_config, name)

    # Check if it's the default LLM
    default_llm = llm_config.get("default_llm", "")
    is_default = name == default_llm

    # Check which modules are using this LLM
    modules_using_llm = get_modules_using_llm(config_data, name, is_default)

    # Display LLM information
    click.echo(f"Removing LLM configuration: {click.style(name, fg='red', bold=True)}")
    if is_default:
        click.echo(
            f"{click.style('[WARN] This is the default LLM', fg='yellow', bold=True)}"
        )

    # Show what uses this LLM
    if modules_using_llm:
        click.echo(
            f"\n{click.style('[WARN] This LLM is currently being used by:', fg='yellow', bold=True)}"
        )
        for module in modules_using_llm:
            click.echo(f"   - {click.style(module, fg='yellow')}")
        click.echo()
        click.echo("Removing this LLM will cause these modules to fail unless you:")
        click.echo("  1. Set a different LLM for these modules")
        click.echo("  2. Set a new default LLM")
        click.echo("  3. Add a replacement LLM with the same name")
    else:
        click.echo(
            f"[OK] This LLM is {click.style('not used by any modules', fg='green')}"
        )

    if not force:
        if modules_using_llm:
            click.echo()
            warning_msg = f"Are you sure you want to remove '{name}' despite it being used by {len(modules_using_llm)} module(s)?"
            if not click.confirm(click.style(warning_msg, fg="red")):
                logger.info("Operation cancelled")
                return
        else:
            if not click.confirm(f"\nRemove LLM '{name}'?"):
                logger.info("Operation cancelled")
                return

    del llm_config[name]

    # Clear default_llm if it was the removed LLM
    if is_default:
        llm_config["default_llm"] = ""
        logger.warning(
            "Default LLM has been cleared. Set a new default with: ./PromeFuzz.py configure assign default <name>"
        )

    if save_config_file(config_path, config_data):
        logger.success(f"Successfully removed LLM '{name}'")
        if modules_using_llm:
            click.echo("Next: Update module LLM references or set a new default LLM")
    else:
        sys.exit(1)


# Add the llm subcommand to the main config group
config.add_command(llm)


# =============================================================================
# Assign Command Group - Module Assignment Management
# =============================================================================


@click.group(help="Manage LLM assignments to modules.")
@config_path_option()
@click.pass_context
def assign(ctx, config_path):
    """Assign LLMs to different modules."""
    ctx.ensure_object(dict)
    ctx.obj["config_path"] = config_path


@assign.command(help="Set the default LLM for all modules.")
@click.argument("llm_name")
@click.pass_context
def default(ctx, llm_name: str):
    """Set the default LLM.

    Examples:
        ./PromeFuzz.py configure assign default mycloud
    """
    config_path = ctx.obj["config_path"]
    config_data = load_config_file(config_path)

    if "llm" not in config_data:
        config_data["llm"] = {}

    llm_config = config_data["llm"]

    # Validate LLM exists and is valid
    validate_llm_exists(llm_config, llm_name)

    # Set as default
    old_default = llm_config.get("default_llm", "None")
    llm_config["default_llm"] = llm_name

    if save_config_file(config_path, config_data):
        logger.success(f"Set '{llm_name}' as default LLM (was: {old_default})")
    else:
        sys.exit(1)


@assign.command(name="list", help="List current LLM assignments.")
@click.pass_context
def list(ctx):
    """List current LLM assignments to modules.

    Examples:
        ./PromeFuzz.py configure assign list
    """
    config_path = ctx.obj["config_path"]
    # Load and validate configuration
    config_data = load_config_file(config_path)

    # Get LLM configuration
    llm_config = config_data.get("llm", {})
    default_llm = llm_config.get("default_llm", "")

    # Display default LLM
    if default_llm:
        click.echo(f"Default LLM: {click.style(default_llm, fg='green', bold=True)}")
    else:
        click.echo(f"Default LLM: {click.style('Not set', fg='red')}")

    click.echo("\nModule LLM Assignments:")

    module_mappings = get_display_mapping()

    assignments_found = False
    for config_key, display_name in module_mappings:
        keys = config_key.split(".")
        section_name = keys[0]
        param_name = keys[1]

        if section_name in config_data and param_name in config_data[section_name]:
            assigned_llm = config_data[section_name][param_name]
            if assigned_llm:
                assignments_found = True
                click.echo(f"  {display_name}: {click.style(assigned_llm, fg='cyan')}")

    if not assignments_found:
        click.echo("  No specific module assignments found")
        click.echo("  All modules will use the default LLM")


def create_module_assignment_command(module_name: str):
    """Factory function to create module assignment commands."""

    @click.argument("llm_name")
    @click.pass_context
    def module_command(ctx, llm_name: str):
        f"""Set LLM for {module_name} module.

        Examples:
            ./PromeFuzz.py configure assign {module_name} mycloud
        """
        set_module_llm(ctx.obj["config_path"], module_name, llm_name)

    module_command.__name__ = module_name
    module_command.__doc__ = f"""Set LLM for {module_name} module.

    Examples:
        ./PromeFuzz.py configure assign {module_name} mycloud
    """
    return module_command


# Register module assignment commands using the factory
for module_name in ["embedding", "comprehension", "generator", "analyzer"]:
    command = create_module_assignment_command(module_name)
    assign.add_command(
        click.command(name=module_name, help=f"Set LLM for {module_name} module.")(
            command
        )
    )


@assign.command(name="options", help="Show all available assignment options.")
def options():
    """Show all available assignment options for modules.

    Examples:
        ./PromeFuzz.py configure assign options
    """
    click.echo("Available assignments:")
    click.echo()

    click.echo("LLM Assignments:")
    for option in get_assignment_options():
        click.echo(option)
    click.echo()

    click.echo("Usage examples:")
    click.echo("  ./PromeFuzz.py configure assign default mycloud")
    click.echo("  ./PromeFuzz.py configure assign generator local_llm")


# =============================================================================
# Validate Command - Configuration Validation
# =============================================================================


@click.command(help="Validate configuration completeness and correctness.")
@config_path_option()
def validate(config_path):
    """Validate configuration completeness and correctness.

    This command checks:
    - Configuration file exists and is readable
    - Required LLM configurations are present
    - Default LLM is set and valid
    - Module assignments are complete

    Examples:
        ./PromeFuzz.py configure validate
    """
    click.echo(f"Validating configuration: {click.style(str(config_path), fg='cyan')}")
    click.echo()
    config_data = load_config_file(config_path)

    issues = []
    warnings = []

    # Check LLM configuration
    llm_config = config_data.get("llm", {})

    # Get default LLM
    default_llm = llm_config.get("default_llm", "")

    # Check LLM instances
    llm_instances = {
        k: v
        for k, v in llm_config.items()
        if isinstance(v, dict) and k != "default_llm"
    }

    if not llm_instances:
        issues.append("No LLM configurations found")
    else:
        click.echo(f"[OK] Found {len(llm_instances)} LLM configuration(s)")

        for name, config in llm_instances.items():
            # Check required fields for each LLM
            llm_type = config.get("llm_type", "")
            model = config.get("model", "")

            if not llm_type:
                issues.append(f"LLM '{name}': missing llm_type")
            elif llm_type not in [
                "openai",
                "openai-reasoning",
                "ollama",
                "ollama-reasoning",
            ]:
                issues.append(f"LLM '{name}': invalid llm_type '{llm_type}'")

            if not model:
                issues.append(f"LLM '{name}': missing model")

            # Type-specific checks
            if llm_type in ["openai", "openai-reasoning"]:
                if not config.get("base_url"):
                    warnings.append(f"LLM '{name}': no base_url specified")
                if not config.get("api_key") and "OPENAI_API_KEY" not in config.get(
                    "api_key", ""
                ):
                    warnings.append(f"LLM '{name}': no API key specified")

            elif llm_type in ["ollama", "ollama-reasoning"]:
                if not config.get("host"):
                    warnings.append(f"LLM '{name}': no host specified (using default)")

    # Check module assignments
    modules = VALIDATION_MODULES

    unassigned_modules = []
    for module_name, llm_fields in modules.items():
        module_config = config_data.get(module_name, {})
        for field in llm_fields:
            assigned_llm = module_config.get(field, "")
            if not assigned_llm:
                unassigned_modules.append(f"{module_name}.{field}")
            else:
                click.echo(f"[OK] {module_name}.{field}: {assigned_llm}")

    # Now check default LLM logic based on unassigned modules
    # First validate default LLM if it's set
    default_llm_valid = False
    if default_llm:
        if default_llm not in llm_instances:
            issues.append(f"Default LLM '{default_llm}' is not configured")
        else:
            default_llm_valid = True
            click.echo(f"[OK] Default LLM: {click.style(default_llm, fg='green')}")

    # Handle unassigned modules
    if unassigned_modules:
        if not default_llm:
            issues.extend(
                [
                    f"No LLM assigned to {module} and no default LLM set"
                    for module in unassigned_modules
                ]
            )
        elif default_llm_valid:
            for module in unassigned_modules:
                click.echo(f"[INFO] {module}: using default LLM ({default_llm})")
    else:
        # All modules are explicitly assigned, default LLM is optional
        if not default_llm:
            click.echo("[INFO] No default LLM set (all modules explicitly assigned)")

    if not issues and not warnings:
        logger.success(
            "Configuration validation passed! All required settings are configured correctly"
        )
        return

    if issues:
        for issue in issues:
            logger.error(f"  {issue}")
    if warnings:
        for warning in warnings:
            logger.warning(f"  {warning}")

    # Provide suggestions
    if issues or warnings:
        click.echo("Suggestions:")

        if not default_llm or default_llm not in llm_instances:
            click.echo("  - Add an LLM: ./PromeFuzz.py configure llm add <name>")
            click.echo(
                "  - Set default LLM: ./PromeFuzz.py configure assign default <llm_name>"
            )

        if unassigned_modules:
            click.echo(
                "  - Assign LLMs to modules: ./PromeFuzz.py configure assign <module> <llm_name>"
            )

        click.echo("  - View assignment options: ./PromeFuzz.py configure assign options")

    if issues:
        sys.exit(1)


# =============================================================================
# Setup Command - Integrated Setup Wizard
# =============================================================================


@config.command(help="Interactive setup wizard to configure PromeFuzz from scratch.")
@config_path_option()
@click.option("--force", is_flag=True, help="Overwrite existing configuration")
@click.option("--skip-validation", is_flag=True, help="Skip final validation step")
def setup(config_path: Path, force: bool, skip_validation: bool):
    """Interactive setup wizard to configure PromeFuzz from scratch.

    This command guides you through the complete configuration process:
    1. Initialize configuration file
    2. Add LLM configurations
    3. Set assignments (default LLM, module assignments)
    4. Validate the final configuration

    Examples:
        ./PromeFuzz.py configure setup
        ./PromeFuzz.py configure setup --config-path my-config.toml --force
    """
    click.echo(
        f"{click.style('PromeFuzz Configuration Setup Wizard', fg='green', bold=True)}"
    )
    click.echo("=" * 40)

    if config_path.exists() and not force:
        if not click.confirm(
            f"Configuration file {config_path} already exists. Overwrite?"
        ):
            logger.info("Setup cancelled")
            return
        force = True

    # Call init command
    ctx = click.get_current_context()
    ctx.invoke(init, config_path=config_path, force=force, quiet=True)

    click.echo()

    # Add LLM configurations
    click.echo(f"{click.style('Add LLM Configurations', fg='yellow', bold=True)}")
    click.echo("-" * 36)
    click.echo(
        "Typically we need at least two LLM configurations, one generative model and one embedding model."
    )

    llms_added = []
    while True:
        if not llms_added:
            llm_name = click.prompt("Enter name for your first LLM", default="primary")
        else:
            click.echo(f"\nLLMs configured so far: {', '.join(llms_added)}")
            if not click.confirm("Add another LLM?", default=False):
                break
            llm_name = click.prompt("Enter name for additional LLM")

        # Call llm add command
        ctx.invoke(add, config_path=config_path, name=llm_name, quiet=True)
        llms_added.append(llm_name)

    click.echo()

    # Set assignments
    click.echo(
        f"{click.style('Step 3: Configure Assignments', fg='yellow', bold=True)}"
    )
    click.echo("-" * 33)

    # Set default LLM
    if len(llms_added) == 1:
        default_llm = llms_added[0]
        click.echo(f"Setting '{default_llm}' as default LLM...")
    else:
        click.echo(f"Available LLMs: {', '.join(llms_added)}")
        default_llm = click.prompt(
            "Choose default LLM", type=click.Choice(llms_added), default=llms_added[0]
        )

    config_data = load_config_file(config_path)
    if "llm" not in config_data:
        config_data["llm"] = {}
    llm_config = config_data["llm"]
    validate_llm_exists(llm_config, default_llm)
    old_default = llm_config.get("default_llm", "None")
    llm_config["default_llm"] = default_llm
    if save_config_file(config_path, config_data):
        logger.success(f"Set '{default_llm}' as default LLM (was: {old_default})")
    else:
        logger.error("Failed to save configuration")
        sys.exit(1)

    # Configure specific module assignments
    click.echo("\nConfiguring LLM assignments for modules:")
    click.echo("(Press Enter to use default LLM for each module)")

    modules = MODULE_DESCRIPTIONS

    for module, description in modules:
        click.echo(f"\n{description}:")
        click.echo(f"Available LLMs: {', '.join(llms_added)}")
        module_llm = click.prompt(
            f"Choose LLM for {module} (default: {default_llm})",
            type=click.Choice(llms_added + [""]),
            default="",
            show_default=False,
        )

        if not module_llm:
            module_llm = ""
        set_module_llm(config_path, module, module_llm)

    # Validate configuration
    if not skip_validation:
        click.echo(f"{click.style('Validate Configuration', fg='yellow', bold=True)}")
        click.echo("-" * 34)
        ctx.invoke(validate, config_path=config_path)

    click.echo()
    click.echo(f"{click.style('Setup Complete!', fg='green', bold=True)}")
    click.echo("=" * 16)
    click.echo("Your PromeFuzz configuration is ready!")
    if not skip_validation:
        click.echo(f"  - Re-validate: ./PromeFuzz.py configure validate")


# =============================================================================
# Command Registration
# =============================================================================
config.add_command(assign)
config.add_command(validate)
