#pragma once
#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "commonheader.h"

void InsertionSort(std::vector<int> &a)
{

	for (int j = 1; j != a.size(); ++j)
	{
		int key = a[j];

		int i = j - 1;
		while (i >= 0 && a[i] > key)
		{
			a[i + 1] = a[i];
			i = i - 1;
		}

		a[i + 1] = key;
	}
}

#endif // !INSERTION_SORT_H
