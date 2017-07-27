#pragma once
#ifndef PROCESS_ALGORITHM_H
#define PROCESS_ALGORITHM_H

#include "bmp_format.h"
#include "commonly_used.h"
#include "bmp_io.h"

void Binarization(IMAGEDATA* imagedata);

void fillRunVectors(IMAGEDATA* imagedata, int& NumberOfRuns, std::vector<int>& stRun,
	std::vector<int>& enRun, std::vector<int>& rowRun);
void firstPass(std::vector<int>& stRun, std::vector<int>& enRun, std::vector<int>& rowRun, int NumberOfRuns,
	std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalences, int offset);
void replaceSameLabel(std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalence);

void connect(IMAGEDATA* imagedata);

#endif // !PROCESS_ALGORITHM_H
