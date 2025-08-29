from src.llm.prompter import CrashConstraintPrompter
from src.utils import setup_llm
from src.llm.llm import LLMChat


def run():
    llm_client = setup_llm("deepseek")
    chat = LLMChat(llm_client)
    prompter = CrashConstraintPrompter(chat)
    cons, code = prompter.prompt(
        library_name="ngiflib",
        library_purpose="",
        crash_reason="ERROR: AddressSanitizer: SEGV on unknown address 0x000000000008 (pc 0x75d207a86444 bp 0x7ffe2dbe4a40 sp 0x7ffe2dbe4a00 T0)",
        backtrace="""==45785==Hint: address points to the zero page.
#0 _IO_fread

#1 fread

#2 GetByteStr
/promefuzz/database/ngiflib/latest/build_asan/ngiflib.c:125:10
   125|		read = fread(p, 1, n, g->input.file);
      |         ^

#3 LoadGif
/promefuzz/database/ngiflib/latest/build_asan/ngiflib.c:657:3
   657|	 GetByteStr(g, g->signature, 6);
      |  ^

#4 LLVMFuzzerTestOneInput
""",
        driver_code="""#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ngiflib.h"
#include "ngiflibSDL.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // CheckGif
    int check_result = CheckGif((u8*)Data);

    // LoadGif
    struct ngiflib_gif gif_struct;
    memset(&gif_struct, 0, sizeof(gif_struct));

    // Ensure the input is treated as a buffer
    gif_struct.input.buffer.bytes = Data;
    gif_struct.input.buffer.count = Size;

    int load_result = LoadGif(&gif_struct);

    // GifImgDestroy
    if (gif_struct.first_img != NULL) {
        GifImgDestroy(gif_struct.first_img);
    }

    // SDL_LoadAnimatedGif
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file != NULL) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
        struct ngiflibSDL_animation* animation = SDL_LoadAnimatedGif("./dummy_file");
        if (animation != NULL) {
            free(animation);
        }
    }

    // GifDestroy
    GifDestroy(&gif_struct);

    return 0;
}""",
        library_code={
            "GetByteStr": """static int GetByteStr(struct ngiflib_gif * g, u8 * p, int n) {
        if(!p) return -1;
#ifndef NGIFLIB_NO_FILE
        if(g->mode & NGIFLIB_MODE_FROM_MEM) {
#endif /* NGIFLIB_NO_FILE */
                if (g->input.buffer.count >= (unsigned)n) {
                        ngiflib_memcpy(p, g->input.buffer.bytes, n);
                        g->input.buffer.count -= n;
                        g->input.buffer.bytes += n;
                        return 0;
                } else {
                        /* buffer overrun */
                        return -1;
                }
#ifndef NGIFLIB_NO_FILE
        } else {
                size_t read;
                read = fread(p, 1, n, g->input.file);
                return ((int)read == n) ? 0 : -1;
        }
#endif /* NGIFLIB_NO_FILE */
}""",
            "LoadGif": """int LoadGif(struct ngiflib_gif * g) {
        struct ngiflib_gce gce;
        u8 sign;
        u8 tmp;
        int i;

        if(!g) return -1;
        gce.gce_present = 0;

        if(g->nimg==0) {
                GetByteStr(g, g->signature, 6);
                g->signature[6] = '\0';
                if(   g->signature[0] != 'G'
                   || g->signature[1] != 'I'
                   || g->signature[2] != 'F'
                   || g->signature[3] != '8') {
                        return -1;
                }
#if !defined(NGIFLIB_NO_FILE)
                if(g->log) fprintf(g->log, "%s\n", g->signature);
#endif /* !defined(NGIFLIB_NO_FILE) */

                g->width = GetWord(g);
                g->height = GetWord(g);
                /* allocate frame buffer */
#ifndef NGIFLIB_INDEXED_ONLY
                if((g->mode & NGIFLIB_MODE_INDEXED)==0) {
                        g->frbuff.p32 = ngiflib_malloc(4*(long)g->height*(long)g->width);
#ifdef EXTRA_MALLOC_CHECK
                        if(g->frbuff.p32 == NULL) {
#if !defined(NGIFLIB_NO_FILE)
// More code is emitted...
""",
        },
        data_definitions="""struct ngiflib_gif {
	struct ngiflib_img * first_img;
	struct ngiflib_img * cur_img;
	struct ngiflib_rgb * palette;
	union {
#ifndef NGIFLIB_NO_FILE
		FILE * file;
#endif /* NGIFLIB_NO_FILE */
		struct {
			const u8 * bytes;
			unsigned long count;
		} buffer;
	} input;	/* used by GetByte */
	union ngiflib_pixpointer frbuff;	/* frame buffer    */
#ifndef NGIFLIB_NO_FILE
	FILE * log;		/* to output log   */
#endif /* NGIFLIB_NO_FILE */
#ifdef NGIFLIB_ENABLE_CALLBACKS
	ngiflib_palette_cb palette_cb;
	ngiflib_line_cb line_cb;
	/* void * priv; */
#endif /* NGIFLIB_ENABLE_CALLBACKS */
	int nimg;
	int netscape_loop_count;	/* from netscape animation extension */
	u16 ncolors;				/* number of colors in the palette */
	u16 width;
	u16 height;
	u8 backgroundindex;
	u8 pixaspectratio;	/* width/height = (pixaspectratio + 15) / 64 */
	u8 imgbits;
	u8 colorresolution;
	u8 sort_flag;
	u8 mode; /* voir avant */
	u8 signature[7];	/* 0 terminated  !=) */
};""",
        api_functions=["GetByteStr", "LoadGif"],
    )

    print(cons)
    print("=======")
    print(code)