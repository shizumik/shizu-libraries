#pragma once
#ifndef PROCESS_ALGORITHM_H
#define PROCESS_ALGORITHM_H

#include "bmp_format.h"
#include "commonly_used.h"
#include "bmp_io.h"

void Binarization(IMAGEDATA* imagedata);
void paintbmp(IMAGEDATA* imagedata);

// connect regions algorithm start
void fillRunVectors(IMAGEDATA* imagedata, int& NumberOfRuns, std::vector<int>& stRun,
	std::vector<int>& enRun, std::vector<int>& rowRun);
void firstPass(std::vector<int>& stRun, std::vector<int>& enRun, std::vector<int>& rowRun, int NumberOfRuns,
	std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalences, int offset);
void replaceSameLabel(std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalence);
void connect(IMAGEDATA* imagedata);
// connect regions algorithm end


void floodfill(int x, int y, int oldcolor, int newcolor);
#define color(i,j) ((*(imagedata + i * width + j)).red + (*(imagedata + i * width + j)).green + (*(imagedata + i * width + j)).blue)
#endif // !PROCESS_ALGORITHM_H
