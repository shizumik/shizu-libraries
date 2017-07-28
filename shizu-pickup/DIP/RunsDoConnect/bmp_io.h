#pragma once
#ifndef BMP_IO_H
#define BMP_IO_H

#include "bmp_format.h"
#include <iostream>

IMAGEDATA* LoadBMP();

int SaveBMP(IMAGEDATA* img);

void showBmpHead(BITMAPFILEHEADER pBmpHead);
void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead);
#endif // !BMP_IO_H
