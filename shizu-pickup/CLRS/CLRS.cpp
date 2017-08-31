// CLRS.cpp : for test using

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"
#include "heapsort.h"
void print(vector<int>& vec)
{
	for (auto v : vec)
		cout << v << " ";
	cout << endl;
}
int main()
{
	vector<int> vec = { 3,1,2,5,6,9,7,8,3,1,0,4 };// 0 1 1 2 3 3 4 5 6 7 8 9
	auto sz = vec.size();
	//print(insertionsort(vec));
	//mergesort(vec, 0, vec.size() - 1);
	//quicksort(vec, 0, vec.size() - 1);
	//randomized_quicksort(vec, 0, sz - 1);
	//heapsort(vec);
	print(vec);

    return 0;
}

