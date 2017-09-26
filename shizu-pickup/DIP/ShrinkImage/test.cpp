#include "skimg.h"
#include <ctime>
using namespace std;
int main()
{
	clock_t st, end;
	BYTE *img = LoadBMP();
	st = clock();
	shrinkImageX(img,2);
	end = clock();
	int f;
	f = SaveBMP(img);
	cout << f << endl;
	cout << "runtime: " << end - st << endl;
	system("pause");
	return 0;
}
