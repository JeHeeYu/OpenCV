## 캐니 에지(Canny Edge)

캐니 에지 검출이란 1986년 캐니(J. Canny)가 소벨 에지 검출 방법의 단점을 해결할 수 있는 방법을 제시한 검출 방법이다.
<br>
제시한 방법은 3가지로, 좋은 에지 검출기의 조건으로 제시했다.

<ol>
  <li>정확한 검출(good detection) : 에지를 검출하지 못하거나 또는 에지가 아닌데 에지로 검출하는 확률을 최소화해야 한다.</li>
  <li>정확한 위치(good localization) : 실제 에지의 중심을 찾아야 한다.</li>
  <li>단일 에지(single edge) : 하나의 에지는 하나의 점으로 표현되어야 한다.</li>
</ol>
캐니는 이러한 조건을 만족하는 새로운 형태의 에지 검출 방법을 제시했고, 이 것을 캐니 에지 검출기(canny edge detector)라고 한다.
<br>
소벨 에지 검출 방법이 그래디언트 크기만을 이용하여 에지를 찾는 방법이라면, 캐니 에지 검출 방법은 그래디언트 크기와 방향을 모두 고려하여 좀 더 정확한 에지 위치를 찾을 수 있다.

## 검출 방법
캐니 에지 검출기는 크게 4개의 연산 과정으로 설명한다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203905256-b735980e-10a5-4b59-b0f9-4b9068dad7f0.png)


<br>
<br>

<ol>
  <li>가우시안 필터링
    <br>
    <br>
    처음 과정은 가우시안 필터링이다. 가우시안 필터링을 이용하여 영상에 포함된 잡음을 제거하기 위함이다.
    <br>
    다만 가우시안 필터링에 의해 영상이 부드러워지면서 에지의 세기도 감소할 수 있기 때문에 적절한 표준 편차를 이용하여 필터링 작업을 수행한다.
    <br>
    영상에 포함된 잡음이 심하지 않으면 필터링 과정은 생략할 수 있다.
    <br>
    <br>
  </li>
  
  <li>그래디언트 계산
    <br>필터링 작업을 거친 후 그래디언트를 구해야 한다.
    <br>캐니 에지 검출기에서는 보통 3 x 3 소벨 마스크를 사용하여 그래디언트를 계산한다.
    <br>가로 방향과 세로 방향으로 각각 소벨 마스크 필터링을 수행한 후 그래디언트 크기와 방향을 모두 계산한다.
    <br>
    <br>
  </li>
  
  <li>비최대 억제(non-maximum suppression)
    <br>
    비최대 억제 과정이란 에지가 두껍게 표현되는 현상을 방지하기 위한 과정이다.
    <br>에지 검출을 위해 단순히 그래디언트 크기가 특정 임계값보다 큰 픽셀을 선택할 경우, 에지 근방의 여러 픽셀이 한꺼번에 에지로 선택될 수 있다.
    <br>이런 현상을 방지하기 위해 비최대 억제 과정을 진행한다.
    <br>
    <br>비최대 억제는 그래디언트 크기가 국지적 최대인 픽셀만을 에지 픽셀로 설정하는 기법이다.
    <br>2차원 영상에서 국지적 최대를 찾으려면 특정 픽셀을 둘러싸고 있는 모든 픽셀 값을 검사하여 국지적 최대인지를 판별해야 한다.
    <br>
    <br>그러나 캐니 에지 검출기의 비최대 억제 과정에서는 그래디언트 벡터의 방향과 같은 방향에 있는 인접 픽셀끼리만 국지적 최대 검사를 수행한다.
    <br>결과적으로 가장 변화율이 큰 위치의 픽셀만 에지로 검색된다.
    <br>
    <br>
  </li>
  
  <li>에지 트래킹
    <br>
    <br>이중 임계값을 이용하여 히스테리시스 에지 트래킹 과정이다.
    <br>1개의 임계값을 사용할 경우 이분법으로 결과가 판단되어 환경 변화에 민감해진다.
    <br>이러한 문제점을 보완하기 위해 캐니 에지 검출기에서는 2개의 임계값을 사용한다.
    <br>
    <br>히스테리시스 에지 트래킹(hystreresis edge tracking)이란 임계값이 낮은 에지 중 최종적으로 에지로 판별할 픽셀을 선택하는 과정이다.
    <br>히스테리시스 에지 트래킹의 방법은 에지 픽셀이 대체로 상호 연결되어 있다는 점을 이용하며,약한 에지 픽셀이 강한 에지 픽셀과 서로 연결되어 있다면 이 픽셀은 최종적으로 에지로 판단한다.
    <br>
    <br>OpenCV에서 캐니 에지 검출을 위한 함수를 제공한다.
    <br>이 함수는 2가지의 원형으로 되어 있다.
  </li>
</ol>

```
void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2,
           int apertureSize = 3, bool L2gradient = false);
void Canny(InputArray dx, InputArray dy, OutputArray edges, double threshold1,
           double threshold2, bool L2gradient = false);

image : 8비트 입력 영상
dx : 입력 영상의 x 방향 미분 영상 CV_16SC1 or CV_16SC3
dy : 입력 영상의 y 방향 미분 영상 CV_16SC1 or CV_16SC3
edges : 출력 에지 영상. 입력 영상과 크기가 같은 8비트 단일 채널 영상
threshold1 : 히스테리시스 에지 검출을 위한 1번째 임계값
threshold2 : 히스테리시스 에지 검출을 위한 2번째 임계값
apertureSize : 그래디언트 계산을 위한 소벨 마스크 크기
L2gradient : 그래디언트 크기 계산 시 L2 노름을 사용하려면 true, L1을 사용하려면 false
```

2개의 원형 중 첫 번째 함수는 일반 영상을 입력으로 전달하여 에지를 검출할 때 사용한다.
<br>
두 번째 함수는 이미 x 방향과 y 방향의 미분 영상을 가지고 있을 때 사용한다.
<br>
<br>
Canny() 함수를 사용할 때 두 개의 임계값을 적절하게 지정하는 것이 중요하다.
<br>
threshold1과 threshold2 두 개의 임계값은 캐니 에지 검출기의 히스테리시스 에지 트래킹 단계에서 사용된다.
<br>
<br>
보통 threshold1에는 낮은 임계값을, threshold2에는 높은 임계값을 지정한다.
<br>
보통 낮은 임계값과 높은 임계값은 1:2 또는 1:3 비율을 사용한다.

### [캐니 에지 검출 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Canny%20Edge/CannyEdge.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203905862-3d47fa65-2c71-48d3-a7fa-a467b044b0a3.png)

<br>
<br>
Canny() 함수를 이용하여 각각 dst1, dst2에 지정한다.
<br>
<br>
임계값의 비율을 1:2 와 1:3으로 설정하고 결과 영상을 출력한다.
<br>
임계값을 낮출수록 에지로 판별되는 픽셀이 더 많아져 dst1 영상에는 에지 픽셀이 더 많이 검출된다.
<br>
다만 임계값을 낮출수록 잡음에 해당하는 픽셀도 에지로 검출할 가능성이 높아진다.