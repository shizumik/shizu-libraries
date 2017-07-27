#pragma once
#include "bmp_io.h"

BITMAPFILEHEADER strHead;
BITMAPINFOHEADER strInfo;
int width, height;

IMAGEDATA* LoadBMP()
{
	char strFile[30];
	std::cout << "Please Input BMP Filename: " << std::endl;
	std::cin >> strFile;
	FILE *fpi;
	fpi = fopen(strFile, "rb");
	if (fpi != NULL)
	{
		WORD bfType;
		fread(&bfType, 1, sizeof(WORD), fpi);
		if (0x4d42 != bfType)
		{
			std::cerr << "The file is not a bmp file!" << std::endl;
			return NULL;
		}
		fread(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpi);
		fread(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpi);
		width = strInfo.biWidth;
		height = strInfo.biHeight;
		IMAGEDATA *imagedata = new IMAGEDATA[width * height];
		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
			{
				(*(imagedata + i * width + j)).blue = 0;
				(*(imagedata + i * width + j)).green = 0;
				(*(imagedata + i * width + j)).red = 0;
			}
		fread(imagedata, sizeof(struct tagIMAGEDATA) * width, height, fpi);
		fclose(fpi);
		return imagedata;
	}
	else
	{
		std::cerr << "file open error!" << std::endl;
		return NULL;
	}

}


int SaveBMP(IMAGEDATA* img)
{
	char strFile[30];
	std::cout << "Please Input BMP Filename: " << std::endl;
	std::cin >> strFile;
	FILE *fpw;
	if ((fpw = fopen(strFile, "wb")) == NULL)
	{
		std::cerr << "create bmp file error!" << std::endl;
		return -1;
	}
	WORD bfType = 0x4d42;
	fwrite(&bfType, 1, sizeof(WORD), fpw);
	fwrite(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpw);
	strInfo.biWidth = width;
	strInfo.biHeight = height;
	fwrite(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpw);
	//for(int i = 0; i < height; ++i)
	//	for (int j = 0; j < width; ++j)
	//	{
	//		fwrite(&(*(img + i * width + j)).red, 1, sizeof(BYTE), fpw);
	//		fwrite(&(*(img + i * width + j)).green, 1, sizeof(BYTE), fpw);
	//		fwrite(&(*(img + i * width + j)).blue, 1, sizeof(BYTE), fpw);
	//	}
	fwrite(img, sizeof(struct tagIMAGEDATA) * width, height, fpw);

	fclose(fpw);
	return 0;
}
