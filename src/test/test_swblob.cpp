# include "swblob.h"
#include <fstream>
#include <string>

int main()
{
    double scale = 1.0;
    BlobImage<char> src(640, 480, IMG_FMT_YUYV);
    BlobImage<float> dst(300, 300, IMG_FMT_RGB24);
    MeanScale ms = {0.0, 0.0, 0.0, 0.0};

    blobFromImage(&src, &dst, scale, ms, false, false);

    return 0;
}

