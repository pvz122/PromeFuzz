cmake_minimum_required(VERSION 3.0)

PROJECT(ffjpeg)

INCLUDE_DIRECTORIES(
	.
)

ADD_LIBRARY(libffjpeg bitstr.c bmp.c color.c dct.c huffman.c jfif.c quant.c zigzag.c)
ADD_EXECUTABLE(ffjpeg ffjpeg.c)
TARGET_LINK_LIBRARIES(ffjpeg libffjpeg)

