#pragma once
#include <vector>

// o(nlgn) use extra two array L, R initial call mergesort(0,size-1)
void merge(std::vector<int>& vec, int p, int q, int r);
void mergesort(std::vector<int>& vec, int p, int r)
{
	if (p < r)
	{
		auto q = (p + r) / 2;
		mergesort(vec, p, q);
		mergesort(vec, q + 1, r);
		merge(vec, p, q, r);
	}
}
void merge(std::vector<int>& vec, int p, int q, int r)
{
	auto n1 = q - p + 1;   //n1+n2 = r-p+1 -> full
	auto n2 = r - q;       // L p,q R q+1,r  + 1
	std::vector<int> L(n1, 0);
	std::vector<int> R(n2, 0);
	L.push_back(INT_MAX);
	R.push_back(INT_MAX);
	for (auto i = 0; i != n1; ++i)
		L[i] = vec[p + i];
	for (auto j = 0; j != n2; ++j)
		R[j] = vec[q + j + 1];
	auto i = 0, j = 0;
	for (auto k = p; k <= r; ++k)    //r is a reachable index
	{                                  
		if (L[i] <= R[j])
		{
			vec[k] = L[i];
			i++;
		}
		else
		{
			vec[k] = R[j];
			j++;
		}
	}
}