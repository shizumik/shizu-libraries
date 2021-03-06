#pragma once

#include "ProcessAlgorithms.h"

extern BITMAPFILEHEADER strHead;
extern BITMAPINFOHEADER strInfo;
extern int width, height;

void Binarization(IMAGEDATA* imagedata)
{
	for (int i = 0; i < height; ++i)
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



void fillRunVectors(IMAGEDATA* imagedata, int& NumberOfRuns, std::vector<int>& stRun,
	std::vector<int>& enRun, std::vector<int>& rowRun, int st_height, int en_height)
{
#define rgb_sum(i,j) ((*(imagedata + i * width + j)).red + (*(imagedata + i * width + j)).green + (*(imagedata + i * width + j)).blue)
	for (int i = st_height; i < en_height; ++i)               //o(height * width)
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
	//std::cout << "NumberOfRuns: " << NumberOfRuns << std::endl;
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
				if (runLabels[i] == 0)
					runLabels[i] = runLabels[j];
				else if (runLabels[i] != runLabels[j])
					equivalences.push_back(std::make_pair(runLabels[i], runLabels[j]));
			}
		}
		if (runLabels[i] == 0)
		{
			//std::cout << "enter here" << std::endl;
			runLabels[i] = idxLabel++;
			//std::cout << "i: " << runLabels[i] << std::endl;
		}

	}
	//std::cout << "equivalence pairs number: " << equivalences.size() << " ";
	//std::cout << std::endl;
}

void replaceSameLabel(std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalence)
{
	int maxLabel = *max_element(runLabels.begin(), runLabels.end());
	std::vector<std::vector<bool>> eqTab(maxLabel, std::vector<bool>(maxLabel, false));
	std::vector<std::pair<int, int>>::iterator vecPairIt = equivalence.begin();
	while (vecPairIt != equivalence.end())
	{
		eqTab[vecPairIt->first - 1][vecPairIt->second - 1] = true;
		eqTab[vecPairIt->second - 1][vecPairIt->first - 1] = true;
		vecPairIt++;
	}
	std::vector<int> labelFlag(maxLabel, 0);
	std::vector<std::vector<int>> equaList;
	std::vector<int> tempList;
	//std::cout << "maxLabel: " << maxLabel << std::endl;   // label start from 1
	for (int i = 1; i <= maxLabel; i++)
	{
		if (labelFlag[i - 1])							//run already done.
		{
			continue;
		}
		labelFlag[i - 1] = equaList.size() + 1;
		tempList.push_back(i);
		for (std::vector<int>::size_type j = 0; j < tempList.size(); j++)
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
		tempList.clear();									// clear templist, do the next 
	}
	//std::cout << "connected regions: " << equaList.size() << std::endl; // numbers of the connect regions
	for (std::vector<int>::size_type i = 0; i != runLabels.size(); i++)
	{
		runLabels[i] = labelFlag[runLabels[i] - 1];  //1-17       
	}
	//std::cout << "runLabels numbers: " << runLabels.size() << std::endl;
}

void paintbmp(IMAGEDATA* imagedata, std::vector<int>& stRun,
	std::vector<int>& enRun, std::vector<int>& rowRun, std::vector<int>& runLabels)
{
	for (int i = 0; i < runLabels.size(); ++i)
		for (int j = stRun[i]; j < enRun[i]; ++j)
		{
			int rgb = runLabels[i] * 20 > 256 ? 200 : runLabels[i] * 20;
			(*(imagedata + rowRun[i] * width + j)).red = rgb * 0.3 * runLabels[i];
			(*(imagedata + rowRun[i] * width + j)).green = rgb * 0.59 * runLabels[i];
			(*(imagedata + rowRun[i] * width + j)).blue = rgb * 0.11 * runLabels[i];
		}
}

void union_pre(std::vector<int>& stRun, std::vector<int>& enRun, std::vector<int>& rowRun, std::vector<int>& runLabels,
	std::vector<int>& stRun1, std::vector<int>& enRun1, std::vector<int>& runLabels1, int tempRuns1, int offset, int h)
{
	for (int i = 0; rowRun[i] == h; ++i)
		for (int j = 0; j < tempRuns1; ++j)
		{
			if (stRun[i] <= enRun1[j] + offset && enRun[i] >= stRun1[j] - offset/* && rowRun[i] == rowRun[j] + 1*/)
			{
				int temp = runLabels[i];
				for (int k = 0; k != runLabels.size(); ++k)
				{
					if (runLabels[k] == temp)
						runLabels[k] = runLabels1[j];
				}
			}
		}
}

