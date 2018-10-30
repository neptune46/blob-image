
struct MeanScale{
    double scale[4];
};

enum ImageFmt {
    IMG_FMT_YUYV,
    IMG_FMT_RGB24
};

template <typename T> struct BlobImage 
{
    BlobImage(int width, int height, ImageFmt format) :
        w(width), h(height), fmt(format)
    {
        for (int i = 0; i < 4; i++) {
            linesize[i] = 0;
            data[i] = nullptr;
        }

        switch (fmt)
        {
        case IMG_FMT_YUYV:
            linesize[0] = w * 2;
            data[0] = new T[linesize[0] * h];
            break;
        case IMG_FMT_RGB24:
            linesize[0] = w * 3;
            data[0] = new T[linesize[0] * h];
            break;
        default:
            break;
        }
    }

    ~BlobImage()
    {
        for (int i = 0; i < 4; i++) {
            if (data[i]) {
                delete[] data[i];
                data[i] = nullptr;
            }
        }
    }

    int w;
    int h;
    ImageFmt fmt;
    int linesize[4];
    T* data[4];
};

int blobFromImage(BlobImage<char>* src, BlobImage<float>* dst, double scale, MeanScale ms, bool swapRB, bool crop);
