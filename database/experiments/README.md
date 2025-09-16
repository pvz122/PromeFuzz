# Reproducing Experiments from Our Paper

## Overview

As illustrated in the Evaluation section of [our paper](/paper/ccs25-full.pdf), we evaluate 22 open-source libraries as our experimental dataset:


| Library       | Version  | Language          |
| ------------- | -------- | ----------------- |
| c-ares        | 7978cf7  | C                 |
| curl          | 4c50998  | C                 |
| lcms          | 04ace9c  | C                 |
| libjpeg-turbo | 36ac5b84 | C                 |
| sqlite3       | 7903db4  | C                 |
| libaom        | 99fcd81  | C                 |
| libpcap       | 2559282  | C                 |
| libvpx        | 9514ab6  | C                 |
| zlib          | 5a82f71  | C                 |
| re2           | c84a140  | C++(or C binding) |
| libmagic      | dadc01f  | C                 |
| libpng        | 738f5e7  | C                 |
| ngiflib       | db19270  | C                 |
| ffjpeg        | caade6   | C                 |
| liblouis      | 3d95765  | C                 |
| libtiff       | fcd4c86  | C                 |
| cjson         | 12c4bf1  | C                 |
| pugixml       | 06318b0  | C++               |
| tinygltf      | a5e653e  | C++               |
| exiv2         | 04e1ea3  | C++               |
| loguru        | 4adaa18  | C++               |
| rapidcsv      | 083851d  | C++               |

We use the following models for different stages of our pipeline:
- **Generation**: `DeepSeek-V3`
- **Crash Analysis**: `DeepSeek-R1`
- **Comprehension**: `GPT-4o-mini`
- **Embedding Model**: `mxbai-embed-large`

All experiments are configured using the default settings specified in `config.template.toml`, along with the library-specific configurations in each corresponding `lib.toml` file located in the respective library directories.

The generation stop condition is set to the default `ALL-COVER` mode. That is, the generation process will continue until all API functions are invoked at least once or fail.

Each fuzzing experiment is conducted using **AFL++** for **24 hours**, repeated **10 times** to ensure statistical reliability. Branch coverage is measured using **GCov**.

> **Note**: For `rapidcsv`, a single-header library, coverage is instead measured using **Clang Coverage** due to compilation constraints.

## RQ1: Generating Fuzzing Harnesses

