# Fuzz driver

```c
int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy table list
    const char *tableList = "en-us-g2.ctb";

    // Prepare input buffer
    widechar *inbuf = (widechar *)Data;
    int inlen = Size / sizeof(widechar);

    // Prepare output buffer
    widechar outbuf[1024];
    int outlen = sizeof(outbuf) / sizeof(widechar);

    // Prepare typeform and spacing buffers with sufficient size
    formtype typeform[1024];
    char spacing[1024];

    // Initialize typeform and spacing
    for (int i = 0; i < 1024; i++) {
        typeform[i] = (formtype)Data[i % Size];
        spacing[i] = (char)Data[(i + 1) % Size];
    }

    // Fuzz lou_backTranslateString
    lou_backTranslateString(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, 0);

    // Fuzz lou_indexTables
    const char *tables[] = {tableList, NULL};
    lou_indexTables(tables);

    // Fuzz lou_checkTable
    lou_checkTable(tableList);

    // Fuzz lou_compileString
    char inString[Size + 1];
    memcpy(inString, Data, Size);
    inString[Size] = '\0';
    lou_compileString(tableList, inString);

    // Prepare additional parameters for lou_backTranslate
    int outputPos[1024];
    int inputPos[1024];
    int cursorPos = 0;

    // Fuzz lou_backTranslate
    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, 0);

    return 0;
}
```

# Crash report

## Crash reason

AddressSanitizer: stack-buffer-overflow on address 0x7f2a40e0b5e0 at pc 0x55c2b3e70449 bp 0x7ffe44a0a510 sp 0x7ffe44a09ce0

## Backtrace

```
WRITE of size 64856 at 0x7f2a40e0b5e0 thread T0

#0 __asan_memset

#1 _lou_backTranslate
/promefuzz/database/liblouis/latest/code/liblouis/lou_backTranslateString.c:222:51
		for (k = 0; k < input.length; k++) outputPos[k] = -1;
                                                  ^

#2 lou_backTranslate
/promefuzz/database/liblouis/latest/code/liblouis/lou_backTranslateString.c:153:9
	return _lou_backTranslate(tableList, tableList, inbuf, inlen, outbuf, outlen,
        ^

#3 LLVMFuzzerTestOneInput_22
/promefuzz/database/liblouis/latest/out/fuzz_driver/synthesized/22.c:63:5
    lou_backTranslate(tableList, inbuf, &inlen, outbuf, &outlen, typeform, spacing, outputPos, inputPos, &cursorPos, 0);
    ^
```

## Related source code

Part of the liblouis library that is relevant to the crash is as follows:

- `_lou_backTranslate`:
```c
// some code omitted...
			if ((mode & dotsIO))
				passbuf1[k] = inbuf[k] | LOU_DOTS;
			else
				passbuf1[k] = _lou_getDotsForChar(inbuf[k], displayTable);
		passbuf1[srcmax] = _lou_getDotsForChar(' ', displayTable);
		input = (InString){ .chars = passbuf1, .length = srcmax, .bufferIndex = idx };
	}
	idx = getStringBuffer(*outlen);
	output = (OutString){ .chars = stringBufferPool->buffers[idx],
		.maxlength = *outlen,
		.length = 0,
		.bufferIndex = idx };
	typebuf = (unsigned char *)typeform;
	spacebuf = spacing;
	if (outputPos != NULL)
		for (k = 0; k < input.length; k++) outputPos[k] = -1;
	if (cursorPos != NULL)
		cursorPosition = *cursorPos;
	else
		cursorPosition = -1;
	cursorStatus = 0;
	if (typebuf != NULL) memset(typebuf, '0', *outlen);
	if (spacebuf != NULL) memset(spacebuf, '*', *outlen);
	if (!(posMapping1 = _lou_allocMem(alloc_posMapping1, 0, input.length, *outlen)))
		return 0;
	if (table->numPasses > 1 || table->corrections) {
		if (!(posMapping2 = _lou_allocMem(alloc_posMapping2, 0, input.length, *outlen)))
			return 0;
		if (!(posMapping3 = _lou_allocMem(alloc_posMapping3, 0, input.length, *outlen)))
			return 0;
	}
// some code omitted...

```

