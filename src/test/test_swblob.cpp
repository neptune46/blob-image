# include "swblob.h"
#include <fstream>
#include <string>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace dnn;

int test_swblob()
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

    std::ofstream dstfile;
    dstfile.open("swblob.bin", std::ios::binary);
    dstfile.write((char*)dst.data[0], dst.linesize[0] * dst.h * sizeof(float));
    dstfile.close();

    return 0;
}

void test_cvblob()
{
    int w = 300, h = 300;
    int size = w * h * 3;
    float scale = (float)0.00392; // (1/255)
    Scalar mean = { 0.0, 0.0, 0.0, 0.0 };
    char* srcbuf = new char[size];
    Mat srcMat, dstMat;

    std::ifstream srcfile;
    srcfile.open("test_rgb24_300x300.rgb", std::ios::binary);
    srcfile.read(srcbuf, size);
    srcfile.close();
    srcMat = Mat(w, h, CV_8UC3, (uchar*)srcbuf);

    blobFromImage(srcMat, dstMat, scale, { w, h }, mean, false, false);

    std::ofstream dstfile;
    dstfile.open("cvblob.bin", std::ios::binary);
    dstfile.write((char*)dstMat.data, size * sizeof(float));
    dstfile.close();

    delete[] srcbuf;
}

int main()
{
    test_swblob();
    test_cvblob();

    return 0;
}

