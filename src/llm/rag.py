"""
RAG (Retrieval Augmented Generation) module
"""

import json
import os
from loguru import logger
from pathlib import Path
from abc import ABC
from dataclasses import dataclass
from langchain_text_splitters import (
    RecursiveCharacterTextSplitter,
)
from langchain_community.embeddings import OllamaEmbeddings
from langchain_community.vectorstores.utils import filter_complex_metadata
from langchain_openai import OpenAIEmbeddings
from langchain_chroma import Chroma
from langchain_community.document_loaders import (
    TextLoader,
    UnstructuredMarkdownLoader,
    UnstructuredPDFLoader,
    UnstructuredHTMLLoader,
)
from chromadb import config as chromadb_config

# WebBaseLoader requires USER_AGENT environment variable to be set
os.environ["USER_AGENT"] = (
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.5359.125 Safari/537.36"
)
from langchain_community.document_loaders import WebBaseLoader


@dataclass
class RAGExcerpt:
    """
    Excerpt retrieved from the RAG retriever
    """

    content: str
    location: str


class RAGRetriever(ABC):
    """
    RAG retriever base class
    """

    def __init__(self):
        self.vector_store: Chroma = None
        self.database_path: Path = None
        self.document_list: list[str] = []

    def retriever(self, k: int = 3):
        """
        Get the retriever

        :param k: Number of nearest neighbors, default is 3
        :return: Retriever
        """
        return self.vector_store.as_retriever(
            search_type="similarity", search_kwargs={"k": k}
        )

    def retrieve(self, query: str, k: int = 3) -> list[RAGExcerpt]:
        """
        Retrieve documents

        :param query: Query string
        :param k: Number of nearest neighbors, default is 3
        :return: A list of retrieved excerpts
        """
        from src.utils import ProgressTitle

        with ProgressTitle(f"Querying RAG retriever with '{query}'..."):
            results = self.retriever(k).invoke(query)

        results = [
            RAGExcerpt(
                result.page_content,
                f"{result.metadata['source']}",
            )
            for result in results
        ]
        return results

    def retrieve_1(self, query: str) -> tuple[str, str]:
        """
        Retrieve a single document

        :param query: Query string
        :return: Retrieved excerpt
        """
        return self.retrieve(query, 1)[0]

    def add_document(self, document: Path):
        """
        Add a local document to the retriever

        :param document: Path to the document
        """
        if self.is_in_database(document):
            logger.warning(f"Document {document} already exists in the retriever")
            return

        from src.utils import ProgressTitle

        with ProgressTitle(f"Loading document {document}..."):
            # load the document
            if document.suffix == ".pdf":
                loader = UnstructuredPDFLoader(
                    str(document), mode="elements", strategy="fast"
                )
                docs = loader.load()
            elif document.suffix in [".html", ".htm"]:
                # unstructured requires `str`` while langchain could give `Path`
                loader = UnstructuredHTMLLoader(
                    str(document), mode="elements", strategy="fast"
                )
                docs = loader.load()
            # XXX: The UnstructuredMarkdownLoader just sucks. It will fragment the document into
            # XXX: many small pieces, which causes the RAG retriever to return many irrelevant results.
            # elif document.suffix == ".md":
            #     loader = UnstructuredMarkdownLoader(
            #         str(document), mode="elements", strategy="fast"
            #     )
            #     docs = loader.load()
            else:
                loader = TextLoader(document, autodetect_encoding=True)
                splitter = RecursiveCharacterTextSplitter(
                    chunk_size=1000, chunk_overlap=200, add_start_index=True
                )
                docs = loader.load_and_split(splitter)

            # refer to https://github.com/langchain-ai/langchain/issues/8556#issuecomment-1806835287
            # OllamaEmbeddings cannot deal with complex types, so only keep
            # `str, bool, int, float` here
            docs = filter_complex_metadata(docs)
            # add the docs to the vector store
            self.vector_store.add_documents(docs)

        self._add_to_document_list(document)

    def add_webpage(self, url: str):
        """
        Add a webpage to the retriever

        :param url: URL of the webpage
        """
        if self.is_in_database(url):
            logger.warning(f"Webpage {url} already exists in the retriever")
            return

        from src.utils import ProgressTitle

        with ProgressTitle(f"Loading webpage {url}..."):
            try:
                loader = WebBaseLoader(url, show_progress=True, raise_for_status=True)
            except Exception as e:
                raise Exception(f"Failed to load webpage {url}: {e}")

            splitter = RecursiveCharacterTextSplitter(
                chunk_size=1000, chunk_overlap=200, add_start_index=True
            )
            docs = loader.load_and_split(splitter)
            docs = filter_complex_metadata(docs)
            self.vector_store.add_documents(docs)

        self._add_to_document_list(url)

    def is_in_database(self, document: Path | str) -> bool:
        """
        Check if a document is in the database

        :param document: Path to the document or web URL
        :return: True if the document is in the database, False otherwise
        """
        return str(document) in self.document_list

    def _add_to_document_list(self, document: Path | str):
        """
        Add a document to the document list

        :param document: Path to the document or web URL
        """
        self.document_list.append(str(document))
        self._save_document_list()

    def _load_document_list(self):
        """
        Load the document list from the database path
        """
        if self.database_path:
            if (doc_list_path := self.database_path / "documents.json").exists():
                with open(doc_list_path, "r") as f:
                    self.document_list = json.load(f)
            else:
                self.document_list = []

    def _save_document_list(self):
        """
        Save the document list to the database path
        """
        if self.database_path:
            with open(self.database_path / "documents.json", "w") as f:
                json.dump(self.document_list, f, indent=4)


