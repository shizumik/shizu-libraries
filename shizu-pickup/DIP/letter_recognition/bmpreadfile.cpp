#pragma once

#include "bmpreadfile.h"
#include <iostream>
#include <stdlib.h> 
#include <time.h>  
using namespace std;

bool readBmpFile()
{
	//变量定义  
	BITMAPFILEHEADER strHead;
	BITMAPINFOHEADER strInfo;

	char strFile[30];//bmp文件名  
	IMAGEDATA *imagedata = NULL;//动态分配存储原图片的像素信息的二维数组  
	int width, height;//图片的宽度和高度  
	cout << "请输入所要读取的文件名:" << endl;
	cin >> strFile;
	FILE *fpi, *fpw;
	fpi = fopen(strFile, "rb");
	if (fpi != NULL) {
		//先读取文件类型  
		WORD bfType;
		fread(&bfType, 1, sizeof(WORD), fpi);
		if (0x4d42 != bfType)
		{
			cout << "the file is not a bmp file!" << endl;
			return NULL;
		}
		//读取bmp文件的文件头和信息头  
		fread(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpi);
		showBmpHead(strHead);//显示文件头  
		fread(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpi);
		showBmpInforHead(strInfo);//显示文件信息头  


		width = strInfo.biWidth;
		height = strInfo.biHeight;
		imagedata = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));
		//初始化原始图片的像素数组   //BGR
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				(*(imagedata + i * width + j)).blue = 0;
				(*(imagedata + i * width + j)).green = 0;
				(*(imagedata + i *  width + j)).red = 0;
			}
		}

		//读出图片的像素数据  
		fread(imagedata, sizeof(struct tagIMAGEDATA) * width, height, fpi);

		fclose(fpi);
	}
	else
	{
		cout << "file open error!" << endl;
		return NULL;
	}


	//保存bmp图片  
	if ((fpw = fopen("YzolaPhilo_OUT.bmp", "wb")) == NULL)
	{
		cout << "create the bmp file error!" << endl;
		return NULL;
	}
	//BMPFile||Fnfo Header
	WORD bfType_w = 0x4d42;
	fwrite(&bfType_w, 1, sizeof(WORD), fpw);
	fwrite(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpw);
	strInfo.biWidth = width;
	strInfo.biHeight = height;
	fwrite(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpw);

	//保存像素数据  
	//srand(time(NULL));

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int rgb_sum = (*(imagedata + i * width + j)).red + (*(imagedata + i * width + j)).green
				+ (*(imagedata + i * width + j)).blue;
		
			if (i < 120)
			{
				(*(imagedata + i * width + j)).blue = 0;
				(*(imagedata + i * width + j)).green = 0;
				(*(imagedata + i *  width + j)).red = 0;
				fwrite(&(*(imagedata + i * width + j)).red, 1, sizeof(BYTE), fpw);
				fwrite(&(*(imagedata + i * width + j)).green, 1, sizeof(BYTE), fpw);
				fwrite(&(*(imagedata + i * width + j)).blue, 1, sizeof(BYTE), fpw);
			}
			else if (rgb_sum != 0)
			{    //每个RGB都是白色！
				//cout << rand() % 255 + 1 << endl;
				(*(imagedata + i * width + j)).blue = rand() % 256;
				//cout << rand() % 255 + 1 << endl;
				(*(imagedata + i * width + j)).green = rand() % 256;
				//cout << rand() % 255 + 1 << endl;
				(*(imagedata + i *  width + j)).red = rand() % 256;
				fwrite(&(*(imagedata + i * width + j)).red, 1, sizeof(BYTE), fpw);
				fwrite(&(*(imagedata + i * width + j)).green, 1, sizeof(BYTE), fpw);
				fwrite(&(*(imagedata + i * width + j)).blue, 1, sizeof(BYTE), fpw);
			}
			else
			{
				fwrite(&(*(imagedata + i * width + j)).red, 1, sizeof(BYTE), fpw);
				fwrite(&(*(imagedata + i * width + j)).green, 1, sizeof(BYTE), fpw);
				fwrite(&(*(imagedata + i * width + j)).blue, 1, sizeof(BYTE), fpw);
			}
		}
	}
	fclose(fpw);

	//free memory  
	delete[] imagedata;

}

void showBmpHead(BITMAPFILEHEADER pBmpHead) {
	cout << "位图文件头:" << endl;
	cout << "文件大小:" << pBmpHead.bfSize << endl;
	cout << "保留字_1:" << pBmpHead.bfReserved1 << endl;
	cout << "保留字_2:" << pBmpHead.bfReserved2 << endl;
	cout << "实际位图数据的偏移字节数:" << pBmpHead.bfOffBits << endl << endl;
}

void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead) {
	cout << "位图信息头:" << endl;
	cout << "结构体的长度:" << pBmpInforHead.biSize << endl;
	cout << "位图宽:" << pBmpInforHead.biWidth << endl;
	cout << "位图高:" << pBmpInforHead.biHeight << endl;
	cout << "biPlanes平面数:" << pBmpInforHead.biPlanes << endl;
	cout << "biBitCount采用颜色位数:" << pBmpInforHead.biBitCount << endl;
	cout << "压缩方式:" << pBmpInforHead.biCompression << endl;
	cout << "biSizeImage实际位图数据占用的字节数:" << pBmpInforHead.biSizeImage << endl;
	cout << "X方向分辨率:" << pBmpInforHead.biXPelsPerMeter << endl;
	cout << "Y方向分辨率:" << pBmpInforHead.biYPelsPerMeter << endl;
	cout << "使用的颜色数:" << pBmpInforHead.biClrUsed << endl;
	cout << "重要颜色数:" << pBmpInforHead.biClrImportant << endl;
}
