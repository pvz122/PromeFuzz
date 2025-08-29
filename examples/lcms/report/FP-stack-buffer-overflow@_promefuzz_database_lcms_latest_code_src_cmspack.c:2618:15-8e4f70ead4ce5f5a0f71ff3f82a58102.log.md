# Fuzz driver

```cpp
extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 10) return 0;

    cmsUInt32Number inputFormat = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number outputFormat = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number intent = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 2);
    cmsUInt32Number proofingIntent = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 3);
    cmsUInt32Number flags = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 4);

    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE proofingProfile = cmsCreate_sRGBProfile();

    cmsHTRANSFORM transform = cmsCreateProofingTransform(inputProfile, inputFormat, outputProfile, outputFormat, proofingProfile, intent, proofingIntent, flags);
    if (transform) {
        cmsUInt32Number retrievedInputFormat = cmsGetTransformInputFormat(transform);
        cmsChangeBuffersFormat(transform, inputFormat, outputFormat);

        uint8_t inputBuffer[1024];
        uint8_t outputBuffer[1024];
        memset(inputBuffer, 0, sizeof(inputBuffer));
        memcpy(inputBuffer, Data, Size < sizeof(inputBuffer) ? Size : sizeof(inputBuffer));
        cmsDoTransform(transform, inputBuffer, outputBuffer, sizeof(inputBuffer));

        cmsDeleteTransform(transform);
    }

    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);

    return 0;
}
```

# Crash report

## Crash reason

AddressSanitizer: stack-buffer-overflow on address 0x7f3188a098a0 at pc 0x55d3dc88b179 bp 0x7fff83ba7f20 sp 0x7fff83ba7f18

## Backtrace

```
WRITE of size 1 at 0x7f3188a098a0 thread T0

#0 Pack1ByteSkip1
/promefuzz/database/lcms/latest/code/src/cmspack.c:2618:15
    *output++ = FROM_16_TO_8(wOut[0]);
              ^

#1 NullXFORM
/promefuzz/database/lcms/latest/code/src/cmsxform.c:391:22
            output = p->ToOutput(p, wIn, output, Stride->BytesPerPlaneOut);
                     ^

#2 cmsDoTransform
/promefuzz/database/lcms/latest/code/src/cmsxform.c:206:5
    p -> xform(p, InputBuffer, OutputBuffer, Size, 1, &stride);
    ^

#3 LLVMFuzzerTestOneInput_140
/promefuzz/database/lcms/latest/out/fuzz_driver/synthesized/140.cpp:49:9
        cmsDoTransform(transform, inputBuffer, outputBuffer, sizeof(inputBuffer));
        ^
```

## Related source code

Part of the lcms library that is relevant to the crash is as follows:

- `Pack1ByteSkip1`:
```cpp
static
cmsUInt8Number* Pack1ByteSkip1(CMSREGISTER _cmsTRANSFORM* info,
                               CMSREGISTER cmsUInt16Number wOut[],
                               CMSREGISTER cmsUInt8Number* output,
                               CMSREGISTER cmsUInt32Number Stride)
{
    *output++ = FROM_16_TO_8(wOut[0]);
    output++;

    return output;

    cmsUNUSED_PARAMETER(info);
    cmsUNUSED_PARAMETER(Stride);
}
```

- `cmsDoTransform`:
```cpp
void CMSEXPORT cmsDoTransform(cmsHTRANSFORM  Transform,
                              const void* InputBuffer,
                              void* OutputBuffer,
                              cmsUInt32Number Size)

{
    _cmsTRANSFORM* p = (_cmsTRANSFORM*) Transform;
    cmsStride stride;

    stride.BytesPerLineIn = 0;  // Not used
    stride.BytesPerLineOut = 0;
    stride.BytesPerPlaneIn = Size * PixelSize(p->InputFormat);
    stride.BytesPerPlaneOut = Size * PixelSize(p->OutputFormat);
           
    p -> xform(p, InputBuffer, OutputBuffer, Size, 1, &stride);
}
```

