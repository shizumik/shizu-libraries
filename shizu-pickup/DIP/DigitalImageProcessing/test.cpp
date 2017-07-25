#include "bmp_io.h"
#include "ProcessAlgorithms.h"

int main()
{
	IMAGEDATA *img = LoadBMP("YzolaPhilo.bmp");
	img = union_find(img);
	int response = SaveBMP("YzolaPhilo_Done.bmp", img);
	std::cout << response << std::endl;

	delete[] img;
	
	return 0;

}