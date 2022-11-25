# 잡음 제거 필터링

영상 처리 관점에서 잡음(noise)란 원본 신호에 추가된 원치 않은 신호를 뜻한다.
<br>
영상에서 잡음은 주로 영상을 획득하는 과정에서 발생하며, 디지털 카메라에서 사진을 촬영하는 경우
<br>
광학적 신호를 전기적 신호로 변환하는 센서에서 주로 잡음이 추가된다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203900934-db624d64-98e1-4ada-a0d8-001612a01cca.png)
<br>
<br>
카메라에서 획득되는 영산신호는 보통 위와 같은 식으로 표현한다.
<br>
<br>
f(x, y) : 실제로 카메라에서 획득되는 영상 신호
<br>
s(x, y) : 디지털 카메라에서 카메라 렌즈가 바라보는 원본 신호
<br>
n(x, y) : 영상에 추가되는 잡음
<br>
<br>
잡음이 생성되는 방식을 잡음 모델(noise model) 이라고 하며, 다양한 잡음 모델 중 가장 대표적인 잡음 모델은 가우시안 잡음 모델이다.
<br>
가우시안 잡음 모델은 보통 평균이 0인 가우시안 분포를 따르는 잡음을 의미한다.
<br>
<br>
대부분의 영상에 가우시안 잡음이 포함되어 있으며, 많은 컴퓨터 비전 시스템이 가우시안 잡음을 제거하기 위해
<br>
가우시안 필터를 사용한다. 입력 영상에서 픽셀 값이 크게 변하지 않는 평탄한 영역에 가우시안 필터가 적용될 경우는
<br>
주변 픽셀 값이 부드럽게 블러링되면서 잡음의 영향이 크게 줄어든다.
<br>
<br>
그러나 픽셀 값이 급격하게 변경되는 에지 근방에 동일한 가우시안 필터가 적용되면 잡음 뿐만 아니라 에지 성분까지 감소하게 된다.
<br>
이러한 단점을 보완하기 위해 다양한 필터링이 존재한다.

## 양방향 필터
양방향 필터(bilateral filter)란 1998년 토마시(C. Tomasi)가 제안한 에지 성분은 그대로 유지하면서 가우시안 잡음을 효과적으로 제거하는 알고리즘이다.
<br>
OpenCV에서 양방향 필터를 위해 함수를 제공한다.

### bilateraFilter()
```
void bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor,
                     double sigmaSpace, int borderType = BORDER_DEFAULT);

src : 입력 영상
dst : 출력 영상
d : 필터링에 사용할 이웃 픽셀과의 거리
sigmaColor : 색 공간에서의 가우시안 필터 표준 편차
sigmaSpace : 좌표 공간에서의 가우시안 필터 표준 편차
borderType : 가장자리 픽셀 확장 방식
```
src 인자는 입력 영상으로 8비트 또는 실수형을 사용하며, 1채널 또는 3채널 영상을 사용한다.
<br>
<br>
dst 인자는 출력 영상으로 src와 같은 크기, 같은 타입을 갖는다.
<br>
<br>
d 인자에 양수가 아닌 값을 지정하면 sigmaSpace로부터 자동 계산된다.
<br>
<br>
bilateralFilter() 함수에서 sigmaSpace 값은 일반적인 가우시안 필터링에서 사용하는 표준 편차와 같은 개념이다.
<br>
<br>
즉, 값이 클수록 더 많은 주변 픽셀을 고려하여 블러링을 수행한다.
<br>
<br>
sigmaColor 값은 주변 픽셀과의 밝기 차이에 관한 표준 편차이며, 값을 작게 지정할 경우 픽셀 값 차이가 큰 주변 픽셀과는 블러링이 적용되지 않는다.
<br>
값을 크게 할 경우 픽셀 값 차이가 조금 크더라도 블러링이 적용된다.
<br>
<br>
즉, sigmaColor 값을 이용하여 어느 정도 발기 차를 갖는 에지를 보존할 것인지를 조정할 수 있다.

