#pragma once
#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "commonheader.h"

void Merge(std::vector<int> &a, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	std::vector<int> L(n1+1, 0);
	std::vector<int> R(n2+1, 0);
	for (int i = 0; i != n1; ++i)
		L[i] = a[p + i];
	for (int j = 0; j != n2; ++j)
		R[j] = a[q + j + 1];
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	int i = 0;
	int j = 0;
	for (int k = p; k != r + 1; ++k)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i = i + 1;
		}
		else
		{
			a[k] = R[j];
			j = j + 1;
		}
	}
}

void MergeSort(std::vector<int> &a, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		MergeSort(a, p, q);
		MergeSort(a, q + 1, r);
		Merge(a, p, q, r);
	}
}
#endif // !MERGE_SORT_H
