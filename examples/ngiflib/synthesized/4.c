// This fuzz driver is generated for library ngiflib, aiming to fuzz the following functions:
// GifImgDestroy at ngiflib.c:26:6 in ngiflib.h
// GifDestroy at ngiflib.c:54:6 in ngiflib.h
// LoadGif at ngiflib.c:647:5 in ngiflib.h
// SDL_LoadAnimatedGif at ngiflibSDL.c:103:31 in ngiflibSDL.h
// SDL_LoadGIF at ngiflibSDL.c:9:15 in ngiflibSDL.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ngiflib.h"
#include "ngiflibSDL.h"

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    // Test LoadGif
    struct ngiflib_gif gif;
    memset(&gif, 0, sizeof(gif));
    gif.mode = NGIFLIB_MODE_FROM_MEM;
    gif.input.buffer.bytes = Data;
    gif.input.buffer.count = Size;
    if (LoadGif(&gif) == 0) {
        GifDestroy(&gif);
    }

    // Test SDL_LoadGIF
    FILE *fp = fopen("./dummy_file", "wb");
    if (fp) {
        fwrite(Data, 1, Size, fp);
        fclose(fp);
        SDL_Surface *surface = SDL_LoadGIF("./dummy_file");
        if (surface) {
            SDL_FreeSurface(surface);
        }
    }

    // Test GifImgDestroy
    struct ngiflib_img *img = (struct ngiflib_img *)calloc(1, sizeof(struct ngiflib_img));
    if (img) {
        img->parent = &gif;
        GifImgDestroy(img);
    }

    // Test SDL_LoadAnimatedGif
    struct ngiflibSDL_animation *animation = SDL_LoadAnimatedGif("./dummy_file");
    if (animation) {
        free(animation);
    }

    return 0;
}