In **RQ1**, we evaluate **PromeFuzz** by generating fuzzing harnesses and conducting fuzzing campaigns to collect generation statistics and branch coverage data. We then compare PromeFuzz against the following baseline approaches: [**PromptFuzz**](https://github.com/FuzzAnything/PromptFuzz), [**CKGFuzzer**](https://github.com/security-pride/CKGFuzzer), [**OSS-Fuzz-Gen**](https://github.com/google/oss-fuzz-gen), and [**OSS-Fuzz**](https://github.com/google/oss-fuzz). (Table 2)

![Table 2](/img/table2.png)

To facilitate reproducibility, we provide a suite of scripts for all **PromeFuzz-related experiments**. For the **baseline tools**, however, we do not provide ready-to-run scripts due to their complex setup procedures and dependencies. We recommend referring to the original papers and repositories for detailed execution instructions.

Please follow the steps in the sections below to set up and run the experiments.

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

## RQ2: Finding Vulnerabilities

In **RQ2**, we evaluate the effectiveness of **PromeFuzz** in discovering real-world vulnerabilities in target libraries. During our fuzzing campaigns, crashes are collected and processed using our crash analyzer module. Each unique crash is then manually triaged to confirm whether it corresponds to a genuine vulnerability.

In total, **PromeFuzz identified 25 previously unknown vulnerabilities** across 7 open-source libraries. Of these, 21 have been confirmed by maintainers. A detailed list of the discovered vulnerabilities is provided below:

| Vulnerability ID                                                            | Library  | Vulnerability Type                   | Status    |
| ----------------------------------------------------------------- | -------- | -------------------------- | --------- |
| [Issue 34](https://github.com/miniupnp/ngiflib/issues/34)         | ngiflib  | NULL Pointer Dereference   | Fixed     |
| [Issue 36](https://github.com/miniupnp/ngiflib/issues/36)         | ngiflib  | NULL Pointer Dereference   | Fixed     |
| [Issue 55](https://github.com/rockcarry/ffjpeg/issues/55)         | ffjpeg   | Use Uninitialized Variable | Reported  |
| [Issue 57](https://github.com/rockcarry/ffjpeg/issues/57)         | ffjpeg   | Buffer Underflow           | Reported  |
| [Issue 58](https://github.com/rockcarry/ffjpeg/issues/58)         | ffjpeg   | Stack Buffer Overflow      | Reported  |
| [Issue 60](https://github.com/rockcarry/ffjpeg/issues/60)         | ffjpeg   | Stack Buffer Overflow      | Reported  |
| [Issue 1708](https://github.com/liblouis/liblouis/issues/1708)    | liblouis | Invalid Free               | Fixed     |
| [Issue 1709](https://github.com/liblouis/liblouis/issues/1709)    | liblouis | Invalid Free               | Fixed     |
| [Issue 1711](https://github.com/liblouis/liblouis/issues/1711)    | liblouis | Memory Leak                | Fixed     |
| [Issue 1718_1](https://github.com/liblouis/liblouis/issues/1718)  | liblouis | Memory Leak                | Fixed     |
| [Issue 1718_2](https://github.com/liblouis/liblouis/issues/1718)  | liblouis | Memory Leak                | Fixed     |
| [Issue 1719](https://github.com/liblouis/liblouis/issues/1719)    | liblouis | Heap Buffer Overflow       | Fixed     |
| [Issue 1720](https://github.com/liblouis/liblouis/issues/1720)    | liblouis | Heap Buffer Overflow       | Fixed     |
| [Issue 1721](https://github.com/liblouis/liblouis/issues/1721)    | liblouis | Heap Buffer Overflow       | Fixed     |
| GHSA-jvjf-3q72-j9qg                                               | liblouis | Infinite Loop              | Confirmed |
| GHSA-w9jg-ggx9-3wwm                                               | liblouis | Heap Buffer Overflow       | Confirmed |
| GHSA-3j86-vjp4-w63h                                               | liblouis | Heap Buffer Overflow       | Confirmed |
| [Issue 669](https://gitlab.com/libtiff/libtiff/-/issues/669)      | libtiff  | Reachable Assertion        | Fixed     |
| [CVE-2025-45701](https://gitlab.com/libtiff/libtiff/-/issues/676) | libtiff  | Memory Leak                | Fixed     |
| [CVE-2025-45701](https://github.com/Exiv2/exiv2/issues/3168)      | exiv2    | Use After Free             | Fixed     |
| [CVE-2025-55450](https://bugs.astron.com/view.php?id=636)         | libmagic | Integer Overflow           | Fixed     |
| [Bug tracker 640](https://bugs.astron.com/view.php?id=640)        | libmagic | Integer Overflow           | Fixed     |
| [Issue 186](https://github.com/d99kris/rapidcsv/issues/186)       | rapidcsv | Out-of-bounds Write        | Fixed     |
| [Issue 187](https://github.com/d99kris/rapidcsv/issues/187)       | rapidcsv | Out-of-bounds Write        | Fixed     |
| [Issue 188](https://github.com/d99kris/rapidcsv/issues/188)       | rapidcsv | Out-of-bounds Read         | Fixed     |

> Vulnerability IDs starting with `GHSA-` are unpublished GitHub security advisories.

Due to the inherent stochasticity of fuzzing, the specific vulnerabilities discovered may vary across different runs. To support analysis and reproducibility, we provide the `crash.py` script in the [utils directory](../utils/README.md) to help you collect, deduplicate, and analyze crashes from your own fuzzing experiments (as outlined in RQ1). Besides, we have provided several crash analysis examples in the [examples directory](/examples/README.md) for your reference.

## RQ3: Ablation Study

## RQ3: Ablation Study

In **RQ3**, we perform an ablation study to evaluate the contribution of key components in PromeFuzz. This includes:  
- **Component ablation**: Assessing the impact of each module on fuzzing effectiveness. (Table 5)
- **Weight ablation**: Analyzing how different weight settings in the scheduler’s scoring function influence performance. (Table 6)

![Table 5](/img/table5.png)

![Table 6](/img/table6.png)

To reproduce the ablation study presented in our evaluation, follow the same harness generation and fuzzing workflow described in RQ1. We have extended the `generate_and_build_drivers.py` script with an **ablation mode** to enable controlled experimentation by disabling specific components or adjusting weighting schemes:

```bash
./generate_and_build_drivers.py one <library_name> <ablation_options>
```

The `<ablation_options>` parameter allows you to configure the variant of PromeFuzz to evaluate:

| Option           | Description |
|------------------|-------------|
| `NONE`           | Run the full PromeFuzz pipeline (no ablation). |
| `WO_COMP`        | Disable the **Comprehender** module. |
| `WO_SCHD`        | Disable the **Scheduler** module. |
| `WO_SAN`         | Disable the **Sanitizer** module. |
| `WEIGHT_COV`     | Use weight vector `(5, 1, 2, 3, 5)` — prioritizing coverage (see Table 6). |
| `WEIGHT_REL`     | Use weight vector `(1, 3, 2, 3, 5)` — prioritizing relevance (see Table 6). |
| `WEIGHT_TYP`     | Use weight vector `(3, 1, 5, 3, 2)` — prioritizing type relevance (see Table 6). |
| `WEIGHT_SCP`     | Use weight vector `(3, 1, 2, 5, 3)` — prioritizing scope relevance (see Table 6). |
| `WEIGHT_EQ1`     | Use weight vector `(1, 1, 2, 3, 5)` — equal emphasis on coverage and relevance (see Table 6). |
| `WEIGHT_EQ2`     | Use uniform weights `(1, 1, 1, 1, 1)` — no prioritization (see Table 6). |


For example, to run the ablation without the Comprehender module on `pugixml`:
```bash
./generate_and_build_drivers.py one pugixml WO_COMP
```

To run the weight ablation with uniform weights:
```bash
./generate_and_build_drivers.py one pugixml WEIGHT_EQ2
```

After generating the harnesses, proceed with fuzzing execution and coverage collecting using the same procedures outlined in RQ1.