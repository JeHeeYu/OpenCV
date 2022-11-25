#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);

	double mx = 0.3;

	Mat M = Mat_<double>({ 2, 3 }, { 1, mx, 0, 0, 1, 0 });  // 가로 방향 0.3 밀림의 행렬 변환 생성

	Mat dst;
	warpAffine(src, dst, M, Size(cvRound(src.cols + src.rows * mx), src.rows)); // 변환 수행

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
}
