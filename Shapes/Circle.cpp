#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img(480, 520, CV_8UC3, Scalar(255, 255, 255));

	circle(img, Point(300, 120), 30, Scalar(255, 0, 255), -1, LINE_AA);
	circle(img, Point(150, 100), 60, Scalar(50, 128, 255), 3, LINE_AA);

	imshow("img", img);

	waitKey(0);
}
