# 블러링 기법

## 블러링 기법(Bluring)이란
블러링이란 마치 초점이 맞지 않은 사진처럼 영상을 부드럽게 만드는 필터링 기법이다. 스무딩(smoothing)이라고도 한다.
<br>
영상에서 인접한 픽셀 간의 픽셀 값 변화가 크지 않은 경우 부드러운 느낌을 받을 수 있다.
<br>
블러링은 거친 느낌의 입력 영상을 부드럽게 만드는 용도로 사용되거나 영상에 존재하는 잡음의 영향을 제거하는 전처리 과정으로 사용한다

### 평균값 필터
블러링 필터 중 단순하고 구현하기 쉬운 평균값 필터(mean filter)가 있다.
<br>
평균값 필터란 입력 영상에서 특정 픽셀과 주변 픽셀들의 산술 평균을 결과 영상 픽셀 값에 설정하는 필터이다.
<br>
평균값 필터에 의해 생성되는 결과 영상은 픽셀 값의 변화가 줄어들고, 날카로운 에지가 무뎌지며 노이즈의 영향이 크게 사라지는 효과가 있다.
<br>
<br>
그러나 평균값 필터를 너무 과도하게 사용하면 사물의 경계가 흐릿해지며 구분이 어려워진다.
<br>
평균값 필터 마스크는 마스크의 크기가 커지면 커질수록 더욱 부드러운 느낌의 결과 영상을 생성할 수 있다.
<br>
대신 연산량이 크게 증가할 수도 있다.
<br>
<br>
3 x 3 크기의 평균값 필터 마스크는 9개의 원소 개수로, 각각의 행렬은 모든 원소가 1/9로 설정된 행렬이다.
<br>
5 x 5 크기의 평균값 필터 마스크는 25개의 원소 개수로, 각각의 행렬은 모든 원소가 1/25로 구성된 행렬이다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203896157-268d8ee3-e788-4fec-8c42-170778857d33.png)

<br>
<br>
OpenCV에서 평균값 필터링 수행을 위해 blur() 함수를 제공한다.

### blur()
```
void blur(InputArray src, OutputArray dst, Size ksize, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT);

src : 입력 영상
src : 출력 영상으로 src와 같은 크기, 같은 채널 수를 갖는다.
ksize : 블러링 커널 크기
anchor : 고정점 좌표로 (-1, -1)을 지정하면 커널 중심점을 고정점으로 사용한다.
borderType : 가장자리 픽셀 확장 방식
```

src인자는 입력 영상으로, 다채널 영상은 각 채널별로 블러링을 수행한다.
<br>
입력 영상의 깊이는 CV_8U, CV_16U, CV_16S, CV_32F, CV_64F 중 하나여야 한다.
<br>
<br>
anchor, borderType 인자는 기본값을 가지고 있으므로 생략할 수 있다.
<br>
ksize는 블러링 커널의 크기로, ksize 크기의 평균값 필터 마스를 사용하여 dst 출력 영상을 생성한다.
<br>
kernel의 크기는 1/ksize.width * ksize.height로 나타낼 수 있다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203896222-51ceba42-da3e-4b43-8f22-a69808eeb51f.png)

<br>
<br>
5 x 5행렬을 기준으로 각 픽셀의 크기이다.

### [블러링 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Bluring%20Gaussian/Bluring.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203896362-f0ec5aa3-e89b-4035-9172-206c31599a15.png)

<br>
<br>
for문을 이용하여 3 x 3, 5 x 5, 7 x 7 크기의 ksize를 설정한다.
<br>
ksize x ksize 크기의 평균값 필터 마스크를 이용하여 블러링을 수행한다.
<br>
<br>
putText()함수를 이용하여 결과 영상 dst 위에 마스크 크기를 문자열 형태로 표현한다.

