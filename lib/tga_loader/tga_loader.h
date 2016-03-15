#ifndef TGA_LOADER_H
# define TGA_LOADER_H

typedef struct
{
    unsigned char imageTypeCode;
    short int imageWidth;
    short int imageHeight;
    unsigned char bitCount;
    unsigned char *imageData;
} TGAFILE;

GLuint	load_tga(const char* filename);
GLuint	load_tga_file(const char *filename);

#endif
