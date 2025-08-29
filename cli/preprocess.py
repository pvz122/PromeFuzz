"""
Preprocessor command line interface.
"""

from pathlib import Path
import click
from loguru import logger
from multiprocessing import cpu_count
import sys
import json

from src import vars as global_vars
from src.utils import setup_default_config
from src.preprocessor.ast import (
    CXXASTPreprocessor,
    RustASTPreprocessor,
    ASTPreprocessor,
)
from src.preprocessor.api import APIExtractor
from src.preprocessor.consumer import ConsumerCallGraphBuilder, OrderSet
from src.preprocessor.incidental import (
    IncidentalsExtractor,
    LibraryCallGraphBuilder,
)
from src.preprocessor.relevance import (
    TypeRelevance,
    ClassScopeRelevance,
    CallScopeRelevance,
)
from src.preprocessor.information import InfoRepository
from src.preprocessor.complexity import ComplexityCalculator


@click.command(help="Preprocess the library to get necessary information.")
@click.option(
    "-L",
    "--library",
    "library_name",
    default=None,
    help="The name of the library for preprocess. You should have it configured in the libraries.toml. \
If the libraries.toml contains only one library, you can omit this option.",
    show_default=True,
)
@click.option(
    "--pool-size",
    "pool_size",
    help="The number of the process running.",
    default=cpu_count(),
    show_default=True,
)
def preprocess(
    library_name: str,
    pool_size: int,
):
    """
    PromeFuzz Preprocessor CLI
    """
    # setup the default configuration
    setup_default_config(library_name)

    # set some configurations
    APIExtractor.RUN_DUMMY_TEST = global_vars.config["preprocessor"][
        "run_dummydriver_test"
    ]
    ASTPreprocessor.POOL_SIZE = pool_size
    ConsumerCallGraphBuilder.POOL_SIZE = pool_size
    ConsumerCallGraphBuilder.BUILD_ARGS = global_vars.library_config[
        "consumer_build_args"
    ]
    LibraryCallGraphBuilder.POOL_SIZE = pool_size
    if (pre_bin := Path(global_vars.config["bin"]["preprocessor"])).is_file() and (
        cg_bin := Path(global_vars.config["bin"]["cgprocessor"])
    ).is_file():
        CXXASTPreprocessor.PROCESSOR_BIN = pre_bin
        ConsumerCallGraphBuilder.PROCESSOR_BIN = cg_bin
        LibraryCallGraphBuilder.PROCESSOR_BIN = cg_bin
    else:
        logger.critical(
            "The processor binary is not found, please run `setup.sh` first."
        )
        sys.exit(1)
    OrderSet.set_size_config(global_vars.config["generator"]["function_set_size"])
    DUMP_CSV = global_vars.config["preprocessor"]["dump_relevance_as_csv"]
    DUMP_CG = global_vars.config["preprocessor"]["dump_call_graph"]

    # create the output and tmp path
    out_path = Path(global_vars.library_config["output_path"]) / "preprocessor"
    out_path.mkdir(parents=True, exist_ok=True)
    tmp_path = Path(global_vars.library_config["output_path"]) / "tmp"
    tmp_path.mkdir(parents=True, exist_ok=True)

    # DO the AST preprocessing
    match global_vars.library_language:
        case global_vars.SupportedLanguages.C | global_vars.SupportedLanguages.CPP:
            preprocessor_class = CXXASTPreprocessor
        case global_vars.SupportedLanguages.RUST:
            preprocessor_class = RustASTPreprocessor
        case _:
            logger.critical(f"Unsupported language {global_vars.library_language}")
            sys.exit(1)
    ast_preprocessor = preprocessor_class.from_library_config(
        global_vars.library_config
    )
    meta = ast_preprocessor.run()
    meta.dump(out_path / "meta.json")

    # DO API extraction
    logger.info("Extracting the API functions.")
    api_extractor = APIExtractor.from_library_config(global_vars.library_config, meta)
    api = api_extractor.extract(pool_size=pool_size)
    api.dump(out_path / "api.pkl")
    api.dump_to_json(out_path / "api.json")
    logger.success(
        f"{api.count} API functions extracted, dumped to {out_path / 'api.pkl'}"
    )

    # dump source files and header files into json
    # They are used to determine whether a file in the backtrace is from the library
    # or not in later analysis process
    source_paths = ast_preprocessor.source_files + api_extractor.header_files
    with open(out_path / "sources.json", "w") as f:
        json.dump([str(_) for _ in source_paths], f, indent=4)
    logger.success(f"Source files dumped to {out_path / 'sources.json'}")

    # DO library call graph extraction
    logger.info("Extracting the library call graph.")
    library_cg_builder = LibraryCallGraphBuilder.from_ast_preprocessor(
        ast_preprocessor, api
    )
    library_cg = library_cg_builder.build_graph()
    if DUMP_CG:
        library_cg.dump_json(out_path / "library_call_graph.json")
        logger.success(
            f"Library call graph dumped to {out_path / 'library_call_graph.json'}"
        )

    incidentals_extractor = IncidentalsExtractor(library_cg)
    incidentals = incidentals_extractor.extract()
    incidentals.dump(out_path / "incidentals.pkl")
    incidentals.dump_json(out_path / "incidentals.json")
    logger.success(
        f"API incidental relationships extracted, dump to {out_path / 'incidentals.pkl'}"
    )

    # DO consumer call graph extraction
    if global_vars.library_config["consumer_case_paths"]:
        logger.info("Extracting the consumer call graph.")
        consumer_cg_builder = ConsumerCallGraphBuilder.from_library_config(
            global_vars.library_config, api, api_extractor.header_files
        )
        consumer_cg = consumer_cg_builder.build_graph()
        if DUMP_CG:
            consumer_cg.dump_json(out_path / "consumer_call_graph.json")
            logger.success(
                f"Consumer call graph dumped to {out_path / 'consumer_call_graph.json'}"
            )

        order_sets = consumer_cg_builder.compose_order_sets()
        order_sets.dump(out_path / "call_order.pkl")
        order_sets.dump_json(out_path / "call_order.json")
        logger.success(
            f"Consumer call order extracted, dumped to {out_path / 'call_order.pkl'}"
        )
    else:
        consumer_cg = None

    # DO info repository generation
    logger.info("Initializing the information repository.")
    info = InfoRepository(meta, api)
    info.dump(out_path / "info.pkl")
    info.dump_json(out_path / "info.json")
    logger.success(
        f"Information repository generated, dumped to {out_path / 'info.pkl'}"
    )

    # DO complexity calculation
    logger.info("Calculating the complexity of the API functions.")
    complexity_calculator = ComplexityCalculator(api, info, library_cg)
    complexity = complexity_calculator.calculate()
    complexity.dump(out_path / "complexity.pkl")
    if DUMP_CSV:
        complexity.dump_csv(out_path / "complexity.csv")
    logger.success(
        f"API complexity calculated, dumped to {out_path / 'complexity.pkl'}"
    )

    # DO relevance calculation
    logger.info("Calculating the relevance of the API functions.")
    type_relevance = TypeRelevance(api, meta)
    type_relevance.dump(out_path / "type_relev.pkl")
    if DUMP_CSV:
        type_relevance.dump_csv(out_path / "type_relev.csv")
    if global_vars.library_language == global_vars.SupportedLanguages.CPP:
        class_scope_relevance = ClassScopeRelevance(api, info)
        class_scope_relevance.dump(out_path / "class_scope_relev.pkl")
        if DUMP_CSV:
            class_scope_relevance.dump_csv(out_path / "class_scope_relev.csv")
    if consumer_cg:
        call_scope_relevance = CallScopeRelevance(api, consumer_cg)
        call_scope_relevance.dump(out_path / "call_scope_relev.pkl")
        if DUMP_CSV:
            call_scope_relevance.dump_csv(out_path / "call_scope_relev.csv")
    logger.success(f"API relevance calculated, dumped to {out_path}/*_relev.pkl")
