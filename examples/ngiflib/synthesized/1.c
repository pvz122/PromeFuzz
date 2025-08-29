// This fuzz driver is generated for library ngiflib, aiming to fuzz the following functions:
// GifDestroy at ngiflib.c:54:6 in ngiflib.h
// CheckGif at ngiflib.c:408:5 in ngiflib.h
// LoadGif at ngiflib.c:647:5 in ngiflib.h
// GifIndexToTrueColor at ngiflib.c:901:5 in ngiflib.h
// SDL_LoadAnimatedGif at ngiflibSDL.c:103:31 in ngiflibSDL.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ngiflib.h"
#include "ngiflibSDL.h"
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    // Test LoadGif
    struct ngiflib_gif gif;
    memset(&gif, 0, sizeof(gif));
    gif.mode = NGIFLIB_MODE_FROM_MEM;
    gif.input.buffer.bytes = Data;
    gif.input.buffer.count = Size;
    if (LoadGif(&gif) == 0) {
        GifDestroy(&gif);
    }

    // Test GifIndexToTrueColor
    struct ngiflib_rgb palette[256];
    for (int i = 0; i < 256; i++) {
        palette[i].r = i;
        palette[i].g = i;
        palette[i].b = i;
    }
    if (Size > 0) {
        GifIndexToTrueColor(palette, Data[0]);
    }

    // Test CheckGif
    if (Size > 6) {
        CheckGif((u8*)Data);
    }

    // Test SDL_LoadAnimatedGif
    FILE *fp = fopen("./dummy_file", "wb");
    if (fp) {
        fwrite(Data, 1, Size, fp);
        fclose(fp);
        struct ngiflibSDL_animation *anim = SDL_LoadAnimatedGif("./dummy_file");
        if (anim) {
            free(anim);
        }
    }

    return 0;
}