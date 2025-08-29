from src.utils import setup_llm
from src.comprehender.prompter import FuncExamplePrompter
from src.generator.llm import Chat
from pathlib import Path

this_dir = Path(__file__).parent


def run():
    llm_client = setup_llm("qwen2_5_remote")

    def query_example(library_name, function_name, function_signature, caller_code):
        prompter = FuncExamplePrompter(Chat(llm_client))
        example = prompter.prompt(
            library_name, function_name, function_signature, caller_code
        )
        print(example)

    library_name = "pugixml"
    function_name = "pugi::xml_node::append_attribute"
    function_signature = """// @name pugi::xml_node::append_attribute
// @brief Adds an attribute to a node by specifying its name, returning the newly created or updated attribute.
// Add attribute with specified name. Returns added attribute, or empty attribute on errors.
xml_attribute append_attribute(const char_t* name);
"""
    caller_code = """
	xml_node node = doc.child(STR("node"));

	node.append_attribute(STR("attr1")) = STR("v1");
	xml_attribute() = STR("v1");

	node.append_attribute(STR("attr2")) = -2147483647;
	node.append_attribute(STR("attr3")) = -2147483647 - 1;
	xml_attribute() = -2147483647 - 1;

	node.append_attribute(STR("attr4")) = 4294967295u;
	node.append_attribute(STR("attr5")) = 4294967294u;
	xml_attribute() = 4294967295u;

	node.append_attribute(STR("attr6")) = 0.5;
	xml_attribute() = 0.5;

	node.append_attribute(STR("attr7")) = 0.25f;
	xml_attribute() = 0.25f;

	node.append_attribute(STR("attr8")) = true;
	xml_attribute() = true;

	CHECK_NODE(node, STR("<node attr1=\"v1\" attr2=\"-2147483647\" attr3=\"-2147483648\" attr4=\"4294967295\" attr5=\"4294967294\" attr6=\"0.5\" attr7=\"0.25\" attr8=\"true\"/>"));
"""

    query_example(library_name, function_name, function_signature, caller_code)

    library_name = "cJSON"
    function_name = "cJSON_ParseWithLengthOpts"
    function_signature = """CJSON_PUBLIC(cJSON *) cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated);"""
    caller_code = """
    String* contentStr = melM_strFromObj(str->pack.obj);
    const char* contentData = melM_strDataFromObj(str->pack.obj);

    const char* errPtr = NULL;
    cJSON* json = cJSON_ParseWithLengthOpts(contentData, contentStr->len + 1, &errPtr, 1);

    if (json == NULL)
    {
        melM_stackPop(&vm->stack);
        melM_vstackPushNull(&vm->stack);
        return 1;
    }

    deserializeJson(vm, json);
    cJSON_Delete(json);

    return 1;
"""
    
    query_example(library_name, function_name, function_signature, caller_code)