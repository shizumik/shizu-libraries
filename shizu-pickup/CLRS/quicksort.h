#pragma once
#include <vector>

//w-c o(n^2) a-c(olgn)   * randomized quicksort always has a o(nlgn)
int partition(std::vector<int>& vec, int p, int r);
void quicksort(std::vector<int>& vec, int p, int r)
{
	if (p < r)                        // choose a pivot then the vec is like 
	{                                 // [ { val < pivot} pivot { val > pivot}]
		auto q = partition(vec, p, r);
		quicksort(vec, p, q - 1);
		quicksort(vec, q + 1, r);
	}
}
int partition(std::vector<int>& vec, int p, int r)
{
	auto pivot = vec[r];
	auto i = p - 1;
	for (auto j = p; j != r; ++j)
	{
		if (vec[j] <= pivot)
		{
			i = i + 1;
			std::swap(vec[i], vec[j]);
		}
	}
	std::swap(vec[i + 1], vec[r]);
	return i + 1;
}

int randomized_partition(std::vector<int>& vec, int p, int r)
{
	auto i = rand() % (r - p + 1) + p;
	std::swap(vec[r], vec[i]);
	return partition(vec, p, r);
}

void randomized_quicksort(std::vector<int>& vec, int p, int r)
{
	if (p < r)
	{
		auto q = randomized_partition(vec, p, r);
		randomized_quicksort(vec, p, q - 1);
		randomized_quicksort(vec, q + 1, r);
	}
}
