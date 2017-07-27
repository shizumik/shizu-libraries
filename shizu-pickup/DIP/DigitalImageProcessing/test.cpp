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

	int response = SaveBMPBin(img);
	std::cout << response << std::endl;
	delete[] img;

	std::cout << "Runtime: " << end - start << std::endl;

	return 0;

}