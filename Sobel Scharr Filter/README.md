# 소벨 필터와 샤르 필터 정리

## 에지(Edge)란

영상에서 에지(edge)란 한쪽 방향으로 픽셀 값이 급격하게 바뀌는 부분을 말한다.
<br>
즉, 어두운 영역에서 갑자기 밝아진다거나, 밝은 영역에서 갑자기 어두워지는 부분을 에지라고 한다.
<br>
<br>
일반적으로 객체와 배경의 경계 또는 객체와 다른 객체의 경계에서 에지가 발생한다.
<br>
영상에서 에지를 찾아내는 작업은 객체의 윤곽을 알아낼 수 있는 유용한 방법이며 비전 시스템에서 객체 판별을 위한 전처리로 에지 검출이 사용되고 있다.
<br>
기본적으로 영상에서 에지를 찾아내려면 픽셀 값의 변화율을 측정하여 변화율이 큰 픽셀을 선택해야 한다.
<br>
<br>
2차원 공간에서 정의된 영상에서 에지를 찾으려면 x축 방향과 y축 방향의 편미분을 모두 사용해야 한다.
<br>
2차원 공간에서 정의된 함수 f(x, y)가 있을 때 이 함수의 x축 방향 미분과 y축 방향 미분을 한꺼번에 벡터로 표현한 것을 그래디언트(gradient)라고 한다.
<br>
<br>
2차원 영상에서 에지를 찾는 기본적인 방법은 그래디언트 크기가 특정 값보다 큰 위치를 찾는 것이다.
<br>
여기서 에지 여부를 판단하기 위해 기준이 되는 값을 임계값(threshold) 또는 문턱치 라고 부른다.
<br>
임계값은 영상의 특성에 따라 다르게 설정해야 하며, 보통 사용자의 경험에 의해 결정된다.
<br>
<br>
일반적으로 임계값을 높게 설정하면 밝기 차이가 급격하게 변하는 에지 픽셀만 검출되고, 임계값을 낮게 설정하면 약한 에지 성분도 검출된다.

## 소벨 필터(Sobel Filter) 마스크
대부분의 영상에는 잡음이 포함되어 있어 1 x 3, 3 x 1 마스크 등은 부적절한 결과가 생성될 수 있다.
<br>
그래서 실제 영상에서 잡음의 영향을 줄일 수 있도록 좀더 큰 크기의 마스크를 이용한다.
<br>
그중 가장 널리 사용되고 있는 미분 마스크가 소벨 필터(Sobel filter) 마스크 이다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203904737-bf403e27-7efa-436d-8ceb-1b49a4908abd.png)


<br>
<br>

영상의 가로 방향과 세로 방향으로 미분하는 3 x 3 크기의 소벨 필터 마스크이다.
<br>
<br>
왼쪽 마스크는 x축 방향으로의 편미분을 구하는 소벨 마스크이고,
<br>
오르쪽 마스크는 y축 방향으로의 편미분을 구하는 소벨 마스크이다.
<br>
<br>
x축 방향 미분 마스크는 현재 행에 대한 중앙 차분 연산을 2회 수행하고, 이전 행과 다음 행에 대해서도 중앙 차분 연산을 1회씩 수행한다.
<br>
이러한 연산은 현재 행과 이웃 행에서의 픽셀 값 변화가 유사하다는 점을 이용하여 잡음의 영향을 줄이기 위함이다.
<br>
현재 행에서 2번의 중앙 차분 연산을 수행하는 것은 현재 행의 주앙 차분 근사에 더 큰 가중치를 주기 위함이다.
<br>
<br>
OpenCV에서 소벨 마스크를 이용하여 영상을 미분하는 Sobel() 함수를 제공한다.
```
void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize =3,
           double scale = 1, double delta = 0, int borderType = BORDER_DEFAULT);

src : 입력 영상
dst : 출력 영상으로 src와 같은 크기, 같은 채널 수를 갖는다.
ddepth : 출력 영상의 깊이
dx : x 방향 미분 차수
dy : y 방향 미분 차수
ksize : 소벨 커널의 크기
scale : 필터링 연산 후 추가적으로 곱할 값
delta : 필터링 연산 후 추가적으로 더할 값
borderType : 가장자리 픽셀 확장 방식
```

