# Source Code Overview

This directory contains the core source code of **PromeFuzz**, structured into modular components that correspond to the different stages of the fuzzing pipeline. Below is an overview of the directory structure and key components:

| Directory / File       | Purpose |
|------------------------|-------|
| `preprocessor/`        | Extracts structural code metadata from target library source code. |
| `comprehender/`        | Extracts documentation and code to build a structured knowledge base. Uses the comprehension LLM to interpret API semantics. |
| `configer/`            | Set the configuration file of PromeFuzz. |
| `generator/`           | Generates fuzz harnesses based on the knowledge base. Ensures correctness and coverage. |
| `analyzer/`            | Analyzes crash logs during fuzzing. Filters duplicates, triages crashes, and identifies root causes. |
| `stats/`               | Collects and reports statistics on the generation process. |
| `llm/`                 | Handles communication with large language models. |
| `prompt/`              | Contains all prompt templates used across modules. |
| `utils.py`             | Shared utility functions used across modules. |
| `vars.py`              | Global configuration variables and constants. |
| `tests/`               | Unit and integration tests developed during implementation to ensure component reliability. |
| `unused/`              | Legacy or experimental code not used in the final evaluation. | 
