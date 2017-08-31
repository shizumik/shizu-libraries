#pragma once
#include <vector>

//o(n+k)
void countingsort(std::vector<int>& A, std::vector<int>& B, int k)
{
	std::vector<int> C(k + 1, 0);
	for (auto j = 0; j != A.size(); ++j)
		C[A[j]] = C[A[j]] + 1;
	for (int i = 1; i <= k;++i)
	{
		C[i] = C[i] + C[i - 1];
	}
	for (int i = A.size() - 1; i >= 0; --i)
	{
		B[C[A[i]] - 1] = A[i];  //B index from 0 , so C[A[i]] - 1
		C[A[i]] = C[A[i]] - 1;
	}
}