#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("C:/opencv/ch02/Project1/circle.JPG", IMREAD_COLOR);
	Mat templ = imread("C:/opencv/ch02/Project1/circle_1.JPG", IMREAD_COLOR);

	if (img.empty() | templ.empty()) {
		cout << "Image Load Failed" << endl;
	}

	img = img + Scalar(50, 50, 50);     // 입력 영상 밝기 50 증가

	Mat noise(img.size(), CV_32SC3);      // 입력 영상에 표준 편차가 10인 가우시안 잡음 추가
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);         

	Mat res, res_norm;
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);       // 정규화된 상관계수 매칭 방법을 사용하여 템플릿 매칭 수행
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);   // 템플릿 매칭 결과 행렬을 res_norm영상에 저장

	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	cout << "maxv : " << maxv << endl;

	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(255, 0, 0), 2);

	imshow("templ", templ);
	imshow("img", img);
	imshow("res_norm", res_norm);

	waitKey();
}
