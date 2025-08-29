# Fuzz driver

```cpp
extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    int componentID = Data[0] % 3;
    int width = (Data[1] << 8) | Data[2];
    int height = (Data[3] << 8) | Data[4];
    int subsamp = Data[5] % 4;
    int align = Data[6] % 2;
    int pitch = (Data[7] << 8) | Data[8];
    int pixelFormat = Data[9] % TJ_NUMPF;
    int flags = 0;

    tjPlaneWidth(componentID, width, subsamp);
    tj3YUVPlaneHeight(componentID, height, subsamp);
    tjPlaneHeight(componentID, height, subsamp);
    tj3YUVPlaneWidth(componentID, width, subsamp);

    tjhandle handle = tjInitDecompress();
    if (handle) {
        unsigned char *srcBuf = (unsigned char *)malloc(Size);
        if (srcBuf) {
            memcpy(srcBuf, Data, Size);
            size_t dstBufSize = width * height * tjPixelSize[pixelFormat];
            if (dstBufSize > 0 && dstBufSize <= Size) {
                unsigned char *dstBuf = (unsigned char *)malloc(dstBufSize);
                if (dstBuf) {
                    tjDecodeYUV(handle, srcBuf, align, subsamp, dstBuf, width, pitch, height, pixelFormat, flags);
                    free(dstBuf);
                }
            }
            free(srcBuf);
        }
        tjDestroy(handle);
    }

    return 0;
}
```

# Crash report

## Crash reason

AddressSanitizer: SEGV on unknown address 0x50ff00680020 (pc 0x7f9bb3f9891e bp 0x7ffc88153910 sp 0x7ffc881530c8 T0)

## Backtrace

```
==2662190==The signal is caused by a WRITE memory access.

#0 __memcpy_evex_unaligned_erms

#1 __asan_memcpy

#2 jcopy_sample_rows
/promefuzz/database/libjpeg-turbo/latest/code/src/jutils.c:121:5
    memcpy(outptr, inptr, count);
    ^

#3 tj3DecodeYUVPlanes8
/promefuzz/database/libjpeg-turbo/latest/code/src/turbojpeg.c:2631:7
      jcopy_sample_rows(inbuf[i],
      ^

#4 tj3DecodeYUV8
/promefuzz/database/libjpeg-turbo/latest/code/src/turbojpeg.c:2717:10
  return tj3DecodeYUVPlanes8(handle, srcPlanes, strides, dstBuf, width, pitch,
         ^

#5 tjDecodeYUV
/promefuzz/database/libjpeg-turbo/latest/code/src/turbojpeg.c:2741:10
  return tj3DecodeYUV8(handle, srcBuf, align, dstBuf, width, pitch, height,
         ^

#6 LLVMFuzzerTestOneInput_21
/promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/synthesized/21.cpp:49:21
                    tjDecodeYUV(handle, srcBuf, align, subsamp, dstBuf, width, pitch, height, pixelFormat, flags);
                    ^
```

## Related source code

Part of the libjpeg-turbo library that is relevant to the crash is as follows:

- `tj3DecodeYUVPlanes8`:
```cpp
// some code omitted...
      inbuf[i][row] = ptr;
      ptr += (strides && strides[i] != 0) ? strides[i] : pw[i];
    }
  }

  if (setjmp(this->jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error. */
    retval = -1;  goto bailout;
  }

  for (row = 0; row < ph0; row += dinfo->max_v_samp_factor) {
    JDIMENSION inrow = 0, outrow = 0;

    for (i = 0, compptr = dinfo->comp_info; i < dinfo->num_components;
         i++, compptr++)
      jcopy_sample_rows(inbuf[i],
        row * compptr->v_samp_factor / dinfo->max_v_samp_factor, tmpbuf[i], 0,
        compptr->v_samp_factor, pw[i]);
    (dinfo->upsample->upsample) (dinfo, tmpbuf, &inrow,
                                 dinfo->max_v_samp_factor, &row_pointer[row],
                                 &outrow, dinfo->max_v_samp_factor);
  }
  jpeg_abort_decompress(dinfo);

bailout:
  if (dinfo->global_state > DSTATE_START) jpeg_abort_decompress(dinfo);
  free(row_pointer);
  for (i = 0; i < MAX_COMPONENTS; i++) {
    free(tmpbuf[i]);
    free(_tmpbuf[i]);
    free(inbuf[i]);
// some code omitted...

```

- `tjDecodeYUV`:
```cpp
int tjDecodeYUV(tjhandle handle, const unsigned char *srcBuf,
                          int align, int subsamp, unsigned char *dstBuf,
                          int width, int pitch, int height, int pixelFormat,
                          int flags)
{
  static const char FUNCTION_NAME[] = "tjDecodeYUV";
  int retval = -1;

  GET_TJINSTANCE(handle, -1);

  if (subsamp < 0 || subsamp >= TJ_NUMSAMP)
    THROW("Invalid argument");

  this->subsamp = subsamp;
  processFlags(handle, flags, DECOMPRESS);

  return tj3DecodeYUV8(handle, srcBuf, align, dstBuf, width, pitch, height,
                       pixelFormat);

bailout:
  return retval;
}
```