- `lou_backTranslate`:
```c
int EXPORT_CALL
lou_backTranslate(const char *tableList, const widechar *inbuf, int *inlen,
		widechar *outbuf, int *outlen, formtype *typeform, char *spacing, int *outputPos,
		int *inputPos, int *cursorPos, int modex) {
	return _lou_backTranslate(tableList, tableList, inbuf, inlen, outbuf, outlen,
			typeform, spacing, outputPos, inputPos, cursorPos, modex, NULL, NULL);
}
```

## Related data definitions

```c
// clang-format on
typedef unsigned short formtype;
// clang-format interacts badly with @foo@
// clang-format off
typedef unsigned short int widechar;
```

# Analysis from LLM



The crash is a **Misuse in fuzz driver**, below is the explanation:

### Crash Type:
**Stack-buffer overflow** due to accessing `outputPos` beyond its allocated size.

---

### Root Cause Analysis:

1. **Crash Location**:  
   The overflow occurs in `_lou_backTranslate()` at line 222, where the loop writes `-1` into `outputPos[k]` for indices up to `input.length`.

2. **Buffer Dimensions**:
   - The fuzz driver declares a fixed-size buffer:  
     ```c
     int outputPos[1024]; // Max index is 1023 (size 1024)
     ```
   - The input length (`inlen`) is derived from `Size / sizeof(widechar)`. For inputs with `Size > 1024 * 2`, `inlen` exceeds `outputPos.length`.

3. **Violation**:
   When the fuzz test provides a large input (e.g., `Size = 3072`), `input.length` becomes `1536`. The loop iterates up to `k=1535`, which overflows `outputPos[1024]`.

---

### Why It's Misuse:
- **Library Expectation**:  
  `lou_backTranslate()` expects `outputPos` to be large enough for the input length. The documentation likely requires callers to validate buffer sizes, potentially by first calling a sizing function (e.g., with `NULL` buffers) before allocating.
  
- **Fuzz Driver Error**:  
  The fuzz driver statically allocates `outputPos[1024]`, which is insufficient for inputs larger than `1024 widechars`. This violates the library’s expected usage, making it a misuse of the API.

---

### Recommendation:
The fuzz driver should dynamically allocate buffers based on input size or use safeguards to enforce minimum buffer sizes. The crash does not indicate a bug in `liblouis` itself.

# Reasoning Process


Okay, let me try to work through this problem step by step. The user is asking about a crash in the liblouis library when running a fuzz test, and I need to determine if it's due to a bug in the library or misuse of the API in the fuzz driver.

First, looking at the crash report: It mentions a stack-buffer-overflow at address 0x7f2a40e0b5e0. The backtrace points to the _lou_backTranslate function in liblouis's code. Specifically, line 222 of lou_backTranslateString.c is where the write happens. That line loops over k from 0 to input.length and sets outputPos[k] to -1.

The fuzz driver calls lou_backTranslate with various parameters, including outputPos which is an array of integers initialized in the fuzz code as outputPos[1024]. The crash occurs when writing to outputPos[k], so maybe the loop's upper limit (input.length) exceeds 1024?

Looking at how input.length is determined. In the fuzz driver, inbuf is a pointer cast from Data (the input data), and inlen is Size divided by sizeof(widechar). The actual input length here could be up to whatever the fuzzer sends. Since it's a fuzz test, the input size might be arbitrary. But outputPos has fixed size 1024. So if input.length (inlen) exceeds 1024, then when the loop runs for k up to input.length, that would go beyond the array bounds of outputPos.

Wait, but in the fuzz driver's code, outputPos is declared as:

int outputPos[1024];

Similarly, the parameters passed into lou_backTranslate include this outputPos. The problem arises if the input length (input.length) from liblouis's side exceeds 1024. Let me check how input.length is set in the library code.

Looking at the _lou_backTranslate code:

The 'input' structure has a .length field which comes from "srcmax", which is *inlen passed in by the user (the fuzz driver). Wait, because when calling lou_backTranslate, the inbuf's length is pointed to by inlen. The fuzz driver initializes inlen as Size divided by sizeof(widechar). Since Data can be up to whatever size the fuzzer provides, if Size is large enough (e.g., larger than 1024*2?), then inlen would be bigger than 1024.

Wait, let me see: in the fuzz driver:

widechar *inbuf = (widechar *)Data;
int inlen = Size / sizeof(widechar);

