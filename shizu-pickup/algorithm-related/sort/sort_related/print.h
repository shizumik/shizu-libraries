#pragma once
#ifndef PRINT_H
#define PRINT_H

#include "commonheader.h"

void ArrayPrint(std::vector<int> &a)
{
	for (auto i : a)
		std::cout << i << " ";
	std::cout << std::endl;
}

#endif // !PRINT_H
