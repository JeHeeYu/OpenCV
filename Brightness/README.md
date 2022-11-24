## 영상의 밝기(Brightness) 조절

OpenCV에서 영상 밝기 조절은 덧셈 연산(밝기) 와 곱센 연산(명암)이 있다.
<br>
영상의 밝기(brightness) 조절이란 영상의 전체적인 밝기를 조절하여 더 밝게 만들거나 어둡게 만드는 작업이다.
<br>
<br>
영상의 밝기를 조절하려면 입력 영상의 모든 픽셀에 일정 값을 더하거나 빼는 연산 작업을 수행하면 된다.
모든 픽셀 값에 양수 값을 더하면 영상이 밝아지고, 양수 값을 빼면 영상이 어두워진다.
<br>
<br>
영상의 밝기 조절을 수식으로 표현할 수 있다.
<pre>
dst(x, y) = src(x, y) + n

dst : 출력 영상
src : 입력 영상
n : 조절할 밝기 값
</pre>

n이 양수이면 dst(출력 영상)의 전체적인 밝기가 증가하고, n이 음수이면 밝기가 감소하여 어두워진다.
<br>
영상의 밝기 조절을 하기 위해 영상의 픽셀 값이 픽셀 값으로 나타낼 수 있는 정해진 값으로 설정되어야 한다.
<br>
<br>
예를 들어, 그레이스케일의 최댓값은 0 ~ 255이다.
입력 영상의 특정 픽셀 값이 210이라고 가정했을 때, 밝기를 50 증가시키면 255보다 큰 260이 되고,
50인 픽셀에 60을 증가시키면 0보다 낮은 -10이 된다.
<br>
<br>
이처럼 행렬의 원소 값을 설정할 때, 원소 자료형이 가질 수 있는 값의 범위를 벗어나는 경우 해당 자료형의
최솟값 또는 최댓값으로 원소 값을 설정하는 연산을 OpenCV에서는 포화(saturate) 연산이라고 한다.
<pre>
saturate(x) = 0       x < 0 
              255     x > 255
              x       x
</pre>
 
x 값에는 0 ~ 255의 값이 들어올 수 있다.
<br>
x가 0보다 낮은 음수의 값이 설정되면 그레이스케일 범위의 최솟값인 0으로 설정된다.
<br>
x가 255보다 높은 양수의 값이 설정되면 그레이스케일 범위의 최댓값인 255로 설정된다.
<pre>
dst(x, y) = saturate(src(x, y) + n)
</pre>
포화 연산을 적용하면 위와 같은 식으로 나타낼 수 있다.
<pre>
unsigned char a = 256;
std::cout << "a = " << a << endl;

a : 0
</pre>
a에 256을 할당했지만, 256이 아닌 0이 출력됐다.
<br>
C/C++의 unsigned char 자료형은 1바이트 메모리 공간을 사용하고 0부터 255까지의 정수 값을 저장한다.
<br>
그러므로 변수 a에 256을 대입하려고 하면 자동으로 0으로 변환되어 저장된다.
<br>
<br>
정수 256을 16진수로 표현하면 0x00000100 인데, 이 값을 unsigned char 자료형에 대입하려고 하면
<br>
하위 1바이트만 대입되기 때문에 변수 a에는 0x00이 저장된다.

