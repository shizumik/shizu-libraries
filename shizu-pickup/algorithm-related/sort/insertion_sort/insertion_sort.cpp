// insertion_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

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

void ArrayPrint(std::vector<int> &a)
{
	for(auto i : a)
		std::cout << i << " ";
	std::cout << std::endl;
}

int main()
{
	std::vector<int> a = { 5,2,4,6,1,3 };
	InsertionSort(a);
	ArrayPrint(a);
    return 0;
}

