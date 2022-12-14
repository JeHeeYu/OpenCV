## 이진화(Binarization)란
영상에서의 이진화란 영상의 각 픽셀을 2개의 부류로 나누는 작업을 말한다.
<br>
예를 들어, 입력 영상을 주요 객체 영역과 배경 영역으로 나눈다거나,
<br>
영상에서 중요도가 높은 관심영역(ROI)과 비관심 영역으로 구분하는 등 이런 용도로 이진화를 사용할 수 있다.
<br>
<br>
디지털 컴퓨팅 분야에서 이진화는 입력 값을 0 또는 1로 설정하지만,
<br>
영상의 이진화에서는 픽셀 값을 0 또는 255로 설정한다. 그러므로 이진화가 적용된 이진 영상은 보통 흰색과 검은색 픽셀로 구성된다.
<br>
<br>
영상의 이진화는 기본적으로 영상의 각 픽셀 값을 이용한다.
<br>
그레이스케일 영상에 대해 이진화를 수행하려면 영상의 픽셀 값이 특정 값보다 크면 255로, 작으면 0으로 설정한다.
<br>
이때 각 픽셀과의 크기 비교 대상이 되는 값을 임계값(threshold)라고 한다.
<br>
임계값은 그레이스케일 범위인 0부터 255까지 사이의 정수를 지정할 수 있다.

## 이진화 검출 방법
OpenCV에서 이진화를 위해 threshold() 함수를 지원한다.

```
double threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type);

src : 입력 영상
dst : 출력 영상
thresh : 임계값
maxval : THRESH_BINARY 또는 THRESH_BINARY_INV 방법을 사용할 때 결과 영상의 최댓값
type : 임계값 연산 방법으로 ThresholdTypes 열거형 상수를 지정할 수 있음
반환값 : 사용된 임계값 THRESH_OTSU 또는 THRESH_TRIANGLE 방법을 사용할 때 자동으로 결정된 임계값 반환
```

threshold() 함수의 동작은 type 인자에 의해 결정된다. 이는 ThresholdTypes 열거형 상수를 지정할 수 있다.

|ThresholdTypes 열거형 상수|값|
|:---:|:---:|:---:|
|THRESH_BINARY|일반적인 이진화 방식으로 픽셀 값이 thresh를 넘으면 최대값, 아니면 0 지정|
|THRESH_BINARY_INV|픽셀 값이 thresh를 넘으면 0, 아니면 최대값 지정|
|THRESH_TRUNC|픽셀 값이 thresh를 넘으면 thresh 값으로, 아니면 그대로 유지|
|THRESH_TOZERO|픽셀 값이 thresh를 넘으면 원본값, 아니면 0 지정|
|THRESH_TOZERO_INV|픽셀 값이 thresh를 넘으면 0, 아니면 원본 값 지정|
|THRESH_OTSU|오츠 알고리즘을 이용한 자동 임계값 설정|
|THRESH_TRIANGLE|삼각 알고리즘을 이용한 자동 임계값 설정|

THRESH_BINARY, THRESH_BINARY_INV, THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV5개의 상수가 threshold() 함수의 동작을 결정한다.
<br>
THRESH_OTSU와 THRESH_TRIANGLE 상수는 영상의 픽셀 값 분포를 임계값으로 자동으로 결정하여 이진화를 수행할 때 사용한다.
<br>
<br>
threshold() 함수를 이용하여 영상을 이진화하려면 maxval 인자에 255를 지정하고, type 인자에 THRESH_BINARY 또는 THRESH_BINARY_INV를 지정한다.
<br>
THRESH_BINARY_INV의 INV는 inverse이므로, THRESH_BINARY 방법으로 이진화를 수행한 후 영상을 반전하는 것과 같다.
<br>
<br>
예를 들어 영상의 임계값 128을 이용하여 이진화를 수행하려면 다음과 같이 코드를 작성한다.

```
Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

Mat dst;
threshold(src, dst, 128, 255, THRESH_BINARY);
```
### [영상 이진화 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Binarization/Threshold.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203908844-1f16dc6c-ae23-4122-a20a-74c1952018d7.png)

<br>
레나 영상에 임계값 128, 255와 255에 inverse를 준 결과 영상이다. 임계값을 128을 줄 경우 정상적인 이진화 작업이 수행되지만,
<br>
255를 줄 경우 그레이스케일 최대값 255와 같아져 영상이 정상 출력되지 않는다.

## 적응형 이진화(Adaptive Binarization)
threshold() 함수를 이용하는 것과 같이 영상의 모든 픽셀에 같은 임계값을 적용하여 이진화를 수행하는 방식을 전역 이진화(global binarization)이라고 한다.
<br>
<br>
그러나 영상 특성에 따라 전역 이진화를 적용하기 어려운 경우가 있다.
<br>
<br>
이처럼 불균일한 조명 성분을 가지고 있는 영상 등에 적용할 수 있는,
<br>
즉, 서로 다른 임계값을 사용하는 방식을 적응형 이진화(adaptive binarization) 이라고 한다.
<br>
<br>
적응형 이진화는 영상의 모든 픽셀에서 정해진 크기의 사각형 블록 영역을 설정하고, 블록 영역의 내부 픽셀 값 분포로부터 고유의 임계값을 결정하여 이진화하는 방식이다.
<br>
<br>
이진화 방식은 다음과 같은 수식으로 결정할 수 있다.
<br>

![image](https://user-images.githubusercontent.com/87363461/203909022-410f49f8-3364-4b81-a350-b909dc1d12d3.png)


<br>

u(x, y)는 (x, y) 주변 블록 영역의 픽셀 값 평균이고 C는 임계값의 크기를 조정하는 상수이다.
<br>
블록 내부 픽셀 값의 평균 u(x, y)는 일반적인 산술 평균을 사용하거나 가우시안 함수 형태의 가중지를 적용한 가중 평균을 사용한다.
<br>
상수 C는 영상 특성에 따라 사용자가 결정한다.

## 검출 방법
```
void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod,
                       int thresholdType, int blockSize, double C);

src : 입력 영상으로 CV_8UC1 또는 CV_8SC1 지정
dst : 출력 영상으로 src와 같은 크기의 같은 타입
maxValue : 이진화 결과 영상의 최댓값
adaptiveMethod : 적응형 이진화에서 블록 평균 계산 방법 지정
thresholdType : THERSH_BINARY 또는 THRESH_BINARY_INV 중 지정
blockSize : 임계값 계산 시 사용하는 블록 크기로 3보다 같거나 큰 홀수 지정
C : 임계값 조정을 위한 상수로 블록 평균에서 C를 뺀 값을 임계값으로 사용
```

adaptiveThreshold() 함수는 각 픽셀 주변의 blockSize x blockSize 영역에서 평균을 구한다.
<br>
그 후 평균에서 상수 C를 뺀 값을 해당 픽셀의 임계값으로 사용한다.
<br>
이때 블록 평균 영역울 구하는 방식은 adaptiveMethod 인자를 통해 설정할 수 있다. adaptiveMethod 인자에 ADAPTIVE_THRESH_MEAN_C 를 지정하면 blockSize x blockSize 크기의 주변 영역 픽셀로부터 산술 평균을 구한다.
<br> 
<br>
ADAPTIVE_THRESH_GAUSSIAN_C 를 지정하면 각 픽셀 주변에 blockSize x blockSize 크기의 가우시안 마스크를 적용하여 가우시안 가중 평균을 계산한다.

### [적응형 이진화 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Binarization/AdaptiveBinarization.cpp)
