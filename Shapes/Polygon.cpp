#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img(480, 520, CV_8UC3, Scalar(255, 255, 255));

	vector<Point> pts;
	pts.push_back(Point(250, 250));
	pts.push_back(Point(300, 250));
	pts.push_back(Point(300, 300));
	pts.push_back(Point(350, 350));
	pts.push_back(Point(250, 350));

	polylines(img, pts, true, Scalar(255, 0, 255), 2);


	imshow("img", img);

	waitKey(0);
}
