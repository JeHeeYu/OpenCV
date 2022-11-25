#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap("C:/opencv/ch02/Project1/people.JPG");

	if (!cap.isOpened()) {
		cout << "Video Open Fail" << endl;
		return - 1;
	}

	HOGDescriptor hog;    // HOGDescriptor 객체 hog 선언
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector()); // 보행자 검출을 위한 훈련된 SVM 분류기 계수 등록

	Mat frame;
	while(1) {
		cap >> frame;
		if (frame.empty())
			break;

		vector<Rect> detected;
		hog.detectMultiScale(frame, detected);    // 보행자 검출 수행

		for (Rect r : detected) {                 // 검출된 정보를 사각형으로 표시
			Scalar c = Scalar(255, 0, 0);
			rectangle(frame, r, c, 3);
		}

		imshow("frame", frame);
		waitKey();

	}
}
