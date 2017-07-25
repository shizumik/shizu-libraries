#include <iostream>
#include <opencv2\opencv.hpp>	
#include <opencv2\opencv_modules.hpp>
using namespace cv;

int main()
{
	Mat img = imread("lena.bmp");
	
	imshow("imgage", img);
	waitKey(0);
	return 0;
}