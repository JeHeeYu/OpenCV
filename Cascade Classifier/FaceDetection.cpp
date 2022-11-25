#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:/opencv/ch02/Project1/lenna.bmp");
	if (src.empty()) {
		cout << "Image Load Fail" << endl;
	}

	CascadeClassifier face_classifier("C:/opencv/ch02/Project1/haarcascade_frontalface_default.xml");
	CascadeClassifier eye_classifier(("C:/opencv/ch02/Project1/eye.xml");

	if (face_classifier.empty() || eye_classifier.empty()) {
		cout << "XML Load Fail" << endl;
	}

	vector<Rect> faces;
	face_classifier.detectMultiScale(src, faces);

	for (Rect face : faces) {
		rectangle(src, face, Scalar(255, 0, 0), 2);

		Mat faceROI = src(face);
		vector<Rect> eyes;
		eye_classifier.detectMultiScale(faceROI, eyes);

		for (Rect eye : eyes) {
			Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			circle(faceROI, center, eye.width / 2, Scalar(255, 255, 0), 2, LINE_AA);
		}
	}

	imshow("src", src);

	waitKey();
}
