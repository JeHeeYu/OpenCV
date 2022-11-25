#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src1 = imread("lenna.bmp", IMREAD_GRAYSCALE);   // 입력 영상 1 Mat 객체 생성
	Mat src2 = imread("lenna.bmp", IMREAD_GRAYSCALE);   // 입력 영상 2 Mat 객체 생성

	Mat dst;    // 출력 영상 저장할 Mat 객체 생성

	add(src1, src2, dst);  // src1과 src2를 입력받아 dst로 출력

	imshow("src1", src1); 
	imshow("src2", src2);
	imshow("dst", dst);

	waitKey();
}
