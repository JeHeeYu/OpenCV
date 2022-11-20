#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);
	imshow("src", src);
	
	Mat dst;
	
	for (int sigma = 1; sigma <= 5; sigma++) {
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);

		float alpha = 1.f;
		Mat dst = (1 + alpha) * src - alpha * blurred;

		String text = format("sigma : %d", sigma);

		putText(dst, text, Point(10, 30), FONT_HERSHEY_COMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}
}
