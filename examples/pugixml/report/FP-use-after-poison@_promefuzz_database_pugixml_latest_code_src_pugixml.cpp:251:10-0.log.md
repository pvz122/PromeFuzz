# Fuzz driver

```cpp
extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.first_child();
    if (!root) return 0;

    pugi::xml_node firstChild = root.first_child();
    if (!firstChild) return 0;

    std::string_view attrName1(reinterpret_cast<const char*>(Data), Size % 256);
    std::string_view attrName2(reinterpret_cast<const char*>(Data + Size % 256), Size % 256);
    std::string_view attrName3(reinterpret_cast<const char*>(Data + (Size % 256) * 2), Size % 256);

    pugi::xml_attribute attr1 = firstChild.attribute(attrName1.data());
    pugi::xml_attribute attr2 = firstChild.attribute(attrName2.data());
    pugi::xml_attribute attr3 = firstChild.attribute(attrName3.data());

    pugi::xml_attribute hint;
    pugi::xml_attribute attr4 = firstChild.attribute(attrName1, hint);
    pugi::xml_attribute attr5 = firstChild.attribute(attrName2, hint);
    pugi::xml_attribute attr6 = firstChild.attribute(attrName3, hint);

    if (attr1) attr1.set_name(attrName1);
    if (attr2) attr2.set_name(attrName2);
    if (attr3) attr3.set_name(attrName3);

    pugi::xml_attribute attr7 = firstChild.attribute(attrName1.data());
    pugi::xml_attribute attr8 = firstChild.attribute(attrName2.data());
    pugi::xml_attribute attr9 = firstChild.attribute(attrName3.data());

    return 0;
}
```

# Crash report

## Crash reason

AddressSanitizer: use-after-poison on address 0x7d363e9f68f3 at pc 0x5b6b0e33504e bp 0x7ffde4255550 sp 0x7ffde4254cf8

## Backtrace

```
READ of size 1 at 0x7d363e9f68f3 thread T0

#0 strcmp

#1 pugi::impl::(anonymous namespace)::strequal(char const*, char const*)
/promefuzz/database/pugixml/latest/code/src/pugixml.cpp:251:10
		return strcmp(src, dst) == 0;
         ^

#2 pugi::xml_node::attribute(char const*) const
/promefuzz/database/pugixml/latest/code/src/pugixml.cpp:5725:17
			if (iname && impl::strequal(name_, iname))
                ^

#3 LLVMFuzzerTestOneInput_35
/promefuzz/database/pugixml/latest/out/fuzz_driver/synthesized/35.cpp:48:44
    pugi::xml_attribute attr2 = firstChild.attribute(attrName2.data());
                                           ^


allocated by thread T0 here:

#0 malloc

#1 ExecuteFilesOnyByOne
/AFLplusplus/utils/aflpp_driver/aflpp_driver.c:222:41
  unsigned char *buf = (unsigned char *)malloc(MAX_FILE);
                                        ^
```

## Related source code

Part of the pugixml library that is relevant to the crash is as follows:

- `pugi::xml_node::attribute`:
```cpp
xml_attribute xml_node::attribute(const char_t* name_) const
	{
		if (!_root) return xml_attribute();

		for (xml_attribute_struct* i = _root->first_attribute; i; i = i->next_attribute)
		{
			const char_t* iname = i->name;
			if (iname && impl::strequal(name_, iname))
				return xml_attribute(i);
		}

		return xml_attribute();
	}
```

## Related data definitions

```cpp
namespace pugi {

struct xml_attribute_struct{

uintptr_t header;

char_t*	name;

xml_attribute_struct* prev_attribute_c;
// ... methods are omitted
};
// Character type used for all internal storage and operations; depends on PUGIXML_WCHAR_MODE
typedef PUGIXML_CHAR char_t;
}
```

# Analysis from LLM



The crash is a Misuse in fuzz driver, below is the explanation.

**Explanation:**

The crash occurs due to invalid memory access when constructing `attrName2` and `attrName3` in the fuzz driver. Specifically:

1. **Invalid Pointer Arithmetic**:  
   The code constructs `attrName2`/`attrName3` using `Data + Size % 256` and `Data + (Size % 256) * 2`, but these offsets may exceed the valid `Data` buffer of size `Size`. For example:
   - If `Size = 100`, `Size % 256 = 100`, so `Data + 100` and `Data + 200` point outside the `Data` buffer (size 100).

2. **Poisoned Memory Access**:  
   The `attrName2.data()`/`attrName3.data()` calls return pointers to invalid memory regions. When `xml_node::attribute()` passes these pointers to `strequal` (via `strcmp`), AddressSanitizer detects the out-of-bounds access as a **use-after-poison** error.

3. **Library Behavior**:  
   The pugixml library correctly validates parsed XML data but cannot protect against external invalid pointers passed to `attribute()`. The crash originates from the fuzz driver's unsafe construction of `attrName2`/`attrName3`, not a library bug.

**Conclusion**:  
The crash is caused by the fuzz driver creating `std::string_view` objects that reference memory outside the valid `Data` buffer. This violates memory safety and constitutes misuse of the library API.

# Reasoning Process

Okay, let's try to figure out why this crash is happening. The crash report mentions a use-after-poison error detected by AddressSanitizer. The backtrace points to strcmp being called in the strequal function, which is part of the xml_node::attribute method. The fuzz driver is doing several things: parsing XML data, accessing attributes, renaming them, and then accessing them again.

Looking at the fuzz driver code, the problem might be in how the attribute names are created. The driver creates three string_views: attrName1, attrName2, attrName3. Each is constructed using Data pointer with offsets based on Size % 256. But wait, if Size is small, adding (Size % 256)*2 to Data might go beyond the allocated buffer. For example, if Size is 300, Size % 256 is 44. So Data + 44*2 = Data + 88, which is within 300. But if Size is 100, then Size % 256 is 100, so Data + 100*2 = Data + 200, which exceeds the Size of 100. That would mean attrName3 is pointing to memory beyond the Data buffer, which is invalid. 

When creating attrName2 and attrName3, the code uses Data + Size % 256 and Data + (Size % 256)*2. If Size is less than 256*2, then Data + (Size % 256)*2 could be beyond the buffer. For example, if Size is 200, Size%256 is 200, so Data + 200*2 = Data + 400, which is way beyond the buffer size of 200. So those string_views would be pointing to invalid memory regions. 

When the code calls firstChild.attribute(attrName2.data()), it's passing a pointer that's outside the original Data buffer. If that memory isn't properly allocated, accessing it would cause undefined behavior. The AddressSanitizer detects this as a use-after-poison because the memory is poisoned (i.e., marked as invalid) when accessed via strcmp in strequal.

So the root cause is that the fuzz driver is creating string_views that reference memory outside the input Data buffer. This is a misuse of the library because the user (the fuzz driver) is providing invalid pointers to the attribute method, leading to undefined behavior. The library itself isn't at fault here; it's the way the test driver constructs the attribute names that's incorrect.
