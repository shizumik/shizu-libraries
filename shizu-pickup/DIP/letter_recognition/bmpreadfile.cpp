#pragma once

#include "bmpreadfile.h"
#include <iostream>
#include <stdlib.h> 
#include <time.h>  
using namespace std;

bool readBmpFile()
{
	//��������  
	BITMAPFILEHEADER strHead;
	BITMAPINFOHEADER strInfo;

	char strFile[30];//bmp�ļ���  
	IMAGEDATA *imagedata = NULL;//��̬����洢ԭͼƬ��������Ϣ�Ķ�ά����  
	int width, height;//ͼƬ�Ŀ�Ⱥ͸߶�  
	cout << "��������Ҫ��ȡ���ļ���:" << endl;
	cin >> strFile;
	FILE *fpi, *fpw;
	fpi = fopen(strFile, "rb");
	if (fpi != NULL) {
		//�ȶ�ȡ�ļ�����  
		WORD bfType;
		fread(&bfType, 1, sizeof(WORD), fpi);
		if (0x4d42 != bfType)
		{
			cout << "the file is not a bmp file!" << endl;
			return NULL;
		}
		//��ȡbmp�ļ����ļ�ͷ����Ϣͷ  
		fread(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpi);
		showBmpHead(strHead);//��ʾ�ļ�ͷ  
		fread(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpi);
		showBmpInforHead(strInfo);//��ʾ�ļ���Ϣͷ  


		width = strInfo.biWidth;
		height = strInfo.biHeight;
		imagedata = (IMAGEDATA*)malloc(width * height * sizeof(IMAGEDATA));
		//��ʼ��ԭʼͼƬ����������   //BGR
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				(*(imagedata + i * width + j)).blue = 0;
				(*(imagedata + i * width + j)).green = 0;
				(*(imagedata + i *  width + j)).red = 0;
			}
		}

		//����ͼƬ����������  
		fread(imagedata, sizeof(struct tagIMAGEDATA) * width, height, fpi);

		fclose(fpi);
	}
	else
	{
		cout << "file open error!" << endl;
		return NULL;
	}


	//����bmpͼƬ  
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

	//������������  
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
			{    //ÿ��RGB���ǰ�ɫ��
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
	cout << "λͼ�ļ�ͷ:" << endl;
	cout << "�ļ���С:" << pBmpHead.bfSize << endl;
	cout << "������_1:" << pBmpHead.bfReserved1 << endl;
	cout << "������_2:" << pBmpHead.bfReserved2 << endl;
	cout << "ʵ��λͼ���ݵ�ƫ���ֽ���:" << pBmpHead.bfOffBits << endl << endl;
}

void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead) {
	cout << "λͼ��Ϣͷ:" << endl;
	cout << "�ṹ��ĳ���:" << pBmpInforHead.biSize << endl;
	cout << "λͼ��:" << pBmpInforHead.biWidth << endl;
	cout << "λͼ��:" << pBmpInforHead.biHeight << endl;
	cout << "biPlanesƽ����:" << pBmpInforHead.biPlanes << endl;
	cout << "biBitCount������ɫλ��:" << pBmpInforHead.biBitCount << endl;
	cout << "ѹ����ʽ:" << pBmpInforHead.biCompression << endl;
	cout << "biSizeImageʵ��λͼ����ռ�õ��ֽ���:" << pBmpInforHead.biSizeImage << endl;
	cout << "X����ֱ���:" << pBmpInforHead.biXPelsPerMeter << endl;
	cout << "Y����ֱ���:" << pBmpInforHead.biYPelsPerMeter << endl;
	cout << "ʹ�õ���ɫ��:" << pBmpInforHead.biClrUsed << endl;
	cout << "��Ҫ��ɫ��:" << pBmpInforHead.biClrImportant << endl;
}