- `tj3DecodeYUV8`:
```cpp
// some code omitted...
    srcPlanes[1] = srcPlanes[2] = NULL;
  } else {
    int pw1 = tj3YUVPlaneWidth(1, width, this->subsamp);
    int ph1 = tj3YUVPlaneHeight(1, height, this->subsamp);

    strides[1] = strides[2] = PAD(pw1, align);
    if ((unsigned long long)strides[0] * (unsigned long long)ph0 >
        (unsigned long long)INT_MAX ||
        (unsigned long long)strides[1] * (unsigned long long)ph1 >
        (unsigned long long)INT_MAX)
      THROW("Image or row alignment is too large");
    srcPlanes[1] = srcPlanes[0] + strides[0] * ph0;
    srcPlanes[2] = srcPlanes[1] + strides[1] * ph1;
  }

  return tj3DecodeYUVPlanes8(handle, srcPlanes, strides, dstBuf, width, pitch,
                             height, pixelFormat);

bailout:
  return retval;
}

```

- `jcopy_sample_rows`:
```cpp
GLOBAL(void)
_jcopy_sample_rows(_JSAMPARRAY input_array, int source_row,
                   _JSAMPARRAY output_array, int dest_row, int num_rows,
                   JDIMENSION num_cols)
/* Copy some rows of samples from one place to another.
 * num_rows rows are copied from input_array[source_row++]
 * to output_array[dest_row++]; these areas may overlap for duplication.
 * The source and destination arrays must be at least as wide as num_cols.
 */
{
  register _JSAMPROW inptr, outptr;
  register size_t count = (size_t)(num_cols * sizeof(_JSAMPLE));
  register int row;

  input_array += source_row;
  output_array += dest_row;

  for (row = num_rows; row > 0; row--) {
    inptr = *input_array++;
    outptr = *output_array++;
    memcpy(outptr, inptr, count);
  }
}
```

## Related data definitions

```cpp
/**
 * TurboJPEG instance handle
 */
typedef void *tjhandle;
```

# Analysis from LLM

The crash is a Misuse in fuzz driver, below is the explanation.

**Explanation:**

The crash occurs due to an invalid memory write in `jcopy_sample_rows` during decompression. The root cause is the fuzz driver's incorrect calculation of the destination buffer size (`dstBufSize`). 

1. **Crash Analysis**:
   - The crash report shows a `SEGV` (segmentation fault) during a `memcpy` write operation in `jcopy_sample_rows`, indicating an attempt to write to an invalid memory address in the destination buffer (`tmpbuf` or `dstBuf`).

2. **Misuse in Fuzz Driver**:
   - The fuzz driver calculates `dstBufSize` as `width * height * tjPixelSize[pixelFormat]`. However, `tjDecodeYUV` uses the `pitch` parameter (passed directly from fuzzed input) to determine the row stride of the destination buffer. The correct required buffer size is **`pitch * height`**, not `width * tjPixelSize[pixelFormat] * height`.
   - If `pitch > width * tjPixelSize[pixelFormat]`, the allocated `dstBuf` is too small. During decompression, writing rows with the larger `pitch` value overflows the buffer, corrupting the heap and triggering the crash.

3. **Library Behavior**:
   - The libjpeg-turbo API expects the caller to ensure the destination buffer is sufficiently sized based on `pitch` and `height`. The library does not validate this internally, relying on correct parameters from the user.

**Conclusion**:
The crash is caused by the fuzz driver miscalculating the destination buffer size, leading to a heap buffer overflow during decompression. This is a misuse of the library API, not a bug in libjpeg-turbo itself. The fix requires using `pitch * height` for `dstBufSize` allocation.

# Reasoning Process

Okay, let's try to figure out why this crash is happening. The crash report says it's a SEGV due to a write memory access. The backtrace shows it's in jcopy_sample_rows, specifically during a memcpy call. The line in jutils.c:121 is memcpy(outptr, inptr, count). So the crash occurs when copying memory.

Looking at the fuzz driver code. The test input is being processed. They create a handle with tjInitDecompress, allocate srcBuf and dstBuf. Then they call tjDecodeYUV with parameters including srcBuf, align, subsamp, dstBuf, width, pitch, height, pixelFormat, flags.

In the crash backtrace, the error happens in tj3DecodeYUVPlanes8, which is called by tj3DecodeYUV8, then by tjDecodeYUV. The key part is the memcpy in jcopy_sample_rows. That suggests that either inptr or outptr is invalid, leading to an invalid memory access.

Looking at the relevant code in tj3DecodeYUVPlanes8. It calls jcopy_sample_rows with inbuf[i], row * compptr->v_samp_factor / dinfo->max_v_samp_factor, tmpbuf[i], 0, compptr->v_samp_factor, pw[i]. The memcpy copies count bytes, which is num_cols * sizeof(JSAMPLE). The problem could be that the rows or columns are miscalculated, leading to reading beyond the buffer.

Now, the fuzz driver. Let's check how they calculate parameters. The width is derived from Data[1] and Data[2], height from Data[3] and Data[4], subsamp from Data[5] mod 4. The pitch is Data[7] <<8 | Data[8]. Then they allocate dstBufSize as width * height * tjPixelSize[pixelFormat]. But if the calculated pitch is larger than the actual allocated buffer, that could cause an overflow.

