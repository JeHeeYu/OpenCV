## 허프 변환(Hough Transform)이란
허프 변환 이란 영상에서 추출한 에지 정보를 이용하여 직선 또는 원을 검출하는 방법을 말한다.
<br>
컴퓨터 비전에서 직선 검출 하기 위해 주로 허프 변환 기법을 사용한다.
<br>
<br>
허프 변환 기법이란 2차원 xy 좌표에서 직선의 방정식을 파라미터(parameter) 공간으로 변환하여 직선을 찾는 알고리즘이다.

## 허프 변환 직선 검출
직선은 영상에서 찾을 수 있는 많은 특징 중 하나이며 영상을 분석함에 중요한 정보를 제공한다.
<br>
직선 검출은 자율 주행 자동차에서 차선을 검출하는 용도로 사용할 수도 있고, 수평이 맞지 않는 영상에서 수평선이나 수직선 성분을 찾아내어 자동 영상 회전을 위한 정보로도 사용할 수 있다.
<br>
<br>
영상에서 직선 성분을 찾기 위해 우선 에지(edge)를 찾아내고, 에지 픽셀들이 일직선상에 배열되어 있는지 확인한다.
<br>
영상에서 직선을 찾기 위한 용도로 허프 변환 기법이 널리 사용된다.
<br>
<br>
보통 2차원 평면에서 직선의 방정식은 다음과 같은 식으로 나타낸다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203906073-54dad048-3663-4494-a749-226c2a1bc59e.png)


<br>

수식에서 a는 기울기(slope), b는 y 절편(y intersection)이다.

이 방정식은 가로축이 x, 세로축이 y인 2차원 xy좌표 공간에서 정의되었고, a와 b는 직선의 형태를 결정하는 파라미터이다.
<br>
<br>
허프 변환을 이용하여 직선의 방정식을 찾으려면 xy 공간에서 에지로 판별된 모든 점을 이용하여 ab파라미터 공간에 직선을 표현하고, 직선이 많이 교차되는 좌표를 모두 찾아야 한다.
<br>
이때 직선이 많이 교차하는 점을 찾기 위해 보통 축적 배열(accumulation array)를 많이 사용한다.
<br>
<br>
축적 배열은 0으로 초기화된 2차원 배열에서 직선이 지나가는 위치의 배열 원소 값을 1씩 증가시켜 생성한다.

### 허프 변환 함수
OpenCV에서 허프 변환의 직선 검출을 위한 함수를 제공한다.

```
void HoughLines(InputArray Image, OutputArray lines, double rho, double theta, int threshold,
                double srn = 0, double stn = 0, double = min_theta = 0, double max_theta = CV_PI);

image : 8비트 단일 채널 입력 영상으로 주로 에지 영상을 지정한다.
lines : 직선 정보(rho, theta)를 저장할 출력 벡터
rho : 축적 배열에서 p 값의 해상도(픽셀 단위)
theta : 축적 배열에서의 해상도(단위는 라디안)
threshold : 축적 배열에서 직선으로 판단할 임계값
srn : 멀티스케일 허프 변환에서 rho 해상도를 나누는 값
stn : 멀티스케일 허프 변환에서 theta 해상도를 나누는 값
min_theta : 검출할 직선의 최소 theta 값
max_theta : 검출할 직선의 최대 theta 값
```

HoughLines() 함수는 image 영상에서 0이 아닌 픽셀을 이용하여 축적 배열을 구성한다.
<br>
직선 파라미터 정보에 받아 올 lines 인자에는 vector<Vec2f> 또는 vector<Vec3f> 자료형 변수를 지정한다.

### [허프 변환 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Hough%20Transform/Hough.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203906279-0089c3ae-d0e9-444d-85f3-ce51ada86b74.png)

<br>
Point pt1과 pt2를 이용하여 직선상의 두 점 좌표를 구한다.
<br>
이 때 alpha 값을 작게 설정하면 직선의 일부만 그려져 주의해야 한다.

## 확률적 허프 변환(Probabilistic Hough Transform)

OpenCV에서는 기본적인 허프 변환 직선 검출 방법 외 확률적 허프 변환에 의한 검출 방법도 제공한다.
<br>
확률적 허프 변환 방법은 직선의 방정식 파라미터를 반환하는 것이 아니라 직선의 시작점과 끝점 좌표를 반환한다.
<br>
<br>
즉, 선분을 찾는 방법이다.

```
void HoughLinesP(InputArray Image, OutputArray lines, double rho, double theta, int threshold,
                 double minLineLength = 0, double maxLineGap = 0);

image : 8비트 단일 채널 입력 영상으로 주로 에지 영상을 지정한다.
lines : 선분의 시작점과 끝점의 정보(x1, y1, x2, y2)를 저장할 출력 벡터
rho : 축적 배열에서 값의 해상도(픽셀 단위)
theta : 축적 배열에서의 해상도(단위는 라디안)
threshold : 축적 배열에서 직선으로 판단할 임계값
minLineLength : 검출할 선분의 최소 길이
maxLineGap : 직선으로 간주할 최대 에지 점 간격
```
HoughLinesP() 함수에서 검출된 선분 정보가 저장되는 lines 인자에는 보통 vector<Vec4i> 자료형 변수를 지정한다.
<br>
각각의 선분 정보는 Vec4i 자료형으로 저장되고, 하나의 Vec4i 객체에는 선분 시작점의 x 좌표와 y 좌표, 선분 끝점의 x 좌표와 y 좌표가 저장된다.
<br>
<br>
maxLineGap 인자는 일직선상의 직선이 잡음 등의 영향으로 끊어져 있을 때 두 직선을 하나의 직선으로 하고자 할 때 사용한다.

