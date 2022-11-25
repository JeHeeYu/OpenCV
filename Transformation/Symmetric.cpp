#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);

	Mat dst1, dst2, dst3;
	
	flip(src, dst1, 1);
	flip(src, dst2, -1);
	flip(src, dst3, 0);
	
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);

	waitKey();
}
