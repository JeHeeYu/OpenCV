#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);

	imshow("src", src);
	
	Mat dst;
	
	for (int ksize = 3; ksize <= 7; ksize += 2) {
		blur(src, dst, Size(ksize, ksize));

		String text = format("Mean : %d, %d", ksize, ksize);

		putText(dst, text, Point(10, 30), FONT_HERSHEY_COMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
}
