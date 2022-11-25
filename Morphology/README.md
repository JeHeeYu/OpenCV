## 모폴로지(Morphology)란
모폴로지란 의미를 보면 형태 또는 모양에 관한 학문을 의미한다. 형태학 이라고도 한다.
<br>
영상 처리에서 모폴로지란 영상에서 객체의 형태 및 구조에 대해 분석하고 처리하는 기법을 의미한다.
<br>
수학적 모폴로지(mathematical morphology)라고도 한다.
<br>
<br>
모폴로지 기법은 그레이스케일 영상과 이진 영상에 대하여 모두 적용할 수 있다.
<br>
하지만 모폴로지는 주로 이진 영상에서 객체의 모양을 단순화시키거나 잡음을 제거하는 용도로 사용한다.

## 모폴로지 연산 방법

모폴로지 연산을 정의하려면 먼저 구조 요소(structuring element)를 정의해야 한다.
<br>
구조 요소는 필터링에서 사용되는 마스크와 같이 모폴로지 연산의 동작을 결정하는 작은 크기의 행렬이다.
<br>
<br>
구조 요소는 다양한 크기와 모양으로 정의할 수 있다.
<br>
필요에 따라 원하는 구조 요소를 선택하여 사용할 수 있지만 대부분의 모폴로지 연산에서는 3 x 3 정방향 구조 요소를 사용한다.
<br>

![image](https://user-images.githubusercontent.com/87363461/203909444-97611400-f4fd-433d-a076-74c02d231db5.png)


<br>

## 침식(erosion)과 팽창(dilation)

영상의 모폴로지 기법 중 가장 기본이 되는 연산은 침식(erosion)과 팽창(dilation)이다.
<br>
침식 연산이란 객체 영역의 외곽을 골로구 깎아 내는 연산으로, 전체적으로 객체 영역은 축소되고 배경은 확대된다.
<br>
침식 연산은 구조 요소를 영상 전체에 대해 스캔하면서, 구조 요소가 객체 영역 내부에 완전히 포함될 경우 고정점 위치 픽셀을 255로 설정한다.
<br>
<br>
팽창 연산이란 객체 외곽을 확대하는 연산으로, 팽창 연산을 수행하면 객체 영역은 확대되고, 배경 영역은 줄어든다.
<br>
팽창 연산은 구조 요소를 영상 전체에 대해 이동시키면서, 구조 요소와 객체 영역이 한 픽셀이라도 만나면 고정점 위치 픽셀을 255로 설정한다.

## 침식과 팽창 연산 수행 과정
침식과 팽창 연산 수행은 입력 영상에 구조 요소를 사용하여 수행한다.
<br>
12 x 12 크기의 입력 이진 영상을 확대하여 나타낸 것이며, 흰색으로 표시된 객체가 있다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203909541-758deb32-eeee-4d77-b692-3d62220aac57.png)

<br>

모폴로지 연산은 주로 3 x 3 정방향 구조 요소를 사용한다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203909574-e08bbc6c-e8b0-4774-8a6c-48e5e4116e53.png)


<br>
12 x 12 크기의 이진영상에 3 x 3 정방향 구조 요소를 이용하여 침식 연산을 수행한 결과이다.
<br>
침식 연산에 의해 객체 모양이 상하좌우 모든 방향에 대해 한 픽셀 정도 깍인 것 같이 변경된다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203909621-f3bf6e04-b67b-43f4-be10-6eac63322dac.png)


<br>

위에 입력 영상에 다시 팽창 연산을 수행한 것이 아래의 결과이다.
<br>
객체 영역이 상하좌우 모든 방향에 대해 한 픽셀 정도 확대된 것처럼 변경되며, 객체 아래쪽에 작게 패인 부분이 깔끔하게 매워진다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203909656-60d69ea0-b193-44fe-ac0b-843c980017e9.png)


<br>

## 침식과 팽창 연산 수행 함수