Sobel() 함수는 입력 영상 src를 편미분한 결과를 dst에 저장한다.
<br>
Sobel() 함수는 x 방향과 y방향으로의 고차 미분을 계산할 수 있지만, 대부분의 경우 x 방향 또는 y 방향으로의 1차 미분을 구하는 용도로 사용된다.
<br>
<br>
결과 영상의 자료는 ddepth 인자를 통해 명시적으로 지정해야 하고, ddepth에 -1을 지정하면 src와 같은 타입을 사용하는 dst 영상을 생성한다.
<br>
<br>
dx와 dy 인자는 각각 x 방향과 y 방향으로의 편미분 차수를 의미한다.
<br>
<br>
ksize 인자에 1을 지정하면 1 x 3이나 3 x 1 커널을 사용하고, 기본값을 3을 지정하면 3 x 3 소벨 마스크를 사용한다.
<br>
ksize 이후의 인자는 모두 기본값을 가지고 있어 함수 호출 시 생략할 수 있다.

## 샤르 필터(Scharr Filter) 마스크

소벨 마스크와 비슷한 샤르 필터 마스크도 OpenCV에서 지원한다.
<br>
샤르 필터 마스크를 이용한 미분 연산을 지원하며, 3 x 3 소벨 마스크보다 정확한 미분 계산을 수행한다.

<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203904868-6df4a42e-daaa-449e-bab1-a1d54b3ff842.png)


<br>
<br>

```
void Scharr(InputArray src, OutputArray dst, int ddepth, int dx, int dy, double scale = 1,
            double delta = 0, int borderType = BORDER_DEFAULT);

src : 입력 영상
dst : 출력 영상으로 src와 같은 크기, 같은 채널 수를 갖는다.
ddepth : 출력 영상의 깊이
dx : x 방향 미분 차수
dy : y 방향 미분 차수
scale : 필터링 연산 후 추가적으로 곱할 값
delta : 필터링 연산 후 추가적으로 더할 값
borderType : 가장자리 픽셀 확장 방식
```

Sobel()함수 또는 Scharr() 함수를 이용하여 x 방향, y방향으로 가각 미분을 계산하여 저장한 후 미분 행렬을 이용하여 그래디언트 크기를 계산할 수 있다.

## 그래디언트 관련 함수
2차원 벡터의 x 방향 좌표와 y 방향 좌표를 이용하여 벡터의 크기를 계산하는 함수를 제공한다.

```
void magnitude(InputArray x, InputArray y, OutputArray magnitude);

x : 벡터의 x 좌표를 나타내는 실수 행렬 또는 벡터
y : 벡터의 y 좌표를 나타내는 실수 행렬 또는 벡터. x와 크기와 타입이 같아야 함
magnitude : 벡터의 크기를 나타내는 실수 또는 행렬 벡터. x와 같은 크기, 같은 타입을 갖는다.
```

magnitude() 함수의 입력으로 사용되는 x와 y는 CV_32F 또는 CV_64F 깊이를 사용하는 행렬 또는 벡터이어야 한다.
<br>
그래디언트 방향을 계산하고 싶을 때도 함수를 제공한다.

```
void phase(InputArray x, InputArray y, OutputArray angle, bool angleInDegrees = false);

x : 벡터의 x 좌표를 나타내는 실수 행렬 또는 벡터
y : 벡터의 y 좌표를 나타내는 실수 행렬 또는 벡터. x와 크기와 타입이 같아야 함
angle : 벡터의 방향을 나타내는 실수 행렬 또는 벡터. x와 같은 크기, 같은 타입을 갖는다.
angleInDegrees : 이 값이 true이면 각도(degree) 단위를 사용하고, false이면 라디안(radian) 단위를 사용함
```

### [소벨 필터 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Sobel%20Scharr%20Filter/SobelFilter.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203905017-c03d7cee-1a4e-4bd9-ac6e-0d4e44680980.png)

<br>
<br>
각 픽셀에서 계산된 그래디언트 크기가 255보다 큰 경우에는 포화 연산에 의해 흰색으로 표현된다.
<br>
edge 영상은 그래디언트 크기가 150보다 큰 픽셀은 흰색으로, 그렇지 않은 픽셀은 검은색으로 표현된 이진 영상이다.
<br>
<br>
임계값을 150보다 낮게 설정하면 더 많은 에지 픽셀이 edge 영상에 나타난다.
<br>
임계값을 너무 낮출 경우 잡음의 영향도 에지로 검출될 수 있다.
