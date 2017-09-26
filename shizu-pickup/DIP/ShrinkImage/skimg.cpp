#include "skimg.h"
using namespace std;
BITMAPFILEHEADER strHead;
BITMAPINFOHEADER strInfo;
WORD *strRGB; // two-value picture  62 - 54 = 8
int width, height;
RGBQUAD *RGBQ = new RGBQUAD[256];

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

		fread(RGBQ, sizeof(RGBQUAD), 256, fpi);   //1024 4x256
		cout << " READ RGBQ" << endl;
		for (int i = 0; i != 256; ++i)
		{
			cout << RGBQ[i].rgbBlue << " " << RGBQ[i].rgbGreen << " " << RGBQ[i].rgbRed << " " << RGBQ[i].rgbReserved << endl;
		}

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
	fwrite(RGBQ, sizeof(RGBQUAD), 256, fpw);
	fwrite(imageindex, sizeof(BYTE) * width, height, fpw);
	fclose(fpw);
	delete[] RGBQ;
	delete[] imageindex;
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

/* 文件头 - 信息头 - 调色板 - 像素信息索引 */
/* 调色板 4 BYTE ，索引1BYTE EX. 索引index*/
/* 那么 RGBQ[index] 即像素信息，RGBQ[index].rgbBlue ... 真实rgb信息*/

void shrinkImageX(BYTE* imageindex, int times)
{
	BYTE idx_x = 0; //width height  index offset
	BYTE pre, now,next,clr;
	int flag = 1;
	cout << "Shrink Start! " << endl;
	pre = RGBQ[0].rgbBlue;
	while (times--)
	{
		for (int row = 0; row != height; row++)
			for (int col = 0; col != width; col++)
			{
				idx_x = *(imageindex + row * width + col);
				now = RGBQ[idx_x].rgbBlue;
				if (now != pre)
				{
					if (flag)
					{
						*(imageindex + row * width + col) = 0;
						flag = 0;
					}
					else flag = 1;
				}
				pre = now;
			}
	}


}

void shrinkImageU(BYTE* imageindex)
{
}
