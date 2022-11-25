#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/monkey.bmp", IMREAD_GRAYSCALE);

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);   // src 영상에 대해 오츠 알고리즘 자동 이진화 수행

	Mat dst1, dst2;
	erode(bin, dst1, Mat());    // bin 영상에 3 x 3 정방향 구조 요소를 이용하여 침식 연산 수행
	dilate(bin, dst2, Mat());   // bin 영상에 3 x 3 정방향 구조 요소를 이용하여 팽창 연산 수행

	imshow("src", src);
	imshow("bin", bin);
	imshow("erode", dst1);
	imshow("dilate", dst2);

	waitKey();
}
