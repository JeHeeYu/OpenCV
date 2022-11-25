#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/Rectangle.JPG", IMREAD_GRAYSCALE);  // 그레이스케일 형식으로 src에 저장

	Mat bin;
	threshold(src, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);  // src 영상을 오츠 알고리즘으로 이진화 변환

	Mat labels, stats, centroids;
	int cnt = connectedComponentsWithStats(bin, labels, stats, centroids);    // bin 영상에 대해 레이블링 후 정보 추출

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);    // src 영상을 3채널 컬러 영상 형식을 변환

	for (int i = 1; i < cnt; i++) {         // 배경 영역을 제외하고 흰색 객체 영역에 대해서만 for문 수행
		int* p = stats.ptr<int>(i);

		if (p[4] < 20) continue;        // 객첼의 픽셀 개수가 20보다 작으면 잡음으로 간주하고 무시

		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 0), 2);    // 검출된 객체를 박스로 그림
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
}
