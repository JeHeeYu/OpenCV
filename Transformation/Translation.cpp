#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);

	Mat M = Mat_<double>({ 2, 3 }, { 1, 0, 150, 0, 1, 100 });  // 가로 150픽셀, 세로 100픽셀 이동하는 변환 행렬 M 생성

	Mat dst;
	warpAffine(src, dst, M, Size());   //   src 영상을 이동 변환하여 dst 영상 생성

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
}
