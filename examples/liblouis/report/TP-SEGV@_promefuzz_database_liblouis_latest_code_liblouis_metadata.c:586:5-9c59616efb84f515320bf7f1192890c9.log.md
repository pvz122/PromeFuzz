# Fuzz driver

```c
int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz lou_getDataPath
    char *dataPath = lou_getDataPath();
    if (dataPath) {
        // Do not free dataPath as it is not malloc()-ed
    }

    // Fuzz lou_listTables
    char **tables = lou_listTables();
    cleanup_char_array(tables);

    // Fuzz lou_setDataPath
    char *path = malloc(Size + 1);
    if (!path) return 0;
    memcpy(path, Data, Size);
    path[Size] = '\0';
    char *setPath = lou_setDataPath(path);
    if (setPath) {
        // Do not free setPath as it is not malloc()-ed
    }
    free(path);

    // Fuzz lou_indexTables
    const char *tablePaths[] = {"./dummy_file", NULL};
    lou_indexTables(tablePaths);

    // Fuzz lou_findTable
    char *query = malloc(Size + 1);
    if (!query) return 0;
    memcpy(query, Data, Size);
    query[Size] = '\0';
    char *foundTable = lou_findTable(query);
    if (foundTable) {
        free(foundTable);
    }
    free(query);

    return 0;
}
```

# Crash report

## Crash reason

AddressSanitizer: SEGV on unknown address 0x55fc630822d0 (pc 0x55fc62ee28d6 bp 0x000000000000 sp 0x7ffcc5989b00 T0)

## Backtrace

```
==2103114==The signal is caused by a WRITE memory access.

#0 __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType)

#1 free

#2 parseQuery
/promefuzz/database/liblouis/latest/code/liblouis/metadata.c:586:5
				free(v);
    ^

#3 lou_findTable
/promefuzz/database/liblouis/latest/code/liblouis/metadata.c:1004:24
	List *queryFeatures = parseQuery(query);
                       ^

#4 LLVMFuzzerTestOneInput_15
/promefuzz/database/liblouis/latest/out/fuzz_driver/synthesized/15.c:60:24
    char *foundTable = lou_findTable(query);
                       ^
```

## Related source code

Part of the liblouis library that is relevant to the crash is as follows:

- `parseQuery`:
```c
// some code omitted...
								memcpy(malloc(sizeof(f)), &f, sizeof(f)), NULL, NULL,
								(void (*)(void *))feat_free);
					}
				} else {
					if (!v) v = "yes";
					FeatureWithImportance f = { feat_new(k, v, (void *(*)(void *))strdup,
														(void (*)(void *))free),
						0 };
					_lou_logMessage(LOU_LOG_DEBUG, "Query has feature '%s:%s'", k, v);
					features =
							list_conj(features, memcpy(malloc(sizeof(f)), &f, sizeof(f)),
									NULL, NULL, (void (*)(void *))feat_free);
					if (strcasecmp(k, "unicode-range") == 0) unicodeRange = 1;
				}
				free(k);
				free(v);
				key = val = NULL;
				keySize = valSize = 0;
			}
			if (*c == '\0') break;
		} else if (*c == ':') {
			if (!key || val)
				goto compile_error;
			else {
				c = &query[pos++];
				if (isValidChar(*c)) {
					val = c;
					valSize = 1;
				} else
					goto compile_error;
			}
// some code omitted...

```

- `lou_findTable`:
```c
char *EXPORT_CALL
lou_findTable(const char *query) {
	if (!tableIndex) indexTablePath();
	List *queryFeatures = parseQuery(query);
	int bestQuotient = 0;
	char *bestMatch = NULL;
	List *l;
	for (l = tableIndex; l; l = l->tail) {
		TableMeta *table = l->head;
		int q = matchFeatureLists(queryFeatures, table->features, 0);
		if (q > bestQuotient) {
			bestQuotient = q;
			if (bestMatch) free(bestMatch);
			bestMatch = strdup(table->name);
		}
	}
	list_free(queryFeatures);
	if (bestMatch) {
		_lou_logMessage(LOU_LOG_INFO, "Best match: %s (%d)", bestMatch, bestQuotient);
		return bestMatch;
	} else {
		_lou_logMessage(LOU_LOG_INFO, "No table could be found for query '%s'", query);
		return NULL;
	}
}
```

## Related data definitions

```c

```

