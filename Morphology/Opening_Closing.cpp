#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/monkey.bmp", IMREAD_GRAYSCALE);

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);   // src 영상에 대해 오츠 알고리즘으로 자동 이진화 수행

	Mat dst1, dst2;
	morphologyEx(src, dst1, MORPH_OPEN, Mat());     // ㅌㅌ
	morphologyEx(src, dst2, MORPH_CLOSE, Mat());

	imshow("src", src);
	imshow("bin", bin);
	imshow("opening", dst1);
	imshow("closing", dst2);

	waitKey();
}
