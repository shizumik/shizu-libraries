#pragma once
#ifndef BMP_IO_H
#define BMP_IO_H

#include "bmp_format.h"
#include <iostream>

IMAGEDATA* LoadBMP();

int SaveBMP24Bit(IMAGEDATA* img);
int SaveBMPBin(IMAGEDATA* img);


#endif // !BMP_IO_H
