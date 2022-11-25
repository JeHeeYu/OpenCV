# 영상의 산술 연산

OpenCV에서 영상은 일종의 2차원 행렬이기 때문에 산술 연산이나 논리 연산을 적용할 수 있다.
<br>
2개의 영상을 서로 더하거나 빼는 등 산술 연산을 수행함으로써 다른 영상을 생성할 수 있다.
<br>
영상들끼리 곱셈이나 나눗셈의 연산은 거의 사용하지 않는다.

## 영상의 덧셈
영상의 덧셈은 2개의 입력 영상에서 같은 위치 픽셀 값을 서로 더하여 결과 영상 픽셀 값으로 설정하는 연산이다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203887417-91172f1d-34d3-4c2a-a7b5-4c1867c9eb44.png)
<br>
<br>
dst는 덧셈 연산의 결과이고, src1과 src2가 입력 영상이다.
<br>
영상의 덧셈 연산을 통하여 그 결과 값이 그레이스케일의 최대값인 255보다 커질 수 있으므로 포화 연산을 함께 적용한다.
<br>
<br>
OpenCV에서 산술 연산을 위해 제공하는 함수가 있다.

### add()

<pre>
void add(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);

src1 : 1번째 입력 행렬 또는 스칼라
src2 : 2번째 입력 행렬 또는 스칼라
dst : 입력 행렬과 같은 크기.
mask : 8비트 1채널 마스크 영샹
dtype : 출력 행렬의 깊이
</pre>
add() 함수는 2개의 행렬 또는 영상을 입력으로 받고, 1개의 행렬 또는 영상을 출력하는 함수이다.
<br>
<br>
src1, src2 인자에는 Mat 객체, Scalar 객체, 정수, 실수 등 여러 자료형을 전달할 수 있다.
<br>
src1, src2가 모두 영상처럼 2차원 행렬을 나타내는 Mat 객체라면 일반적인 행렬의 덧셈 연산을 수행한다.
<br>
src1이 Mat 객체이고, src2가 Scalar나 정수, 실수 등의 자료형 이라면 src1 행렬의 모든 픽셀 값에 src2 값을 더한다.
<br>
결과가 dst 객체가 표현할 수 있는 자료형 범위를 벗어나면 자동으로 포화 연산을 수행한다.
<br>
<br>
mask 인자는 기본값을 가지고 있으며, 기본값을 변경할 필요가 없으면 생략할 수 있다.
<br>
mask 행렬 원소 값이 0이 아닌 위치에서만 덧셈 연산을 수행한다.
<br>
<br>
dtype 인자는 -1을 기본값으로 가지고 있으며, 변경할 필요가 없으면 생략할 수 있다.
<br>
src1과 src2 깊이가 같은 경우, dtype에 -1을 지정할 수 있는데, 이 경우 dst의 깊이는 src1, src2와 같은 깊이로 설정된다.
<br>
src1과 src2의 깊이가 서로 다른 경우 dtype을 반드시 지정해야 한다.

### [영상의 덧셈 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Arithmetic/Add.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203887719-cefc150d-dec6-4e7b-8453-51140d97cf55.png)
<br>
<br>
Mat 객체 src1과 src2에 각각 레나 영상을 저장하고, add함수로 출력된 영상을 dst에 저장한다.
<br>
입력 영상의 타입이 같으므로 dtype 인자는 따로 설정하지 않고, mask 인자를 따로 저장하지 않았으므로 입력 영상의 모든 픽셀 위치에서 덧셈 연산을 수행한다.
<br>
<br>
같은 레나 영상끼리의 덧셈 연산 수행 시, 픽셀 값이 증가하여 밝아지는 것을 볼 수 있다.
<br>
만약 덧셈 연산의 입력 영상 타입이 같다면 add() 함수 대신 + 연산자 재정의를 사용할 수도 있다.
<pre>
Mat dst = src1 + src2;
</pre>

