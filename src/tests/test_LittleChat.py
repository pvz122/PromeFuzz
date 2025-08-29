from src.utils import setup_llm
from src.llm.llm import LLMChat, ReasoningLLMClient

# importing readline to enable arrow key navigation
import readline


def run():
    llm_client = setup_llm("gpt_41nano")
    chat = LLMChat(llm_client)
    while True:
        try:
            user_input = input("> ")
        except KeyboardInterrupt:
            break
        if isinstance(llm_client, ReasoningLLMClient):
            response, reasoning = chat.query_reasoning(user_input)
            print("\033[90m" + reasoning + "\033[0m\n" + response)
        else:
            response = chat.query(user_input)
            print(response)
