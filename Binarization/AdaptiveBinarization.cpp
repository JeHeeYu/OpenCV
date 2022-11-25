#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
 

int main(int argc, char* argv[])
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);

	Mat dst1, dst2;
	
	adaptiveThreshold(src, dst1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 51, 5);
	adaptiveThreshold(src, dst2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 51, 5);
	
	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	
}
