#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/Test.JPG", IMREAD_GRAYSCALE);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(src, contours, RETR_LIST, CHAIN_APPROX_NONE);
	findContours(src, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);

	Mat dst1, dst2;
	
	cvtColor(src, dst1, COLOR_GRAY2BGR);
	cvtColor(src, dst2, COLOR_GRAY2BGR);

	for (int i = 0; i < contours.size(); i++) {
		Scalar c(0, 255, 0);
		drawContours(dst1, contours, i, c, 2);
	}

	for (int j = 0; j >= 0; j = hierarchy[j][0]) {
		Scalar c(255, 0, 0);
		drawContours(dst2, contours, j, c, -1, LINE_8, hierarchy);
	}

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
}
