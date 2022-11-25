## 템플릿 매칭(Template Matching)이란

템플릿 매칭이란 입력 영상에서 작은 크기의 부분 영상 위치를 찾아내고 싶은 경우에 사용하는 기법을 말한다.
<br>
여기서 템플릿(template)이란 찾고자 하는 대상이 되는 작은 크기의 영상을 의미한다.
<br>
<br>
템플릿 매칭은 작은 크기의 템플릿 영상을 입력 영상 전체 영역에 대해 이동하면서 가장 비슷한 위치를 수치적으로 찾아내는 방식이다.

## 템플릿 매칭 동작 방식
템플릿 영상을 입력 영상 전체 영역에 대해 이동하면서 템플릿 영상과 입력 영상 부분 영상과의 유사도(similarity) 또는 비유사도(disimilarity)를 계산한다.
<br>
유사도를 계산할 경우 템플릿 영상과 비슷한 부분 영상 위치에서 값이 크게 나타나고, 비유사도를 계산할 경우에는 템플릿 영상과 비슷한 부분에서 값이 작게 나타난다.
<br>

![image](https://user-images.githubusercontent.com/87363461/203923200-0983d3f6-5123-49ad-8b3c-1911b5d667fe.png)

<br>

레나 영상에서 레나 얼굴 영역 부분 영상을 템플릿으로 사용하여 템플릿 매칭을 수행하는 과정이다.
<br>
두 번째 그림은 입력 영상의 모든 위치에서 템플릿 영상과의 유사도를 계산하고 그 결과를 그레이스케일 형태로 나타낸 것이다.
<br>
이 위치를 빨간색으로 표시한 결과가 세 번째 그림이다.

## 템플릿 매칭 함수

OpenCV에서는 템플릿 매칭을 위해 matchTemplate() 함수를 제공한다.

```
void matchTemplate(InputArray image, InputArray templ, OutputArray result, int method, InputArray mask = noArray());

image : 입력 영상으로 8비트 또는 32비트 실수형 지정
templ : 템플릿 영상으로 입력 영상인 image보다 같거나 작아야 하며 image와 타입이 같아야 한다.
result : 출력 비교 결과를 저장할 행렬로 CV_32FC1 타입
method : 템플릿 매칭 비교 방법으로 TemplateMatchModes 열거형 상수 중 하나 지정
mask : 찾을 템플릿 마스크 영상으로 mask는 templ과 같은 크기, 같은 타입이어야 한다.
```

matchTemplate() 함수는 입력 영상 image 에서 템플릿 영상 templ을 이용하여 템플릿 매칭을 수행하고, 그 결과로 생성되는 유사도 맵 또는 비유사도 맵은 result인자로 반환한다.
<br>
템플릿 영상과 입력 영상 간 비교 방식은 method 인자로 설정한다.
<br>
method 인자에 TemplateMatchModes 열거형 상수 중 하나를 지정할 수 있다.

|주요 TemplateMatchModes 열거형 상수|설명|
|:---:|:---:|
|TM_SQDIFF|제곱차 매칭 방법|
|TM_SQDIFF_NORMED|정규화된 제곱차 매칭 방법|
|TM_CCORR|상관관계 매칭 방법|
|TM_CCORR_NORMED|정규화된 상관간계 매칭 방법|
|TM_CCOEFF|상관계수 매칭 방법|
|TM_CCOEFF_NORMED|정규화된 상관계수 매칭 방법|

TM_SQDIFF는 제곱차 매칭 방법을 의미하며, 이 경우는 두 영상이 완벽하게 일치하면 0이되고, 서로 유사하지 않으면 0보다 큰 양수를 갖는다.
<br>
TM_CCORR은 상관관계 매칭 방법을 의미하며, 이 경우는 두 영상이 유사하면 큰 양수가 나오고 유사하지 않으면 작은 값이 나온다.
<br>
<br>
TM_CCOEFF는 상관계수 매칭 방법을 의미하며, 이는 비교할 두 영상을 미리 평균 밝기로 보정한 후 상관관계 매칭을 수행하는 방식이다.
<br>
이 방식은 두 비교 영상이 유사하면 큰 양수가 나오고, 유사하지 않으면 0에 가까운 양수 또는 음수가 나온다.
<br>
<br>
matchTemplate() 함수의 마지막 인자 mask는 TM_SQDIFF와 TM_CCORR_NORMED 방법에서만 지원된다.

## [템플릿 매칭 예제 코드]
