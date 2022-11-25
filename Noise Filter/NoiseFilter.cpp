#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);
	imshow("src", src);
	
	Mat noise(src.size(), CV_32SC1);       
	randn(noise, 0, 5);                  
	add(src, noise, src, Mat(), CV_8U);     // 가우시안 잡음 추가

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);     // 가우시안 필터링 수행

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);  // 양방향 필터링 수행

	imshow("dst1", dst1);
	imshow("dst2", dst2);
	waitKey();
	
}
