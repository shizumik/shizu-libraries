#pragma once
#include "countingsort.h"
//TODO:
void radixsort(std::vector<int>& A, std::vector<int>& B, int d)
{
	for (int i = 1; i != d; ++i)
		countingsort(A, B, 8);
}