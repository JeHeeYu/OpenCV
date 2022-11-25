# 히스토그램(Histogram)

## 히스토그램(Histogram)이란
히스토그램(histogram)이란 표로 되어 있는 도수 분포를 정보 그래프 형태로 표현한 것이다.
<br>
영상의 히스토그램(histogram)이란 영상의 픽셀 값 분포를 그래프 형태로 표현한 것을 의미한다.
<br>
그레이스케일 영상의 경우, 각 그레이스케일 값에 해당하는 픽셀이 개수를 구하고 이를 막대 그래프 형태로 표현함으로써 히스토그램을 구할 수 있다.
<br>
<br>
4 x 4 영상이 있다고 가정하고, 이 영상 의 픽셀이 0 ~ 7 사이의 밝기를 가질 수 있는 형태의 영상이 있다.
<br>
영상을 이루고 있는 각각의 밝기에 해당하는 픽셀 개수를 세어서 막대그래프 형태로 표현한 것이 히스토그램이다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203883421-987d9285-9a08-41f3-aac8-d2956407ffb4.png)

<br>
<br>
히스토그램 그래프에서 가로축을 히스토그램의 빈(bin) 이라고 한다.'
<br>
<br>
위의 히스토그램에서 빈 개수는 8개 이다. 픽셀이 0 ~ 7 사이의 값을 가질 수 있기 때문에 8개의 빈으로 구성된 히스토그램이다.
<br>
그레이스케일 영상의 경우 256개의 빈을 갖는 히스토그램이 일반적이다.
<br>
<br>
빈의 개수가 픽셀 값 범위와 다를 수 있다. 위의 픽셀은 8개, 빈이 8개로 표현된 히스토그램이다.
<br>
빈의 개수를 줄일 수도 있고 늘릴 수도 있다.
<br>
<br>
일반적으로 히스토그램의 빈 개수가 줄어들면 히스토그램이 표현하는 영상의 픽셀 값 분포가 대략적 형태로 변하고,
<br>
빈 개수가 많아지면 세밀한 픽셀 값 분포 표현이 가능하다.
<br>
<br>

![image](https://user-images.githubusercontent.com/87363461/203884651-bbf4655c-f06f-4947-a885-f9893cd44d29.png)

<br>
<br>
0번 빈 : 픽셀 값이 0, 1인 픽셀 개수
<br>
1번 빈 : 팍셀 값이 2, 3
<br>
2번 빈 : 픽셀 값이 4, 5
<br>
3번 빈 : 픽셀 값이 6, 7
<br>
<br>
위와 같이 빈의 개수가 줄어들면 대략적인 형태로 바뀐다.
<br>
OpenCV에서 영상의 히스토그램을 구하기 위해 calcHist() 함수를 제공한다.

### calcHist();
<pre>
void calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, OutputArray hist,
              int dims, const int* histSize, const float** ranges, bool uniform = true, bool accumulate = false);

images : 입력 영상의 배열 또는 입력 영상의 주소. 영상의 배열인 경우 모든 영상의 크기와 깊이는 같아야 한다.
nimages : 입력 영상 개수
channels : 히스토그램을 구할 채널을 나타내는 정수형 배열
mask : 마스크 영상. 입력 영상과 같은 크기가 같은 8비트 배열이어야 한다. 
hist : 출력 히스토그램. CV_32F 깊이를 사용하는 dims- 차원의 행렬이다.
dims : 출력 히스토그램의 차원 수
histSize : 각 차원의 히스토그램 배열 크기를 나타내는 배열 (각 차원의 히스토그램 빈 개수를 나타내는 배열)
ranges : 각 차원의 히스토그램 범위
uniform : 히스토그램 빈의 간격이 균등한지 나타내는 플래그
accumulate : 누적 플래그. 이 값이 true이면 hist 배열을 초기화하지 않고 누적하여 히스토그램을 계산한다.
</pre>

calcHist() 함수는 1장의 영상뿐 아니라 여러 장의 영상으로부터 히스토그램을 구할 수 있고, 여러 채널로부터 히스토그램을 구할 수도 있다.
<br>
또한 빈 개수도 조절할 수 있다.
<br>
mask 인자는 마스크 행렬의 원소 값이 0이 아닌 좌표에 픽셀만 히스토그램 계산에 사용되며,
<br>
mask 인자에 Mat() 또는 noArray()를 지정하면 입력 영상 전체에 대해 히스토그램을 구한다.
<br>
<br>
uniform과 accumulate 인자를 명시적으로 지정하지 않으면 자동으로 각각 true, false가 설정되며,
<br>
이 경우 hist 배열을 0으로 초기화한 후 등간격 히스토그램을 계산한다.
<br>
등간격 히스토그램이란 빈이 표현하는 밝기 값 간격이 균일하다는 의미이다.

## 히스토그램 구하기
<pre>
Mat Hist(const Mat& img)
{
	CV_Assert(img.type() == CV_8UC1);             // 전달된 img 영상이 그레이스케일인지 검사

	Mat hist;                                     /*
	int channels[] = { 0 };
	int dims = 1;                                     calHist() 함수에 전달할 인자들
	const int histSize[] = { 256 };
	float graylevel[] = { 0, 256 };
	const float* ranges[] = { graylevel };                              */

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);    // img 영상의 히스토그램을 hist 변수에 저장

	return hist;  // hist 반환
}
</pre>
hist는 CV_32FC1 타입을 갖는 256 x 1 크기의 행렬이다.
<br>
즉, hist 행렬의 행 개수는 256개, 열 개수는 1개이다.
<br>
<br>
calHist() 함수를 통해 리턴받은 hist를 이용해 행렬을 막대그래프 형태로 나타낼 수 있다.
<br>
직접 hist 행렬을 참조하여 막대그래프 영상을 생성해야 한다.
<pre>
Mat HistGraph(const Mat& hist)
{
	CV_Assert(hist.type() == CV_32FC1);          // 전달된 영상이 그레이스케일인지 검사
	CV_Assert(hist.size() == Size(1, 256));      // 전달된 hist 행렬이 256개의 빈으로 구성되어 있는지 검사

	double histMax;
	minMaxLoc(hist, 0, &histMax);                // hist 행렬 원소의 최대값을 histMax 변수에 저장

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));    // for문을 이용하여 그래프를 그림
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100), Point(i, 100 - cvRound(hist.at<float > (i, 0) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}
</pre>
## 히스토그램 스트레칭(histogram streching)
히스토그램에는 스트레칭이란 개념이 있다.
<br>
히스토그램 스트레칭이란 영상의 히스토그7램이 그레이스케일 전 구간에 걸쳐 나타나도록 변경하는 선형 변환 기법이다.
<br>
<br>
보통 명암비가 낮은 영상은 히스토그램이 특정 구간에 집중되어 나타나는데 이러한 히스토그램 그래프가
<br>
전 구간에서 나타도록 변환하는 기법을 말한다.
<br>
히스토그램 스트레칭을 수행하면, 수행한 영상은 명암비가 높아지기 때문에 대체로 보기 좋은 사진으로 바뀐다.
<br>
<br>
히스토그램 스트레칭을 표현하는 수식이다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203883921-6a60963e-7c1c-4d41-9075-266c9372cbcd.png)
<br>
<br>
dst : 출력 영상
<br>
<br>
src : 입력 영상
<br>
<br>
G(max) : 입력 영상의 픽셀 값 중 가장 큰 그레이스케일 값
<br>
<br>
G(min) : 입력 영상의 픽셀 값 중 작은 큰 그레이스케일 값