- `NullXFORM`:
```cpp
// some code omitted...

    _cmsHandleExtraChannels(p, in, out, PixelsPerLine, LineCount, Stride);

    strideIn = 0;
    strideOut = 0;
    memset(wIn, 0, sizeof(wIn));

    for (i = 0; i < LineCount; i++) {

        accum = (cmsUInt8Number*)in + strideIn;
        output = (cmsUInt8Number*)out + strideOut;

        for (j = 0; j < PixelsPerLine; j++) {

            accum = p->FromInput(p, wIn, accum, Stride->BytesPerPlaneIn);
            output = p->ToOutput(p, wIn, output, Stride->BytesPerPlaneOut);
        }

        strideIn += Stride->BytesPerLineIn;
        strideOut += Stride->BytesPerLineOut;
    }

}

```

## Related data definitions

```cpp
typedef unsigned int        cmsUInt32Number;

typedef void* cmsHTRANSFORM;
```

# Analysis from LLM

The crash is a Misuse in fuzz driver, below is the explanation.

**Crash Analysis:**

1. **Crash Type:**  
   Stack-buffer-overflow during a write operation in `Pack1ByteSkip1`, caused by exceeding the bounds of the `outputBuffer` array.

2. **Root Cause:**  
   The fuzz driver incorrectly calculates the `Size` parameter for `cmsDoTransform`.  
   - `cmsDoTransform` expects `Size` to represent the **number of pixels** to process.  
   - The driver erroneously passes `sizeof(inputBuffer)` (1024 bytes) as `Size`, treating it as the number of pixels instead of using the correct pixel count derived from the input format's bytes-per-pixel.

3. **Overflow Mechanism:**  
   The `Pack1ByteSkip1` function writes 1 byte per pixel but advances the output pointer by 2 bytes per pixel (due to `output++` twice). For `Size = 1024` pixels, this requires 2048 bytes in `outputBuffer`, which exceeds its 1024-byte allocation.

4. **Library vs. Driver Fault:**  
   The crash stems from the fuzz driver misusing the `cmsDoTransform` API by passing an invalid `Size`. The library functions operate correctly under the assumption that the caller ensures valid buffer sizes and parameters. No evidence of a library bug exists in the provided code. 

**Key Misuse:**  
`cmsDoTransform(transform, ..., sizeof(inputBuffer))`  
→ Should use `Size = sizeof(inputBuffer) / BytesPerPixel(inputFormat)` to calculate the correct pixel count.

# Reasoning Process

Okay, let's try to figure out why this crash is happening. The user provided a fuzz driver and a crash report. The crash is a stack-buffer-overflow detected by AddressSanitizer. The backtrace points to the Pack1ByteSkip1 function in cmspack.c, specifically when writing to the output buffer.

First, let's look at the fuzz driver. The test function uses cmsCreateProofingTransform to create a transform, then calls cmsChangeBuffersFormat. The input and output buffers are 1024 bytes each. Then cmsDoTransform is called with sizeof(inputBuffer) as the size, which is 1024. 

In the crash report, the error is a write of size 1 at a certain address. The backtrace shows that Pack1ByteSkip1 is writing to the output buffer. The line in question is *output++ = FROM_16_TO_8(wOut[0]); followed by another output++. So each call to this function writes one byte and increments the pointer twice. That means each pixel writes 1 byte but skips the next. So if the output format is such that each pixel requires 1 byte but with some stride or padding, maybe the output buffer isn't large enough?

Looking at the cmsDoTransform code, the stride.BytesPerPlaneOut is calculated as Size * PixelSize(p->OutputFormat). The Size here is the third argument to cmsDoTransform, which in the driver is sizeof(inputBuffer) (1024). But if the OutputFormat's pixel size is larger, or the transform's format after changing the buffer format causes each pixel to require more bytes, then the output buffer might overflow.

Wait, the fuzz driver uses cmsChangeBuffersFormat after getting the transform. The original transform is created with inputFormat, outputFormat, etc., taken from the data. Then they call cmsChangeBuffersFormat with inputFormat and outputFormat again. Maybe changing the buffer formats alters how the data is processed, but the output buffer size isn't adjusted accordingly.

