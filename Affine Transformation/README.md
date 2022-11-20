## 어파인 변환의 개념

어파인 변환(affine transformation)이란 영상의 평행 이동, 확대 및 축소, 회전 등의 조합으로 만들 수 있는 기하학적 변환을 나타낸다.
<br>
영상을 확대 또는 축소하는 크기 변환과 임의의 각도만큼 회전하는 작업은 다양한 컴퓨터 비전 시스템에서 전처리 과정으로 널리 사용된다.
<br>
<br>
어파인 변환은 영상을 평행 시키거나 회전, 크기 변환 등을 통해 만들 수 있는 변환을 통칭한다.
<br>
영상을 한쪽 방향으로 밀어서 만든 것 같은 전단 변환도 어파인 변환에 포함된다.
<br>
<br>
영상에 어파인 변환을 적용할 경우 직선은 그대로 직선으로 나타나고,
<br>
직선 간의 길이 비율과 평행 관계가 그대로 유지된다.
<br>
직사각형 형태의 영상은 어파인 변환에 의해 평행사변형에 해당하는 모습으로 변경된다.
<br>
<br>
영상의 기하학적 변환(geometric transform)이란 영상을 구성하는 픽셀의 배치 구조를 변경함으로써 전체 영상의 모양을 바꾸는 작업이다.
<br>
픽셀 값은 그대로 유지하면서 위치를 변경하는 작업이다.
<br>
<br>
<img src="https://user-images.githubusercontent.com/87363461/202885856-917c0a1f-1a13-4761-8617-6e1342f87f9f.JPG" width="300" height="100">
<br>
<br>
입력 영상에서 (x, y) 좌표의 픽셀 결과 영상의 (x', y') 좌표로 변환하는 함수의 형태이다.
<br>
f1과 f2는 각각 x와 y를 입력받아 결과 영상에서의 픽셀 좌표를 출력하는 함수이다.
<br>
<br>
어파인 변환 작업을 수행하기 위해 어파인 행렬을 알아야 한다.
<br>
어파인 행렬은 2 x 3 행렬로 구성되어 있고, 6개의 파라미터가 존재한다.
<br>
<br>
<img src="https://user-images.githubusercontent.com/87363461/202885884-48509577-8743-4f02-9d55-c32cd10b0ee7.JPG" width="500" height="100">
<br>
<br>
1차 다항식으로 표현되어 있는 함수는 행렬을 이용하여 1개의 수식으로 표현할 수 있다.
<br>
<br>
<img src="https://user-images.githubusercontent.com/87363461/202885900-a5b35a83-660d-4eff-97e1-1917c7e42fd9.JPG" width="500" height="100">
<br>
<br>
입력 영상의 좌표를 나타내는 행렬 x, y 앞에 2 x 2 행렬 a ~ e를 곱하고 그 뒤에 2 x 1 행렬 c, f를 더하는 형태로
<br>
어파인 변환을 표현한다.
<br>
<br>
위 수식에서 6개의 파라미터로 구성된 2 x 3 행렬 a ~ f 까지를 어파인 변환 행렬(affine transformation matrix) 이라고 한다.
<br>
<br>
입력 영상과 어파인 변환 결과 영상으로부터 어파인 변환 행렬을 구하기 위해서 최소 3 점의 이동 관계를 알아야 한다.
<br>
점 1개의 이동 관계로부터 x 좌표와 y 좌표에 대한 변환 수식 2개를 얻을 수 있고, 점 3개의 이동 관계로부터 총 6개의 방정식을 구할 수 있다.
<br>
<br>
즉, 점 3개의 이동 관계를 알고 있다면 6개의 원소로 정의되는 어파인 변환 행렬을 구할 수 있다.
<br>
<br>
<img src="https://user-images.githubusercontent.com/87363461/202885919-f8876ceb-dce1-4f42-ad2b-bcc35edaf521.JPG" width="600" height="300">
<br>
<br>
어파인 변환에 의해 직사각형 영상은 평행사변형 형태로 변환될 수 있기 때문에
<br>
입력 영상의 좌측 하단 모서리 점이 이동하는 위치로 자동 결정된다.