So if Data has a size of more than 1024*sizeof(widechar), then inlen would be larger than 1024. For example, if Size is 2048 bytes (since widechar is two bytes?), then inlen is 2048/2=1024, exactly matching the outputPos size of 1024 elements? Wait but maybe even that's a problem because when looping up to input.length which would be inlen. Wait no, if input.length is equal to srcmax (the initial value?), then srcmax comes from *inlen before any processing?

Wait in the code for _lou_backTranslate:

input = (InString){ .chars = passbuf1, .length = srcmax, ... }

And earlier, I think 'srcmax' would be the original input length passed by the user. So if inlen is set to something larger than 1024, then input.length will be that value. Therefore when _lou_backTranslate does:

for (k=0; k < input.length; k++) outputPos[k] = -1;

if outputPos's size is only 1024 but the loop runs up to more than 1023, this would overflow.

So why is that happening? Because in the fuzz driver, outputPos is of fixed size 1024. However, if the input length (inlen) passed into lou_backTranslate is larger than 1024, then the loop would write beyond the buffer's capacity. 

The crash report says that the overflow was at address ... but in any case, the error seems to be that outputPos[k] is being written when k exceeds the array size.

Now why did this happen? The fuzz driver allocated a fixed-size outputPos of 1024 elements, which might not be sufficient if the input length (inlen) is larger. 

So the problem arises because the fuzzer provided an input where inbuf's length (inlen) exceeds 1024, but outputPos is only size 1024. Wait, actually:

Wait, outputPos has a maximum index of 1023 if it's size 1024. If inlen is exactly 1024, then the loop runs for k from 0 to 1023 (since input.length would be inlen). That's okay. But if inlen is more than that? For example, if Size is such that inlen is 2048, then in that case outputPos only has 1024 elements, but the loop will go up to 2047, which is way beyond.

Wait no: The fuzz driver's outbuf and outlen are initialized as:

widechar outbuf[1024];
int outlen = sizeof(outbuf) / sizeof(widechar); → 1024 elements. 

But in the call to lou_backTranslate, they pass *outlen which is a pointer to this variable. But when calling _lou_backTranslate, does that function modify outlen? Or perhaps the input length (inlen) is being set by the fuzzer's input data Size?

Wait, in the fuzz driver:

the inbuf is Data cast as widechar*, and inlen is Size divided by sizeof(widechar). Since the user can control Data and its size, this could be any value. So if the fuzzer provides a Data of 3072 bytes (for example), then inlen would be 1536.

Then when calling lou_backTranslate with outputPos which is an array of 1024 elements, the library code loops for k up to input.length (which is inlen=1536). So writing outputPos[1535] is way beyond the buffer's capacity of 1024. That would cause a stack overflow since it's on the stack as declared by the fuzz driver.

So why is this happening? Because the fuzz driver has not properly sized the output buffers to handle all possible inputs, especially during fuzz testing where inputs can be arbitrary and large. 

Now the question: Is this a bug in liblouis or misuse of the API?

The library's function lou_backTranslate requires that the caller provides an outputPos array (and others) of sufficient size. The documentation for these functions should specify how to determine required buffer sizes, perhaps by first calling another function with NULL pointers to get the needed lengths.

Alternatively, if liblouis allows the user to pass in buffers and expects them to be correctly sized based on input parameters, then it's up to the caller (the fuzz driver here) to ensure that. In this case, because the fuzz driver passes a fixed-size outputPos[1024], but when the input is larger than 1024 units, it causes an overflow in liblouis's code.

Therefore, the problem seems to be due to the fuzz driver not properly managing buffer sizes for these parameters. The library may expect that the caller ensures that all buffers (outputPos, etc.) are of sufficient size based on the input length and other factors. Hence, this is a misuse by the fuzzer rather than a bug in liblouis itself.

Wait but let me check: does the function's documentation state that outputPos must be at least as large as the input length? If so then the driver is at fault. The crash occurs when writing to outputPos[k], where k can go up to input.length (the user-provided inlen). So the library expects that the caller has allocated an array for outputPos of sufficient size.

Looking back at the code of lou_backTranslate: the function passes these parameters into _lou_backTranslate, which then uses them. The loop over k < input.length is part of liblouis's implementation, but it relies on the user having provided a large enough buffer. So if the user didn't, that's their fault.

Hence, this crash is due to the fuzz driver using buffers that are too small for some inputs. Therefore, it's misuse.