In the driver, the outputBuffer is 1024 bytes. But when the buffer format is changed, maybe the required output size is larger than 1024. For example, if each pixel in the output format requires 2 bytes, and there are 1024 pixels, the output buffer would need 2048 bytes, which would overflow the 1024-byte buffer. But the driver uses sizeof(inputBuffer) as the number of pixels (third argument to cmsDoTransform). Wait, the third parameter to cmsDoTransform is the number of pixels, not the buffer size. Wait, according to the LCMS documentation, cmsDoTransform's fourth parameter is the number of pixels to process. But in the driver, the code is passing sizeof(inputBuffer) as the Size. That's a problem. Because sizeof(inputBuffer) is 1024 bytes, but the number of pixels depends on the pixel size. For example, if each input pixel is 4 bytes (like RGBA), then 1024 bytes would be 256 pixels. But if the code uses Size as 1024, it's processing 1024 pixels, each of which requires a certain number of bytes. So the output buffer may not be large enough.

Wait, let me check the parameters. The cmsDoTransform function's parameters are InputBuffer, OutputBuffer, and Size. The Size is the number of pixels to process. So if the input buffer is 1024 bytes and each input pixel is (for example) 4 bytes, then the maximum number of pixels is 256. But the driver is passing sizeof(inputBuffer) as the Size, which is 1024, implying that each pixel is 1 byte. But that's only correct if the input format is 1 byte per pixel. However, if the input format uses more bytes per pixel (like 4 bytes), then passing 1024 as the Size would read beyond the input buffer and also write beyond the output buffer.

Wait, the problem here is that in the fuzz driver, after creating the transform and changing the buffer format, the code calls cmsDoTransform with Size set to sizeof(inputBuffer). But the Size parameter is supposed to be the number of pixels, not the number of bytes. So if the input format's bytes per pixel is more than 1, then the input buffer of 1024 bytes can't hold 1024 pixels. For example, if each input pixel is 4 bytes, 1024 pixels would require 4096 bytes. But the input buffer is only 1024 bytes. So the code is processing more pixels than the buffer can hold, leading to buffer overflow.

In the crash report, the output buffer is being overflowed. The Pack1ByteSkip1 function writes 1 byte per pixel, then skips a byte (output += 1; then output++ again). So each pixel writes 1 byte, but moves the pointer by 2 bytes. So for each pixel, the output buffer needs 2 bytes. If the code processes N pixels, the output buffer needs N*2 bytes. But the output buffer is 1024 bytes. If the Size is 1024 pixels, then the output buffer needs 2048 bytes, which overflows the 1024-byte buffer. Hence, the stack overflow.

So the root cause is that in the fuzz driver, the Size parameter passed to cmsDoTransform is sizeof(inputBuffer), which is 1024, but that's the number of bytes in the input buffer. However, the Size parameter should be the number of pixels, not bytes. Therefore, if the input format's bytes per pixel is 1, then 1024 pixels would fit in 1024 bytes, but the output format's bytes per pixel (after Pack1ByteSkip1) would require 2 bytes per pixel (since each write increments by 2). So 1024 pixels would require 2048 bytes in the output buffer, but the output buffer is only 1024 bytes. This causes a buffer overflow in the output buffer.

Therefore, the crash is caused by the fuzz driver incorrectly calculating the Size parameter as the size of the input buffer (in bytes) instead of the number of pixels. The correct Size should be the input buffer size divided by the bytes per pixel of the input format. However, the driver does not do this. So it's a misuse of the library API in the fuzz driver. The library functions are being called with incorrect parameters, leading to buffer overflow.

Another angle: the library's functions may require that the output buffer is sufficiently large. If the user passes a Size that's too large, causing the output buffer to be exceeded, that's a misuse. The library expects the user to provide properly sized buffers. The fuzz driver's mistake is passing Size as sizeof(inputBuffer), which is the number of bytes, not pixels. Therefore, the crash is due to the fuzz driver's misuse, not a bug in the library.