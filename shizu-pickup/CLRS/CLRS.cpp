// CLRS.cpp : for test using

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//#include "insertionsort.h"
//#include "mergesort.h"
//#include "quicksort.h"
//#include "heapsort.h"
//#include "countingsort.h"
//#include "radixsort.h"
void print(vector<int>& vec)
{
	for (auto v : vec)
		cout << v << " ";
	cout << endl;
}
int main()
{
	vector<int> vec = { 3,1,2,5,6,9,7,8,3,1,0,4 };// 0 1 1 2 3 3 4 5 6 7 8 9
	vector<int> vec_radix = { 329,457,657,839,436,720,355 };
	auto sz = vec.size();
	//int max = 9;//obviously
	std::vector<int> ret(vec.size(), 0);
	//print(insertionsort(vec));
	//mergesort(vec, 0, vec.size() - 1);
	//quicksort(vec, 0, vec.size() - 1);
	//randomized_quicksort(vec, 0, sz - 1);
	//heapsort(vec);
	//countingsort(vec, ret, max);
	print(ret); // to print counting sort return array
	print(vec);

    return 0;
}

