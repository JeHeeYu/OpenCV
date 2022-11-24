## 문자열 출력 예제

openCV에서 영상에 직접 영상 처리 결과 또는 추가적인 정보를 문자열 형태로 나타낼 수 있는 함수를 제공한다.

### putText();
<pre>
void putText(InputOutputArray img, const String& text, Point org, int fontFace, double fontScale,
             Scalar color, int thickness = 1, int lineType_LINE_8, bool bottomLeftOrigin = false);

img : 입출력 영상
text : 출력할 문자열
org : 영상에서 문자열을 출력할 위치의 좌측 하단 좌표
fontFace : 폰트 종류로 cv::HersheyFonts에서 선택 가능
fontScale : 폰트 크기 확대/축소 비율
color : 문자열 색상
thickness : 문자열을 그릴 때 사용할 선 두께
lineType : 선 타입으로 LINE_4, LINE_8, LINE_AA 중 하나를 지정할 수 있다.
bottomLeftOrigin : 이 값이 true이면 영상의 좌측 하단을 원점으로 간주하고, false이면 좌측 상단이 원점이 된다.
</pre>

putText() 함수는 img 영상의 org 위치에 text로 지정된 문자열을 출력할 수 있다.
<br>
<br>
사용할 폰트 종류는 fontFace 인자로 설정하고, fontScale 인자로 폰트 크기를 조정할 수 있다.
<br>
fontFace 인자에는 HersheyFonts 열거형 상수 값을 지정할 수 있다.

|HersheyFonts 열거형 상수|설명|
|:---:|:---:|
|FONT_HERSHEY_SIMPLEX|일반 크기의 산세리프 폰트|
|FOR_HERSHEY_PLAIN|작은 크기의 산세리프 폰트|
|FOR_HERSHEY_DUPLEX|일반 크기의 산세리프 폰트 (FONT_HERSHEY_SIMPLEX 보다 복잡한 형태)|
|FOR_HERSHEY_TRIPLEX|일반 크기의 산세리프 폰트 (FONT_HERSHEY_COMPLEX 보다 복잡한 형태)|
|FONT_HERSHEY_COMPLEX_SMALL|FONT_HERSHEY_COMPLEX 보다 작은 폰트|
|FONT_HERSHEY_SCRIPT_SIMPLEX|필기체 스타일의 폰트|
|FONT_HERSHEY_SCRIPT_COMPLEX|필기체 스타일의 폰트(FONT_HERSHEY_SCRIPT_SIMPLEX 보다 복잡한 형태)|
|FONT_ITALIC|이탤릭체를 위한 플래그|

<br>

### [putText() 함수 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Print%20String/PrintText.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203698331-426ee81a-f595-428e-a088-1cf5fdd075a5.png)

### getTextSize();
<pre>
Size getTextSize(const String& text, int fontface, double fontScale, int thickness, int* baseLine);

text : 출력할 문자열
fontFace : 폰트 종류
fontScale : 폰트 크기 확대/축소 비율
thickness : 문자열을 그릴 때 사용할 선 두께
baseLine : (출력) 가장 하단의 텍스트 위치를 기준으로 하는 기준선(baseline)의 y 좌표, 필요 없으면 0 지정
반환값 : 지정할 문자열 출력 시 차지하는 사각형 크기
</pre>

getTextSize() 함수는 지정한 문자열, 폰트 종류, 폰트 크기 등을 이용하여 문자열을 출력할 때 차지할 사각형 영역 크기 정보를 반환한다.
<br>
putText() 함수를 이용하여 특정 위치 좌표에 문자열을 출력하는 경우, 보통 문자열 길이와 크기에 따라
<br>
문자열이 차지하는 영역 크기가 달라지기 때문에 문자열이 한쪽으로 치우쳐서 나타날 수 있다.
<br>
<br>
그때 getTextSize() 함수가 반환하는 문자열 영역 크기 정보를 이용하면 문자열 출력 위치를 적절하게 조절할 수 있다.

### [getTextSize() 함수 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Print%20String/TextSize.cpp)

img.size() 코드를 이용하여 img 영상 크기를 받아 와서 sizeImg 변수에 저장한다.
<br>
그러므로 영상의 가로 크기는 sizeImg.width, 세로 크기는 sizeImg.height 형태로 참조할 수 있다.
<br>
<br>
출력할 문자열이 차지할 영역의 크기는 getTextSize() 함수를 이용하여 sizeText 변수에 저장한다.

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203698593-7e68741d-7ae7-4015-a2e6-e986c8600c8b.png)
<br>
<br>
영상의 크기와 실제 문자열이 출력된 사각형의 크기를 알기 때문에, 좌표를 계산할 수 있다.
<br>
<br>
org.x = (sizeImg.width - sizeText.width) / 2
<br>
org.y = (sizeImg.height + sizeText.height) / 2
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203698660-19e5bd92-5f93-4859-b50e-93719f74c58a.png)
