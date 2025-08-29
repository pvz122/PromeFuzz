from src.utils import setup_rag
from pathlib import Path
from loguru import logger
from src.comprehender.dockeeper import Knowledge

def run():
    rag = setup_rag("embed_qwen_remote", Path("out/test"))

    docs = Knowledge(
        document_paths=["https://pugixml.org/docs/manual.html"],
        rag=rag,
    )

    while True:
        query = input("Query: ")
        if query == "exit":
            break

        contents, locations = rag.retrieve(query, 4)
        i = 0
        for content, location in zip(contents, locations):
            i += 1
            logger.info(f"Result {i} of query \"{query}\" at location {location}:\n{content}")
