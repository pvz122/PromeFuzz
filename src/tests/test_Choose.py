from src.utils import setup_llm
from src.comprehender.prompter import FuncRelevancePrompter
from src.generator.llm import Chat
import json
from pathlib import Path
import time

this_dir = Path(__file__).parent

def run():
    llm_client = setup_llm("qwen2_5_remote")
    library_name = "pugixml"
    library_purpose = "pugixml is a C++ XML processing library providing DOM-like interface, fast XML parsing and XPath 1.0 implementation for performance and easy data-driven queries."

    def query_relevant_functions(target_function_name, target_function_signature, candidate_function_signatures):
        prompter = FuncRelevancePrompter(Chat(llm_client))
        return prompter.prompt(library_name, library_purpose, target_function_name, target_function_signature, candidate_function_signatures)
    
    with open(this_dir / "pugixml_functions.json") as f:
        functions:dict = json.load(f)
    function_list = list(functions.items())[:32]

    target_function_name = "pugi::xml_node::select_node"
    target_function_signature = functions.pop(target_function_name)
    
    results = []
    # 30 functions a time
    start = time.time()
    for i in range(0, len(function_list), 30):
        candidate_function_signatures = dict(function_list[i:i+30])
        response = query_relevant_functions(target_function_name, target_function_signature, candidate_function_signatures)
        print("===Responses:")
        print(response)
        results.extend(response)
    elapsed = time.time() - start

    print(f"===Results in {elapsed:.2f}s")
    for r in results:
        print(r)