## 어파인 변환 함수
OpenCV에서 어파인 변환 행렬을 구하는 함수와 실제 영상을 어파인 변환하는 함수를 모두 제공한다.

### getAffineTransform();
<pre>
Mat getAffineTransformat(const Point2f src[], const Point dst[]);

src : 입력 영상에서 3점의 좌표
dst : 결과 영상에서 3점의 좌표
반환값 : 2 x 3 어파인 변환 행렬
</pre>
getAffineTransform() 함수는 src에 저장된 3점읠 dst 좌표의 점으로 옮기는 어파인 행렬을 변환한다.
<br>
점의 좌표를 담고 있는 src와 dst에는 크기가 3인 Point2f 배열을 사용해도 되고, vector<Point2f> 자료형 변수를 사용해도 된다.
<br>
반환하는 Mat 객체는 CV_64FC1 타입을 사용하는 2 x 3 크기의 어파인 변환 행렬이다.
  
### warpAffine();
<pre>
void warpAffine(InputArray src, OutputArray dst, InputArray M, Size dsize, int flags = INTER_LINEAR,
                int borderMode = BORDER_CONSTANT, const Scalar& borderValue = Scalar());

src : 입력 영상
dst : 결과 영상
M : 2 x 3 어파인 변환 행렬
dsize : 결과 영상 크기
flags : 보간법 알고리즘
borderMode : 가장자리 픽셀 확장 방식
borderValue : bordermode가 BORDER_CONSTANT일 때 사용할 상수 값
</pre>
dst는 src와 같은 타입의 결과 영상이고 크기는 dsize에 의해 결정된다.
<br>
<br>
flags 인자는 OR 연산자를 이용하여 WARP_INVERSE_MAP 플래그를 함께 지정하면 역방향 변환을 수행할 수 있다.
<br>
<br>
borderMode 인자는 BorderTypes 열거형 상수중 하나를 지정하고, 만약 BORDER_TRANSPARENT를 지정하면
<br>
입력 영상의 픽셀 값이 복사되지 않는 영역은 dst 픽셀 값을 그대로 유지한다.
<br>
<br>
borderValue 인자는 기본값으로 검은색이 지정되어 있다.
<br>
<br>
warpAffine() 함수는 src 영상을 어파인 변환하여 dst 영상을 생성하는 함수이다.
<br>
이때 전달되는 어파인 변환 행렬 M은 CV_32FC1 또는 CV_64FC1 타입이어야 하고, 크기는 2 x 3 이어야 한다.
<br>
<br>
어파인 결과 영상의 크기 dsize는 어파인 변환 성격에 따라 사용자가 적절하게 지정해야 하며,
<br>
dsize 인자에 Size()를 전달하면 입력 영상과 같은 크기의 결과 영상을 생성한다.
<br>
<br>
warpAffine()함수는 7개의 인자를 가지고 있지만, 3개는 기본 값을 가지고 있어 처음 4개의 인자만 지정해서 사용할 수 있다.
  
### [예제 코드](https://github.com/JeHeeYu/OpenCV/tree/main/Affine%20Transformation)

## 실행 결과
<img src="https://user-images.githubusercontent.com/87363461/202886030-a7734e98-1bdc-4b34-a460-b233bdae94c9.JPG" width="600" height="300">
<br>
<br>
입력 영상과 출력 영상에서 좌표를 저장할 srcPts, dstPts를 배열로 선언한다.
<br>
srcPts 배열에는 입력 영상의 좌측 상단, 우측 상단, 우측 하단의 좌표를 저장하고
<br>
dstPts 배열에는 srcPts 점들이 이동할 좌표를 저장한다.
<br>
<br>
Mat 객체 M에 getAffineTransform() 함수를 이용하여 어파인 변환 행렬을 저장한다.
