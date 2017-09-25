#include "skimg.h"
using namespace std;

int main()
{

	BYTE *img = LoadBMP();
	int f;
	f = SaveBMP(img);
	cout << f << endl;
	return 0;
}