
struct Size2D{
    int w;
    int h;
};

struct MeanScale{
    double scale[4];
};

enum ImageFmt {
    IMG_FMT_YUYV,
    IMG_FMT_RGB24
};

template <typename T>
struct BlobImage {
    int w;
    int h;
    ImageFmt fmt;
    int size[4];
    T* data[4];
};

int blobFromImage(BlobImage<char>* src, BlobImage<float>* dst, double scale, Size2D sz, MeanScale ms, bool swapRB, bool crop);
