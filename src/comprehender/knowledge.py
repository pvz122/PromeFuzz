"""
Get and retrieve library documents knowledge.
"""

from pathlib import Path
from loguru import logger
from urllib.parse import urlparse
from tqdm import tqdm
from typing import Callable

from src.utils import path_in_paths, setup_rag
from src.llm.rag import RAGRetriever, RAGExcerpt


class Knowledge:
    """
    Class to store knowledge, i.e. documents and their retriever.
    """

    # the number of document excerpts to retrieve each time
    RETRIEVE_TOP_K = 3

    def __init__(
        self,
        document_paths: list[str],
        rag: RAGRetriever,
        exclude_paths: list[Path] = [],
    ):
        """
        Initialize the knowledge with the document paths and the RAG retriever.

        :param document_paths: The paths or urls to the documents.
        :param rag: The initialized RAG retriever.
        :param exclude_paths: The paths to exclude from the document files.
        """
        # get the document files
        urls, docs = list(), list()
        for _p in document_paths:
            (urls if self._is_url(_p) else docs).append(_p)
        self.urls = urls
        self.doc_files = self._get_document_files(docs, exclude_paths)

        # load the documents
        self.rag = rag
        docs = self.doc_files + self.urls
        for doc in tqdm(
            docs,
            desc=f"Loading {len(docs)} documents",
            unit="doc",
            colour="MAGENTA",
            disable=(len(docs) <= 1),
            leave=False,
        ):
            if not self.rag.is_in_database(doc):
                try:
                    if isinstance(doc, Path):
                        self.rag.add_document(doc)
                    else:
                        self.rag.add_webpage(doc)
                except Exception as e:
                    logger.critical(f"Failed to load document {doc}: {e}")
                    exit(1)

    @classmethod
    def from_config(cls, config: dict, library_config: dict):
        """
        Initialize the knowledge from the configuration.

        :param config: The PromeFuzz configuration.
        :param library_config: The library configuration.
        """
        # load configs and setup RAG
        document_paths = library_config["document_paths"]
        exclude_paths = [Path(_) for _ in library_config["exclude_paths"]]
        database_path = (
            Path(library_config["output_path"]) / "comprehender" / "documents"
        )
        rag = setup_rag(config["comprehender"]["embedding_llm"], database_path)
        return cls(document_paths, rag, exclude_paths)

    @staticmethod
    def _is_url(s: str) -> bool:
        """
        Check if a string is a url.

        :param s: The string to check.
        :return: True if the string is a url, False otherwise.
        """
        try:
            result = urlparse(s)
            return all([result.scheme, result.netloc])
        except ValueError:
            return False

    def _get_document_files(
        self, document_paths: list[str], exclude_paths: list[Path]
    ) -> list[Path]:
        """
        Get the document files from the document paths.

        :param document_paths: The paths or urls to the documents.
        :param exclude_paths: The paths to exclude from the document files.
        :return: The document files.
        """
        # known doc extensions: .md/.txt/.html/.htm/.pdf/.adoc/.rst
        DOC_SUFFIX = [".md", ".txt", ".html", ".htm", ".pdf", ".adoc", ".rst"]
        DOC_KEYWORD = ["README", "readme", "USAGE", "usage"]
        is_doc_file: Callable[[Path], bool] = (
            lambda doc_file: doc_file.suffix in DOC_SUFFIX
            or any(keyword == doc_file.name for keyword in DOC_KEYWORD)
        )

        # get the document files
        doc_files: list[Path] = []
        for doc_path in document_paths:
            doc_path = Path(doc_path)
            if doc_path.is_file():
                doc_files.append(doc_path)
            elif doc_path.is_dir():
                doc_files.extend([_f for _f in doc_path.rglob("*") if is_doc_file(_f)])
            else:
                logger.warning(
                    f"Document path {doc_path} is not a file, directory, or url"
                )

        # remove excluded paths
        doc_files = [
            doc_file
            for doc_file in doc_files
            if not path_in_paths(doc_file, exclude_paths)
        ]

        logger.debug(
            f"Found {len(doc_files)} document files: {[str(doc_file) for doc_file in doc_files]}"
        )
        doc_files = [doc_file.resolve() for doc_file in doc_files]
        return doc_files

    def retrieve(self, query: str) -> list[RAGExcerpt]:
        """
        Wrapper for RAG retrieve, with configured top k.

        :param query: The query to retrieve documents.
        :return: The retrieved document excerpts.
        """
        return self.rag.retrieve(query, k=self.RETRIEVE_TOP_K)
