## 영상의 투시 변환(Perspective Transform)
 
영상의 투시 변환이란 직사각형 형태의 영상을 임의의 블록 사각형 형태로 변경하는 변환이다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203904012-d5615f81-3629-4d13-991e-0345143be761.png)


<br>
<br>
점 4개의 이동 관계에 의해 결정되는 투시 변환의 예이다.
<br>
왼쪽 직사각형 꼭지점 4개를 표시하고, 이 점들이 이동한 위치를 꼭지점으로 사용하는 사각형의 변환 형태이다.
<br>
투시 변환은 직선의 평행 관계가 유지되지 않기 때문에 결과 영상의 형태가 임의의 사각형 형태로 나타나게 된다.
<br>
<br>
투시 변환은 보통 3 x 3 크기의 실수 행렬로 표현한다.
<br>
투시 변환은 8개의 파라미터로 표현할 수 있지만, 좌표 계산의 편의상 9개의 원소를 갖는 3 x 3 행렬을 사용한다.
<br>
<br>
OpenCV는 투시 변환 행렬을 구하는 함수와 투시 변환을 수행하는 함수를 모두 제공한다.

### getPerspectiveTransform()
```
Mat getPerspectiveTransform(const Point2f src[], const Poin1t2f dst[], int solveMethod = DECOP_LU);1
Mat getPerspectiveTransform(InputArray src, InputArray dst, int solveMethod = DECOMP_LU);

src : 입력 영상에서 4점의 좌표
dst : 결과 영상에서 4점의 좌표
solveMethod : 계산 방법 지정
반환값 : 3 x 3 크기의 투시 변환 행렬
```

getPerspectiveTransform() 함수는 투시 변환 행렬을 구하는 함수이다.
<br>
<br>
src에 저장된 4점을 dst 좌표의 점으로 옮기는 투시 변환 행렬을 반환한다.
<br>
점의 좌표를 담고 있는 src와 dst는 Point2f 자료형 4개를 가지고 있는 배열을 사용해도 되고,
<br>
vector<Point2f> 자료형을 사용해도 된다.
<br>
<br>
반환하는 Mat 객체는 CV_64FC1 타입을 사용하는 3 x 3 크기의 투시 변환 행렬이다.

### warpPerspective()
```
void warpPerspective(InputArray src, OutputArray dst, InputArray M, Size dsize, int flags = INTER_LINEAR, 
                     int borderMode = BORDER_CONSTANT, const Scalar& borderValue = Scalar());

src : 입력 영상
dst : 결과 영상으로 src와 같은 타입의 dsize의 크기를 갖는다.
M : 3 x 3 투시 변환 행렬
dsize : 결과 영상의 크기
flags : 보간법 알고리즘
borderMode : 가장자리 픽셀 확장 방식
borderValue : boderMode가 BORDER_CONSTANT일 때 사용할 상수 값
```
warpPerspective() 함수는 3 x 3 투시 변환 행렬을 가지고 있을 때, 영상의 투시 변환한 결과 영상을 생성하는 함수이다.
<br>
<br>
투시 변환 행렬 M을 이용하여 src 영상으로부터 dst 영상을 생성한다.
<br>
<br>
이때 전달되는 투시 변환 행렬은 CV_32FC1 또는 CV_64FC1 타입이어야 하며 크기는 3 x 3 크기여야 한다.
<br>
투시 변환 결과 영상의 크기 dsize는 사용자가 지정해야 하며, Size()를 지정하면 입력 영상과 같은 크기의 영상을 생성한다.
<br>
src, dst, M, dsize 4개의 인자만 지정하여 사용할 수 있고 나머지 인자는 기본 값을 가지고 있다.
  
### [투시 변환 예제 코드]
