# 영상의 논리 연산

OpenCV에서 영상의 논리 연산(logical operation)이란 픽셀 값을 2진수로 표현하여 각 비트 단위 논리 연산을 수행하는 것을 의미한다.
<br>
OpenCV에서는 논리합(OR), 논리곱(AND), 부정(NOT), 배타적 논리합(XOR) 연산을 지원한다.

<ul>
  <li>논리합(OR) : 2개의 입력 비트 중 1개라도 1이면 결과가 1이 되는 연산</li>
  <li>논리곱(AND) : 2개의 입력 비트 중 모두 1인 경우만 결과가 1이 되는 연산</li>
  <li>부정(NOT) : 입력 비트가 0이면 결과가 1, 1이면 결과가 0이 되는 연산</li>
  <li>배타적 논리합(XOR) : 2개의 입력 비트 중 1개만 1인 경우 결과가 1이 되는 연산</li>
</ul>

![image](https://user-images.githubusercontent.com/87363461/203889009-c217ae8c-4d16-4588-bd1e-d2e5cbcf77ab.png)
<br>
<br>
영상의 논리 연산은 각 픽셀 값에 대하여 비트 단위로 이루어진다.
<br>
그레이스케일 영상의 경우 1픽셀을 구성하는 8개의 비트에 모두 논리 연산이 이루어 진다.
<br>
<br>
예를 들어, 특정 좌표에 있는 픽셀의 그레이스케일 값이 100과 200이라고 했을 때, 각 비트 모두에 연산을 수행한다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203889043-749dcb18-2428-4ea8-8131-dcb33a328a03.png)
<br>
<br>
OpenCV에서는 영상의 비트 단위 논리 연산을 수행하는 함수를 제공한다.​

### bitwise_or()
```
void bitwise_or(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray());

src1 : 1번째 입력 행렬 또는 스칼라
src2 : 2번째 입력 행렬 또는 스칼라
dst : 출력 행렬
mask : 마스크 영상
```
### bitwise_and()
<pre>
void bitwise_and(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray());

src1 : 1번째 입력 행렬 또는 스칼라
src2 : 2번째 입력 행렬 또는 스칼라
dst : 출력 행렬
mask : 마스크 영상
</pre>

### bitwise_not()
```
void bitwise_not(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray());

src1 : 1번째 입력 행렬 또는 스칼라
dst : 출력 행렬
mask : 마스크 영상
```

### bitwise_xor()
```
void bitwise_xor(InputArray src1, InputArray src2, OutputArray dst, InputArray mask = noArray());

src1 : 1번째 입력 행렬 또는 스칼라
src2 : 2번째 입력 행렬 또는 스칼라
dst : 출력 행렬
mask : 마스크 영상
```

각각 OR, AND, NOT, XOR 순으로 OpenCV에서 제공하는 함수이다.

### [예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Logical/Logical.cpp)


### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203889306-79f4e7f7-3e43-4132-bc05-9264e49a89cb.png)
<br>
<br>

Mat 객체 src1, src2에 각각 다른 영상을 저장하고 두 영상간의 논리 연산을 수행한다.
<br>
<br>
위 2개의 영상을 각각 src1, src2로 저장한 영상이다.
<br>
각 영상의 논리 연산 결과는 아래 이미지와 같다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203889371-d5111efb-967b-4a76-a950-ff241087668d.png)
