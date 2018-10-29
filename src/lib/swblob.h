
typedef struct _Size2D{
    int w;
    int h;
} Size2D;

typedef struct _MeanScale{
    double scale[4];
} MeanScale;

int blobFromImage(char* src, char*dst, double scale, Size2D sz, MeanScale ms, bool swapRB, bool crop);