## 영상의 뺄셈
영상의 뺄셈은 2개의 입력 영상에서 같은 위치에 있는 픽셀끼리 빼기 연산을 수행하는 것이다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203887846-3de1fc1f-335d-4026-b9f0-8eaea106c92e.png)
<br>
<br>
dst는 덧셈 연산의 결과이고, src1과 src2가 입력 영상이다.
<br>
영상의 뺄셈 연산을 통하여 그 결과 값이 그레이스케일의 최소값인 0보다 작아질 수 있으므로 포화 연산을 함께 적용한다.

### subtract()

<pre>
void add(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray(), int dtype = -1);

src1 : 1번째 입력 행렬 또는 스칼라
src2 : 2번째 입력 행렬 또는 스칼라
dst : 입력 행렬과 같은 크기.
mask : 8비트 1채널 마스크 영샹
dtype : 출력 행렬의 깊이
</pre>

subtract() 함수의 인자는 add() 함수와 동일하다.
<br>
뺄셈 연산의 두 입력 영상 타입이 같다면 + 연자와 마찬가지로 subtract() 함수 대신 - 연산자 재정의를 사용할 수 있다.
<br>
그러나 서로 타입이 다르다면 subtract() 함수를 사용해야 하고, dtype 인자를 명시해야 한다.

### [영상의 뺄셈 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Arithmetic/Subtract.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203888128-a12535bf-b3cb-468a-84a1-e248a13c20ce.png)
<br>
<br>
같은 영상끼리의 뺄셈 연산을 수행하였으므로, 각 픽셀 값이 0으로 설정된다.
<br>
<br>
덧셈 연산과 달리 뺄셈 연산은 뺄셈의 대상이 되는 영상 순서에 따라 결과가 달라진다.
<br>
만약 영상의 뺄셈 순서에 상관없이 픽셀 값 차이가 큰 영역을 두드러지게 나타내고 싶다면 차이 연산을 수행할 수 있다.
<br>
차이 연산은 뺄셈 연산 결과에 덜댓값을 취하는 연산이며, 차이 연산으로 구한 결과 영상을 차영상(difference image) 이라고 한다.
<br>
<br>
OpenCV에서 차영상을 구하기 위해 absdiff() 함수를 제공한다.


### absdiff()
<pre>
void absdiff(InputArray src1, InputArray src2, OutputArray dst);

src1 : 1번째 입력 행렬 또는 스칼라
src2 : 2번째 입력 행렬 또는 스칼라
dst : 출력 행렬로 입력 행렬과 같은 크기, 같은 수의 행렬이 생성된다.
</pre>

차이 연산을 이용하면 2개의 영상에서 변화가 있는 영역을 쉽게 찾을 수 있다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203888434-6df8804c-2a9a-4734-877b-e72b3d803856.png)
<br>
<br>
움직임이 없는 정적인 배경 영상에서 자동차가 지나가는 사진에 차이 연산을 수행하면 움직이는 자동차 영역에서만
<br>
픽셀 값 차이가 두드러지게 나타나므로 변화된 부분만 추출해낼 수 있다.
<br>
<br>
OpenCV에서 행렬의 곱셈과 나눗셈 함수도 제공한다.
<br>
영상도 일종의 행렬이므로 입력 영상을 행렬로 생각하여 곱, 나눗셈이 가능하다.
<br>
그러나 곱셈과 나눗셈을 사용하는 경우는 많지 않다.

### multiply()
<pre>
void multiply(InputArray src1, InputArray src2, OutputArray dst, scale, int dtype = -1);

src1 : 1번째 입력 행렬 또는 스칼라
src2 : 2번째 입력 행렬 또는 스칼라
dst : 입력 행렬과 같은 크기.
scale : 추가적으로 확대/축소할 비율
dtype : 출력 행렬의 깊이
</pre>

### divide()
<pre>
void divide(InputArray src1, InputArray src2, OutputArray dst, scale, int dtype = -1);

src1 : 1번째 입력 행렬 또는 스칼라
src2 : 2번째 입력 행렬 또는 스칼라
dst : 입력 행렬과 같은 크기.
scale : 추가적으로 확대/축소할 비율
dtype : 출력 행렬의 깊이
</pre>
