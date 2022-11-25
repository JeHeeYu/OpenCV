#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);

	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);   // x축, y축 방향으로 1차 편미분을 구하여 dx, dy에 저장

	Mat fmag, mag;
	magnitude(dx, dy, fmag);          // dx, dy 행렬로부터 그래디언트 크기 계산
	fmag.convertTo(mag, CV_8UC1);     // 행렬 fmag를 그레이스케일 형식으로 변환

	Mat edge = mag > 150;             // 에지 판별을 위한 그래디언트 크기 계산
	
	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();

	return 0;
}
