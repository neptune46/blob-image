#include "ffdec.h"

VideoDec::VideoDec(const char* videoFileName):
    fileName_(videoFileName)
{
}

VideoDec::~VideoDec()
{
    destroy();
}

int VideoDec::initialize(enum AVMediaType type)
{
    int ret;
    AVStream *st;
    AVCodecContext *dec_ctx = NULL;
    AVCodec *dec = NULL;
    AVDictionary *opts = NULL;

    if (avformat_open_input(&formatCtx_, fileName_.c_str(), NULL, NULL) < 0) 
    {
        fprintf(stderr, "Could not open source file %s\n", fileName_.c_str());
        return -1;
    }

    if (avformat_find_stream_info(formatCtx_, NULL) < 0) 
    {
        fprintf(stderr, "Could not find stream information\n");
        return -1;
    }

    ret = av_find_best_stream(formatCtx_, type, -1, -1, &dec, 0);
    if (ret < 0) 
    {
        fprintf(stderr, "Could not find %s stream in input file '%s'\n",
            av_get_media_type_string(type), fileName_.c_str());
        return ret;
    }
    else 
    {
        int stream_idx = ret;
        st = formatCtx_->streams[stream_idx];

        dec_ctx = avcodec_alloc_context3(dec);
        if (!dec_ctx) 
        {
            fprintf(stderr, "Failed to allocate codec\n");
            return -1;
        }

        ret = avcodec_parameters_to_context(dec_ctx, st->codecpar);
        if (ret < 0) 
        {
            fprintf(stderr, "Failed to copy codec parameters to codec context\n");
            return ret;
        }

        /* Init the video decoder */
        av_dict_set(&opts, "flags2", "+export_mvs", 0);
        if ((ret = avcodec_open2(dec_ctx, dec, &opts)) < 0) 
        {
            fprintf(stderr, "Failed to open %s codec\n", av_get_media_type_string(type));
            return ret;
        }

        streamIdx_ = stream_idx;
        videoStream_ = formatCtx_->streams[streamIdx_];
        decodeCtx_ = dec_ctx;

        if (!videoStream_) 
        {
            fprintf(stderr, "Could not find video stream in the input, aborting\n");
            return -1;
        }

        frame_ = av_frame_alloc();
        if (!frame_) 
        {
            fprintf(stderr, "Could not allocate frame\n");
            return -1;
        }
    }

    return 0;
}

int VideoDec::decodePacket(const AVPacket *pkt, ImageBlob<char>& img, int& gotFrame)
{
    int ret = 0;
    gotFrame = 0;

    ret = avcodec_send_packet(decodeCtx_, pkt);
    if (ret < 0 && pkt != NULL)
    {
        fprintf(stderr, "Error while sending a packet to the decoder: %s\n", "");
        return ret;
    }

    ret = avcodec_receive_frame(decodeCtx_, frame_);
    if (ret == AVERROR(EAGAIN))
    {
        return 0;
    }
    else if (ret == AVERROR_EOF)
    {
        return -1;
    }
    else if (ret < 0)
    {
        fprintf(stderr, "Error while receiving a frame from the decoder: %s\n", "");
        return ret;
    }

    if (ret >= 0)
    {
        sws_scale(swsCtx_, (const uint8_t * const*)frame_->data, frame_->linesize,
            0, frame_->height, (uint8_t * const*)img.data, img.linesize);

        frameCount_++;
        gotFrame = 1;
        av_frame_unref(frame_);
    }

    return 0;
}

int VideoDec::decode(ImageBlob<char>& img)
{
    int ret = 0;
    AVPacket pkt = { 0 };
    int gotFrame = 0;

    if (initialized_ == false)
    {
        // initialize decode context
        if (initialize(AVMEDIA_TYPE_VIDEO) != 0)
        {
            return -1;
        }

        // initialize sw scale context
        swsCtx_ = sws_getContext(decodeCtx_->width, decodeCtx_->height, decodeCtx_->pix_fmt,
            img.w, img.h, AV_PIX_FMT_RGB24, SWS_BICUBLIN, NULL, NULL, NULL);
        if (!swsCtx_)
        {
            fprintf(stderr, "failed to create software scale context\n");
            return -1;
        }

        initialized_ = true;
    }

    if (av_read_frame(formatCtx_, &pkt) >= 0)
    {
        do 
        {
            if (pkt.stream_index == streamIdx_) 
            {
                ret = decodePacket(&pkt, img, gotFrame);
            }

            av_packet_unref(&pkt);

            if (ret < 0 || gotFrame)
                break;

        } while (av_read_frame(formatCtx_, &pkt) >= 0);
    } 
    else
    {
        // flush cached frames
        ret = decodePacket(NULL, img, gotFrame);
    }

    return ret;
}

int VideoDec::destroy()
{
    avcodec_free_context(&decodeCtx_);
    avformat_close_input(&formatCtx_);
    av_frame_free(&frame_);
    sws_freeContext(swsCtx_);

    return 0;
}
