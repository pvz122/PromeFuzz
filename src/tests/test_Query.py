from src.utils import setup_llm
from src.llm.llm import LLMChat
from pathlib import Path

def run(arg):
    content = Path(arg).read_text()

    llm_client = setup_llm("gpt_4o_mini")
    chat = LLMChat(llm_client)
    response = chat.query(content)
    print(response)
