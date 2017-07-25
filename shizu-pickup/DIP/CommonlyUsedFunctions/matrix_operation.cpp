#include "matirx_operation.h"

void MatrixReverse(std::vector<std::vector<int> > &matrix)
{
	auto sz = matrix.size();
	//reverse row
	std::reverse(matrix.begin(), matrix.end());
	//reverse coloum
	for (auto row = 0; row != sz; ++row)
		std::reverse(matrix[row].begin(), matrix[row].end());
}

void  MatrixPrint(std::vector<std::vector<int> > &matrix)
{
	for (auto& vec : matrix)
	{
		for (auto& v : vec)
			std::cout << std::setw(2) << v << " ";
		std::cout << std::endl;
	}
}