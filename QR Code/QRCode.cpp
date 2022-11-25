#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cout << "Camera Open Fail" << endl;
	}
	QRCodeDetector detector;

	Mat frame;
	while (1) {
		cap >> frame;

		if (frame.empty()) {
			cout << "Frame Load Fail" << endl;
			break;
		}
		vector<Point> points;
		String info = detector.detectAndDecode(frame, points);

		if (!info.empty()) {
			polylines(frame, points, true, Scalar(0, 255, 255), 2);
			putText(frame, info, Point(10, 30), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0));
		}

		imshow("frame", frame);
		if (waitKey(1) == 27)
			break;
	}
}
