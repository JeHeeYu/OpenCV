## 도형(Shape) 그리기

OpenCV 에선 사각형, 원, 다각형 등 도형에 관한 여러 가지 함수들을 제공한다.


### rectangle();
<pre>
void rectangle(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);
void rectangle(InputOutputArray img, Rect rec, const Scalar& color, int thickness = 1, int linetype = LINE_8, shift = 0);

img : 입출력 영상
pt1 : 사각형 꼭지점 좌표 (Point 객체)
pt2 : pt1과 대각 방향에 있는 사곽형 꼭지점 좌표 (Point 객체)
rec : 사각형 위치 정보 (Rect 객체)
color : 사각형 색상(밝기)
thickness : 사각형 외곽선 두께. 이 값이 음수(-1 또는 FILLED)이면 내부를 채운다.
lineType : 선 타입
shift : 그리기 좌표 값의 축소 비율 (오른쪽 비트 시프트 연산 >>)
</pre>

rectangle() 함수는 사각형을 그리는 함수이다.
<br>
사각형을 그리는 방법은 2가지가 있다.
<br>
그림을 그릴 사각형 정보는 사각형의 대각 위치에 있는 두 꼭지점 좌표를 이용하거나, Rect 클래스 타입의 객체를 이용하여 전달할 수 있다.
<br>
<br>
함수 인자 중 thickness, lineType, shift 인자는 기본 값을 가지고 있으므로 생략할 수 있다.

### rectangle() 함수 예제 코드

