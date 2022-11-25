## 레이블링(Labeling)이란
레이블링이란 이진화한 이미지에서 형체를 알아볼 수 있도록 하기 위해서 같은 픽셀 값들 끼리 그룹화하여 번호를 매기는 것을 말한다.
<br>
<br>
영상을 이진화 작업을 수행하면 주요 객체와 배경 영역을 구분할 수 있다.
<br>
일단 배경과 객체를 구분하였다면 이제 다시 각각의 객체를 구분하고 분석하는 작업이 필요한데, 이때 사용하는 기법이 레이블링 기법이다.
<br>
<br>
레이블링은 영상 내에 존재하는 객체 집합에 고유 번호를 매기는 작업으로 연결된 구성 요소 레이블링(connected components labling)이라고도 한다.
<br>
레이블링 기법을 이용하여 각 객체의 위치와 크기 등 정보를 추출하는 작업은 객체 인식을 위한 전처리 과정으로 자주 사용된다.
<br>
<br>
영상의 레이블링은 일반적으로 이진화된 영상에서 수행된다. 이때 검은색 픽셀은 배경으로 간주하고, 흰색 픽셀은 객체로 간주한다.
<br>
정확하게는 입력 영상의 픽셀 값이 0이면 배경, 0이 아니면 객체 픽셀로 인식한다.
<br>
하나의 객체는 한 개 이사의 인접한 픽셀로 이루어지며, 하나의 객체를 구성하는 모든 픽셀에는 같은 레이블 번호가 지정된다.

## 픽셀의 연결 관계
특정 픽셀과 이웃한 픽셀의 연결 관계는 크게 두 가지 방식으로 정의할 수 있다.
<br>
첫 번째는 특정 픽셀의 상하좌우로 붙어 있는 픽셀끼리 연결되어 있다고 정의하는 4-방향 연결성(4-way connectivity)이다.
<br>
<br>
두 번째는 상하좌우로 연결된 픽셀뿐만 아니라 대각선 방향으로 인접한 픽셀도 연결되어 있다고 정의하는 8-방향 연결성(8-way connectivity)이다.
<br>

![image](https://user-images.githubusercontent.com/87363461/203915779-ab091029-371d-4974-80e6-6601956fb55c.png)

<br>

위 그림에서 왼쪽을 4 방향 연결성, 오른쪽을 8 방향 연결성으로 연결된 방식을 그림으로 나타낸다.
<br>
배경은 검은색 픽셀이며, 흰색 픽셀은 각 방향 연결성에 맞는 연결된 픽셀이다.

## 레이블 맵(Lable Map)이란
레이블 맵이란 이진 영상에 레이블링을 수행하면 각각의 객체 영역에 고유의 번호가 매겨진 2차원 정수 행렬이 만들어짐을 뜻한다.
<br>
즉, 레이블링에 의해 만들어지는 2차원 정수 행렬을 레이블 맵이라고 한다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203915856-262c09a1-c021-40f0-a888-e7f8fd120e50.png)

<br>

위 그림은 작은 크기의 입력 영상에 대해 레이블링을 수행하였을 때 만들어지는 레이블 맵이다.
<br>
왼쪽 그림은 레이블링 입력으로 사용한 8 x 8 크기의 이진 영상이다.
<br>
오른쪽 그림은 왼쪽 이진화 영상에 레이블링을 수행하면 정수로 구성된 레이블 맵 행렬이 생성된 것이다.
<br>
<br>
입력 영상에서 배경 픽셀은 레이블 맵 행렬에서 0으로 설정되고, 입력 영상의 각 객체 픽셀 영역에는 고유의 번호가 매겨진다.

## 레이블링 함수
OpenCV에서는 레이블링 관련 함수인 connectedComponents()를 제공하고, 3.0.0 버전부터 제공한다.

```
int connectedComponents(InputArray image, OutputArray labels, int connectivity = 8, int ltype = CV_32S);

image : 입력 영상으로 CV_8UC1 또는 CV_8SC1을 지정한다.
labels : 출력 레이블 맵 행렬
connectivity : 연결성으로 8 또는 4를 지정한다.
ltype : 출력 행렬 타입으로 CV_32S 또는 CV_16S를 지정한다.
반환값 : 레이블 개수
```

connectedComponents() 함수는 입력 영상 image에 대해 레이블링을 수행하여 구한 레이블 맵 labels를 반환한다.
<br>
<br>
함수의 입력 image에는 보통 threshold() 또는 adaptiveThreshold() 함수를 통해 얻은 이진 영상을 지정한다.
<br>
회색이 포함된 그레이스케일 영상을 입력으로 사용할 경우, 픽셀 값이 0이 아니면 객체 픽셀로 간주한다.
<br>
<br>
labels 인자에는 Mat 자료형의 변수 이름을 전달한다.
<br>
<br>
반환값으로는 반환값이 N이면 0부터 N - 1까지의 레이블 번호가 존재하며, 이 중 0번 레이블은 배경을 나타낸다.
<br>
실제 객체 개수는 N - 1이다.
<br>
<br>
뒤쪽 2개의 인자는 기본 값을 가지고 있어, 앞의 인자만 값을 주고 사용할 수 있다.
<br>
<br>
connectecComponents() 함수는 레이블링을 수행하여 레이블 맵을 구하는 함수였다면, 레이블 맵과 각 객체 영역의 통계 정보를 한꺼번에 반환하는 함수도 OpenCV 에서 제공한다.

```
int connectedComponentsWithStats(InputArray image, OutputArray labels, OutputArray stats, OutputArray centroids,
                                 int connectivity = 8, int ltype = CV_32S);

image : 입력 영상으로 CV_8UC1 또는 CV_8SC1을 지정한다.
labels : 출력 레이블 맵 행렬
stats : 각각의 레이블 영역에 대한 통계 정보를 담은 행렬로 CV_32S 타입
centroids : 각각의 레이블 영역의 무게 중심 좌표를 담은 행렬로 CV_64F 타입
connectivity : 연결성으로 8 또는 4를 지정한다.
ltype : 출력 행렬 타입으로 CV_32S 또는 CV_16S를 지정한다.
반환값 : 레이블 개수
```
connectedComponentsWithStats() 함수의 인자 구성은 stats와 centroids 말고는 connectedComponents() 함수와 동일하다.
<br>
보통 stats와 centroids 인자에는 Mat 자료형 변수를 지정한다.

### [레이블링 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Labeling/Labeling.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203916181-46629614-17d3-4847-a2b8-45edf81b0163.png)

<br>

왼쪽 그림은 src 입력 영상이고 오른쪽 영상은 흰색 점을 찾아 초록색 사각형으로 표시한 결과이다.
