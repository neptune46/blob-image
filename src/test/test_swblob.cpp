# include "swblob.h"

int main()
{
    BlobImage<char> src;
    BlobImage<float> dst;
    double scale = 1.0;
    Size2D sz = {300, 300};
    MeanScale ms = {0.0, 0.0, 0.0, 0.0};

    blobFromImage(&src, &dst, scale, sz, ms, false, false);

    return 0;
}

