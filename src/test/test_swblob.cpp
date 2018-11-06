#include "swblob.h"
#include "ffdec.h"

#include <fstream>
#include <string>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "perf_util.h"

PerfUtil puInstance;

using namespace cv;
using namespace dnn;

int test_swblob(ImageBlob<char>& src, ImageBlob<float>& dst)
{
    double scale = 0.00392; // (1/255)
    MeanScale ms = { 127.0, 127.0, 127.0, 127.0 };

    std::ifstream srcfile;
    srcfile.open("test_yuyv_640x480.yuv", std::ios::binary);
    if (!srcfile.is_open())
    {
        fprintf(stderr, "failed to open input yuv file\n");
        return -1;
    }
    srcfile.read(src.data[0], src.linesize[0] * src.h);
    srcfile.close();

    puInstance.startTick("swblob");
    blobFromImage(&src, &dst, scale, ms, false, false);
    puInstance.stopTick("swblob");

    std::ofstream dstfile;
    dstfile.open("swblob.bin", std::ios::binary);
    dstfile.write((char*)dst.data[0], dst.linesize[0] * dst.h * sizeof(float));
    dstfile.close();

    return 0;
}

void test_cvblob(Mat& srcMat, Mat& dstMat, int w, int h)
{
    int size = w * h * 3;
    float scale = (float)0.00392; // (1/255)
    Scalar mean = { 127.0, 127.0, 127.0, 127.0 };
    char* srcbuf = new char[size];

    std::ifstream srcfile;
    srcfile.open("test_rgb24_300x300.rgb", std::ios::binary);
    srcfile.read(srcbuf, size);
    srcfile.close();
    srcMat = Mat(w, h, CV_8UC3, (uchar*)srcbuf);

    puInstance.startTick("cvblob");
    blobFromImage(srcMat, dstMat, scale, { w, h }, mean, false, false);
    puInstance.stopTick("cvblob");

    std::ofstream dstfile;
    dstfile.open("cvblob.bin", std::ios::binary);
    dstfile.write((char*)dstMat.data, size * sizeof(float));
    dstfile.close();

    delete[] srcbuf;
}

double compare(float* ref, float* cur, int size)
{
    double sum = 0.0;
    for (int i=0; i<size; i++)
    {
        sum += abs(*(ref + i) - *(cur + i));
    }
    return sum/size;
}

void test_blob()
{
    int w = 300, h = 300;
    Mat srcMat, dstMat;
    test_cvblob(srcMat, dstMat, w, h);

    ImageBlob<char> src(640, 480, IMG_FMT_YUYV);
    ImageBlob<float> dst(w, h, IMG_FMT_RGB24);
    test_swblob(src, dst);

    double error = compare((float*)dstMat.data, dst.data[0], w * h * 3);
    std::cout << "error = " << error << std::endl;
}

int test_ffdec()
{
    VideoDec vdec("test.mp4");
    ImageBlob<char> img(300, 300, IMG_FMT_RGB24);
    int frameIdx = 0;

    while (vdec.decode(img) >= 0)
    {
        printf("get one frame\n");
        img.saveBmp(frameIdx++);
    }

    return 0;
}

int main()
{
    test_ffdec();

    for (int i=0; i<10; i++)
    {
        test_blob();
    }

    return 0;
}

