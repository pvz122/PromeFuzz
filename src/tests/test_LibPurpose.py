from src.comprehender.knowledge import Knowledge
from src.comprehender.comprehender import LibPurposeComprehender
from src.utils import setup_rag, setup_llm
from src import vars as global_vars
from loguru import logger
from pathlib import Path

def run():
    global_vars.library_name = "pugixml"

    llm = setup_llm("qwen_2_5_72b_remote")
    rag = setup_rag("embed_large", Path("out/test"))

    docs = Knowledge(
        document_paths=["https://pugixml.org/docs/manual.html"],
        rag=rag,
    )

    comp = LibPurposeComprehender(llm, docs)

    logger.success(comp.comprehension())