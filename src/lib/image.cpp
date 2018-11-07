#include "image.h"
#include <fstream>

typedef struct
{
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
} BmpFileHeader;

typedef struct
{
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
} BmpInfoHeader;

typedef struct 
{
    char r;
    char g;
    char b;
} BmpPixel;

void rgb2bmp(int w, int h, char* data, char* filename)
{
    BmpFileHeader bfh = {};
    BmpInfoHeader bih = {};

    unsigned short bfType = 0x4d42;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfSize = 2 + sizeof(BmpFileHeader) + sizeof(BmpInfoHeader) + w * h * 3;
    bfh.bfOffBits = 0x36;

    bih.biSize = sizeof(BmpInfoHeader);
    bih.biWidth = w;
    bih.biHeight = h;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = 0;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 5000;
    bih.biYPelsPerMeter = 5000;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;
 
    std::ofstream fout;
    fout.open(filename, std::ios::binary);
    fout.write((const char*)&bfType, sizeof(bfType));
    fout.write((const char*)&bfh, sizeof(bfh));
    fout.write((const char*)&bih, sizeof(bih));

    int line = 0; 
    char* bmpBuf = new char[w * h * 3]; 
    for (int y = bih.biHeight - 1; y >= 0; y--) 
    {
        for (int x = 0; x < bih.biWidth; x++) 
        {
            bmpBuf[line * w * 3 + x*3 + 0] = data[y * w * 3 + x*3 + 2];
            bmpBuf[line * w * 3 + x*3 + 1] = data[y * w * 3 + x*3 + 1];
            bmpBuf[line * w * 3 + x*3 + 2] = data[y * w * 3 + x*3 + 0];
        }
        line++;
    }
    fout.write((const char*)bmpBuf, w*h*3);
    delete[] bmpBuf;
    fout.close();
}
