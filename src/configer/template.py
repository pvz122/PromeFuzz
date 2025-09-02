"""
Configuration file templates.

This module provides template generation functions for creating
clean configuration files without comments.
"""

import os


def create_minimal_config() -> str:
    """Create empty configuration file with basic structure."""
    # Use appropriate binary extension for the current platform
    exe_ext = ".exe" if os.name == "nt" else ""

    return f"""[preprocessor]

[comprehender]
embedding_llm = ""
comprehension_llm = ""

[generator]
generation_llm = ""

[generator.schedule_weights]
type_relevance = 2
call_scope_relevance = 3
semantic_relevance = 5
coverage = 3
relevance = 1

[analyzer]
analysis_llm = ""

[llm]
default_llm = ""
validate_llm = true
enable_log = true

[bin]

"""
