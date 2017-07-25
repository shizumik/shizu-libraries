#include "commonheader.h"
#include "CorrelationAndConvonlution.h"
#include "matirx_operation.h"


int main()
{
	std::vector<std::vector<int> > matrix = { { 1,2,3,4 },
											{ 5,6,7,8 },
											{ 9,10,11,12 },
											{ 13,14,15,16 } };
	MatrixPrint(matrix);
	MatrixReverse(matrix);
	MatrixPrint(matrix);
	return 0;
}