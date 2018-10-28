#include <fstream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace dnn;

void blob_cap()
{
    VideoCapture cap;
    cap.open("test.mp4");
    Mat frame, blob;
    float scale = (float)0.00392; // (1/255)
    Scalar mean = { 0.0, 0.0, 0.0, 0.0 };
    bool swapRB = false;

    while (1)
    {
        cap >> frame;
        if (frame.empty())
            break;

        Size inpSize(frame.cols, frame.rows);
        blobFromImage(frame, blob, scale, inpSize, mean, swapRB, false);
    }
}

void blob_rgb24()
{
    int w = 300, h = 300;
    int size = w * h * 3;
    float scale = (float)0.00392; // (1/255)
    Scalar mean = { 0.0, 0.0, 0.0, 0.0 };
    char* src_buf = new char[size];
    Mat src_mat, dst_mat;

    std::ifstream fsrc;
    fsrc.open("src.rgb", std::ios::binary);
    fsrc.read(src_buf, size);
    fsrc.close();
    src_mat = Mat(w, h, CV_8UC3, (uchar*)src_buf);

    blobFromImage(src_mat, dst_mat, scale, {w, h}, mean, false, false);

    std::ofstream fdst;
    fdst.open("dst.bin", std::ios::binary);
    fdst.write((char*)dst_mat.data, size*4);
    fdst.close();

    delete[] src_buf;
}

int main()
{
    //blob_cap();

    blob_rgb24();

    return 0;
}