## 밝기 조절 방법
이미지를 Mat 객체에 불러와 저장하고, 덧셈 또는 뺄셈 연산을 수행한다.
<pre>
void brightness()
{
   Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
   
   Mat dst = src + 100;

   imshow("src", src);
   imshow("dst", dst);
   waitKey();

   destoryAllWindows();
}
</pre>
lenna.bmp 영상을 그레이스케일 형태로 불러와 Mat 객체인 src에 저장한다.
<br>
src 에 + 100이라는 연산을 수행한 후, Mat 객체인 dst에 저장한다.
<br>
<br>
OpenCV에서는 덧셈, 뺄셈 연산자에 대하여 연산자 재정의가 되어 있어 Mat 객체와 C/C++ 기본 자료형과의 덧셈 및 뺄셈 연산이 가능하다.
그래서 src + 100 이라는 코드도 가능한 코드이다.
<br>
<br>
즉, src 행렬의 모든 원소에 100을 더하고, 포화 연산까지 수행한 결과를 dst 행렬에 저장한다.
<br>
<br>
src에는 기존 그레이스케일 형식의 레나 영상이 들어있고,
<br>
dst에는 레나 영상 + 100만큼의 밝아진 영상이 들어있다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203717015-79f7ea8b-23a5-4d91-aa44-eba391e9903a.png)
<br>
<br>
src 영상을 다른 객체에 저장해서 작업하지 않고 스스로 밝기 값에 대한 작업을 할 수 있다.
<pre>
Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
src += 100;
</pre>
영상 밝기 조절을 연산 작업 수행해서 조절하는 것이 아닌 직접 구현하는 방법도 있다.
<br>
Mat 행렬의 원소 값 참조 방법을 사용하면 밝기 조절을 구현할 수 있다.
<pre>
void brightness()
{
   Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
   
   Mat dst(src.rows, src.cols, src.type());

   for(int j = 0; j < src.rows; j++) {
      for(int i = 0; int < src.cols; i++) {
         dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
      }
   }

   imshow("src", src);
   imshow("dst", dst);
   waitKey();

   destoryAllWindows();
}
</pre>
lenna.bmp 영상을 그레이스케일 형태로 불러와 src에 저장한다.
<br>
Mat 객체 dst에 src를 저장해 크기와 타입을 같게한다.
<br>
2중 for문을 이용해 영상 전체를 스캔하면서 픽셀 값에 100을 더하여 결과 영상 픽셀 값으로 설정한다.
<br>
<br>
사용자가 직접 영상의 픽셀 값을 설정하려면 반드시 미리 초기화하여야 한다.
<br>
단순히 Mat dst; 형태로 결과 영상을 저장할 변수를 선언하면,
<br>
dst 객체는 비어 있는 행렬 객체로 만들어지고 이 경우 Mat::at() 함수로 dst 영상의 픽셀 값을 참조하려고 하면 에러가 발생한다.

## 영상의 명암 조절

명암비란 영상에서 밝은 영역과 어두운 영역 사이에 드러나는 밝기 차이의 강도를 의미한다.
<br>
명암 대비 또는 콘트라스트(contrast) 라고도 한다.
<br>
<br>
영상이 전반적으로 어둡거나 또는 전반적으로 밝은 픽셀로만 구성된 경우, 명암비다 낮다고 표현하고
<br>
밝은 영역과 어두운 영역이 골고루 섞여 있는 영상은 명암비가 높다고 한다.
<br>
<br>
명암비가 낮은 영상은 객체 간의 구분이 잘 되지않아 흐릿하게 느껴지고,
<br>
명암비가 높은 영상은 사물의 구분이 잘 되어 선명한 느낌을 준다.
<br>
<br>
명암 조절을 수식으로 나타낼 수 있다.
<br>
밝기 값이 덧셈이나 뺼셈 연산이라면, 명암 조절은 곱셈 연산을 사용해서 구현한다.
<pre>
dst(x, y) = saturate(s * src(x, y))

src : 입력 영상
dst : 출력 영상
s : 0보다 큰 실수
</pre>
s가 1보다 작은 경우에는 명암비가 낮아지는 효과가 있고,
<br>
s가 1보다 큰 경우에는 명암비가 높아지는 효과가 있다.
<br>
<br>
예를 들어 s = 2인 경우, 원본 영상에서 밝기가60이었던 픽셀은 120으로 변경되고, 100은 200으로 변경된다.
<br>
그 결과 두 픽셀의 밝기 차이가 원본 영상에서는 100 - 60 = 40 이지만, 결과 영상에서는 200 - 120 = 80 으로 증가한다.
<br>
<br>
입력 영상 픽셀 값에 상수 s를 곱한 결과가 255보다 커지는 경우가 발생할 수 있으므로,
<br>
명암 조절(곱셈 연산) 에서도 포화 연산도 함께 사용해야 한다.

### 명암 조절 방법
<pre>
void brightness()
{
   Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
   
   float s = 2.f
   Mat dst = s * src;

   imshow("src", src);
   imshow("dst", dst);
   waitKey();

   destoryAllWindows();
}
</pre>

Mat 객체 src에 레나 영상을 그레이스케일 형태로 불러와 저장한다.
<br>
<br>
s를 실수 형태로 값을 초기화하고, src와 곱한 연산을 dat에 저장한다.
<br>
Mat 행렬의 모든 원소에 주어진 실수 값을 곱한 행렬을 반환한다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203717410-8fd87c77-07a3-4634-a062-0cc6755f453f.png)
