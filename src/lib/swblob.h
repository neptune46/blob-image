#pragma once

#include "image.h"

int blobFromImage(ImageBlob<char>* src, ImageBlob<float>* dst, double scale, MeanScale ms, bool swapRB, bool crop);
