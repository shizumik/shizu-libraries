#include "bmp_io.h"
#include "ProcessAlgorithms.h"

int main()
{
	clock_t start, end;
	IMAGEDATA *img = LoadBMP();
	//Binarization(img);

	start = clock();
	//connect(img);
	end = clock();

	int response = SaveBMP(img);
	std::cout << response << std::endl;
	//std::cout << "Runtime: " << end - start << std::endl;

	//BYTE c1 = 0x13;
	//for(int i = 0; i < 8; ++i)
	//	std::cout << ((c1 << i >> 7) & 1) << " ";
	//int k = 0;
	//for (int i = 0; i < 10; ++i)
	//	for (int j = 0; j < 10; ++j)
	//	{
	//		std::cout << i << " " << j << " " << k++ << std::endl;
	//		if (k == 7) k = 0;
	//	}
	return 0;

}