#pragma once

#include <string>

extern "C" {
#include <libavutil/motion_vector.h>
#include <libavformat/avformat.h>
}

class VideoDec
{
public:
    VideoDec(const char* videoFileName);
    ~VideoDec();

    int decode();

private:
    int initialize(enum AVMediaType type);
    int decode_packet(const AVPacket *pkt, int* gotFrame);
    int destroy();

private:
    std::string fileName_;
    AVFormatContext *formatCtx_ = NULL;
    AVCodecContext *decodeCtx_ = NULL;
    AVStream *videoStream_ = NULL;
    int streamIdx_ = -1;
    AVFrame *frame_ = NULL;
    int frameCount_ = 0;
    bool initialized_ = false;
};

