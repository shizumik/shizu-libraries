#pragma once
#ifndef BMP_READ_FILE_H
#define BMP_READ_FILE_H

#pragma pack(2)
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

//λͼ�ļ�ͷ����;  
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������  
//Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��  
typedef struct  tagBITMAPFILEHEADER {
	//WORD bfType;//�ļ����ͣ�������0x424D�����ַ���BM��  
	DWORD bfSize;//�ļ���С  
	WORD bfReserved1;//������  
	WORD bfReserved2;//������  
	DWORD bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���  
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;//��Ϣͷ��С  
	LONG biWidth;//ͼ����  
	LONG biHeight;//ͼ��߶�  
	WORD biPlanes;//λƽ����������Ϊ1  
	WORD biBitCount;//ÿ����λ��  
	DWORD  biCompression; //ѹ������  
	DWORD  biSizeImage; //ѹ��ͼ���С�ֽ���  
	LONG  biXPelsPerMeter; //ˮƽ�ֱ���  
	LONG  biYPelsPerMeter; //��ֱ�ֱ���  
	DWORD  biClrUsed; //λͼʵ���õ���ɫ����  
	DWORD  biClrImportant; //��λͼ����Ҫ��ɫ����  
}BITMAPINFOHEADER; //λͼ��Ϣͷ����  

//�Ҷ�ͼҲ����õ�,24bitͼ����Ҫ��
//typedef struct tagRGBQUAD {
//	BYTE rgbBlue; //����ɫ����ɫ����  
//	BYTE rgbGreen; //����ɫ����ɫ����  
//	BYTE rgbRed; //����ɫ�ĺ�ɫ����  
//	BYTE rgbReserved; //����ֵ  
//}RGBQUAD;//��ɫ�嶨��  

		 //������Ϣ  
typedef struct tagIMAGEDATA
{
	BYTE red;
	BYTE green;
	BYTE blue;
}IMAGEDATA;


bool readBmpFile();
//��ʾλͼ�ļ�ͷ��Ϣ  

void showBmpHead(BITMAPFILEHEADER pBmpHead);
void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead);

#endif // !BMP_READ_FILE_H
