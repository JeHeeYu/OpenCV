## 외곽선(Contour) 검출 방법

외곽선 객체의 외곽선이란 객체 영역 픽셀 중에서 배경 영역과 인접한 일련의 픽셀을 의미한다.
<br>
<br>
보통 검은색 배경 안에 있는 흰색 객체 영역에서 가장 최외곽에 있는 픽셀을 찾아 외곽선으로 정의한다.
<br>
만약 흰색 객체 영역 안에 검은색 배경 영역인 홀이 존재한다면, 홀을 둘러싸고 있는 객체 픽셀들도 외곽선으로 검출할 수 있다.
<br>
<br>
즉, 객체의 외곽선은 객체 바깥쪽 외곽선과 안쪽 홀 외곽선으로 구분할 수 있다.
<br>
<br>
하나의 영상에는 여러 개의 객체가 존재할 수 있으므로 영상 하나에서 추출된 전체 객체의 외곽선 정보는 vector 타입으로 표현한다.

```
vector<vector<Point>> contours;
```

## 선 검출 원리

외곽선 검출 원리는 객체의 외곽선 픽셀 좌표를 모두 추출하여 계층 정보와 함께 반환한다.
<br>
예를 들어, 아래와 같이 8 x 8 크기의 이진 영상이 있다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203916698-8d493973-e287-4290-85ef-e31ff0289934.png)

<br>

이 영상은 흰색으로 표현된 객체 영역이 세 개 있는 단순한 형태이다.
<br>
이 영상에 대해 검출을 수행하면 흰색으로 표현된 객체 영역의 외곽이 검출되어 검출 작업이 수행된다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203916760-16f3a501-e836-4b8d-8048-50f5d83b2e1b.png)


<br>

위 그림에서 녹색으로 표현한 픽셀들이 외곽선 점들로 검출되는 원리이다.
<br>
검출된 외곽선 점들의 좌표는 변수에 모두 저장된다.
<br>
따라서 위 그림들의 좌표는 아래와 같이 배열로 접근할 수 있다.

```
contours[0] : [1, 1], [1, 2], [1, 3], [2, 4], [3, 3], [3, 2], [3, 1], [2, 1]
contours[1] : [6, 1]
contours[2] : [5, 4], [4, 5], [4, 6], [5, 6], [6, 6], [6, 5], [6, 4]
```

## 외곽선 검출 함수
OpenCV에서 영상 내부 객체들의 외곽선 검출을 위한 함수 findContours()를 제공한다.
<br>
이 함수는 외곽선들의 계층 정보를 받아오는 hierarchy 인자가 있는 형태와 없는 형태 두 가지로 정의되어 있다.

```
void findContours(InputArray image, OutputArrayOfArray contours, OutputArray hierarchy, int mode),
                  int method, Point offset = Point());
void findContours(InputArray image, OutputArrayOfArray contours, int mode, int method, Point offset = Point());

image : 입력 영상으로 8비트 1채널 영상이어야 하며 0이 아닌 픽셀을 객체로 취급한다.
contours : 검출된 외곽선 정보로 vector<vector<Point>> 타입의 변수를 지정한다.
hierarchy : 외곽선 계층 정보로 vector<Vec4i> 타입의 변수를 지정한다.
mode : 외곽선 검출 모드로 RetrievalModes 열거형 상수를 지정한다.
method : 외곽선 근사화 방법으로 ContourApproximationModes 열거형 상수를 지정한다.
offset : 외곽선 점 좌표의 오프셋(이동 변위)
```

findContours() 함수의 입력인자 src에는 보통 threshold() 등 함수에 의해 만들어진 이진 영상을 사용한다.
<br>
실제 동작할 때는 입력 영상에서 픽셀 값이 0이 아니면 객체로 간주하여 외곽선을 검출한다.
<br>
만약 mode가 RETR_CCOMP이면 CV_32SC1 타입의 영상을 지정할 수 있다.
<br>
hierarchy 인자에는 검출된 외곽선의 계층 정보가 저장되는데, 보통 vector<Vec4i> 타입의 변수를 지정한다.
<br>
<br>
Vec4i 클래스는 int 자료형 네 개를 저장할 수 있는 OpenCV 벡터 클래스이다.
<br>
i 번째 외곽선에 대해 hierarchy[i][0]에는 다음 외곽선 번호, hierarchy[i][1]에는 이전 외곽선 번호,
<br>
hierarchy[i][2]에는 자식 외곽선 번호, hierarchy[i][3]에는 부모 외곽선 정보가 저장된다.
<br>
<br>
만약 계층 구조에서 해당 외곽선이 존재하지 않으면 -1이 저장된다.
<br>
<br>
mode 인자에는 외곽선 검출 방식에 대한 검출 모드를 지정한다.
<br>
이 인자에는 RetrievalModes 열거형 상수 중 하나를 지정한다.
|주요 RetrievalModes 열거형 상수|설명|
|:---:|:---:|
|RETR_EXTERNAL|객체 바깥쪽 외곽선만 검색하며 계층 구조는 만들지 않는다.|
|RETR_LIST|객체 바깥쪽과 안쪽 외곽선을 모두 검색하며 계층 구조는 만들지 않는다.|
|RETR_CCOMP|모든 외곽선을 검색하고 2단계 게층 구조를 구성한다.|
|RETR_TREE|모든 외곽선을 검색하고 전체 계층 구조를 구성한다.|
 
  <br>
  
method 인자에는 검출된 외곽선 점들의 좌표를 근사화하는 방법을 지정한다.
<br>
이 인자에는 ContourApproximationModes 열거형 상수를 지정한다.
  
|주요 ContourApproximationModes 열거형 상수|설명|
|:---:|:---:|
|CHAIN_APPROX_NONE|모든 외곽선 점들의 좌표를 저장한다.|
|CHAIN_APPROX_SIMPLE|외곽선 중에서 수평선, 수직선, 대각선 성분의 끝점만 저장한다.|
|CHAIN_APPROX_TC89_L1|Teh & Chin L1 근사화를 적용한다.|
|CHAIN_APPROX_TC89_KCOS|Teh & Chin k cos 근사화를 적용한다.|
 
<br>
  
findContours() 함수로 검출한 외곽선 정보를 이용하여 영상 위에 외곽선을 그릴 수 있다.
<br>
이때 사용하는 함수가 drawContours() 함수이다.
```
  void drawContours(InputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, 
                  int thickness = 1, int lineType = LINE_8, InputArray hierarchy = noArray(),
                  int maxLevel = INT_MAX, Point offset = Point());

image : 외곽선을 그릴 영상
contours : findContours() 함수로 구한 전체 외곽선 정보로 vector<vector<Point>> 타입의 변수 지정
contourIdx : 외곽선 번호로 음수를 지정하면 전체 외곽선을 그린다.
color : 외곽선 색상(밝기)
thickness : 외곽선 두께로 FILLED 또는 -1을 지정하면 외곽선 내부를 채움
lineType : 외곽선 타입
hierarchy : 외곽선 계층 정보
maxLevel : 그릴 외곽선의 최대 레벨로 0 지정 시 번호의 외곽선을, 1보다 같거나 크면 하위 레벨의 외곽선까지 그린다.
offset : 추가로 지정할 외곽선 점 좌표의 오프셋
```
  
drawContours() 함수는 findContours() 함수로 얻은 외곽선 정보를 이용하여 영상에 외곽선을 그린다.
<br>
전체 외곽선을 한꺼번에 그릴 수도 있고, 특정 번호의 외곽선을 선택하는 등 여러 방법으로 그릴 수 있다.
  
### [외곽선 검출 예제 코드]()
