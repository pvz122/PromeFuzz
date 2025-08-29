"""
Global variables
"""

from enum import Enum
from pathlib import Path


# ==================== Basic Info ====================
class SupportedLanguages(Enum):
    """
    Supported languages
    """

    NONE = "none"
    C = "c"
    CPP = "c++"
    RUST = "rust"


promefuzz_path: Path = None

# ==================== Configuration ====================

# template configuration, as default value
config_template = dict()
libraries_template = dict()

# PromeFuzz configuration
config = dict()

# libraries configuration
libraries = dict()

# ==================== Current Library ====================

# target library name
library_name = ""

# target library language
library_language = SupportedLanguages.NONE

# target library configuration
library_config = dict()
