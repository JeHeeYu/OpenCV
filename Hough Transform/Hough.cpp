#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/capture.jpg", IMREAD_GRAYSCALE);

	Mat edge;
	Canny(src, edge, 50, 150);      // 캐니 에지 검출기를 이용하여 영상을 edge에 저장

	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 250);  // 직선의 방정식 파라미터를 lines에 저장

	Mat dst;
	cvtColor(edge, dst, COLOR_GRAY2BGR);

	for (size_t i = 0; i < lines.size(); i++) {    
		float r = lines[i][0], t = lines[i][1];
		double cos_t = cos(t), sin_t = sin(t);
		double x0 = r * cos_t, y0 = r * sin_t;
		double alpha = 1000;

		Point pt1(cvRound(x0 + alpha * (-sin_t)), cvRound(y0 + alpha * cos_t));
		Point pt2(cvRound(x0 - alpha * (-sin_t)), cvRound(y0 - alpha * cos_t));
		line(dst, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	return 0;
}
