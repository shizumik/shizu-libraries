#pragma once

#include "ProcessAlgorithms.h"
 
extern BITMAPFILEHEADER strHead;
extern BITMAPINFOHEADER strInfo;
extern int width, height;

void Binarization(IMAGEDATA* imagedata)
{
	for(int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
		{
			int gray_level = (*(imagedata + i * width + j)).red * 0.3 + (*(imagedata + i * width + j)).green * 0.59
				+ (*(imagedata + i * width + j)).blue * 0.11;
			gray_level = gray_level > 128 ? 255 : 0;   //change your treethold here ps:lena 60
			(*(imagedata + i *  width + j)).red = gray_level; //0.3
			(*(imagedata + i *  width + j)).green = gray_level;//0.59
			(*(imagedata + i *  width + j)).blue = gray_level;//0.11
		}
}

void paintbmp(IMAGEDATA* imagedata)
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
		{
			if (color(i, j) != 0)
			{
				(*(imagedata + i * width + j)).blue = 255;
				(*(imagedata + i * width + j)).green = 255;
				(*(imagedata + i * width + j)).red = 255;
			}
			else
			{
				(*(imagedata + i * width + j)).blue = 0;
				(*(imagedata + i * width + j)).green = 0;
				(*(imagedata + i * width + j)).red = 0;
			}
		}
}

void fillRunVectors(IMAGEDATA* imagedata, int& NumberOfRuns, std::vector<int>& stRun,
	std::vector<int>& enRun, std::vector<int>& rowRun)
{
	#define rgb_sum(i,j) ((*(imagedata + i * width + j)).red + (*(imagedata + i * width + j)).green + (*(imagedata + i * width + j)).blue)
	for (int i = 0; i < height; ++i)               //o(height * width)
	{
		if (rgb_sum(i, 0) != 0)           
		{
			NumberOfRuns++;
			stRun.push_back(0);
			rowRun.push_back(i);
		}
		for (int j = 1; j < width; ++j)
		{
			if (rgb_sum(i, j - 1) == 0 && rgb_sum(i, j) != 0)
			{
				NumberOfRuns++;
				stRun.push_back(j);
				rowRun.push_back(i);
			}
			else if (rgb_sum(i, j - 1) != 0 && rgb_sum(i, j) == 0)
			{
				enRun.push_back(j);   
			}

		}
		if (rgb_sum(i, width - 1))        
		{
			enRun.push_back(width - 1);
		}

	}
	std::cout << "NumberOfRuns: " << NumberOfRuns << std::endl;
}

void firstPass(std::vector<int>& stRun, std::vector<int>& enRun, std::vector<int>& rowRun, int NumberOfRuns,
	std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalences, int offset)
{
	runLabels.assign(NumberOfRuns, 0);
	int idxLabel = 1;
	int curRowIdx = 0;
	int firstRunOnCur = 0;
	int firstRunOnPre = 0;
	int lastRunOnPre = -1;
	for (int i = 0; i < NumberOfRuns; i++)
	{
		if (rowRun[i] != curRowIdx)
		{
			curRowIdx = rowRun[i];
			firstRunOnPre = firstRunOnCur;
			lastRunOnPre = i - 1;
			firstRunOnCur = i;
		}
		for (int j = firstRunOnPre; j <= lastRunOnPre; j++)
		{
			if (stRun[i] <= enRun[j] + offset && enRun[i] >= stRun[j] - offset && rowRun[i] == rowRun[j] + 1)
			{
				if (runLabels[i] == 0) // 没有被标号过
					runLabels[i] = runLabels[j];
				else if (runLabels[i] != runLabels[j])// 已经被标号             
					equivalences.push_back(std::make_pair(runLabels[i], runLabels[j])); // 保存等价对
			}
		}
		if (runLabels[i] == 0) // 没有与前一列的任何run重合
		{
			//std::cout << "enter here" << std::endl;
			runLabels[i] = idxLabel++;
			//std::cout << "i: " << runLabels[i] << std::endl;
		}

	}
	std::cout << "equivalence pairs number: " << equivalences.size() << " ";
	std::cout << std::endl;
}

void replaceSameLabel(std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalence)
{
	int maxLabel = *max_element(runLabels.begin(), runLabels.end());
	std::vector<std::vector<bool>> eqTab(maxLabel, std::vector<bool>(maxLabel, false));
	std::vector<std::pair<int, int>>::iterator vecPairIt = equivalence.begin();
	while (vecPairIt != equivalence.end()) //无向图邻接矩阵
	{
		eqTab[vecPairIt->first - 1][vecPairIt->second - 1] = true;
		eqTab[vecPairIt->second - 1][vecPairIt->first - 1] = true;
		vecPairIt++;
	}
	std::vector<int> labelFlag(maxLabel, 0);
	std::vector<std::vector<int>> equaList;
	std::vector<int> tempList;
	std::cout << "maxLabel: " << maxLabel << std::endl;   // label start from 1
	for (int i = 1; i <= maxLabel; i++)
	{
		if (labelFlag[i - 1])
		{
			continue;
		}
		labelFlag[i - 1] = equaList.size() + 1;
		tempList.push_back(i);
		for (std::vector<int>::size_type j = 0; j < tempList.size(); j++)   //if pairs equal, add to tempList
		{
			for (std::vector<bool>::size_type k = 0; k != eqTab[tempList[j] - 1].size(); k++)
			{
				if (eqTab[tempList[j] - 1][k] && !labelFlag[k])
				{
					tempList.push_back(k + 1);
					labelFlag[k] = equaList.size() + 1;
				}
			}
		}
		equaList.push_back(tempList);
		tempList.clear();
	}
	std::cout << "connected regions: " << equaList.size() << std::endl; // numbers of the connect regions
	for (std::vector<int>::size_type i = 0; i != runLabels.size(); i++)
	{
		runLabels[i] = labelFlag[runLabels[i] - 1];  //1-17
	}
	std::cout << "runLabels numbers: " << runLabels.size() << std::endl;
}

void connect(IMAGEDATA* imagedata)
{
	int NumberOfRuns = 0;
	std::vector<int> stRun, enRun, rowRun;
	fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun);
	std::vector<int> runLabels;
	std::vector<std::pair<int, int>> equivalences;
	int offset = 1; //1 8-n; 0 4-n
	firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	replaceSameLabel(runLabels, equivalences);
	for (int i = 0; i < runLabels.size(); ++i)
	{
		for (int j = stRun[i]; j < enRun[i]; ++j)
		{
			int rgb = runLabels[i] * 20 > 256 ? 200 : runLabels[i] * 20;
			(*(imagedata + rowRun[i] * width + j)).red = rgb * 0.3 * runLabels[i];
			(*(imagedata + rowRun[i] * width + j)).green = rgb * 0.59 * runLabels[i];
			(*(imagedata + rowRun[i] * width + j)).blue = rgb * 0.11 * runLabels[i];
		}
	}

}

//void floodfill(IMAGEDATA* imagedata, int x, int y, int oldcolor, int newcolor)
//{
//	if (color(x, y) == oldcolor)
//	{
//		putpixel(x, y, newcolor);
//		floodFill(imagedata, x + 1, y, oldcolor, newcolor);
//		floodFill(imagedata, x, y + 1, oldcolor, newcolor);
//		floodFill(imagedata, x - 1, y, oldcolor, newcolor);
//		floodFill(imagedata, x, y - 1, oldcolor, newcolor);
//	}
//}