OpenCV에서 구조 요소는 원소 값이 0 또는 1로 구성된 CV_8UC1 타입의 Mat 행렬로 표현한다.
<br>
구조 요소 행렬에서 값이 1인 원소만을 이용하여 구조 요소의 모양을 결정한다.
<br>
<br>
이 구조 요소 행렬을 간단하게 생성할 수 있도록 OpenCV에서는 함수를 제공한다.

```
Mat getStructuringElement(int shape, Size ksize, Point anchor = Point(-1, -1));

shape : 구조 요소의 모양으로 MorphShapes 열거형 상수 지정
ksize : 구조 요소의 크기
anchor : 중심 좌표로 (-1, -1)을 지정하면 구조 요소의 중앙을 십자가 중심 좌표로 사용
반환값 : 구조 요소 행렬
```

getStructuringElement() 함수는 지정한 모양과 크기에 해당하는 구조 요소 행렬을 반환한다.
<br>
첫 번째 인자 shape는 구조 요소의 모양을 결정하는 역할을 하며, MorphShapes 열거형 상수를 지정할 수 있다.

|MorphShapes 열거형 상수|설명|
|:---:|:---:|
|MORPH_RECT|사각형 모양의 구조 요소|
|MORPH_CROSS|십자가 모양의 구조 요소|
|MORPH_ELLIPSE|타원 모양의 구조 요소. 지정한 구조 요소 크기의 사각형에 내접하는 타원을 이용|


OpenCV에서 영상의 침식 연산은 erode() 함수를 이용하여 수행한다.

```
void erode(InputArray src, OutputArray dst, InputArray kernel, Point anchor = Point(-1, -1), int iterations = 1
           int borderType = BORDER_CONSTANT, Const Scalar& borderValue = morphologyDefaultBorderValue());

src : 입력 영상
dst : 출력 영상으로 src와 같은 크기, 같은 타입을 갖는다.
kernel : 구조 요소
anchor : 고정점 위치
iterations : 반복 횟수
borderType : 가장자리 픽셀 확장 방식
borderValue : borderType이 BORDER_CONSTANT일 경우 확장된 가장자리 픽셀값을 채운다.
```

kernel 인자는 구조 요소로서, 만약 Mat() 또는 noArray()를 지정하면 3 x 3 사각형 구조 요소를 사용한다.
<br>
그 외의 구조 요소는 getStructuringElement() 함수를 이용하여 만들 수 있다.
<br>
<br>
anchor : 고정점 위치로 (-1, -1)을 지정하면 구조 요소 중앙을 고정점으로 사용한다.
<br>
<br>
borderValue 인자는 bordertype이 BORDER_CONSTANT인 경우, 확장된 가장자리 픽셀을 채울 값이다.
<br>
기본값으로 설정된 morphologyDefaultBorderValue() 함수는 모든 멤버 변수가 DBL_MAX로 채워진 Scalar 객체를 반환한다.
<br>
<br>
src, dst, kernel 인자를 제외한 나머지 인자들은 기본값이 설정되어 있으므로 생략할 수 있다.
<br>
<br>
OpenCV에서 팽창 연산을 수행하려면 dilate() 함수를 이용한다.

```
void dilate(InputArraty src, OutputArray dst, InputArray kernel, Point anchor = Point(-1, -1), int iterations = 1,
            int borderType = BORDER_CONSTANT, const Scalar& borderValue = morpholgyDefaultBorderValue());

src : 입력 영상
dst : 입력 영상으로 src와 같은 크기, 같은 타입을 갖는다.
kernel : 구조 요소
anchor : 고정점 위치
interations : 반복 횟수
borderType : 가장자리 픽셀 확장 방식
borderValue : borderType이 BORDER_CONSTANT인 경우 확장된 가장자리 픽셀을 채울 값
```

dilate() 함수의 인자 구성은 erode() 함수와 완전히 같다.

### [침식과 팽창 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Morphology/Erosion_Dilation.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203910112-84f7ad7d-e72b-4d98-a342-510670a74806.png)

