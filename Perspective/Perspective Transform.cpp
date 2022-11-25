#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src;
Point2f src_arr[4], dst_arr[4];

void on_mouse(int event, int x, int y, int flags, void* userdata);


int main()
{
	src = imread("C:/opencv/ch02/Project1/lenna.bmp", IMREAD_GRAYSCALE);

	namedWindow("src");
	setMouseCallback("src", on_mouse);

	imshow("src", src);
	waitKey();

	return 0;

}

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	static int cnt = 0;

	if (event == EVENT_LBUTTONDOWN) {
		if (cnt < 4) {
			src_arr[cnt++] = Point2f(x, y);

			circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);
			imshow("src", src);

			if (cnt == 4) {
				int w = 200, h = 300;

				dst_arr[0] = Point2f(0, 0);
				dst_arr[1] = Point2f(w - 1, 0);
				dst_arr[2] = Point2f(w - 1, h - 1);
				dst_arr[3] = Point2f(0, h - 1);

				Mat pers = getPerspectiveTransform(src_arr, dst_arr);

				Mat dst;
				warpPerspective(src, dst, pers, Size(w, h));

				imshow("dst", dst);
			}
		}
	}
}
