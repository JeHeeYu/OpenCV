#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img(480, 620, CV_8UC3, Scalar(255, 255, 255));

	arrowedLine(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255), 1, LINE_4);
	arrowedLine(img, Point(50, 100), Point(200, 100), Scalar(255, 0, 255), 1, LINE_8);
	arrowedLine(img, Point(50, 150), Point(200, 150), Scalar(255, 0, 0), 1, LINE_8, 0, 0.05);

	imshow("img", img);

	waitKey(0);
}