### [양방향 필터 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Noise%20Filter/NoiseFilter.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203901345-165d2c16-51e6-4caf-a19c-691c156f1dc0.png)
<br>
<br>
src 영상은 평균이 0이고 표준 편차가 5인 가우시안 잡음이 추가된 영상이다.
<br>
src 영상에 대해 표준 편차가 5인 가우시안 필터링은 수행한 결과가 dst1이다.
<br>
src에 비해 지글거리는 잡음의 영향은 줄었지만, 전체적으로 블러링되어 흐릿하게 보인다.
<br>
<br>
dst2 영상은 양방향 필터가 적용된 영상이다.
<br>
전체적으로 그대로 유지되어 깔끔한 느낌을 주는 것이 보인다.

## 미디언 필터(Median Filter)
미디언 필터란 입력 영상에서 자기 자신 픽셀과 주변 픽셀 값 중에서 중간값을 선택하여 결과 영상 픽셀 값으로 설정하는 필터링 기법이다.
<br>
미디언 필터는 특히 잡음 픽셀 값이 주변 픽셀 값과 큰 차이가 있는 경우 효과적으로 동작한다.
<br>
<br>
미디언 필터는 마스크 행렬과 입력 영상 픽셀 값을 서로 곱한 후, 더하는 형태의 연산을 하지 않는다.
<br>
미디언 필터는 주변 픽셀 값들의 중간값을 선택하기 위해 내부에서 픽셀 값 정렬 과정이 사용된다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203901429-f1fdc494-dfe1-4778-b235-91a2a6ff9bf4.png)
<br>
<br>
미디언 필터의 동작 방식이다.
<br>
3 x 3 픽셀의 배열을 나타내고, 이 영역의 픽셀 값을 일렬로 세운 후, 픽셀 값 크기 순으로 정렬한다.
<br>
그리고 정렬된 데이터에서 중앙에 있는 값 72를 선택하여 결과 영상의 픽셀 값으로 설정한다.
<br>
이런 과정을 영상 전체에 수행하면 미디언 필터 영상이 만들어진다.
<br>
<br>
OpneCV에서 미디언 필터 관련 함수를 제공한다.


### medianBlur()
```
void medianBlur(InputArray src, OutputArray dst, int ksize);

src : 입력 영상
dst : 출력 영상
ksize : 필터 크기
```
src 인자는 입력 영상으로 1, 3, 4 채널 영상을 사용할 수 있다.
<br>
<br>
ksize가 3이나 5이면 src는 CV_8U, CV_16U, CV_32F의 깊이를 가질 수 있고,
<br>
그 이상의 필터 크기에서는 CV_8U 깊이만 사용할 수 있다.
<br>
<br>
dst 인자는 출력 영상으로 src와 같은 크기, 같은 타입을 갖는다.
<br>
<br>
ksize 인자는 필터 크기로 3과 같거나 큰 홀수를 지정한다.
<br>
<br>
medianBlur() 함수는 ksize x ksize 필터 크기를 이용하여 미디언 필터링을 수행한다.
<br>
다채널 영상인 경우 각 채널별로 필터링을 수행하고, 내부적으로 BORDER_REPLICATE 방식으로 가장자리 외곽 픽셀 값을 설정하여 필터링을 수행한다.

### [미디언 필터 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Noise%20Filter/MedianFilter.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203901649-8c909809-b931-424b-8838-37f065d03bc7.png)

<br>
<br>
레나 영상에 잡음이 추가된 영상으로 이 영상에 대해 가우시안 필터를 적용한 결과가 dst1이고, 미디안 필터가 적용된 결과가 dst2이다.
<br>
미디언 필터를 적용한 dst2 영상에서는 잡음에 의해 추가된 픽셀이 제거됐다.

