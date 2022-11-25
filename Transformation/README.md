# 영상 변환 방법

## 영상의 이동 변환(Translation Transformation)

영상의 이동 변환이란 영상을 가로나 세로 방향으로 일정 크기만큼 이동 시키는 연산을 의미한다.
<br>
시프트(shift) 연산 이라고도 한다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203901946-15130d80-237e-43fe-8ad6-4acedc4d89ff.png)

<br>
<br>
노란색으로 표현한 사각형이 w x h 크기의 원본 영상이다.
<br>
녹색으로 표현한 사각형은 가로 방향으로 a, 세로 방향으로 b 만큼 이동 변환 결과 영상이다.
<br>
<br>
위의 그림과 같이 영상을 x 방향으로 a 만큼, y 방향으로 b 만큼 이동하는 어파인 변환 행렬은 M과 같이 구할 수 있다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203903657-678c1b54-c2f6-4c30-bbb9-8846a8514694.png)

<br>

<br>
OpenCV에서 영상을 이동 변환하려면 2 x 3 형태의 실수 행렬을 만들고, 이를 warpAffine() 함수 인자로 전달한다.

### [영상 이동 변환 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Transformation/Translation.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203902202-9464c061-4a8a-4d1b-b85b-97c2b8bcc52a.png)

<br>
<br>
src 원본 영상에서 이미지가 x 좌표로부터 150 픽셀, y좌표로부터 100픽셀 만큼 시프트 연산된 것을 볼 수 있다.
<br>
입력 영상의 픽셀 값이 복사되지 않은 영역은 검은색으로 채워진다.

## 영상의 전단 변환(shear transformation)

영상의 전단 변환이란 직사각형 형태의 영상을 한쪽 방향으로 밀어서 평행사변형 모양으로 변환하는 것을 말한다.
<br>
층밀림 변환 이라고도 한다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203902264-dee5d617-6de6-45a0-8b0e-9ec27abfcfd6.png)

<br>
<br>
y좌표가 증가함에 따라 영상이 가로 방향으로 이동하는 변환을 가로 방향 전단 변환,
<br>
x좌표가 증가함에 따라 영상이 세로 방향으로 이동하는 변환을 세로 방향 전단 변환 이라고 한다.
<br>
<br>
전단 변환은 영상의 픽셀을 가로 방향 또는 세로 방향으로 이동하지만, 픽셀이 어느 위치에 있는가에 따라 이동 정도가 달라진다.
<br>
입력 영상에서 원점은 전단 변환에 의해 이동하지 않고 그대로 원점에 머물러 있는다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203902302-3ef4c7fd-6464-45da-9993-c02045f1f029.png)

<br>
<br>
mx와 my는 각각 가로 방향과 세로 방향으로 밀림 전단을 나타내며, 변환 행렬 M은 위와 같이 나타낸다.

### [영상 전단 변환 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Transformation/Shear.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203902431-503eb5db-7a7d-4d04-850c-bb04fcd4f5be.png)

<br>
<br>
y좌표가 증가함에 따라 0.3y에 해당하는 x 좌표에서 원본 영상이 전단 변환을 수행한다.

## 영상의 크기 변환(scale transformation)
영상의 크기 변환이란 영상의 전체적인 크기를 확대 또는 축소하는 변환이다.
<br>
<br>
영상의 크기 변환 작업은 비전 프로그램에서 자주 사용한다.
<br>
정해진 크기의 영상만을 입력으로 받는데, 원하는 크기에 맞게 입력받을 때 자주 사용한다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203902516-6f6729ad-fb25-4d3e-a804-9c865fcc552c.png)

<br>
<br>
노란색 사각형 영역은 w x h 크기의 원본 영상이고, 녹색으로 표시한 영역은 w' x h' 크기로 확대된 결과 영상이다.
<br>
원본 영상의 가로 픽셀 크기가 w이고, 결과 영상의 가로 크기가 w'이다.
<br>
영상의 크기 변환을 나타내는 어파인 변환 행렬은 M과 같다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203902583-c3fcfca4-7259-4020-b33d-e37fb93b531b.png)

<br>
<br>
OpenCV는 보다 간단하게 크기를 변경할 수 있는 resize() 함수를 제공한다.

### resize()
```
void resize(InputArray src, OutputArray dst, Size dsize, double fx = 0, double fy = 0, int interpolation = INTER_LINEAR);

src : 입력 영상
dst : 결과 영상
dsize : 결과 영상 크기
fx : x축 방향으로의 크기 변환 비울
fy : y축 방향으로의 크기 변환 비율
interpolation : 보간법 지정
```
resize() 함수는 src 입력 영상을 dsize 크기로 확대 또는 축소한 dst 영상을 생성한다.
<br>
결과 영상의 크기는 dsize 인자를 통해 명시적으로 저장할 수도 있지만, fx, fy값을 통해 결정할 수도 있다.
<br>
결과 영상의 크기를 픽셀 단위로 지정하여 크기 변환을 수행하려면 dsize에 0이 아닌 값을 저장하고, fx와 fy는 0으로 설정하면 된다.
<br>
<br>
입력 영상 크기를 기준으로 크기 변환 비율을 지정하여 영상을 확대 또는 축소하려면 dsize 인자에는 Size()를 지정하고 fx와 fy에는 0이 아닌 양의 실수를 저장한다.
<br>
<br>
iterpolation에는 보간법(iterpolation) 알고리즘을 나타내는 InterpolationFlags 열거형 상수를 지정한다.
<br>

