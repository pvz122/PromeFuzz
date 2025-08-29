from src.utils import setup_llm
from src.comprehender.prompter import FuncPurposePrompter
from src.generator.llm import Chat
import json
from pathlib import Path

this_dir = Path(__file__).parent

def run():
    llm_client = setup_llm("llama3_2_remote")
    library_name = "pugixml"
    library_purpose = "pugixml is a C++ XML processing library providing DOM-like interface, fast XML parsing and XPath 1.0 implementation for performance and easy data-driven queries."

    def query_purpose(function_name, function_signature):
        prompter = FuncPurposePrompter(Chat(llm_client))
        return prompter.prompt(library_name, library_purpose, function_name, function_signature)
    
    with open("out/pugixml/preprocessor/info.json") as f:
        info = json.load(f)

    results = {}
    for func_obj in info["function_infos"].values():
        name = func_obj["name"]
        signature = func_obj["signature"]
        purpose = query_purpose(name, signature)
        print(f"{name}:\n{purpose}\n")
        results[name] = purpose.strip() + "\n" + signature.strip()

    with open(this_dir / "pugixml_functions.json", "w") as f:
        json.dump(results, f, indent=2)