"""
Shared constants for configuration management.
"""

from typing import List, Tuple

# Module mappings for configuration
MODULE_MAPPINGS = {
    "embedding": ("comprehender", "embedding_llm"),
    "comprehension": ("comprehender", "comprehension_llm"),
    "generator": ("generator", "generation_llm"),
    "analyzer": ("analyzer", "analysis_llm"),
}

# Module descriptions for setup wizard
MODULE_DESCRIPTIONS = [
    ("embedding", "Text embedding for RAG"),
    ("comprehension", "Code comprehension"),
    ("generator", "Fuzz harness generation"),
    ("analyzer", "Crash analysis"),
]

# Module display names for options/listing
MODULE_DISPLAY_NAMES = {
    "embedding": "Embedding",
    "comprehension": "Comprehension",
    "generator": "Generator",
    "analyzer": "Analyzer",
}

# Validation structure for checking assignments
VALIDATION_MODULES = {
    "comprehender": ["embedding_llm", "comprehension_llm"],
    "generator": ["generation_llm"],
    "analyzer": ["analysis_llm"],
}


def get_display_mapping() -> List[Tuple[str, str]]:
    """Get module mappings in display format (config_key, display_name)."""
    return [
        (f"{section}.{param}", MODULE_DISPLAY_NAMES[module])
        for module, (section, param) in MODULE_MAPPINGS.items()
    ]


def get_assignment_options() -> List[str]:
    """Get formatted assignment options for CLI help text."""
    options = ["  default       - Default LLM for all modules"]

    for module, description in MODULE_DESCRIPTIONS:
        section, param = MODULE_MAPPINGS[module]
        option_line = f"  {module:<12} - {description} ({section}.{param})"
        options.append(option_line)

    return options
