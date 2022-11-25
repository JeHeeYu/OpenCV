#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{

	Mat src1 = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);
	Mat src2 = imread("C:/opencv/ch02/Project1/test.bmp", IMREAD_GRAYSCALE);

	imshow("src1", src1);
	imshow("src2", src2);

	Mat dst_or, dst_and, dst_not, dst_xor;

	bitwise_or(src1, src2, dst_or);
	bitwise_and(src1, src2, dst_and);
	bitwise_not(src1, dst_not);
	bitwise_xor(src1, src2, dst_xor);

	imshow("dst_or", dst_or);
	imshow("dst_and", dst_and);
	imshow("dst_not", dst_xor);
	imshow("dst_xor", dst_xor);

	waitKey();

}
