## HOG(Histogram of Oriented Gradients)란
HOG 알고리즘이란 2005년 다랄(N. Dalal)과 트릭스(B. Triggs)가 발표한 알고리즘으로, 보행자 검출을 하기 위해 널리 사용되는 기법 중 하나이다.
<br>
<br>
HOG는 그래디언트 방향 히스토그램을 의미한다.
<br>
사람이 서 있는 영상에서 그래디언트를 구하고, 그래디언트의 크기와 방향 성분을 이용하여 사람이 서 있는 형태에 대한 특징 벡터를 정의했다.
<br>
여기에 머신 러닝의 일종인 서포트 벡터 머신(SVM. Support Vector Machine) 알고리즘을 이용하여 입력 영상에서 보행자 위치를 검출할 수 있도록 방법을 제안했다.

## HOG 계산 방법

보행자 검출을 위한 HOG는 기본적으로 64 x 128 크기의 영상에서 계산한다.
<br> 
HOG 알고리즘은 먼저 입력 영상으로부터 그래디언트를 계산한다.
<br>
그래디언트는 크기와 방향 성분으로 계산하며, 방향 성분은 0° 부터 180°까지 범위로 설정한다.
<br>
<br>
그 다음 입력 영상을 8 x 8 크기로 분할한다. 입력 영상인 64 x 128 영상에서는 가로 방향으로 8개, 세로 방향으로 16개가 생성된다.
<br>
이때 8 x 8 부분 영상을 셀(cell)이라고 하며, 인접한 4개의 셀을 합쳐서 블록(block)이라고 한다.
<br>
<br>
각각의 셀로부터 그래디언트 방향 성분에 대한 히스토그램을 구하며, 이때 방향 성분을 20°단위로 구분하면 총 9개의 빈으로 구성된 방향 히스토그램이 만들어진다.
<br>
<br>
1개의 블록에는 4개의 셀이 존재하고 각 셀에는 9개의 빈으로 구성된 히스토그램 정보가 있다.
<br>
그래서 블록 1개에서는 총 36개의 실수 값으로 이루어진 방향 히스토그램 정보가 추출되고 각 블록은 가로와 세로 방향으로 각각 1개의 셀만큼 이동하면서 정의한다.
<br>
<br>
입력 영상인 64 x 128 영상에서 블록은 가로 방향으로 7개, 세로 방향으로 15개로 정의할 수 있다.
<br>
계산해보면 105개의 블록이 추출될 수 있고, 전체 블록에서 추출되는 방향 히스토그램 실수 값 개수는 105 * 36 = 3780이 계산된다.
<br>
이 3780개의 실수 값이 64 x 128 영상을 표현하는 HOG 특징 벡터 역할을 한다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203925375-93d970dc-276c-48f1-8b89-b5881a50a684.png)



<br>

왼쪽 그림에서 녹색 선이 셀을 구분하는 선이고, 빨간색 사각형은 블록 하나를 나타낸다.
<br>
하나의 블록에는 4개의 셀로 이루어져 있다.
<br>
오른쪽 그림은 각 셀에서 계산된 그래디언트 방향 히스토그램을 비주얼하게 표현한 결과이다.

## HOG 알고리즘 구현 함수
OpenCV는 HOG 알고리즘을 구현한 HOGDescriptor 클래스를 제공한다. 이 클래스를 이용하면 특정 객체의 HOG 기술자를 쉽게 구현할 수 있다.
<br>

HOGDescriptor 클래스를 이용하려면 먼저 HOGDescriptor 객체를 생성하여야 한다.
<br>
객체를 생성하기 위해 기본 생성자를 이용하면 되는데, 이 기본 생성자는 윈도우 검색 크기를 64 x 128로 설정하고, 셀 크기는8 x 8, 블록 크기는 16 x 16, 그래디언트 방향 히스토그램 빈 개수는 9개로 설정한다.
<br>
<br>
즉, 기본 생성자에 의해 만들어지는 HOG 기술자 하나는 3780개의 float 실수로 구성된다.
<br>
<br>
HOG 기술자를 이용하여 입력 영상에서 객체 영역을 검출할 수 있는 HOGDescriptor::detecMultiScale() 멤버 함수를 제공한다.

```
virtual void HOGDescriptor::detecMultiScale(InputArray img, std::vector<Rect>& foundLocations, 
                                            std::vector<double>& fondWeights, double hitTreshold = 0, 
                                            Size winStride = Size(), Size padding = Size(), double scale = 1.05, 
                                            double final Threshold = 2.0, bool useMeanshiftGrouping = false) const;

virtual void HOGDescriptor::detecMultiScale(InputArray img, std::vector<Rect>& foundLocations, double hitTreshold = 0,
                                            Size winStride = Size(), Size padding = Size(), double scale = 1.05, 
                                            double final Threshold = 2.0, bool useMeanshiftGrouping = false) const;

img : 입력 영상으로 CV_8UC1 또는 CV_8UC3 타입
foundLocations : 검출된 사각형 영역 정보
foundWeights : 검출된 사각형 영역에 대한 신뢰도
hitTreshold : 특징 벡터와 SVM 분류 평면까지의 거리에 대한 임계값
winStride : 셀 윈도우 이동 크기로 Size() 지정 시 셀 크기와 같게 설정됨
padding : 패딩 크기
scale : 검색 윈도우 크기 확대 비율
finalTreshold : 검출 결정을 위한 임계값
useMeanshiftGrouping : 겹쳐진 검색 윈도우를 합치는 방법 지정 플래그
```

HOGDescriptor::detectMultiScale() 함수는 입력 영상img 에서 다양한 크기의 객체 사각형 영역을 검출하고, 그 결과를 std::vector<Rect> 타입의 인자 foundLocations에 저장한다.
<br>
보행자 검출을 목적하으로 하는 HOGDescriptor::getDefaultPeopleDetector() 정적 멤버 함수도 제공한다.
  
```
static std::vector<float> HOGDescriptor::getDefaultPeopleDetector();

반환값 : 보행자 검출을 위해 훈련된 분류기 계수
```
HOGDescriptor::getDefaultPeopleDetector()함수는 64 x 128 크기의 윈도우에서 똑바로 서 있는 사람을 검출하는 용도로 훈련된 분류기 계수를 반환한다.
<br>
<br>
이 함수는 정적 멤버 함수이기 때문에 소스 코드 작성 시 클래스 이름과 함께 사용해야 한다.
<br>
HOGDescriptor 클래스를 이용하여 원하는 객체를 검출하기 위해서 먼저 검출할 객체에 대해 훈련된 SVM분류기 계수를 HOGDescriptor::setSVMDetector() 함수에 등록해야 한다.
  
```
virtual void HOGDescriptor::setSVMDetector(InputArray svmdetector);

svmdetector : 선형 SVM 분류기를 위한 계수
```
보행자 검출을 할 경우 HOGDescriptor::getDefaultPeopleDetector() 함수가 반환한 분류기 계수를 HOGDescriptor::setSVMDetector() 함수의 인자로 전달하면 된다.

  
### [보행자 검출 예제 코드]
