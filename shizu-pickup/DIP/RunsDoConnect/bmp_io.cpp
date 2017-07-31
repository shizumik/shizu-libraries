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
			delete[] imgdata;
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
	strInfo.biBitCount = 24;
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
	std::cout << "λͼ�ļ�ͷ:" << std::endl;
	std::cout << "�ļ���С:" << pBmpHead.bfSize << std::endl;
	std::cout << "������_1:" << pBmpHead.bfReserved1 << std::endl;
	std::cout << "������_2:" << pBmpHead.bfReserved2 << std::endl;
	std::cout << "ʵ��λͼ���ݵ�ƫ���ֽ���:" << pBmpHead.bfOffBits << std::endl << std::endl;
}

void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead) {
	std::cout << "λͼ��Ϣͷ:" << std::endl;
	std::cout << "�ṹ��ĳ���:" << pBmpInforHead.biSize << std::endl;
	std::cout << "λͼ��E" << pBmpInforHead.biWidth << std::endl;
	std::cout << "λͼ��:" << pBmpInforHead.biHeight << std::endl;
	std::cout << "biPlanesƽ����:" << pBmpInforHead.biPlanes << std::endl;
	std::cout << "biBitCount������ɫλ��:" << pBmpInforHead.biBitCount << std::endl;
	std::cout << "ѹ����ʽ:" << pBmpInforHead.biCompression << std::endl;
	std::cout << "biSizeImageʵ��λͼ����ռ�õ��ֽ���:" << pBmpInforHead.biSizeImage << std::endl;
	std::cout << "X����ֱ���:" << pBmpInforHead.biXPelsPerMeter << std::endl;
	std::cout << "Y����ֱ���:" << pBmpInforHead.biYPelsPerMeter << std::endl;
	std::cout << "ʹ�õ���ɫ��:" << pBmpInforHead.biClrUsed << std::endl;
	std::cout << "��Ҫ��ɫ��:" << pBmpInforHead.biClrImportant << std::endl;
}

