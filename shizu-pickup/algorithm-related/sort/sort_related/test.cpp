// insertion_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "commonheader.h"
#include "insertionsort.h"
#include "print.h"
#include "mergesort.h"
int main()
{
	/*Here Is Insertion Sort TEST */
	std::vector<int> a = { 5,2,4,6,1,3 };
	InsertionSort(a);
	ArrayPrint(a);

	MergeSort(a, 0, 5);
	ArrayPrint(a);

	std::vector<int> b = { 5,2,4,7,1,3,2,6 };
	MergeSort(b, 0, 7);
	ArrayPrint(b);


    return 0;
}