## 가우시안 필터(Gaussian Filter)
가우시안 필터(Gaussian filter)란 가우시안 분포(Gaussian distribution) 함수를 근사하여 생성한 필터 마스크를 사용하는 필터링 기법이다.
<br>
가우시안 분포는 평균을 중심으로 좌우 대칭의 종 모양을 갖는 확률 분포를 말한다. 정규 분포(normal distibution)이라고도 한다.
<br>
<br>
가우시안 분포는 평균과 표준 편차에 따라 분포 모양이 결정된다. 다만 영상의 가우시안 필터에서는
<br>
주로 평균이 0인 가우시안 분포 함수를 사용한다.
<br>
<br>
가우시안 분포를 따르는 2차원 필터 마스크 행렬을 생성하려면 2차원 가우시안 분포 함수를 근사해야 한다.
<br>
2차원 가우시안 분포 함수는 x, y 2개의 변수를 사용하고, 분포의 모양을 결정하는 평균과 표준 편차도 x, y축 방향에 따라 따로 설정한다.
<br>
<br>
가우시안 필터 마스크 행렬은 중앙부에서 비교적 큰 값을 가지고, 사이드로 갈 수록 행렬 원소 값이 0에 가까운 작은 값을 가진다.
<br>
이런 필터 마스크를 이용하여 마스크 연산을 수행한다는 것은 필터링 대상 픽셀 근처에서 가중치를 크게 주고,
<br>
필터링 대상 픽셀과 멀리 떨어져 있는 주변부에는 가중치를 조금만 주어서 가중 평균을 구하는 것과 같다.
<br>
<br>
즉, 가우시안 필터 마스크가 가중 평균을 구하기 위한 가중치 행렬 역할을 하는 것이다.
<br>
<br>
OpenCV에서 가우시안 필터링을 수행하기 위해 GaussianBlur() 함수를 제공한다.

### GaussianBlur()
```
void GaussianBlur(InputArray src, OutputArray dst, Size kszie, 
                  double sigmaX, double sigmaY = 0, int borderType = BORDER_DEFAULT);

src : 입력 영상
dst : 출력 영상
ksize : 가우시안 커널 크기
sigmaX : x 방향으로의 가우시안 커널 표준 편차
sigmaY : y 방향으로의 가우시안 커널 표준 편차
borderType : 가장자리 픽셀 확장 방식
```
src 인자는 입력 영상으로 다채널 영상은 각각의 채널별로 블러링을 수행한다.
<br>
<br>
dst 인자는 출력 영상으로 입력 영상(src)와 같은 크기, 같은 타입을 갖는다.
<br>
<br>
ksize 인자는 가우시안 커널 크기로, ksize.width와 ksize.height는 0보다 큰 홀수여야 한다.
<br>
ksize에 Size()를 지정하면 표준 편차로부터 커널 크기를 자동으로 결정한다.
<br>
<br>
sigma X, Y 인자는 가우시안 커널 표준 편차로, 만약 sigmaY = 0이면 sigmaX와 같은 값을 사용한다.
<br>
sigmaX, sigmaY가 모두 0이면 ksize의 width와 height 값으로 표준 편차를 계산하여 사용한다.
<br>
<br>
GaussianBlur() 함수는 src 영상에 가우시안 필터링을 수행하고 그 결과를 dst 영상에 저장한다.
<br>
보통 sigmaX, sigmaY의 값은 같은 값을 사용한다. 특별한 경우 서로 다른 값을 지정해주어도 된다.
<br>
<br>
가우시안 필터의 크기를 지정하는 ksize 인자에도 특별한 이유가 없다면 Size()를 전달하여
<br>
적절한 필터 크기를 자동으로 결정하도록 하는 것이 좋다.

### [가우시안 필터 예제 코드](https://github.com/JeHeeYu/OpenCV/tree/main/Bluring%20Gaussian)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203896607-f0e1279b-d2a2-48fc-b28b-c8659558a00b.png)

<br>
<br>
sigma 값을 1부터 5까지 증가시키면서 가우시안 블러링을 수행하고 그 결과를 화면에 나타낸다.
<br>
표준 편차 값이 커질수록 결과 영상이 더욱 부드럽게 변경된다.
<br>
<br>
GaussianBlur() 함수 내부에서 가우시안 필터링을 구현할 때 x축 방향과 y축 방향에 따라 1차원 가우시안 필터 마스크를
<br>
각각 생성하여 필터링을 수행하는데, 이때 1차원 가우시안 필터 마스크를 생성할 수 있다.


### getGaussianKernel()
```
Mat getGaussianKernel(int ksize, double sigma, int ktype = CV_64F);

ksize : 커널 크기
sigma : 가우시안 표준 편차
ktype : 필터의 타입
반환값 : ksize x 1 크기의 가우시안 필터 커널
```

ksize 인자는 커널의 크기로 0보다 큰 홀수여야 한다.
<br>
<br>
sigma 인자는 가우시안 표준 편차로 만약 0 이나 음수를 지정하면
<br>
sigma = 0.3*((ksize-1) * 0.5 - 1) + 0.8 형태로 sigma를 계산한다.
<br>
<br>
ktype 인자는 필터의 타입으로 CV_32F 또는 CV_64F를 사용한다.
<br>
<br>
getGaussianKernel() 함수는 표준 편차가 sigma인 1차원 가우시안 분포 함수로부터 ksize x 1 크기의 필터 마스크 행렬을 생성해서 반환한다.
<br>
<br>
ksize는 (8 * sigma + 1)보다 같거나 크게 지정하는 것이 좋다.
