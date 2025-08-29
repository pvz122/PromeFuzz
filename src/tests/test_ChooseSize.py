from src.utils import setup_llm
from src.comprehender.prompter import FuncRelevancePrompter
from src.generator.llm import Chat
from loguru import logger
import json
from pathlib import Path
import time

this_dir = Path(__file__).parent

def run():
    llm_client = setup_llm("qwen2_5_remote")
    library_name = "pugixml"
    library_purpose = "pugixml is a C++ XML processing library providing DOM-like interface, fast XML parsing and XPath 1.0 implementation for performance and easy data-driven queries."

    def query_relevant_functions(target_function_signature, candidate_function_signatures):
        prompter = FuncRelevancePrompter(Chat(llm_client))
        return prompter.prompt(library_name, library_purpose, target_function_signature, candidate_function_signatures)
    
    with open(this_dir / "pugixml_functions.json") as f:
        functions:dict = json.load(f)

    target_function_name = "pugi::xml_node::select_node"
    target_function_signature = functions.pop(target_function_name)
    candidate_function_signatures = list(functions.values())[:32] # Only take 32 functions for testing
    
    def n_function_generator(n: int):
        for i in range(0, len(candidate_function_signatures), n):
            yield candidate_function_signatures[i:i+n]

    for batch_size in range(5, 30, 1):
        result = ""
        start_time = time.time()
        for candidate_function_signatures_batch in n_function_generator(batch_size):
            response = query_relevant_functions(target_function_signature, candidate_function_signatures_batch)
            print("===Responses:" + response)
            result += response + "\n"
        elapsed_time = time.time() - start_time
        result = result.replace("None\n", "").strip()
        print("===")
        print(f"Batch size: {batch_size}")
        print(f"Elapsed time: {elapsed_time:.2f}s")
        print("Result:\n", result)
        with open(this_dir / "batch_test.txt", "a") as f:
            f.write("===\n")
            f.write(f"Batch size: {batch_size}\n")
            f.write(f"Elapsed time: {elapsed_time:.2f}s\n")
            f.write(result + "\n")