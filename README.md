<br />
<p align="center">
<img src="img/logo.png" alt="Logo" width="156" height="156">
<h2 align="center" style="font-weight: 600">PromeFuzz</h2>
<p align="center">A Knowledge-Driven Approach to Fuzzing Harness Generation with Large Language Models</p>
<br />
<br />
</p>

![workflow](img/workflow.svg)

<br />

**PromeFuzz** is a state-of-the-art framework for automatically generating fuzzing harnesses (fuzz drivers) for C and C++ libraries. It employs a knowledge-driven approach that leverages structured information from code metadata, documentation, and API usage patterns to produce highly effective fuzzing harnesses.

PromeFuzz outperforms existing approaches—including [Google OSS-Fuzz-Gen](https://github.com/google/oss-fuzz-gen), [PromptFuzz](https://github.com/FuzzAnything/PromptFuzz) and [CKGFuzzer](https://github.com/security-pride/CKGFuzzer)—in both branch coverage and vulnerability discovery.

For more details, see our research [paper](TOBEADDED) at ACM CCS 2025.

## ✨ Highlights

- **Systematic Knowledge Integration:** PromeFuzz systematically integrates knowledge from various sources, including code metadata, documentation, and API usage patterns, to ensure both the syntactic and semantic correctness of the generated fuzzing harnesses.
- **Intelligent API Scheduling:** PromeFuzz employs advanced API correlation analysis to optimize the scheduling of API calls within the generated harnesses, thereby improving their effectiveness.
- **Built-in Crash Analysis:** PromeFuzz includes a dedicated crash analyzer that automatically detects, triages, and analyzes crashes triggered by the generated fuzzing harnesses, facilitating reliable vulnerability discovery.
- **Practical and Production-Ready Design:** PromeFuzz is robustly implemented to support both C and C++ libraries, featuring an end-to-end pipeline that ensures seamless integration and practical usability in real-world software testing environments.

## 📦 Setup PromeFuzz

The recommended way to set up PromeFuzz is using Docker for a consistent and isolated environment. Alternatively, you can install it manually on your system.

### 🐳 Setup Using Docker

1. **Install Docker**  
   Ensure Docker is installed and your user is added to the `docker` group:

   ```bash
   sudo apt update
   sudo apt install docker.io
   sudo usermod -aG docker $USER
   newgrp docker  # Refresh group membership
   ```

2. **Build the Docker image**  
   From the PromeFuzz root directory:

   ```bash
   docker build -t promefuzz:latest .
   ```

3. **Run the container**  
   We allocate additional shared memory (`shm`) to improve performance during file processing:

   ```bash
   docker run -itd --shm-size=16g --name promefuzz promefuzz:latest
   ```

4. **Access the container**  
   Enter the running container:

   ```bash
   docker exec -it promefuzz /bin/bash
   ```

### 🛠️ Manual Setup

If you prefer a native installation, follow these steps:

1. **Set up the Python environment**  
   PromeFuzz uses [`uv`](https://github.com/astral-sh/uv) as the Python package manager for faster dependency resolution:

   ```bash
   # Install uv
   curl -LsSf https://astral.sh/uv/install.sh | sh
   # Restore dependencies
   uv sync
   # Activate virtual environment
   source .venv/bin/activate
   ```

2. **Install system dependencies**  
   Install required build tools and libraries:

   ```bash
   sudo apt install bear build-essential cmake clang llvm libclang-dev clang-format libomp-dev
   ```

3. **Build processor binaries**  
   Compile the core analysis tools:

   ```bash
   ./setup.sh
   ```

## ⚙️ Using PromeFuzz

> 👉 This section describes the usage of PromeFuzz. If your goal is simply to reproduce our experiments, we recommend using the ready-to-run scripts located in the `database/experiments` directory. For detailed instructions, refer to [`database/experiments/README.md`](database/experiments/README.md).

PromeFuzz is controlled via the command-line script `PromeFuzz.py`, which supports the following subcommands:

- `preprocess`: Preprocess the library to extract code metadata knowledge.
- `comprehend`: Comprehend the library using LLM to extract documentation knowledge.
- `generate`: Generate fuzzing harnesses using the extracted knowledge.
- `analyze`: Analyze ASan crashes to generate a report.
- `stats`: Collect statistics.

For detailed usage of each subcommand, run:

```bash
./PromeFuzz.py [subcommand] --help
```

Additionally, a set of [utility scripts](database/utils/README.md) are available in the `database/utils/` directory to assist with common tasks such as fuzzing execution, coverage collection, and result evaluation.

Below, we walk through a complete example using `pugixml` to demonstrate the end-to-end workflow.

### 1. **Configure PromeFuzz**

PromeFuzz relies on two configuration files:

- `config.toml` — Controls the global behavior of the framework (e.g., LLM settings, analysis parameters).  
- `libraries.toml` — Defines metadata for the target libraries (e.g., header paths, build args).

To get started:

1. Copy the template configuration:
   ```bash
   cp config.template.toml config.toml
   ```

2. Edit `config.toml` to match your environment and requirements.

> 👉 The [template file](./config.template.toml) includes detailed comments explaining each option. Be sure to update all fields marked with `[MODIFY THIS]`.

##### Example: Using GPT-5 and Ollama Embeddings

If you'd like to use **OpenAI's GPT-5** as the primary LLM and **`mxbai-embed-large`** (via Ollama) for embeddings, configure `config.toml` as follows:

```toml
[comprehender]
# [MODIFY THIS] The llm used for RAG embedding.
embedding_llm = "mxbai"

[llm]
# [MODIFY THIS] The default llm used for the generation, comprehension, and analysis.
# If the llm is not specified in the corresponding section, the default llm will be used.
default_llm = "gpt-5"

# [MODIFY THIS] Your custom llm name.
[llm.gpt-5]
# The llm type, currently support "ollama", "openai", "ollama-reasoning", "openai-reasoning"
llm_type = "openai"
# The base url for the openai api.
base_url = "https://api.openai.com/v1/  "
# The api key for the openai api, default using the environment variable "OPENAI_API_KEY".
api_key = ""
# The model used for the llm query.
model = "gpt-5"
# The temperature for the llm query. Recommend to set it lower for generating code.
temperature = 0.5

# [MODIFY THIS] Your custom llm name.
[llm.mxbai]
# The llm type, currently support "ollama" and "openai".
llm_type = "ollama"
# The ollama server host.
host = "localhost"
# The ollama server port.
port = 11434
# The model used for the llm query.
model = "mxbai-embed-large"
```

Once configured, PromeFuzz will use these settings across all stages: comprehension, harness generation, and crash analysis.

### 2. **Obtain and Build the Library**

Before generating fuzzing harnesses, you need to fetch and compile the target library with compilation database (`compile_commands.json`) support. This enables PromeFuzz to accurately analyze build contexts and dependencies.

#### For Libraries in the Dataset

For libraries included in our [dataset](database/README.md), we provide automated scripts to simplify this process.

For example, to set up **pugixml**:

```bash
cd database/pugixml
./fetch.sh                  # Clone the latest version
cd latest
./build.sh normal && ./build.sh asan  # Build normal + ASan instrumented versions
```

> ✅ This generates a `compile_commands.json` file in the `build_asan` directory, which PromeFuzz uses for code analysis.

#### For Custom Libraries (Not in Dataset)

If you're testing a library **not included** in our dataset, follow these manual steps. Here’s an example using `pugixml`:

```bash
mkdir library && cd library
git clone https://github.com/zeux/pugixml.git pugixml && cd pugixml
mkdir build && cd build
cmake ..
bear -- make
```

> ✅ This generates `compile_commands.json` in `library/pugixml/build`.

### 3. **Configure the Library**

Each target library must be described in a configuration file (`libraries.toml`) that specifies essential metadata such as header locations, documentation paths, compilation details, and output settings.

#### For Libraries in the Dataset

For libraries included in our [dataset](database/README.md), we provide ready-to-use configuration files. For example, the configuration for **pugixml** is located at:

```
database/pugixml/latest/lib.toml
```

To use it, simply pass the file path to PromeFuzz:

```bash
./PromeFuzz.py -F database/pugixml/latest/lib.toml [subcommand]
```

This enables immediate use with validated, optimized settings.

#### For Custom Libraries (Not in Dataset)

To add a custom library, copy the template:

```bash
cp libraries.template.toml libraries.toml
```

Then edit `libraries.toml` accordingly. All fields marked with `[MODIFY THIS]` must be filled. Refer to the comments in the [template file](./libraries.template.toml) for guidance.

##### Example: Manual Configuration for `pugixml`

Below is a complete example configuration for `pugixml`:

```toml
# [MODIFY THIS] The name of the library.
[pugixml]

# [MODIFY THIS] The language of the library. The possible values are "c" and "c++".
language = "c++"

# [MODIFY THIS] The header paths of library. A header path is a directory or a file where the API functions are declared.
header_paths = ["library/pugixml/src/pugixml.hpp"]

# [MODIFY THIS] The path of "compile_commands.json" which records the compilation database of the library.
# You can generate the "compile_commands.json" using Bear or CMake with the -DCMAKE_EXPORT_COMPILE_COMMANDS=ON flag.
compile_commands_path = "library/pugixml/build/compile_commands.json"

# [MODIFY THIS] The path of the documentation file of the library. It can be:
# 1. A documentation file like README.md.
# 2. A directory containing documentation files. PromeFuzz will read all files with .md/.txt/.html/.htm/.pdf/.adoc/.rst extension or named "README"/"USAGE".
# 3. A website URL. PromeFuzz will download the website and extract the text content.
document_paths = ["https://pugixml.org/docs/manual.html"]

# [MODIFY THIS] Whether the document has API usage. If true, PromeFuzz will try to comprehend the API usage from the document.
document_has_api_usage = true

# [MODIFY THIS] The output path for PromeFuzz to store the results.
output_path = "out/pugixml"

# [MODIFY THIS] The compile arguments while building the fuzz driver. The fuzz driver will be built using command like:
# clang++ path/to/fuzz/driver.cpp -o path/to/output -fsanitize=fuzzer,address,undefined -Ipath/to/headers [configured build args]
# This option usually includes the path to the library binary (.so/.a file). It is strongly recommended that you build the library
# with -g flag to include debug information in the binary, on which PromeFuzz Sanitizer and ConstraintLearner rely to analyze the source code.
driver_build_args = ["library/pugixml/build/libpugixml.a", "-DPUGIXML_NO_EXCEPTIONS"]

# The consumer case source paths of the library, e.g., the test cases or examples using the library.
# These cases will be used to infer the API relationships.
consumer_case_paths = ["database/pugixml/latest/code/tests"]
```

With this configuration in place, PromeFuzz can effectively analyze the library and generate high-quality fuzzing harnesses.

### 4. **Preprocess the Library**

Run the `preprocess` command to extract essential code information from the library, such as API signatures, call patterns, and metadata dependencies.

With the library configuration file (e.g., `lib.toml`) in place, execute:

```bash
./PromeFuzz.py -F database/pugixml/latest/lib.toml preprocess
```

The extracted knowledge will be saved to the output directory specified in the config—by default:  
`database/pugixml/latest/out/preprocessor/`.

##### Output Artifacts

The preprocessor produces a set of structured files:

- `sources.json`: Source files.
- `api.pkl` & `api.json`: API functions.
- `info.pkl` & `info.json`: Metadata dependency graph.
- `call_graph.json` & `call_graph.pkl`: Consumer call graph.
- `call_order.json` & `call_order.pkl`: API call sequences.
- `type_relev.pkl`: Type relevance.
- `call_scope_relev.csv` & `call_scope_relev.pkl`: Call scope relevance.
- `class_scope_relev.csv` & `class_scope_relev.pkl`: Class scope relevance.

### 5. **Comprehend Library Semantics**

Run the `comprehend` step to extract semantic knowledge from both the library’s source code and its documentation.

This step is optional but strongly recommended to improve the quality and correctness of generated fuzzing harnesses.

With your `lib.toml` configuration ready, execute:

```bash
./PromeFuzz.py -F database/pugixml/latest/lib.toml comprehend --pool-size 50
```

> 💡 **Parallel Processing**: The comprehension tasks are highly parallelizable. You can increase `--pool-size` to speed up processing, depending on your available LLM API rate limits and system resources.
> 🔔 **LLM Selection**: The comprehension tasks can consume a significant number of tokens, so opting for a cost-effective LLM at this stage is recommended.

##### Output Artifacts

The comprehender generates structured knowledge artifacts under the output directory (e.g., `database/pugixml/latest/out/comprehender/`):

- `comp.pkl` & `comp.json`: Documentation knowledge, including library purpose and API usage.
- `semantic_relev.csv` & `semantic_relev.pkl`: Semantic relevance.
- `documents/`: Vector database for semantic search.

### 6. **Generate Fuzzing Harnesses**

Run the `generate` command to generate fuzzing harnesses based on the knowledge extracted during preprocessing and comprehension.

By default, PromeFuzz operates in **ALL-COVER mode**, aiming to generate fuzzing harnesses such that each API function is invoked at least once. You can customize the stop condition using the `--task` option.

With your `lib.toml` configuration ready, execute:

```bash
./PromeFuzz.py -F database/pugixml/latest/lib.toml generate
```

> 🔔 **Parallel Processing**: While parallelization is supported, it is recommended to keep `--pool-size` ≤ 10. As the generation process benefits from runtime feedback, so excessive parallelism may reduce effectiveness.

> 💡 **Resumable Execution**: PromeFuzz automatically saves its internal state to `database/pugixml/latest/out/generator/state.pkl`. If the process is interrupted, simply re-running the command will resume generation from the last saved state. To discard previous progress and regenerate from scratch, use `--clear-state`.

##### Output Artifacts

Generated harnesses are stored in `database/pugixml/latest/out/fuzz_driver/`:

- `fuzz_driver_{id}.c(pp)`: Individual C/C++ fuzzing harness using libFuzzer.
- `build_fuzz_driver_{id}.sh`: Build script that compiles the harness.
- `synthesize_into_one`: Helper script to merge all individual harnesses into a single, unified fuzz harness.

### 7. **Perform Fuzzing**

The generated fuzzing harnesses can be merged into a unified driver using the `synthesize_into_one` script located in the `fuzz_driver` directory. To merge them, simply run:

```bash
./synthesize_into_one
```

Merged harness enables the fuzzing engine (e.g., LibFuzzer or AFL++) to leverage its mutation and state exploration capability to select effective harnesses.

The script generates a directory `synthesized/` containing the merged fuzzing harness and the following build scripts:

- `build_synthesized_driver.sh`: Builds the merged harness with **LibFuzzer** and AddressSanitizer (ASan).
- `build_aflpp_synthesized_driver.sh`: Builds the harness for **AFL++**.

- `build_gcov_synthesized_driver.sh`: Builds with **GCov** instrumentation for coverage analysis.

- `build_cov_synthesized_driver.sh`: Builds with **Clang Coverage**.

Once built, you can start the fuzzing campaign in your preferred way. For example, with LibFuzzer:

```bash
./build_synthesized_driver.sh
./synthesized_driver -jobs=4 -workers=4 ../../../in/
```

Or with AFL++:

```bash
./build_aflpp_synthesized_driver.sh
# initial seeds are at database/pugixml/in/
afl-fuzz -i ../../../in/ -o fuzz/ -- ./aflpp_synthesized_driver @@
```

> 🛠️ **Automation Tip**: We provide utility scripts for orchestrating fuzzing, coverage collection, and crash reproducing. See [`database/utils/README.md`](database/utils/README.md) for details.

### 8. **Collect Statistics**

#### Generation Metrics

PromeFuzz includes a built-in `stats` command to gather detailed metrics throughout the harness generation process. This includes insights into API coverage, token usage, crash learning, and more.

To generate a report, run:

```bash
./PromeFuzz.py -F database/pugixml/latest/lib.toml stats
```

This produces an Excel workbook at `database/pugixml/latest/out/statistics_for_pugixml.xlsx`.

#### Fuzzing-Stage Metrics

For runtime statistics such as code coverage, and crash reports during fuzzing, PromeFuzz integrates with utility scripts located in `database/utils/`. These tools support coverage collection and crash reproducing. See [`database/utils/README.md`](database/utils/README.md) for instructions.

### 9. **Analyze Crashes**

During fuzzing, crashes may be triggered—some of which are genuine vulnerabilities in the library (**true positives**, TP), while others stem from incorrect harness usage or invalid assumptions (**false positives**, FP). To help distinguish between them, PromeFuzz includes a **crash analyzer** that triages and interprets crash reports.

This crash analyzer runs automatically during the generation phase. If you'd like to use it to analyze crashes from your own fuzzing campaign, follow these steps:

If AddressSanitizer (ASan) logs are stored in a directory such as `database/pugixml/latest/crashes/*.log`, you can analyze them using the `analyze` subcommand:

```bash
./PromeFuzz.py -F database/pugixml/latest/lib.toml analyze database/pugixml/latest/crashes/*.log -O database/pugixml/latest/reports
```

This command processes each crash log, deduplicates them, and generates detailed analysis reports in the output directory.

Each report is named after:

- `TP-{crash_type}@{crash_location}`: This is possibly a true positive (TP) vulnerability.
- `FP-{crash_type}@{crash_location}`: This is likely a false positive (FP) due to API misuse.
- `UN-{crash_type}@{crash_location}`: This is an unclassified crash that requires further investigation.