#pragma once

struct MeanScale
{
    double scale[4];
};

enum ImageFmt 
{
    IMG_FMT_YUYV,
    IMG_FMT_RGB24
};

struct RectMask
{
    int left;
    int top;
    int right;
    int bottom;
};

void rgb2bmp(int w, int h, char* data, char* filename);

template <typename T> struct ImageBlob 
{
    ImageBlob(int width, int height, ImageFmt format) :
        w(width), h(height), fmt(format)
    {
        for (int i = 0; i < 4; i++) 
        {
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

    ~ImageBlob()
    {
        for (int i = 0; i < 4; i++) 
        {
            if (data[i]) 
            {
                delete[] data[i];
                data[i] = nullptr;
            }
        }
    }

    void drawMask(RectMask* r);
    void saveBmp(int index);

    int w;
    int h;
    ImageFmt fmt;
    int linesize[4];
    T* data[4];
};

template <typename T>
void ImageBlob<T>::drawMask(RectMask* r)
{

}

template <typename T>
void ImageBlob<T>::saveBmp(int index)
{
    char filename[256] = {};
    sprintf_s(filename, 256, "out_%06d.bmp", index);
    rgb2bmp(w, h, (char*)data[0], filename);
}
