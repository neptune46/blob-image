# include "swblob.h"
#include <fstream>
#include <string>

int testSwblob()
{
    double scale = 1.0;
    BlobImage<char> src(640, 480, IMG_FMT_YUYV);
    BlobImage<float> dst(300, 300, IMG_FMT_RGB24);
    MeanScale ms = { 0.0, 0.0, 0.0, 0.0 };

    std::ifstream srcfile;
    srcfile.open("test_yuyv_640x480.yuv", std::ios::binary);
    if (!srcfile.is_open())
    {
        fprintf(stderr, "failed to open input yuv file\n");
        return -1;
    }
    srcfile.read(src.data[0], src.linesize[0] * src.h);
    srcfile.close();

    blobFromImage(&src, &dst, scale, ms, false, false);

    return 0;
}

int main()
{
    testSwblob();

    return 0;
}

