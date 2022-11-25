#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);

	Mat dst1, dst2, dst3;

	threshold(src, dst1, 128, 255, THRESH_BINARY);
	threshold(src, dst2, 255, 255, THRESH_BINARY);
	threshold(src, dst3, 255, 255, THRESH_BINARY_INV);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("dst3", dst3);

	waitKey();
}
