# Useful Utilities for Running Fuzz Tests and Analyzing Results

This section describes a set of helper scripts to run fuzzing campaigns, collect crashes, and analyze coverage data. These tools streamline the reproduction of experiments and facilitate result parsing.

---

## `fuzz.py` — Run Fuzzing Campaigns

This script uses the generated fuzz driver to launch fuzzing experiments with AFL++.

### Setup
Before running, copy the template configuration:
```bash
cp fuzz.template.toml fuzz.toml
```

Edit `fuzz.toml` to define your fuzzing tasks. Each task is specified as a section with three fields:
- `target_name`: Name of the target library (e.g., `ngiflib`)
- `version`: Version tag (e.g., `latest`)
- `identification_name`: Identifier for the experiment (e.g., `promefuzz`)

For example, a task named `ngiflib.latest.promefuzz` defines a fuzzing run on `ngiflib` at version `latest` using the `promefuzz` harness.

Refer to the [template file](fuzz.template.toml) for a full example.

### Run Fuzzing
Start the fuzzing campaign with:
```bash
./fuzz.py -p ngiflib -v latest -fi promefuzz
```

This command:
- Creates a `tmux` session in the background,
- Launches **four parallel AFL++ instances**, each running for **24 hours**.

To monitor progress:
```bash
tmux a -t fuzz-aflpp
```

Results are saved in:  
`database/ngiflib/latest/out_promefuzz_24_x` (where `x` is the instance index).

---

## `crash.py` — Collect and Reproduce Crashes

After fuzzing, use this script to extract and reproduce detected crashes.

Ensure `fuzz.toml` is properly configured, then run:
```bash
./crash.py -p ngiflib -v latest -fi promefuzz
```

Crashes are saved to:  
`database/ngiflib/latest/crashes/`

Each crash is stored as a pair:
- `x.input`: The input triggering the crash,
- `x.log`: The console output and stack trace from AFL++.

### Analyze Crashes
To analyze collected crashes using PromeFuzz’s crash analyzer, navigate to the PromeFuzz root directory and run:
```bash
./PromeFuzz.py -F database/tinygltf/lib.toml analyze database/ngiflib/latest/crashes/*.log
```

This leverages crash analysis LLM to triage and summarize each crash.

---

## `gcov.py` — Collect GCov Coverage

This script extracts line and branch coverage using **GCC's `gcov`** tool from the fuzzing results.

Prerequisite: A configured `fuzz.toml`.

Run:
```bash
./gcov.py -p ngiflib -v latest -f promefuzz
```

Coverage data is saved to:  
`database/ngiflib/latest/gcov/`

Output includes:
- `coverage.csv`: Aggregated coverage over time,
- `gcov-x.json`: Per-hour detailed coverage (line and branch) in JSON format.

---

## `cov.py` — Collect LLVM Coverage

This script is functionally similar to `gcov.py`, but uses **LLVM’s `llvm-cov`** for coverage collection.
