#pragma once

#include <vector>

// o(n^2) in place in worst case
std::vector<int>& insertionsort(std::vector<int>& vec)
{
	for (auto j = 1; j != vec.size(); ++j)
	{
		auto key = vec[j];
		auto i = j - 1; //insert key to the right position
		while (i >= 0 && key < vec[i])         //3 2 1 1 3 4 6 5 7 8
		{									 
			vec[i + 1] = vec[i];
			i = i - 1;
		}
		vec[i + 1] = key;
	}
	return vec;
}