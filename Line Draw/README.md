## 선(Line) 그리기

OpenCV 에서 그리기 함수는 영상 위에 직선을 그리는 line() 함수가 있다.
<br>
line() 함수는 cv 네임스페이스 안에 선언되어 있다.

### line();
<pre>
void line(InputOutputArray img, Point pt1, Point pt2, const Scalar& color,
          int thickness = 1, int lineType = LINE_8, int shift = 0);

img : 입출력 영상
pt1 : 시작점
pt2 : 끝점
color : 색 선상(밝기)
thickness : 선 두께
lineType : 선 타입. LINE_4, LINE_8, LINE_AA 중 하나를 지정할 수 있다.
shift : 그리기 좌표 값의 축소 비율 (오른쪽 비트 시프트 연산 >> )
</pre>

line() 함수는 img 영상 위에 pt1 좌표부터 pt2 좌표까지 직선을 그린다.
<br>
선 색상 또는 밝기는 color 인자로 지정한다.
<br>
<br>
예를 들어 3채널 컬러 영상에 빨간색 선을 그리려면 color 인자에 Scalar(0, 0, 255)를 전달한다.
<br>
lineType 인자에는 LineTypes 열거형 상수 중 하나를 지정할 수 있다.

|LineTypes 열거형 상수|값|설명|
|:---:|:---:|:---:|
|FILLED|-1|내부룰 채움 (직선 그리기 함수에서 사용 불가)|
|LINE_4|4|4방향 연결|
|LINE_8|8|8방향 연결|
|LINE_AA|18|안티에일리어싱(anti-aliasing)|

<br>
shift 인자는 0보다 같거나 큰 정수를 지정할 수 있다.
<br>
지정한 크기만큼 좌표 값을 오른쪽 비트 시프트 연산(>>)을 수행한 후 직선 그리기 작업을 수행한다.(offset)
<br>
<br>
shift 인자 값이 0이면 지정한 좌표 그대로 그리기를 수행한다.
<br>
line() 함수 인자 중 thinkness, lineType, shift 인자는 기본값이 지정되어 있어 생략할 수 있다.
<br>
<br>

### [line 함수 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Line%20Draw/LineDraw.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203671744-287f9dbb-7311-432f-b39e-59656d2c5af1.png)

<br>

## arrowedline();

<pre>
void arroweLine(InputOutputArray img, Point pt1, Point pt2, const Scalar& color,
                int thickness = 1, int line_Type = LINE_8, int shift = 0, double tipLength = 0.1);

img : 입출력 영상
pt1 : 시작점
pt2 : 끝점
color : 색 선상(밝기)
thickness : 선 두께
line_Type : 선 타입. LINE_4, LINE_8, LINE_AA 중 하나를 지정할 수 있다.
shift : 그리기 좌표 값의 축소 비율 (오른쪽 비트 시프트 연산 >> )
tipLength : 전체 직선 길이에 대한 화살표 길이의 비율
</pre>

arrowedLine() 함수는 img 영상 위에 pt1 좌표부터 pt2 좌표까지 직선을 그리고,
<br>
끝점인 pt2에 화살표 모양의 직선 2개를 추가로 그린다.
<br>
<br>
이때 화살표 모양의 직선 길이는 tipLength 인자로 조절하며, 기본으로 0.1이 지정되어 있다.

### [line 함수 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Line%20Draw/ArrowedLine%20Draw.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203672531-7a582941-a4b8-44bd-b5a5-3978ad2752cf.png)

<br>

## drawMarker();

<pre>
void drawMarker(InputOutputArray img, Point position, const Scalar& color, int markerType = MARKER_CROSS, 
                int markerSize = 20, int thickness = 1, int line_type = 8);

img : 입출력 영상
position : 마커 출력 위치
color : 선 색상
markerType : 마커 종류. MarkerTypes 열거형 상수 중 하나를 지정할 수 있다.
thickness : 선 두께
line_type : 선 타입. LINE_4, LINE_8, LINE_AA 중 하나를 지정할 수 있다.
</pre>

drawMarker() 함수는 직선 그리기 함수를 이용하여 다양한 모양의 마커를 그린다.
<br>
img 영상의 position 좌표에 color 색상을 이용하여 마커를 그린다.
<br>
<br>
마커 종류는 markerType 인자로 지정할 수 있으며, 기본 값으로 십자가 모양을 의미하는 MARKER_CROSS가 지정되어 있다.


|LineTypes 열거형 상수|값|
|:---:|:---:|
|MARKER_CROSS|십자가 모양 ( + 모양 )|
|MARKER_TILTED_CROSS|45도 회전된 십자가 모양 ( x 모양 )|
|MARKER_STAR|MARKER_CORSS 모양과 MARKER_TILTED_CROSS 모양이 합쳐진 모양 형태 (※ 모양 )|
|MARKER_DIAMOND|마름모 모양( ◇ 모양)|
|MARKER_SQUARE|정사각형 모양 ( □ 모양)|
|MARKER_TRIANGLE_UP|삼각형 모양 ( △ 모양)|
|MARKER_TRIANGLE_DOWN|역삼각형 모양 ( ∇ 모양)|

<br>
