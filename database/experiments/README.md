# Reproducing Experiments from Our Paper

In our study, we evaluate 22 open-source libraries as part of our experimental dataset.

We use the following models for different stages of our pipeline:
- **Generation**: `DeepSeek-V3`
- **Crash Analysis**: `DeepSeek-R1`
- **Comprehension**: `GPT-4o-mini`
- **Embedding Model**: `mxbai-embed-large`

All experiments are configured using the default settings specified in `config.template.toml`, along with the library-specific configurations in each corresponding `lib.toml` file located in the respective library directories.

The generation stop condition is set to the default `ALL-COVER` mode. That is, the generation process will continue until all API functions are invoked at least once or fail.

Each fuzzing experiment is conducted using **AFL++** for **24 hours**, repeated **10 times** to ensure statistical reliability. Branch coverage is measured using **GCov**.

> **Note**: For `rapidcsv`, a single-header library, coverage is instead measured using **Clang Coverage** due to compilation constraints.

We provide a suite of scripts to help you reproduce our experiments efficiently. Follow the instructions in the subsequent sections to set up the environment and run the experiments.

### 0. **Configure PromeFuzz**

Before running the experiments, you need to setup the environment and configure LLMs in `config.toml`. Refer to the [PromeFuzz documentation](../../README.md) for detailed instructions.

### 1. **Obtain and Build the Target Library**

To begin, fetch and build the target library using the `build_dataset.py` script. For example, to set up `pugixml`:

```bash
./build_dataset.py one pugixml
```

This will:
- Download the library source code into `database/pugixml/latest/code`,
- Build the library, and
- Generate the corresponding `build_xxx` and `bin_xxx` directories.

### 2. **Generate and Build Fuzzing Harnesses**

We provide pre-generated fuzzing harnesses in the [examples directory](../../examples/README.md), which we recommend using. This avoids the need to re-generate harnesses from scratch.

To compile the provided example harnesses, run:

```bash
./build_example_drivers.py one pugixml
```

This script compiles the example fuzzing drivers and outputs to `database/pugixml/latest/out/fuzz_driver`.

> **Optional: Generate Harnesses from Scratch**  
> If you wish to generate the fuzzing harnesses yourself, use the `generate_and_build_drivers.py` script instead:
> ```bash
> ./generate_and_build_drivers.py one pugixml
> ```

### 3. **Run Fuzzing Experiments**

Use `run_fuzz.py` to launch the fuzzing experiments with the compiled fuzzing harnesses:

```bash
./run_fuzz.py one pugixml
```

This script starts **4 independent AFL++ instances** in the background using `tmux`, each running for **24 hours**. The fuzzing data is stored in `database/pugixml/latest/fuzz`.

To monitor the progress, attach to the `tmux` sessions with:

```bash
tmux a
```

> **Tip**: You can run `run_fuzz.py` multiple times to launch additional AFL++ instances for repeated trials.

### 4. **Collect Coverage Data**

Use `run_gcov.py` to collect code coverage data from the fuzzing experiments. This script processes the generated fuzzing artifacts and computes coverage over time:

```bash
./run_gcov.py one pugixml
```

The script generates a coverage report directory at `database/pugixml/latest/gcov`, containing **per-hour JSON files** that record **line and branch coverage** throughout the 24-hour fuzzing period, and a **summary CSV file** that aggregates the coverage data across all runs.