Wait, when calling tjDecodeYUV, the pitch parameter is passed as 'pitch', which is the pitch of the destination buffer. The function expects that the pitch (bytes per row) is at least width * bytes per pixel. If the pitch passed is larger than the actual buffer's row size, then during decoding, writing each row could exceed the buffer's allocated memory. However, the dstBuf is allocated with size width * height * tjPixelSize[pixelFormat], which assumes that the pitch is exactly width * tjPixelSize[pixelFormat]. But the pitch is a parameter here. So if the user passes a pitch larger than width * tjPixelSize[pixelFormat], then each row's write would require pitch * height bytes, which could exceed the allocated dstBufSize. For example, if pitch is larger than width * tjPixelSize[pixelFormat], then the total required buffer size would be pitch * height, not width * height * tjPixelSize. If the fuzz driver calculates dstBufSize as width * height * tjPixelSize, but then uses a pitch that's larger, then when tjDecodeYUV writes each row with 'pitch' bytes, it could overflow the buffer.

Looking at the fuzz driver code: They calculate dstBufSize as width * height * tjPixelSize[pixelFormat]. Then allocate that. Then call tjDecodeYUV with 'pitch' as the parameter. But the pitch is (Data[7] <<8) | Data[8]. So if this pitch is larger than width * tjPixelSize[pixelFormat], then the destination buffer is too small. For example, if the pitch is 1000, but width * tjPixelSize is 500, then each row writes 1000 bytes, leading to a buffer overflow after a few rows.

In this case, the fuzz driver is not validating that the pitch is at least width * tjPixelSize[pixelFormat]. Instead, they just check that dstBufSize (which is width*height*tjPixelSize) is <= Size (the input data size). But that's not sufficient because the actual required buffer is pitch * height. So the problem is that the fuzz driver is using an incorrect calculation for the destination buffer size, leading to an undersized buffer. When tjDecodeYUV writes with the given pitch, it writes beyond the allocated dstBuf, causing a heap buffer overflow. The crash in memcpy would be when copying data into the destination buffer, which is overflown.

So the crash is due to the fuzz driver miscalculating the required buffer size for the destination buffer. The correct calculation should be pitch * height, not width * tjPixelSize. Therefore, the crash is a misuse in the fuzz driver because they didn't properly allocate the destination buffer based on the pitch and height. The library functions are expecting that the destination buffer is large enough to accommodate pitch * height bytes, but the fuzz driver's allocation is based on width * tjPixelSize * height, which can be smaller than needed if pitch is larger than width * tjPixelSize.

