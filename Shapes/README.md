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

### [rectangle() 함수 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Shapes/Rectangle.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203687998-ac795a29-874f-46fe-8186-9849ff09d4bd.png)

### circile();

<pre>
void circile(InputOutputArray img, Point center, int radius, const Scalar& color, int thickness = 1, int lineType = LINE_8, int shift = 0);

img : 입출력 영상
center : 원의 중심
radius : 원의 반지름
color : 원 색상
thickness : 원 외곽선 두께. 이 값이 음수(-1 또는 FILLED) 이면 내부를 채운다.
lineType : 선 타입
shift : 그리기 좌표 값의 축소 비율 (오른쪽 비트 시프트 연산 >>)
</pre>

circe() 함수는 원을 그리는 함수이다.
<br>
<br>
원을 그리기 위해서는 원의 중심점 좌표와 반지름을 지정해야 한다.
<br>
함수 인자 중 thickness, lineType, shift 인자는 기본 값을 가지고 있으므로 생략할 수 있다.

### [circle() 함수 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Shapes/Circle.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203688178-75cf665d-89a6-4485-b878-a695942251cb.png)

### ellipse();
ellipse() 함수는 다양한 형태의 타원 또는 타원의 일부인 호를 그릴 수 있는 함수이다.
<br>
<br>
타원의 크기는 axes 인자를 통해 지정하며, Size 자료형을 사용한다. x축 방향 타원의 반지름과 y축 방향의 반지름을 정한다.​
<br>
angle 인자에 0이 아닌 값을 전달하면, 회전된 타원을 그릴 수 있다.
<br>
startAngle과 endAngle 인자를 적절하게 이용하면 호를 그리는 용도로 사용할 수 있다.
<br>
<br>
예를 들어, startAngle = 0, endAngle = 360을 지정하면 완전한 타원이 되고,
<br>
startAngle = 0, endAngle = 180을 지정하면 타원의 반에 해당하는 호를 그릴 수 있다.
<br>
<br>
함수 인자 중 thickness, lineType, shift 인자는 기본 값을 가지고 있으므로 생략할 수 있다.

### [ellipse() 함수 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Shapes/Ellipse.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203688368-6daf1a7d-66ec-444e-b356-157e09a11e7e.png)

### polylines();
<pre>
void polylines(InputOutputArray img, InputOutputARrays pts, bool isClosed, const Scalar& color, int thickness = 1, int lineType = LINE_8, shift = 0);

img : 입출력 영상
pts : 다각형 외곽 점들의 좌표 배열. 주로 vector<Point> 타입
isClosed : 다각형이 닫혀 있는지를 나타내는 플래그. 이 값이 true이면 다각형의 마지막 꼭지점과 첫 번째 꼭지점을 잇는 직선을 추가로 그린다.
color : 선 색상
thickness : 선 두께. 이 값이 음수(-1 또는 FILLED)이면 내부를 채운다.
lineType : 선 타입
shift : 그리기 좌표 값의 축소 비율 (오른쪽 비트 시프트 연산 >>)
</pre>

polylines() 함수는 다각형을 그릴 수 있는 함수이다.
<br>
다각형의 꼭지점 좌표를 전달해야 하며, 꼭지점 좌표는 보통 vector<Point> 자료형에 저장하여 전달한다.

### [polylines() 함수 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Shapes/Polygon.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203688734-b49e3c2a-0e60-44f1-b94c-c8d3fb83e605.png)