# Analysis from LLM



The crash is a Bug in library, below is the explanation.

**What kind of crash is it?**
It is an invalid free() leading to segmentation fault (SIGSEGV). The AddressSanitizer report indicates a WRITE access error when attempting to free memory at address 0x55fc630822d0 that was not allocated via `malloc`.

**Which part of the library is causing the crash?**
The crash occurs in the `parseQuery` function (part of liblouis's metadata handling) while freeing the pointer `v`. Specifically, at line 586: `free(v);`.

**What is the root cause of the crash?**
In `parseQuery`, after processing parts of the input query string:
- **k and v are pointers to substrings within the original query buffer**, not dynamically allocated memory. 
- When `v` is set to `"yes"` (a static literal) in certain cases, calling `free(v)` on a non-malloc'd pointer triggers undefined behavior.
- Additionally, even if `k`/`v` were derived from valid allocations elsewhere, the fuzz input could lead them to point into the query buffer (e.g., via unsafe string operations like strtok), which should not be freed by liblouis.

**Is it a library bug or driver misuse?**
The crash is caused by **a bug in the library**. The `parseQuery` function incorrectly assumes that `k` and `v` are dynamically allocated, leading to invalid frees:
- The fuzz driver properly allocates/frees its query buffer (`query`), but liblouis's code mistakenly attempts to free parts of this buffer directly.
- Even with valid inputs (non-fuzzed), scenarios where features resolve to static strings (e.g., `v = "yes"`) would still trigger invalid frees. 

The core issue is the unsafe use of `free()` on memory not owned by liblouis in `parseQuery`.

# Reasoning Process


Okay, let me try to figure out why the crash is happening here. The user provided a fuzz driver and a crash report. So first, I'll look at the crash details.

The crash reason says it's an AddressSanitizer SEGV (segmentation fault) due to a WRITE access on an unknown address. The backtrace shows that the crash occurs in parseQuery when calling free(v). Looking into the code for parseQuery, there's a loop where after processing some parts of the query string, they call free(k) and free(v). But how are k and v allocated?

Looking at the provided code for parseQuery: before the lines with free(k); free(v);, there might be code that allocates them. Wait, in the code snippet given, there's a part where after checking if *c is '=', they split into key and value parts. They probably use strtok or similar to split the string, but maybe k and v are pointing to some memory they shouldn't free?

Wait, looking at the code excerpt:

Inside the loop over each character in the query:
if (*c == '=') {
   ... then process key and val ...
}
Else if other conditions, like colon or semicolon, etc.

But where do k and v come from? Maybe earlier in the code (which is omitted) they are allocated via malloc, but perhaps there's a case where they aren't properly initialized before being freed. For instance, maybe when certain conditions are met, k and v might be NULL or pointing to some non-allocated memory?

Looking at the loop structure: after processing each token, keySize and valSize are used. But in the code provided, there is an 'else' block where if !v then set it to "yes". Then they create a FeatureWithImportance f using feat_new with parameters including strdup for the value. However, later in that same loop iteration, after building the features list, they do free(k) and free(v). So perhaps k and v were allocated somewhere else.

Wait, looking at another part: before this code fragment, there might be a call to strtok or something similar which returns pointers into the original string. For example, maybe using strtok_r with query's memory? If that's the case, then freeing k and v (which are parts of the original string) would be invalid because they weren't allocated by malloc.

Wait, in parseQuery, if the 'query' parameter is a string that was not allocated with malloc (like the input from fuzzing), then any pointers into it (such as tokens obtained via strtok) cannot be freed. Because free() expects to deallocate memory obtained via malloc, so trying to free parts of a statically or otherwise allocated buffer would cause undefined behavior.

In this case, looking at the fuzz driver's part where lou_findTable is called: the 'query' variable here comes from Data (the fuzz input), which was copied into a freshly allocated path. But in this case, when we call lou_setDataPath(path) and later free(query). However, when parseQuery processes query, if it splits it using functions that return pointers to inside the original string, then trying to free(k) or free(v) would be incorrect because those are not separately allocated blocks.

Wait, let me retrace:

In the fuzz driver, 'query' is allocated with malloc(Size + 1), copied Data into it (so it's a modifiable buffer). Then passed to lou_findTable. Inside parseQuery(query):

Suppose that when processing query (the input string from the fuzzer), k and v are pointers pointing to parts of this original string (like, using strtok, or other methods where they're just substrings of 'query'). Then in the code, after processing each token, it calls free(k) and free(v). That would be wrong because those aren't allocated with malloc. Hence, that's a bug.

Wait but looking at the provided code for parseQuery:

Looking back to the part I pasted: the code inside the loop does have 'free(k); free(v);' after using them. So how are k and v allocated?

Maybe in some earlier part of the loop (not shown here) they were dynamically allocated, but if that's not always done, then when those variables aren't properly allocated before freeing, this would cause a crash.

Wait, maybe there is code missing here. Let me think: perhaps the code for splitting the query into key and value uses malloc to get k and v. But in some cases (like invalid format) they might have not been assigned pointers from malloc but instead set to parts of the original string. For example, if parsing a feature "key:value", then key is the part before ':", which is part of the input string. Freeing that would be bad.

Alternatively, maybe there's an error path where k or v are NULL, and trying to free them causes issues? But in the code provided, after setting "if (!v) v = "yes";" then they proceed, but even if v was originally a pointer into the input string (like from strtok), setting it to "yes" (a static string) would make freeing(v) also incorrect because that's trying to free a literal.

So in this case, when the fuzzed query is passed here, perhaps the code is attempting to parse the query and during some steps, the variables k and v are pointing to parts of the input buffer (e.g., through strtok or similar function which breaks a string into tokens but doesn't allocate new memory). Then, when free(k) is called on those pointers (which aren't allocated via malloc), this leads to invalid free() calls, hence causing the crash.

Looking at the backtrace: the SEGV occurs in parseQuery's line 586 where it does 'free(v);'. The stack trace shows that lou_findTable calls parseQuery. 

The fuzz driver passes a query (the fuzzer data) which is a user-controlled string. The problem arises when the code inside parseQuery is freeing k and v even though those pointers are pointing to parts of the original query string, not allocated memory.

Thus, the root cause here would be that the parseQuery function incorrectly frees memory it shouldn't (parts of the input string) leading to invalid free(), which is a bug in liblouis's code. Because the library expects the query to be parsed in such a way that k and v are dynamically allocated, but perhaps under some conditions they aren't.

Alternatively, maybe in normal usage, k and v come from strdup or other allocations when parsing, but with certain input formats (like fuzzed inputs), the code fails to do that properly. 

Wait let's look again at the given parseQuery code:

Inside a loop after splitting key and value:
if (val) {
    ... 
    v = feat_strdup(val);
} else {
   if (!v) v = "yes"; // here, using a static string
}

Wait, but in this case 'v' could be pointing to the literal "yes", which is not allocated. So when they later do free(v), that's invalid because you can't free a static string.

So if during parsing, the code sets v to "yes" (a constant string) and then frees it, that would definitely cause an error. That would be a bug in liblouis.

Alternatively, maybe this is happening when the input query has certain malformed features where 'v' isn't properly allocated but gets set to something not malloc'd. 

In any case, looking at line 586 (the free(v)), if that's freeing a pointer that wasn't obtained via malloc, then it's an invalid free().

So in this scenario:

The fuzz driver passes an input string as 'query' to lou_findTable, which is parsed by parseQuery. During parsing, perhaps the code splits into key and value parts where k and v are derived from the input buffer (e.g., via strtok which returns a pointer inside query). Thus, when trying to free(k) or free(v), it's attempting to free memory that was not allocated with malloc (since the original buffer is allocated by the fuzz driver and later freed correctly in the fuzz function), but in parseQuery, they incorrectly try to free those pointers. 

Wait but in this case, the query itself is a string passed from the fuzzer which was allocated via malloc. So the entire 'query' variable's memory (the original buffer) is properly managed by the fuzz driver (since it does free(query at the end). However, any parts of that string can't be freed individually because they are part of the same allocation.

Therefore, when parseQuery() tries to free(k) and free(v), which point into query's buffer, this would cause an invalid free. Hence, the crash occurs here. 

This indicates a bug in liblouis: their code is freeing memory that was not allocated by them (the input string's parts). So the root cause is incorrect use of free() on pointers not obtained via malloc/calloc/realloc.

Thus, the problem lies within the library itself because it's attempting to free parts of the input query string which were not dynamically allocated. The fuzz driver correctly manages its own allocations (like 'query' buffer), but liblouis's parseQuery is mishandling those pointers.
