#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img(480, 520, CV_8UC3, Scalar(255, 255, 255));

	ellipse(img, Point(100, 100), Size(60, 30), 20, 0, 270, Scalar(0, 0, 0), -1, LINE_AA);
	ellipse(img, Point(300, 100), Size(100, 50), 20, 0, 360, Scalar(255, 50, 10), 2, LINE_AA);


	imshow("img", img);

	waitKey(0);
}
