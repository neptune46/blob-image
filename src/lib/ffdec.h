#pragma once

#include "image.h"

#include <string>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/parseutils.h>
#include <libswscale/swscale.h>
}

class VideoDec
{
public:
    VideoDec(const char* videoFileName);
    ~VideoDec();

    int decode(ImageBlob<char>& img);

private:
    int initialize(enum AVMediaType type);
    int decodePacket(const AVPacket *pkt, ImageBlob<char>& img, int& gotFrame);
    int destroy();

private:
    std::string fileName_;
    AVFormatContext *formatCtx_ = nullptr;
    AVCodecContext *decodeCtx_ = nullptr;
    struct SwsContext *swsCtx_ = nullptr;
    AVStream *videoStream_ = nullptr;
    int streamIdx_ = -1;
    AVFrame *frame_ = nullptr;
    int frameCount_ = 0;
    bool initialized_ = false;
};

