#pragma once
#ifndef BMP_IO_H
#define BMP_IO_H

#include "bmp_format.h"
#include <iostream>



IMAGEDATA* LoadBMP(char strFile[30]);

int SaveBMP(char strFile[30], IMAGEDATA* img);

#endif // !BMP_IO_H
