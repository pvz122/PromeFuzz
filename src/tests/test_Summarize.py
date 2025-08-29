from src import vars as global_vars
from src.utils import setup_llm
from src.comprehender.prompter import LibPurposePrompter
from src.generator.llm import Chat

def get_top_100_lines(readme: str):
    lines = readme.split("\n")
    if len(lines) <= 100:
        return readme
    return "\n".join(lines[:100])

def run():
    llm_client = setup_llm("llama3_2_remote")
    
    # ===pugixml===
    prompter = LibPurposePrompter(Chat(llm_client))
    with open("/promefuzz/library/pugixml/README.md") as f:
        readme = get_top_100_lines(f.read())
    summary = prompter.prompt("pugixml", readme)
    print(summary)

    # ===cJSON===
    prompter = LibPurposePrompter(Chat(llm_client))
    with open("library/cJSON/README.md") as f:
        readme = get_top_100_lines(f.read())
    summary = prompter.prompt("cJSON", readme)
    print(summary)

    # ===racoon2===
    prompter = LibPurposePrompter(Chat(llm_client))
    with open("/promefuzz/library/racoon/racoon2/README.md") as f:
        readme = get_top_100_lines(f.read())
    summary = prompter.prompt("racoon2", readme)
    print(summary)