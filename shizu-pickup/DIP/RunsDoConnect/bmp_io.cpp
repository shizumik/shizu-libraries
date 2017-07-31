#pragma once
#include "bmp_io.h"
#include "ProcessAlgorithms.h"

BITMAPFILEHEADER strHead;
BITMAPINFOHEADER strInfo;
RGBQUAD strRGB;
int width, height;

IMAGEDATA* LoadBMP()
{
	char strFile[30];
	std::cout << "Load: Please Input BMP Filename: " << std::endl;
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
		fread(&strRGB, 1, sizeof(tagRGBQUAD), fpi);
		//showBmpHead(strHead);
		//showBmpInforHead(strInfo);
		width = strInfo.biWidth;
		height = strInfo.biHeight;
		if (strInfo.biBitCount == 1)
		{
			BYTE *imgdata = new BYTE[width * height / 8];
			fread(imgdata, sizeof(BYTE) * width / 8, height, fpi);
			fclose(fpi);
			IMAGEDATA *imagedata = new IMAGEDATA[width * height];
			int count = 0, k = 0;
			for (int i = 0; i < height; ++i)
				for (int j = 0; j < width, k < width * height / 8; ++j)
				{
					//(*(imagedata + i * width + j)).blue = 0;
					//(*(imagedata + i * width + j)).green = 0;
					//(*(imagedata + i * width + j)).red = 0;
					(*(imagedata + i * width + j)).blue = (*(imagedata + i * width + j)).green
						= (*(imagedata + i * width + j)).red = (*(imgdata + k) << count++ >> 7) == 1 ? 255 : 0;
					if (count > 7)
					{
						count = 0;
						k++;
					}

				}
			return imagedata;
		}
		else if (strInfo.biBitCount == 24)
		{
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
	strInfo.biWidth = width;
	strInfo.biHeight = height;
	WORD bfType = 0x4d42;
	//strHead.bfOffBits = 54;
	//strHead.bfSize = strHead.bfOffBits + width * sizeof(struct tagIMAGEDATA) * height;
	fwrite(&bfType, 1, sizeof(WORD), fpw);
	fwrite(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpw);

	strInfo.biSize = sizeof(BITMAPINFOHEADER);
	strInfo.biSizeImage = 0;
	strInfo.biBitCount = 1;
	strInfo.biClrUsed = 0;
	fwrite(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpw);
	fwrite(&strRGB, 1, sizeof(tagRGBQUAD), fpw);
	//paintbmp(img);

	fwrite(img, sizeof(struct tagIMAGEDATA) * width, height, fpw);
	fclose(fpw);
	delete[] img;
	return 0;
}

void showBmpHead(BITMAPFILEHEADER pBmpHead) {
	std::cout << "位图文件头:" << std::endl;
	std::cout << "文件大小:" << pBmpHead.bfSize << std::endl;
	std::cout << "保留字_1:" << pBmpHead.bfReserved1 << std::endl;
	std::cout << "保留字_2:" << pBmpHead.bfReserved2 << std::endl;
	std::cout << "实际位图数据的偏移字节数:" << pBmpHead.bfOffBits << std::endl << std::endl;
}

void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead) {
	std::cout << "位图信息头:" << std::endl;
	std::cout << "结构体的长度:" << pBmpInforHead.biSize << std::endl;
	std::cout << "位图宽:" << pBmpInforHead.biWidth << std::endl;
	std::cout << "位图高:" << pBmpInforHead.biHeight << std::endl;
	std::cout << "biPlanes平面数:" << pBmpInforHead.biPlanes << std::endl;
	std::cout << "biBitCount采用颜色位数:" << pBmpInforHead.biBitCount << std::endl;
	std::cout << "压缩方式:" << pBmpInforHead.biCompression << std::endl;
	std::cout << "biSizeImage实际位图数据占用的字节数:" << pBmpInforHead.biSizeImage << std::endl;
	std::cout << "X方向分辨率:" << pBmpInforHead.biXPelsPerMeter << std::endl;
	std::cout << "Y方向分辨率:" << pBmpInforHead.biYPelsPerMeter << std::endl;
	std::cout << "使用的颜色数:" << pBmpInforHead.biClrUsed << std::endl;
	std::cout << "重要颜色数:" << pBmpInforHead.biClrImportant << std::endl;
}