Additionally, looking at the code in tj3DecodeYUVPlanes8: The jcopy_sample_rows is copying data into tmpbuf, which might be part of the decompression process. However, the actual crash in memcpy is during writing to the output buffer. Wait, the backtrace shows that the crash is in jcopy_sample_rows called from tj3DecodeYUVPlanes8. The inbuf is the input planes, and tmpbuf is temporary buffers. Wait, maybe the input planes are not correctly set up. But the fuzz driver is using tjDecodeYUV which combines the YUV planes into a single buffer. Let me check the parameters for tjDecodeYUV. The function expects srcBuf to be a YUV image packed into a single buffer with the planes laid out according to the subsampling and alignment. The align parameter is used to compute strides. The library code (tj3DecodeYUV8) computes the strides based on the alignment and subsampling, then sets up srcPlanes pointers. If the align parameter is incorrect, the strides could be miscalculated, leading to reading beyond the allocated srcBuf. But in the crash, the problem is in jcopy_sample_rows, which is part of the decompression process. Wait, maybe the source buffer is too small. The fuzz driver copies Data into srcBuf, which is of size Size. But the required size for the YUV planes depends on subsamp, align, width, and height. If the srcBuf is not large enough to hold all the YUV planes, then accessing srcPlanes[0], [1], [2] would read beyond the buffer. Let's see. For example, if subsamp is 420, then the Y plane is full size, and the U and V planes are quarter size each. The strides would be calculated as aligned versions. The code in tj3DecodeYUV8 computes srcPlanes[1] as srcPlanes[0] + strides[0] * ph0, and srcPlanes[2] as srcPlanes[1] + strides[1] * ph1. The total required size for srcBuf would be the sum of the sizes of each plane. But the fuzz driver just uses Size (the input size) as the srcBuf size. So if the input data is not large enough to cover all the planes, then accessing srcPlanes[1] or [2] would read out of bounds. However, in the crash, the error is a WRITE access violation in memcpy. So the crash is during a write to outptr, which is part of the output buffer (dstBuf?), or perhaps the tmpbuf. Wait, jcopy_sample_rows is part of the decompression. Let me look at the code in tj3DecodeYUVPlanes8. The code sets up inbuf[i], which are pointers to the input planes. Then, during decompression, it copies sample rows from inbuf to tmpbuf. The memcpy in jcopy_sample_rows is copying from inbuf[i] to tmpbuf[i]. If inbuf[i] is pointing to invalid memory (e.g., beyond the srcBuf), then memcpy would read from an invalid address, causing a crash. However, the crash report says it's a WRITE memory access. Wait, the memcpy is from inptr (source) to outptr (destination). So the SEGV could be writing to outptr if the destination buffer is invalid, or reading from inptr if the source is invalid. The crash report says it's a WRITE, so the problem is in outptr, the destination. So the tmpbuf[i] in tj3DecodeYUVPlanes8 is allocated with free(tmpbuf[i]) at the end. How is tmpbuf allocated? In the code snippet for tj3DecodeYUVPlanes8, there's a loop where tmpbuf[i] and _tmpbuf[i] are freed. So during setup, tmpbuf[i] is allocated as some buffer. If tmpbuf[i] is not allocated properly (e.g., if the allocation size is wrong), then writing to it would cause a write to invalid memory. But why would tmpbuf[i] be invalid? Maybe the allocation is based on some miscalculated parameters. For example, if pw[i] (plane width) is calculated incorrectly, then the count in jcopy_sample_rows would be too large, leading to a buffer overflow in tmpbuf[i]. Alternatively, if the number of rows to copy is more than the allocated tmpbuf[i] can hold. How is tmpbuf allocated? Looking into the code, in tj3DecodeYUVPlanes8, before the crash point: It seems that tmpbuf is allocated as arrays of pointers. But the code for that isn't shown. However, the error occurs during the jcopy_sample_rows call. The parameters to jcopy_sample_rows are inbuf[i], row * compptr->v_samp_factor / dinfo->max_v_samp_factor (source_row), tmpbuf[i] (output_array), 0 (dest_row), compptr->v_samp_factor (num_rows), pw[i] (num_cols). So for each component, they are copying v_samp_factor rows from inbuf[i] to tmpbuf[i]. The count is pw[i] * sizeof(JSAMPLE). If tmpbuf[i] is allocated with insufficient space, then writing to tmpbuf[i][0] (the first row) would overflow. So how is tmpbuf allocated? In the code for tj3DecodeYUVPlanes8, before the loop, perhaps tmpbuf is allocated as a 2D array where each tmpbuf[i] has enough rows for the components. If the allocation is incorrect, then writing to tmpbuf[i] could cause a buffer overflow. Alternatively, the problem is in the input parameters. Let's think: The crash happens during the copying from inbuf to tmpbuf. The source is inbuf[i], which is part of the srcBuf passed to tjDecodeYUV. If the srcBuf is not large enough to contain all the YUV planes (given the align and subsamp parameters), then inbuf[i] could point beyond the allocated srcBuf, leading to a read overflow. However, in the fuzz driver, srcBuf is allocated as Size bytes, which is the same as the input data. But the required size for the YUV planes may be larger than Size. For example, when aligning the planes, the strides could require more bytes than available in srcBuf. The code in tj3DecodeYUV8 calculates the strides[0] as PAD(pw0, align), where pw0 is tj3YUVPlaneWidth(0, width, subsamp). Then strides[0] * ph0 (plane height) for Y plane, and similarly for U and V. The total required size for srcBuf would be the sum of strides[0] * ph0 + strides[1] * ph1 + strides[2] * ph1 (if subsamp is 4:2:0). But in the fuzz driver, srcBuf is allocated as Size bytes, which is the input size. The code checks if dstBufSize (width*height*tjPixelSize) is <= Size, but that's for the destination buffer, not the source. The problem here is that the source buffer's required size is determined by the YUV plane sizes, which depends on align, width, height, and subsamp. The fuzz driver doesn't check if the srcBuf (allocated to Size) is large enough for the YUV planes. If the input data (Size) is too small, then the code in tj3DecodeYUV8 would compute srcPlanes[1] and [2] as pointers beyond the allocated srcBuf, leading to accessing invalid memory when reading the U and V planes. However, in the crash backtrace, the error is in memcpy during a WRITE operation, which suggests that the destination buffer (tmpbuf[i]) is invalid. So maybe tmpbuf[i] is not allocated correctly. Let me check the code for tj3DecodeYUVPlanes8. In the code snippet provided, there's a loop that frees tmpbuf[i] and inbuf[i]. This suggests that these buffers are allocated earlier. Looking into the code, perhaps tmpbuf[i] is allocated with a size based on the component's width and samples. For example, if the component's width is larger than expected, tmpbuf[i] might be too small, leading to a write overflow. Alternatively, if the number of rows to copy (compptr->v_samp_factor) exceeds the allocated tmpbuf[i] rows. Let me think about the parameters. The code in tj3DecodeYUVPlanes8's jcopy_sample_rows is called with num_rows as compptr->v_samp_factor. The tmpbuf[i] is supposed to hold those rows. If tmpbuf[i] is allocated with enough rows, but not enough columns (num_cols is pw[i]), then the memcpy of count (pw[i] * sizeof(JSAMPLE)) bytes per row could overflow. So if tmpbuf[i] is allocated with a row length less than pw[i], then writing pw[i] elements would overflow. How is tmpbuf allocated? The code might allocate tmpbuf[i] as a buffer with enough space for each row. For example, in the code, perhaps tmpbuf[i] is allocated with a certain row stride. But if the allocation for tmpbuf is based on miscalculated parameters, then this could happen. However, given the information provided, it's hard to see exactly how tmpbuf is allocated. Alternatively, maybe the crash is due to the fuzz driver passing an invalid subsamp value, but subsamp is modulo 4, which should be valid. Let's recap. The fuzz driver passes subsamp as Data[5] %4, which is 0-3, corresponding to TJ_SAMP_444, 422, 420, etc. So that's okay. The align parameter is Data[6]%2 (0 or 1). The pitch is (Data[7]<<8) | Data[8], which can be up to 65535. The problem is that in the fuzz driver, they allocate dstBuf as width * height * tjPixelSize[pixelFormat], but the pitch passed to tjDecodeYUV could be larger than width * tjPixelSize. The tjDecodeYUV function uses the pitch parameter as the row stride for the destination buffer. If the allocated dstBuf is only width * tjPixelSize * height bytes, but the actual required size is pitch * height, then writing each row (with pitch bytes) would overflow the buffer. This would lead to a heap buffer overflow when writing to dstBuf. However, the crash backtrace shows that the error is in jcopy_sample_rows, which is part of the decompression process, copying from the input planes to tmpbuf. Wait, but that's part of processing the input YUV data. So the crash might not be in the destination buffer, but in processing the input. Let me check tj3DecodeYUVPlanes8 again. The code sets up srcPlanes, which are pointers into the srcBuf. The strides for each plane are computed based on alignment and plane dimensions. If the computed strides require more data than available in srcBuf, then accessing the planes (srcPlanes[1], srcPlanes[2]) would read beyond srcBuf. But the crash is in a write to tmpbuf. Alternatively, the tmpbuf is being written to, but tmpbuf's allocation is wrong. For example, if tmpbuf[i] is allocated with a row size of pw[i], but the code tries to copy more data than that. How is tmpbuf allocated? The code snippet in tj3DecodeYUVPlanes8 shows that tmpbuf[i] is freed, so they must have been allocated earlier. Let's suppose tmpbuf is allocated with rows based on compptr->v_samp_factor. But if the code is trying to copy compptr->v_samp_factor rows into tmpbuf[i], which might not have enough space. However, the exact allocation code is not provided. Given the backtrace, the crash is in the memcpy(outptr, inptr, count), where outptr is from tmpbuf[i]. If tmpbuf[i] is not allocated with enough space for the count (num_cols = pw[i]), then writing to outptr would overflow. For example, if tmpbuf[i] is allocated with rows of size less than pw[i], then memcpy would write beyond the allocated buffer. This would be a library bug if the allocation is incorrect. But how is tmpbuf allocated? Let me think: The code in tj3DecodeYUVPlanes8 probably allocates tmpbuf[i] as a buffer that can hold compptr->v_samp_factor rows of pw[i] samples. If that's not the case, then there's a bug. But how would that happen? For example, if the component's width (pw[i]) is miscalculated. Wait, the component ID is passed as part of the function. In tjPlaneWidth and tj3YUVPlaneWidth calls in the fuzz driver, componentID is Data[0]%3. Component IDs in YUV are 0 (Y), 1 (U), 2 (V). But for 4:2:0 subsampling, the U and V planes are smaller. The tj3YUVPlaneWidth function should return the correct width for the plane based on component ID. If the componentID is passed as 3 (but in the fuzz driver, it's Data[0]%3, so 0-2, which is valid), then the code should handle it. But in the fuzz driver, before calling tjDecodeYUV, they call tjPlaneWidth and similar functions. Maybe this is irrelevant. The key issue is that in the crash, during decompression, the code is trying to write to tmpbuf[i], which is not properly allocated, leading to a buffer overflow. If the library code correctly allocates tmpbuf[i] based on the component parameters, then this shouldn't happen. But if there's a miscalculation in the component parameters (like width, subsamp), leading to a larger pw[i] than expected, then tmpbuf[i] would be too small, leading to overflow. Alternatively, if the subsamp parameter is invalid. But the fuzz driver passes subsamp as Data[5]%4, which is valid (0-3). The tjDecodeYUV function checks if subsamp is within TJ_NUMSAMP (which is 4), so that's okay. Therefore, if the crash is due to the tmpbuf[i] being too small, then it's a library bug. But how could that happen? Let's think about the code flow. When tj3DecodeYUVPlanes8 is called, it sets up the decompression parameters based on the input parameters. For each component, it calculates pw[i] (plane width) and ph[i] (plane height). Then, during decompression, it copies rows from the input planes (srcPlanes) into tmpbuf[i], which is a buffer for processing. The jcopy_sample_rows copies compptr->v_samp_factor rows from the input to tmpbuf. The memcpy copies count = pw[i] * sizeof(JSAMPLE) bytes for each row. If tmpbuf[i] is allocated to have rows of exactly pw[i] elements, then this is safe. But if for some reason, the actual pw[i] is larger than the allocated tmpbuf's row size, then the memcpy would write beyond the buffer. Why would that happen? Maybe due to incorrect calculation of pw[i] in the library. For example, if tj3YUVPlaneWidth returns a larger value than expected. Wait, the fuzz driver calculates pitch as (Data[7] <<8) | Data[8], which is arbitrary. But in tj3DecodeYUV8, when processing the YUV planes, the code calculates strides for each plane. For example, for component 0 (Y plane), the stride is PAD(pw0, align). If align is 0 or 1, PAD might be adding alignment. But the calculation of pw0 (plane width) is done using tj3YUVPlaneWidth(componentID, width, subsamp). If this function returns a width that, when multiplied by the v_samp_factor, exceeds some internal buffer size, it could cause an overflow. Alternatively, the problem could be in the way the library handles the align parameter. For example, if align is 1, which makes the stride for the Y plane to be PAD(pw0, 1), which would be pw0. Then the srcPlanes[1] would be srcPlanes[0] + (strides[0] * ph0). If ph0 is the plane height, which is calculated as tj3YUVPlaneHeight(0, height, subsamp). If the total required size for the Y, U, V planes exceeds the allocated srcBuf (which is Size), then srcPlanes[1] and [2] could point beyond srcBuf, leading to reading invalid data. However, the crash is a WRITE in jcopy_sample_rows, which suggests that the destination buffer (tmpbuf) is the problem. But maybe the invalid read from srcBuf (due to srcPlanes[i] pointing beyond srcBuf) would cause a crash. Wait, but the crash report says the signal is caused by a WRITE. So the invalid memory access is writing to a bad address. So the problem is with the destination buffer of the memcpy (outptr). Which is in tmpbuf[i]. Therefore, the tmpbuf[i] buffer is either not allocated or allocated with insufficient size. Why would that happen? The library should be allocating tmpbuf[i] with sufficient size based on the component's parameters. If there's a bug in the library where tmpbuf[i] is not allocated properly, then that's a library bug. Alternatively, if the parameters passed to the library (width, height, subsamp, align) are invalid, leading to incorrect calculations. For example, if width is 0, but the fuzz driver checks if width is derived from Data[1] and Data[2], which could be zero if Data[1] and Data[2] are zero. Wait, in the fuzz driver, the code has: if (Size < 10) return 0; So they require at least 10 bytes. Then componentID is Data[0] mod 3, which is okay. width is (Data[1]<<8) | Data[2], which could be up to 65535. Similarly, height could be up to 65535. But if width or height is zero, then in tj3YUVPlaneWidth, for component 0, subsamp could be 420, which for Y plane, plane width is the same as image width. If width is zero, tj3YUVPlaneWidth(0, 0, subsamp) would return zero. Then pw0 would be zero. In the code in tj3DecodeYUVPlanes8, during the jcopy_sample_rows call, count would be zero. But memcpy with count zero is harmless. However, if width or height is zero, the code might proceed with invalid parameters, leading to division by zero or other issues. But the fuzz driver does not check that width and height are positive. However, the crash is occurring during a memcpy with a count that's possibly large. For example, if width is very large, then pw[i] (plane width) could be large, leading to a large count in memcpy. But tmpbuf[i] is allocated with that size. If the allocation is not done correctly, then memcpy would write out of bounds. But why would that be a library bug? The library should handle all possible valid parameters. However, if the parameters passed are invalid (e.g., width or height too large), leading to an integer overflow during buffer allocation, that could cause tmpbuf[i] to be allocated with insufficient size. For example, if pw[i] is very large, then count = pw[i] * sizeof(JSAMPLE) could be a large value, but if the tmpbuf[i] allocation uses an int type which overflows, the allocated buffer would be smaller than needed. In such a case, the memcpy would overflow the buffer. However, the code in the library should check for integer overflows during buffer size calculations. Looking at the code in tj3DecodeYUV8: There's a check for whether strides[0] * ph0 exceeds INT_MAX. If so, it throws an error. So that's checked. But if the tmpbuf[i] allocation is done with a size based on pw[i] * v_samp_factor, and if pw[i] is very large, the allocation could fail or be truncated. For example, if tmpbuf[i] is allocated as malloc(pw[i] * v_samp_factor * sizeof(JSAMPLE)), and pw[i] is very large, this could lead to a buffer that's too small. But in that case, the malloc would return NULL, and using it would crash. However, in the code, after allocating tmpbuf[i], is there a check? The code in tj3DecodeYUVPlanes8's bailout section frees tmpbuf[i], which suggests that it's allocated with malloc. But if malloc fails (returns NULL), then writing to tmpbuf[i] would cause a crash. However, the fuzz driver is using Data as input, and the parameters (width, height, etc.) could be such that the required allocations are too large, leading to malloc failures. For example, if width and height are 65535, then tj3YUVPlaneWidth(0, 65535, subsamp) would return 65535. Then the plane width for Y is 65535. The tmpbuf[i] for component 0 would need to hold v_samp_factor rows of 65535 elements. If v_samp_factor is 2 (e.g., for 4:2:2), then 2*65535 * sizeof(JSAMPLE) would be 131070 bytes. Which is possible, but if the system can't allocate that, then tmpbuf[i] would be NULL, and memcpy would crash. However, the crash report mentions AddressSanitizer, which would detect a write to a null pointer (which would be address 0x0 or similar). But the crash address here is 0x50ff00680020, which is not near NULL. So that's not the case. So the problem is likely elsewhere. Another possibility is that the componentID is invalid in some context. But the fuzz driver uses componentID = Data[0] mod 3, which is 0,1,2. However, in the calls to tjPlaneWidth, tj3YUVPlaneHeight, etc., the componentID is passed. Those functions may expect componentID to be 0,1,2 for Y, U, V planes. So if componentID is 3, which is possible if Data[0] is 3 mod 3, but componentID is mod 3, so 0-2. So that's okay. Let's think again about the parameters passed to tjDecodeYUV. The subsamp is determined by Data[5] mod4. So valid. The align is 0 or 1. The width and height are arbitrary (up to 65535). The pitch is also arbitrary (up to 65535). The pixelFormat is Data[9] mod TJ_NUMPF. So that's valid. The problem is likely in the fuzz driver's allocation of srcBuf and/or dstBuf. Let me check: srcBuf is allocated as Size bytes, which is the input data size. However, the required size for srcBuf depends on the YUV planes. The code in tj3DecodeYUV8 calculates the required size for the YUV planes as strides[0] * ph0 + strides[1] * ph1 + strides[2] * ph1. If this sum is larger than Size (the input data size), then srcPlanes[1] and [2] would point beyond srcBuf, leading to reading invalid data when accessing those planes. However, in the crash, the memcpy is writing to tmpbuf[i], which is part of the decompression process. So maybe during the decompression, the code reads invalid data from srcBuf, which could cause the decompressor to generate invalid parameters, leading to incorrect tmpbuf allocations. For example, if the YUV planes in srcBuf are corrupt, the decompressor might set compptr->v_samp_factor to a larger value than expected, leading to tmpbuf[i] being allocated with insufficient rows. But this is speculative. Alternatively, the problem is in the pitch parameter. The fuzz driver passes pitch as (Data[7] <<8) | Data[8], which can be up to 65535. The tjDecodeYUV function uses this pitch as the destination buffer's row stride. The destination buffer's required size is pitch * height. But the fuzz driver allocates dstBuf as width * height * tjPixelSize[pixelFormat]. If pitch is larger than width * tjPixelSize, then the allocated dstBuf is too small, leading to a heap buffer overflow during decompression when writing each row. This would explain a write to an invalid address (the dstBuf's allocated memory plus pitch * row exceeds the allocation). The crash backtrace shows the memcpy in jcopy_sample_rows is part of the decompression process, writing to tmpbuf, which is part of processing the YUV data. But if the problem is in the destination buffer (dstBuf), then the crash would be during the final write to dstBuf, not during the processing of YUV planes. So maybe the issue is not with dstBuf. The crash is in jcopy_sample_rows, which is part of the decompression process, handling the input planes. Therefore, the problem is more likely with the source buffer (srcBuf) being too small, leading to reading invalid data which then causes invalid parameters during decompression. But how does that lead to a write to an invalid address in jcopy_sample_rows? Let's imagine that in the source YUV data, the code reads corrupted parameters, leading to compptr->v_samp_factor being invalid. For example, if the v_samp_factor is very large, then num_rows passed to jcopy_sample_rows is very large, leading to copying more rows than tmpbuf[i] can hold. But tmpbuf[i] is allocated based on the components' parameters. Alternatively, if the component's width (pw[i]) is very large, then the count (num_cols * sizeof(JSAMPLE)) is very large, leading to a buffer overflow in tmpbuf[i]. In either case, if the library fails to validate these parameters correctly and allocates tmpbuf[i] with insufficient size, that's a library bug. However, the parameters passed to the library (width, height, subsamp, etc.) are controlled by the fuzz driver. If the fuzz driver passes invalid parameters that the library does not properly validate, leading to incorrect buffer allocations, then it's a library bug. For example, if the library allows width or height to be zero, leading to division by zero or other errors. But the fuzz driver allows width and height to be zero (since it's derived from Data[1-4]). However, the tj3YUVPlaneWidth and tj3YUVPlaneHeight functions likely handle zero width/height by returning zero. But if the code then proceeds to allocate buffers of zero size, and then tries to copy data into them, that could lead to undefined behavior. However, memcpy with count zero is allowed and a no-op. So that's probably not the case. Let me look at the jcopy_sample_rows function. The parameters are num_rows and num_cols. If num_cols is zero, count is zero. So no problem. If num_rows is zero, the loop doesn't run. So the crash must be when count is non-zero and either inptr or outptr is invalid. The crash report says it's a write to 0x50ff00680020, which is in outptr. So outptr is a bad pointer. outptr is *output_array++, where output_array is tmpbuf[i] + dest_row. So tmpbuf[i] must be an array of pointers to rows. Each tmpbuf[i][row] is a pointer to the row's data. If tmpbuf[i] is not allocated correctly, then *output_array could be an invalid pointer. How is tmpbuf[i] allocated? In the code snippet provided, tmpbuf[i] is allocated with free(tmpbuf[i]) in the bailout section, which implies that tmpbuf[i] is a pointer to a buffer. But looking at the jcopy_sample_rows call: output_array is tmpbuf[i], and dest_row is 0. So output_array += dest_row is tmpbuf[i] + 0, so output_array starts at tmpbuf[i]. Then, for each row, outptr = *output_array++. So tmpbuf[i] is expected to be an array of pointers to rows. If tmpbuf[i] is not allocated properly (e.g., not enough pointers), then *output_array could be invalid. For example, if tmpbuf[i] is allocated with only 1 row pointer, but num_rows is compptr->v_samp_factor, which is 2, then accessing the second row would read an invalid pointer. But how is tmpbuf[i] allocated? The code snippet in tj3DecodeYUVPlanes8 shows that tmpbuf[i] is allocated as a 2D array. Possibly, tmpbuf[i] is allocated with compptr->v_samp_factor rows. For example, if v_samp_factor is 2, tmpbuf[i] is an array of 2 pointers, each pointing to a row of pw[i] samples. If tmpbuf[i] is allocated with enough row pointers, but in the jcopy_sample_rows call, the num_rows is compptr->v_samp_factor, which matches the allocation. But if, due to some error, tmpbuf[i] has fewer row pointers than needed, then *output_array++ would access beyond the allocated array. For example, if tmpbuf[i] is allocated for 2 rows, but num_rows is 3, then the third iteration would read an invalid pointer. This could cause the outptr to be invalid. This would be a library bug if the code allocates tmpbuf[i] with insufficient rows. But why would that happen? For example, if compptr->v_samp_factor is larger than the maximum expected value. The library code should correctly handle the components' v_samp_factor. For standard subsampling values (like 420, 422, 444), the v_samp_factor for each component is either 1 or 2. For example, in 4:2:0, the Y component has v_samp_factor 2, and the U and V components have v_samp_factor 1. If the subsamp parameter is invalid or if the component's v_samp_factor is corrupted, this could lead to tmpbuf[i] being allocated with fewer rows than needed. But in the fuzz driver, subsamp is mod4, which is valid. Therefore, this suggests that the library is not properly handling certain combinations of parameters, leading to incorrect allocation of tmpbuf[i]. But without seeing the exact allocation code for tmpbuf[i], it's hard to say. However, considering the information available, the crash occurs in the library's code during the processing of valid parameters (as per the fuzz driver's setup), implying a library bug. Alternatively, the fuzz driver is passing invalid parameters that the library fails to check, leading to an error. For example, the fuzz driver does not check if width and height are positive. If width or height is zero, then during decompression, the code may divide by zero or calculate invalid plane sizes. But in the tj3YUVPlaneWidth and tj3YUVPlaneHeight functions, passing zero width/height would result in zero, leading to zero-sized planes. However, if the code proceeds to allocate zero-sized buffers and then write to them, that could cause issues. But memcpy with count zero is allowed. So that's probably not the case. Another possibility is that the align parameter is being misused. The align parameter is Data[6]%2, which is 0 or 1. The code in tj3DecodeYUV8 calculates strides as PAD(pw, align). The PAD macro (probably) adds padding to meet alignment. For example, PAD(pw, align) could be ((pw + align) & ~align), but if align is 0 or 1, then for align=0, it's pw, and align=1, it's pw rounded up to the next even number. If this calculation is incorrect, then the strides could be larger than necessary, leading to srcPlanes[1] or [2] pointing beyond the allocated srcBuf. But the fuzz driver uses the input data's size (Size) for srcBuf, which may not be sufficient. For example, if the required strides for the Y, U, V planes exceed Size, then the code would read beyond srcBuf. However, in the crash, the memcpy is writing to tmpbuf[i], so the invalid read from srcBuf may not directly cause this. But if the data read from srcBuf is used to calculate parameters that influence tmpbuf[i]'s allocation, it could indirectly cause the crash. For example, if the Y plane's data indicates a larger component width or height than expected, leading to incorrect allocations. But the fuzz driver uses the same srcBuf for the YUV data as the input data, which may not be a valid YUV image. This could corrupt the decompression parameters. However, the tjDecodeYUV function is supposed to handle any input data, even corrupt ones, by erroring out. But the code in tj3DecodeYUVPlanes8 has a setjmp to catch errors. If an error is signaled, it would jump to bailout. However, the crash is occurring during normal processing, not in the error handling path. This suggests that the library is proceeding with invalid parameters, leading to the crash. So, if the library does not properly validate the input parameters (like ensuring that the srcBuf is large enough for the calculated strides and plane sizes), then it's a library bug. However, the fuzz driver is responsible for providing a valid srcBuf that meets the requirements of the YUV format, alignment, and plane sizes. If the fuzz driver's srcBuf is not properly allocated (based on the required YUV plane sizes), then the crash is due to a misuse of the library. For example, if the required size for srcBuf is larger than the allocated Size bytes, then accessing srcPlanes[1] or [2] would read out of bounds, leading to undefined behavior, which could include writing to invalid addresses if the read data is used to compute pointers. However, the crash in this case is during a write to tmpbuf, so it's more likely related to the destination buffer in the decompression process. Putting it all together, the most plausible explanation is that the fuzz driver is not correctly calculating the required size for the destination buffer. The tjDecodeYUV function requires the destination buffer to have a size of pitch * height. The fuzz driver calculates dstBufSize as width * height * tjPixelSize[pixelFormat], which assumes that pitch is width * tjPixelSize. However, if the pitch passed to tjDecodeYUV is larger than this value, then the allocated dstBuf is too small. When the library writes the decompressed data into dstBuf using the larger pitch, it overflows the buffer, leading to a heap buffer overflow and a crash. This is a misuse of the library because the fuzz driver is responsible for ensuring that the destination buffer is large enough for the given pitch and height. The library's function does not check if the provided dstBuf is sufficient, relying on the caller to provide a buffer of adequate size. Since the fuzz driver does not calculate dstBufSize correctly (it uses width * tjPixelSize * height instead of pitch * height), it's a mistake in the fuzz driver. Therefore, the crash is due to a misuse in the fuzz driver.