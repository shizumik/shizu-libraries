#pragma once

#include <vector>	

//max heap o(nlgn)
int parent(int i)
{
	return (i - 1) / 2;
}

int left(int i)
{
	return 2*i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void max_heapify(std::vector<int>& A, int i, int heapsz)
{
	auto l = left(i);
	auto r = right(i);
	auto largest = i;
	if (l <= heapsz && A[l] > A[i])
		largest = l;
	else largest = i;
	if (r <= heapsz && A[r] > A[largest])
		largest = r;
	if (largest != i)
	{
		std::swap(A[i], A[largest]);
		max_heapify(A, largest,heapsz);
	}
}

void build_max_heap(std::vector<int>& A)
{
	for (int i = (A.size() - 1) / 2; i >= 0; --i)
		max_heapify(A, i,A.size() - 1);
}

void heapsort(std::vector<int>& A)
{
	build_max_heap(A);
	auto heapsz = A.size() - 1;
	for (auto i = A.size() - 1; i >= 1; --i)
	{
		std::swap(A[0], A[i]);
		heapsz--;
		max_heapify(A, 0,heapsz);
	}
}