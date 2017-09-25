#include "skimg.h"

BITMAPFILEHEADER strHead;
BITMAPINFOHEADER strInfo;
WORD *strRGB; // two-value picture  62 - 54 = 8
int width, height;
BYTE *RGBQ = new BYTE[1024];

BYTE* LoadBMP()
{
	char strFile[30];
	std::cout << "Load: Please Input BMP Filename: " << std::endl;
	std::cin >> strFile;
	FILE *fpi;
	fpi = fopen(strFile, "rb");
	if (fpi != NULL)
	{
		WORD bfType;
		fread(&bfType, sizeof(WORD), 1, fpi);
		if (0x4d42 != bfType)
		{
			std::cerr << "The file is not a bmp file!" << std::endl;
			return NULL;
		}
		fread(&strHead, sizeof(tagBITMAPFILEHEADER), 1, fpi);
		fread(&strInfo, sizeof(tagBITMAPINFOHEADER), 1, fpi);

		width = strInfo.biWidth;
		height = strInfo.biHeight;

		fread(RGBQ, sizeof(BYTE), 1024, fpi);   //1024 4x256

		BYTE *imageindex = new BYTE[width * height]; 
		fread(imageindex, sizeof(BYTE) * width, height, fpi);
		fclose(fpi);
		return imageindex;
	}
	else
	{
		std::cerr << "file open error!" << std::endl;
		return NULL;
	}
}


int SaveBMP(BYTE* imageindex)
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

	fwrite(&bfType, sizeof(WORD), 1, fpw);
	fwrite(&strHead, sizeof(tagBITMAPFILEHEADER), 1, fpw);
	fwrite(&strInfo, sizeof(tagBITMAPINFOHEADER), 1, fpw);
	fwrite(RGBQ, sizeof(BYTE), 1024, fpw);
	fwrite(imageindex, sizeof(BYTE) * width, height, fpw);
	fclose(fpw);
	delete[] RGBQ;
	delete[] imageindex;
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
	std::cout << "λͼ��:" << pBmpInforHead.biWidth << std::endl;
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

/* �ļ�ͷ - ��Ϣͷ - ��ɫ�� - ������Ϣ���� */
/* ��ɫ�� 4 BYTE ������1BYTE EX. ����index*/
/* ��ô RGBQ[index] ��������Ϣ��RGBQ[index].rgbBlue ... ��ʵrgb��Ϣ*/

void shrinkImage(BYTE* imageindex)
{
	BYTE idx; //width height  index offset

}