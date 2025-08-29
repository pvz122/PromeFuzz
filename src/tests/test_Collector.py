from src.generator.collector import CppInfoCollector, InfoRepository
from src.preprocessor.api import APICollection
from src.comprehender.comprehender import LibraryComprehension
from src.generator.scheduler import FunctionSet
from src.llm.prompter import Prompter

from pathlib import Path

def run():
    api_collection = APICollection.load(Path("out/pugixml/preprocessor/api.pkl"))
    info_repo = InfoRepository.load(Path("out/pugixml/preprocessor/info.pkl"))
    comprehension = LibraryComprehension.load(Path("out/pugixml/comprehender/comp.pkl"))
    collector = CppInfoCollector(info_repo, comprehension)

    targets = [
        "/promefuzz/library/pugixml/src/pugixml.cpp:7452:46",
        "/promefuzz/library/pugixml/src/pugixml.cpp:7503:34",
        "/promefuzz/library/pugixml/src/pugixml.cpp:5430:35",
        "/promefuzz/library/pugixml/src/pugixml.cpp:5486:35",
        "/promefuzz/library/pugixml/src/pugixml.hpp:621:47",
    ]

    function_set = FunctionSet(list())
    for t in targets:
        function_set.append(api_collection.get_by_location(t))
    print(function_set)

    gen_requirements = collector.collect(function_set)

    template = """
{INDEX}. `{FUNCTION_NAME}`
​    {FUNCTION_PURPOSE}
​    {FUNCTION_USAGE}
​    Its signature is:
​    ```cpp
{FUNCTION_SIGNATURE}
​    ```
    {EXPLANATION}

"""

    print("=== Target Functions ===")
    EXPLANATION = "You should invoke all {} overloads above for this function."
    function_str = "".join(
        template.format(
            INDEX=i,
            FUNCTION_NAME=func.name,
            FUNCTION_PURPOSE=func.purpose,
            FUNCTION_USAGE=func.usage if func.usage is not None else "",
            FUNCTION_SIGNATURE=Prompter.format_code(func.signature),
            EXPLANATION=(
                EXPLANATION.format(func.signature_count)
                if func.signature_count > 1
                else ""
            ),
        )
        for i, func in enumerate(gen_requirements.target_functions, start=1)
    )
    print(Prompter.economize_prompt(function_str))

    print("=== Data Definitions ===")
    print(Prompter.format_code(gen_requirements.data_definitions))
    
    print("=== Constructor Signatures ===")
    print(Prompter.format_code(gen_requirements.constructor_signatures))