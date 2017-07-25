#include "CorrelationAndConvonlution.h"
#include "matirx_operation.h"

void correlation(std::vector<std::vector<int> > &w, std::vector<std::vector<int> > f)
{

}

void convonlution(std::vector<std::vector<int> > &w, std::vector<std::vector<int> > f)
{
	MatrixReverse(w);
	correlation(w, f);
}