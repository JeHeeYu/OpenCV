#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat dst;

	subtract(src1, src2, dst);

	imshow("src1", src1);
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
}
