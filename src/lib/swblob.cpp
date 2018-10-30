#include "swblob.h"

extern "C" {
#include <libavutil/imgutils.h>
#include <libavutil/parseutils.h>
#include <libswscale/swscale.h>
}

inline AVPixelFormat convertFmt(ImageFmt fmt)
{
    AVPixelFormat avFmt = AV_PIX_FMT_NONE;
    switch (fmt)
    {
    case IMG_FMT_YUYV:
        avFmt = AV_PIX_FMT_YUYV422;
        break;
    case IMG_FMT_RGB24:
        avFmt = AV_PIX_FMT_RGB24;
        break;
    }
    return avFmt;
}

void normalize(uint8_t* src, int w, int h, double scale, MeanScale ms, float* dst)
{
    int pitch = w * 3;
    for (int y=0; y<h; y++) 
    {
        for (int x=0; x<w; x++)
        {
            dst[y*pitch + x * 3 + 0] = (float)((double)src[y*pitch + x * 3 + 0] - ms.scale[0]) * scale;
            dst[y*pitch + x * 3 + 1] = (float)((double)src[y*pitch + x * 3 + 1] - ms.scale[1]) * scale;
            dst[y*pitch + x * 3 + 2] = (float)((double)src[y*pitch + x * 3 + 2] - ms.scale[2]) * scale;
        }
    }
}

int blobFromImage(BlobImage<char>* src, BlobImage<float>* dst, double scale, MeanScale ms, bool swapRB, bool crop)
{
    int ret;
    uint8_t *rgbData[4];
    int rgbLinesize[4];
    int rgbW = dst->w;
    int rgbH = dst->h;
    int rgbBufsize = 0;
    struct SwsContext *swsCtx;

    if ((rgbBufsize = av_image_alloc(rgbData, rgbLinesize,
        rgbW, rgbH, convertFmt(dst->fmt), 1)) < 0) 
    {
        fprintf(stderr, "failed to allocate rgb surface\n");
        ret = -1;
        goto _finish;
    }

    swsCtx = sws_getContext(src->w, src->h, convertFmt(src->fmt),
        rgbW, rgbH, convertFmt(dst->fmt),
        SWS_BILINEAR, NULL, NULL, NULL);
    if (!swsCtx) 
    {
        fprintf(stderr, "failed to create software scale context\n");
        ret = -1;
        goto _finish;
    }

    normalize(rgbData[0], rgbW, rgbH, scale, ms, dst->data[0]);

_finish:
    av_freep(&rgbData[0]);
    sws_freeContext(swsCtx);
    return 0;
}