### [확률 허프 변환 예제 코드](https://github.com/JeHeeYu/OpenCV/tree/main/Hough%20Transform)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203906474-ebf8e915-cffd-40d2-a4af-e0707183f383.png)

## 허프 변환 원(Probabilistic Hough Circle) 검출
허프 변환을 이용하여 원을 검출할 수 있다. 검출 방식은 아래와 같은 수식으로 정의한다.
<br>

![image](https://user-images.githubusercontent.com/87363461/203906554-d9b06396-c7b4-4d2d-b995-d46a50875f31.png)


<br>
<br>

중심 좌표가 (a, b)이고 반지름이 r인 원의 방정식 표현 방법이다.
<br>
이러한 원의 방정식은 3개의 파라미터를 가지고 있다.
<br>
허프 변환을 그대로 적용하려면 3차원의 파라미터 공간에서 축적 배열을 정의하고 가장 누적이 많은 위치를 찾아야 한다.
<br>
<br>
3차원 파라미터 공간에서 축적 배열을 정의하고 사용하려면 많은 메모리와 연산 시간을 필요로 한다.
<br>
그래서 OpenCV에선 일반적인 허프 변환 대신 허프 그래디언트 방법을 사용하여 원을 검출한다.

## 검출 방법
허프 그래디언트 방법은 2단계로 구성된다.
<br>
1단계 : 영상에 존재하는 모든 원의 중심 좌표를 찾는다.
<br>
<br>
2단계 : 검출된 원의 중심으로부터 원에 적합한 반지름을 구한다.
<br>
<br>
1단계에서 축적 배열이 사용된다.
<br>
허프 그래디언트 방법에서 사용하는 축적 배열은 파라미터 공간에서 만드는 것이 아닌 동일한 xy 좌표 공간에서 2차원 배열로 만든다.
<br>
원의 중심을 찾기 위해 허프 그래디언트 방법은 입력 영상의 모든 에지 픽셀에서 그래디언트를 구하고, 그래디언트 방향을 따르는 직선상의 축적 배열 값을 1씩 감소시킨다.

<br>
  
![image](https://user-images.githubusercontent.com/87363461/203906637-21a15e2f-a3c1-41ee-905c-0eb8b080b4c8.png)

<br>
<br>
원주상에 모든 점에 대해 그래디언트 방향의 직선을 그리고, 직선상의 축적 배열 값을 증가시키면 원의 중심 위치에서 축적 배열 값이 크게 나타난다.
<br>
원의 중심을 찾은 후 다양한 반지름의 원에 대해 원주상에 충분히 많은 에지 픽셀이 존재하는지 확인하여 적절한 반지름을 선택한다.
<br>
<br>
OpenCV에서는 원을 검출하는 함수를 제공한다.
```
void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist,
                  double param1 = 100, double param2 = 100, int minRadius = 0, int maxRadius = 0);

image : 입력 영상으로 에지 영상이 아닌 원본 그레이스케일 영상 지정
circles : 검찰된 원 정보를 저장할 출력 벡터
method : HOUGH_GRADIENT만 지정 가능
dp : 입력 영상과 축적 배열의 크기 비율
minDist : 인접한 원 중심의 최소 거리
param1 : Canny 에지 검출기의 높은 임계값
param2 : 축적 배열에서 원 검출을 위한 임계값
minRadius : 검출할 원의 최소 반지름
maxRadius : 검출할 원의 최대 반지름
```
HoughCircles() 함수에는 원본 그레이스케일 입력 영상을 전달한다. 그러면 함수 내부에서 Sobel() 함수와 Canny() 함수를 이용하여 그래디언트와 에지 영상을 계산한 후 허프 그래디언트 방법으로 원을 검출한다.
<br>
<br>
circles 인자에는 보통 vetor<Vec3f> 또는 vector<Vec4f> 자료형 변수를 지정한다.
<br>
<br>
dp 인자는 사용할 축적 배열의 크기를 결정하는 용도로 사용되는데, 1로 지정하면 입력 영상과 같은 크기의 축적 배열을 사용하고 2를 지정하면 입력 영상의 가로 세로 크기를 2로 나눈 크기의 축적 배열로 사용한다.
<br>
<br>
minDist 인자는 최소 거리를 지정한다. 두 원의 중심점 사이 거리가 minDist 보다 작으면 두 원 중 1개는 검출하지 않는다.

### [허프 변환 원 검출 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Hough%20Transform/HoughCircle.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203906827-48550b8a-47e6-47f0-827b-1d87e1f49cb2.png)

<br>
입력 영상 src의 잡음을 제거하는 용도로 blur() 함수를 적용한다.
<br>

HourCircles() 함수를 이용하여 원을 검출하고, 검출된 원의 중심 좌표와 반지름 정보는 circles 변수에 저장된다.