class OllamaRetriever(RAGRetriever):
    """
    Ollama RAG retriever
    """

    def __init__(
        self,
        host: str,
        port: int,
        model: str,
        max_tokens: int,
        database_path: Path = None,
    ):
        """
        Initialize the Ollama RAG retriever

        :param host: Hostname of the Ollama server
        :param port: Port of the Ollama server
        :param model: Embedding model to use
        :param max_tokens: Maximum tokens of the Ollama input
        :param database_path: Path to store the vector database, default is None
        """
        # XXX: The OllamaEmbeddings in langchain_community.embeddings is deprecated.
        # XXX  However, the new OllamaEmbeddings in langchain_ollama.embeddings is not implemented well yet.
        # XXX  To pass num_cyx and show_progress to the OllamaEmbeddings, we have to use the deprecated one.
        # XXX  So we suppress the DeprecationWarning here.
        import warnings

        warnings.filterwarnings("ignore", category=DeprecationWarning)

        embedding_client = OllamaEmbeddings(
            base_url=f"http://{host}:{port}",
            model=model,
            num_ctx=max_tokens if max_tokens != -1 else None,
            show_progress=True,
        )

        warnings.filterwarnings("default", category=DeprecationWarning)

        self.vector_store = Chroma(
            embedding_function=embedding_client,
            persist_directory=str(database_path.resolve()) if database_path else None,
            client_settings=chromadb_config.Settings(anonymized_telemetry=False),
            # XXX: Fuck Chroma DB, it uploads telemetry data without consent
        )

        # set the database path
        self.database_path = database_path
        self._load_document_list()


class OpenAIRetriever(RAGRetriever):
    """
    OpenAI RAG retriever
    """

    def __init__(
        self,
        base_url: str = "https://api.openai.com/v1",
        api_key: str = "",
        model: str = "text-embedding-ada-002",
        max_tokens: int = -1,
        database_path: Path = None,
    ):
        """
        Initialize the OpenAI RAG retriever

        :param base_url: Base URL of the OpenAI API
        :param api_key: OpenAI API key
        :param model: Model to use
        :param max_tokens: Maximum tokens of the OpenAI input
        :param database_path: Path to store the vector database, default is None
        :param database_name: Name of the vector database, default is "RAG"
        """
        # deal with default parameters
        max_tokens = max_tokens if max_tokens > 0 else 8191

        # initialize the OpenAI embeddings and vector store
        embedding_client = OpenAIEmbeddings(
            base_url=base_url,
            api_key=api_key,
            model=model,
            embedding_ctx_length=max_tokens,
            show_progress_bar=True,
        )
        self.vector_store = Chroma(
            embedding_function=embedding_client,
            persist_directory=str(database_path.resolve()) if database_path else None,
            client_settings=chromadb_config.Settings(anonymized_telemetry=False),
        )

        # set the database path
        self.database_path = database_path
        self._load_document_list()
