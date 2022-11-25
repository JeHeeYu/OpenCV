## QR(Quick Response) 코드란
QR 코드란 컴퓨터가 만든 흑백 격자무늬 패턴 코드로, 정보를 나타내는 매트릭스 형식의 2차원 코드이다.
<br>
다른 2차원 코드로 비슷한 바코드가 존재한다.
<br>
QR 코드는 숫자, 영문자, 8비트 문자, 한자 등의 정보를 저장할 수 있다.

## QR 코드 검출 방법

 

입력 영상에서 QR 코드를 인식하기 위해서 먼저 QR 코드 세 모서리에 포함된 흑백 정사각형 패턴을 찾아 QR 코드 전체 영역 위치를 알아내야 한다.
<br>
그리고 검출된 QR 코드를 정사각형 형태로 투시 변환한 후 QR 코드 내부에 포함된 흑백 격자 무늬를 해석하여 문자열을 추출해야 한다.
<br>
원래 이러한 작업은 매우 복잡하고 정교한 영상 처리를 필요로 하는데, OpenCV 4.0.0 버전부터 QR 코드를 검추랗고 해석하는 기능을 제공한다.

## QR 코드 인식 함수
OpenCV에서 QR 코드를 검출하고 해석하는 기능은 QRCodeDetector 클래스에 구현되어 있다.
<br>
QRCodeDetector 클래스를 이용하여 영상에서 QR 코드를 검출하거나 해석하려면 먼저 QRCodeDetector 객체를 생성해야 한다.
<br>
<br>
QRCode 객체를 생성한 후 QRCodeDetector 클래스 멤버 함수를 이용하여 QR 코드를 검출하거나 문자열을 해석할 수 있다.
<br>
입력 영상에서 QR 코드 영역을 검출하기 위해 QRCodeDetector::detect() 함수를 사용한다.
```
bool QRCodeDetector::detect(InputArray img, OutputArray points) const;

img : 입력 영상으로 CV_8U 또는 CV_8UC3 타입
points : QR 코드를 감싸는 사각형의 네 꼭지점 좌표
반환값 : QR 코드를 검출하면 true, 검출하지 못하면 false 반환
```

QRCodeDetector::detect() 함수는 입력 영상 img에서 QR 코드를 검출하고, QR 코드를 감싸는 사각형의 꼭지점 좌표를 반환한다.
<br>
points 인자에는 보통 vector<Point2f> 또는 vector<Point> 타입의 변수를 지정한다.
<br>
검출된 QR 코드 영역에서 QR 코드에 저장된 문자열을 추출할 때는 QRCodeDetector::decode() 함수를 사용한다.
  
```
std::string QRCodeDetector::decode(InputArray img, InputArray points, OutputArray straight_qrcode = noArray());

img : 입력 영상
points : QR 코드를 감싸는 사각형의 네 꼭지점 좌표
straight_qrcode : 정사각형 QR 코드 영상으로 CV_8UC1 타입
반환값 : QR 코드에 포함된 문자열
```
  
QRCodeDetector::decode() 함수는 img 영상에서 QR 코드를 해석하여 QR 코드에 암호화되어 있는 문자열을 반환한다.
<br>
points 인자에는 보통 QRCodeDetector::detect() 함수로 구한 QR 코드 꼭지점 좌표를 전달한다.
<br>
<br>
만약 straight_qrcode 인자에 Mat 자료형의 변수를 전달하면 정사각형 형태로 투명 변한된 QR 코드 영상이 반환된다.
<br>
QR 코드에 포함된 문자열 추출에 실패하면 빈 문자열을 반환한다.
<br>
<br>
입력 영상에서 QR 코드 검출과 해석을 한꺼번에 수행하는 함수도 제공한다.
  
```
std::string QRCodeDetector::detectAndDecode(InputArray img, OutputArray points = noArray(), 
                                           OutputARray straight_qrcode = noArray());

img : 입력 영상으로 CV_8U 타입
points : QR 코드를 감싸는 네 꼭지점 좌표
straight_qrcode : 정사각형 QR 코드 영상으로 CV_8UC1 타입
반환값 : QR코드에 포함된 문자열
```
  
QRCodeDetector::detectAndDecode() 함수는 기본적으로 입력 영상 img에서 QR코드의 검출과 해석을 동시에 수행하고 해석된 문자열을 반환한다.
<br>
만약 QR 코드의 네 꼭지점 좌표 또는 정사각형 형태의 QR 코드 영상이 필요하다면 points와 straight_qrcode 인자를 전달하면 된다.

