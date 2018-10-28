extern "C" {
#include <libavutil/imgutils.h>
#include <libavutil/parseutils.h>
#include <libswscale/swscale.h>
}

int main()
{
    uint8_t *src_data[4], *dst_data[4];
    int src_linesize[4], dst_linesize[4];
    int src_w = 640, src_h = 480, dst_w, dst_h;
    enum AVPixelFormat src_pix_fmt = AV_PIX_FMT_YUYV422, dst_pix_fmt = AV_PIX_FMT_RGB24;
    const char *dst_size = NULL;
    const char *src_filename = "test_yuyv_300x300.yuv", *dst_filename = "out.rgb";
    FILE *src_file = NULL, *dst_file = NULL;
    int src_bufsize = 0, dst_bufsize = 0;
    struct SwsContext *sws_ctx;
    int ret;

    dst_size = "300x300";
    if (av_parse_video_size(&dst_w, &dst_h, dst_size) < 0) {
        fprintf(stderr,
            "Invalid size '%s', must be in the form WxH or a valid size abbreviation\n",
            dst_size);
        exit(1);
    }

    /* create scaling context */
    sws_ctx = sws_getContext(src_w, src_h, src_pix_fmt,
        dst_w, dst_h, dst_pix_fmt,
        SWS_BILINEAR, NULL, NULL, NULL);

    if (!sws_ctx) {
        fprintf(stderr,
            "Impossible to create scale context for the conversion "
            "fmt:%s s:%dx%d -> fmt:%s s:%dx%d\n",
            av_get_pix_fmt_name(src_pix_fmt), src_w, src_h,
            av_get_pix_fmt_name(dst_pix_fmt), dst_w, dst_h);
        ret = AVERROR(EINVAL);
        goto end;
    }

    /* allocate source image buffers */
    if ((ret = av_image_alloc(src_data, src_linesize,
        src_w, src_h, src_pix_fmt, 16)) < 0) {
        fprintf(stderr, "Could not allocate source image\n");
        goto end;
    }
    src_bufsize = ret;

    src_file = fopen(src_filename, "rb");
    if (!src_file) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        exit(1);
    }
    fread(src_data[0], 1, src_bufsize, src_file);
    fclose(src_file);

    /* buffer is going to be written to raw video file, no alignment */
    if ((ret = av_image_alloc(dst_data, dst_linesize,
        dst_w, dst_h, dst_pix_fmt, 1)) < 0) {
        fprintf(stderr, "Could not allocate destination image\n");
        goto end;
    }
    dst_bufsize = ret;

    /* convert to destination format */
    sws_scale(sws_ctx, (const uint8_t * const*)src_data,
        src_linesize, 0, src_h, dst_data, dst_linesize);

    dst_file = fopen(dst_filename, "wb");
    if (!dst_file) {
        fprintf(stderr, "Could not open destination file %s\n", dst_filename);
        exit(1);
    }
    fwrite(dst_data[0], 1, dst_bufsize, dst_file);

end:
    fclose(src_file);
    fclose(dst_file);
    av_freep(&src_data[0]);
    av_freep(&dst_data[0]);
    sws_freeContext(sws_ctx);
    return 0;
}