void check_clear(std::vector<int>& stRun, std::vector<int>& enRun, std::vector<int>& rowRun,
	std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalences
	, std::vector<int>& stRun1, std::vector<int>& enRun1, std::vector<int>& runLabels1,
	int &tempRuns1, int &NumberOfRuns, int &rowRun1)
{
	stRun1.clear(); enRun1.clear(); runLabels1.clear(); tempRuns1 = 0;// clear the last last info
	rowRun1 = (*(rowRun.end() - 1));
	for (auto i = 0; i != NumberOfRuns; ++i)
	{
		if (rowRun[i] == rowRun1)
		{
			tempRuns1++;
			stRun1.push_back(stRun[i]);
			enRun1.push_back(enRun[i]);
			runLabels1.push_back(runLabels[i]);
		}
	}
	NumberOfRuns = 0; stRun.clear(); enRun.clear(); rowRun.clear(); equivalences.clear(); runLabels.clear();
}


void dosth(IMAGEDATA* imagedata, std::vector<int>& stRun, std::vector<int>& enRun, std::vector<int>& rowRun,
	std::vector<int>& runLabels, std::vector<std::pair<int, int>>& equivalences
	, std::vector<int>& stRun1, std::vector<int>& enRun1, std::vector<int>& runLabels1,
	int &tempRuns1, int &NumberOfRuns, int &rowRun1, int& offset, int slice)
{
	for (int i = 1; i < slice - 1; ++i)
	{
		fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / slice * i, height / slice * (i + 1));
		firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
		replaceSameLabel(runLabels, equivalences);
		union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / slice * i);
		paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

		check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);
	}
}
void connect(IMAGEDATA* imagedata)
{
	int NumberOfRuns = 0;
	std::vector<int> stRun, enRun, rowRun;
	std::vector<int> runLabels;
	std::vector<std::pair<int, int>> equivalences;
	int offset = 1; //1 8-n; 0 4-n
	std::vector<int> stRun1, enRun1;
	int rowRun1;
	std::vector<int> runLabels1;
	int tempRuns1 = 0;
	int slice;
	slice = 25;

	fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, 0, height / slice);
	firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	replaceSameLabel(runLabels, equivalences);
	paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);
	rowRun1 = (*(rowRun.end() - 1));
	for (auto i = 0; i != NumberOfRuns; ++i)
	{
		if (rowRun[i] == rowRun1)
		{
			tempRuns1++;
			stRun1.push_back(stRun[i]);
			enRun1.push_back(enRun[i]);
			runLabels1.push_back(runLabels[i]);
		}
	}
	NumberOfRuns = 0; stRun.clear(); enRun.clear(); rowRun.clear(); equivalences.clear(); runLabels.clear(); //clear

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12, height / 12 * 2);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 2, height / 12 * 3);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 2);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 3, height / 12 * 4);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 3);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 4, height / 12 * 5);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 4);
	////for (int i = 0; rowRun[i] == height / 12 * 4; ++i)
	////	for (int j = 0; j < tempRuns1; ++j)
	////	{
	////		if (stRun[i] <= enRun1[j] + offset && enRun[i] >= stRun1[j] - offset/* && rowRun[i] == rowRun[j] + 1*/)
	////		{
	////			int temp = runLabels[i];
	////			for (int k = 0; k != runLabels.size(); ++k)
	////			{
	////				if (runLabels[k] == temp)
	////					runLabels[k] = runLabels1[j];
	////			}
	////		}
	////	}
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 5, height / 12 * 6);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 5);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 6, height / 12 * 7);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 6);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 7, height / 12 * 8);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 7);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 8, height / 12 * 9);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 8);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 9, height / 12 * 10);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 9);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	//fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / 12 * 10, height / 12 * 11);
	//firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	//replaceSameLabel(runLabels, equivalences);
	//union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / 12 * 10);
	//paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	//check_clear(stRun, enRun, rowRun, runLabels, equivalences, stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1);

	dosth(imagedata, stRun, enRun, rowRun, runLabels, equivalences,  
		stRun1, enRun1, runLabels1, tempRuns1, NumberOfRuns, rowRun1, offset, slice);
	fillRunVectors(imagedata, NumberOfRuns, stRun, enRun, rowRun, height / slice * (slice-1), height);
	firstPass(stRun, enRun, rowRun, NumberOfRuns, runLabels, equivalences, offset);
	replaceSameLabel(runLabels, equivalences);
	union_pre(stRun, enRun, rowRun, runLabels, stRun1, enRun1, runLabels1, tempRuns1, offset, height / slice * (slice - 1));
	paintbmp(imagedata, stRun, enRun, rowRun, runLabels);

	NumberOfRuns = 0; stRun.clear(); enRun.clear(); rowRun.clear(); equivalences.clear(); runLabels.clear();
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