|InterpolationFlags 열거형 상수|설명|
|:---:|:---:|
|INTER_NEAREST|최근방 이웃 보간법|
|INTER_LINEAR|양선형 보간법|
|INTER_CUBIC|3차 보간법|
|INTER_AREA|픽셀 영역 리샘플링|
|INTER_LANCZOS4|8 x 8 이웃 픽셀을 사용하는 란초스 보간법|

INTER_NEAREST 방법은 가장 빠르게 동작하지만 결과 영상의 화질이 좋지 않다.
<br>
<br>
INTER_LINEAR 방법은 연산 속도가 빠르고 화질도 괜찮은 수준이라 널리 사용된다.
<br>
<br>
INTER_CUBIC이나 INTER_LANCZOS4는 INTER_LINEAR보다 화질은 좋지만, 연산의 속도가 증가한다.
<br>
<br>
INTER_AREA 밥업을 사용하면 모아레(moire) 현상이 적게 발생하며 화질 면에서 유리하다.

### [영상 크기 변환 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Transformation/Scale.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203903054-e6809eb1-5a67-4f3e-a9b7-d2a73fabcd91.png)
<br>
<br>
dst1 ~ 4 영상은 reisze() 함수에 의해 4배 확대된 결과 영상에서 추출한 부분 영상이다.
<br>
보간법의 방법에 따라 영상의 화질, 연산 속도가 달라진다.

## 영상의 회전 변환(rotation transformation)
영상의 회전 변환이란 특정 좌표를 기준으로 영상을 원하는 각도만큼 회전하는 변환이다.
<br>
영상 처리 시스템에서 입력 영상을 회전하는 경우는 자주 발생한다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203903105-a15abe1b-513a-4278-9547-e57a827004e0.png)

<br>
<br>
노란색 사각형은 원본 영상이고, 녹색으로 표시한 사각형이 회전 변환으로 생성된 결과이다.
<br>
OpenCV는 영상의 회전을 위한 어파인 변환 행렬을 생성하는 함수를 제공한다.

### getRotationMatrix2D()
```
Mat getRotationMatrix2D(Point2f center, double angle, double scale);

center : 회전 중심 좌표
angle : 회전 각도로 양수는 반시계 방향, 음수는 시계 방향을 의미한다.
scale : 회전 후 추가적으로 확대 또는 축소할 비율이며, 크기를 유지하려면 1을 지정한다.
반환값 : 2 x 3 어파인 변환 행렬(CV_64F)
```

getRotationMatrix2D() 함수는 영상을 center 기준으로 반시계 방향으로 angle각도만큼 회전한 후, scale 크기만큼 확대 또는 축소하는 2 x 3 어파인 반환 행렬을 반환한다.
<br>
영상을 90도 단위로 회전하고 싶은 경우에는 rotate() 함수를 제공한다.
```
void rotate(InputArray src, OutputArray dst, int rotateCode);

src : 입력 행렬
dst : 출력 행렬
rotateCode : 회전 각도 지정 플래그
```
3번 째 인자 rotateCode에는 3개의 상수중 1개를 지정할 수 있다.
<br>
<br>
ROTATE_90_CLOCKWISE : 시계 방향으로 90도 회전
<br>
<br>
ROTATE_90_COUNTERCLOCKWISE : 반시계 방향으로 90도 회전
<br>
<br>
ROTATE_180 : 180도 회전

### [영상 회전 변환 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Transformation/Rotation.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203903280-a0f22ba1-626d-4291-bf0c-373f63f040ea.png)

<br>
<br>
영상의 중심 좌표를 2Pointf 자료형의 변수 cp에 저장한다.
<br>
이 점을 기준으로 영상을 반시계 방향으로 20도만큼 회전한다.
<br>
<br>
dst2, 3, 4 결과 영상은 rotate() 함수를 이용해 각도를 회전한 결과 영상이다.

## 영상의 대칭 변환(symmetric transformation)
영상의 대칭 변환이란 영상의 좌우를 서로 바꾸거나, 상하를 뒤집는 형태의 변환을 뜻한다.
<br>
상하 대칭 또는 상하 반전이라고도 한다.
<br>
<br>
OpenCV 에서 영상의 대칭 변환을 수행하는 함수를 따로 제공한다.

### filp()

```
void flip(InputArray src, OutputArray dst, int flipCode);

src : 입력 영상
dst : 출력 영상
flipCode : 대칭 방법 지정 플래그로 양수면 좌우 대칭, 0이면 상하 대칭, 음수면 둘 다 수행
```

flip() 함수는 src 영상을 대칭 변환하여 결과 영상 dst를 생성한다.
<br>
대칭 방법은 flipCode 인자의 부호에 따라 결정된다. 
<br>
(1, -1, 0) 상하 대칭과 좌우 대칭을 모두 수행한 결과 영상은 입력 영상을 180도 회전한 것과 같다.

### [영상 대칭 변환 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Transformation/Symmetric.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203903550-6f9cf413-22c0-4933-bf2d-9dcbd3a062bf.png)
<br>
<br>
file() 함수의 인자에 따라 대칭이 변하는 것을 볼 수 있다.