왼쪽 부터 순서대로 입력 영상, 이진화 영상, 침식 연산, 팽창 연산 수행 결과이다.
<br>
침식 연산과 팽창 연산은 3 x 3 구조 요소를 이용하여 수행한 결과이다.

## 열기(Opening)와 닫기(Closing)

모폴로지 기법 중 침식과 팽창 말고도 열기와 닫기 연산도 존재한다.
<br>
<br>
열기와 닫기 연산은 침식과 팽창 연산을 이용하여 쉽게 구할 수 있는 영상이다.
<br>
열기 연산이란 입력 영상에 대하여 침식 연산을 수행한 후, 다시 팽창 연산을 수행하는 연산이다.
<br>
<br>
닫기 연산이란 입력 영상의 반대로 팽창 연산을 먼저 수행한 후, 다시 침식 연산을 수행하는 연산이다.
<br>
<br>
열기와 닫기 연산은 각각 침식과 팽창 연산이 한 번씩 적용되기 때문에 객체 영역의 크기가 크게 바뀌지 않는다.
<br>
다만 침식과 팽창 연산을 적용하는 순서에 따라 서로 다른 효과가 발생한다.
<br>
<br>
열기 연산은 침식 연산을 먼저 수행하기 때문에 한두 픽셀짜리 영역이 제거된 후, 팽창 연산이 수행된다.
<br>
그 결과 입력 이진 영상에 존재하는 작은 크기의 객체가 효과적으로 제거된다.
<br>
<br>
닫기 연산은 팽창 연산을 수행하기 때문에 객체 내부의 작은 구멍이 메워진 후, 침식 연산이 수행된다.
<br>
결과적으로 닫기 연산은 객체 내부의 작은 구멍을 제거한다.

## 열기와 닫기 연산 수행 함수
OpenCV에서 모폴로지 열기와 닫기 연산은 morphologyEx() 함수를 이용하여 수행한다.
<br>
열기와 닫기 뿐 아니라, 침식과 팽창 같은 일반적인 모폴로지 연산도 수행할 수 있는 범용적인 모폴로지 함수이다.

```
void morphologyEx(InputArray src, OutputArray dst, int op, InputArray kernel, Point anchor = Point(-1, -1)
                 int iterations = 1, int borderType = BORDER_CONSTANT, const Scalar& borderValue = morphologyDefaultBorderValue());

src : 입력 영상
dst : 출력 영상으로 src와 같은 크기, 같은 타입을 갖는다.
op : 모폴로지 연산 타입으로 morphTypes 열거형 상수를 지정한다.
kernel : 구조 요소
anchor : 고정점 위치
iterations : 반복 횟수
borderType : 가장자리 픽셀 확장 방식
borderValue : borderType이 BORDER_CONSTANT인 경우 가장자리 픽셀 값
```

morphologyEx 함수는 op 인자를 제외한 모든 인자는 erode, dilate 함수와 같다.
<br>
op 인자를 이용하여 모폴로지 연산 방법을 지정한다.
<br>
op 인자에는 MorphTypes 열거형 상수 중 하나를 지정할 수 있다.

|주요 MorphTypes 열거형 상수|설명|
|:---:|:---:|
|MORPH_ERODE|침식 연산|
|MORPH_DILATE|팽창 연산|
|MORPH_OPEN|열기 연산|
|MORPH_CLOSE|닫기 연산|
|MORPH_GRADIENT|모폴로지 그래디언트 계산 dst = dilate(src, element) - erode(src, element)|

MORPH_GRADIENT 상수는 팽창 결과 영상에서 침식 결과 영상을 빼는 연산을 수행하며, 객체의 외곽선이 추출되는 효과가 있다.

### [열기와 닫기 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Morphology/Opening_Closing.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203910506-c682bbab-c0ea-4979-98ec-d1e8cbcbd04f.png)

<br>

왼쪽 부터 순서대로 입력 영상, 이진화 영상, 열기 연산, 닫기 연산 수행 결과이다.
