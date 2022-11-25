## 캐스케이드 분류기(Cascade Classifier)란

캐스케이드 분류기란 얼굴 검출에 사용되는 알고리즘이다.
<br>
OpenCV에서 제공하는 얼굴 검출 기능은 2001년에 비올라(P. Viola)와 존스(M. Jones)가 발표한 부스팅(boosing) 기반의 캐스케이드 분류기 알고리즘을 기반으로 만들어졌다.
<br>
비올라-존스 얼굴 검출 알고리즘이라고도 부른다.
<br>
<br>
비올라 존스 얼굴 검출 알고리즘은 기본적으로 영상을 24 x 24 크기로 정규화한 후에 하르 필터(Haar-like filter) 집합으로부터 특징 정보를 추출하여 얼굴 여부를 판단한다.
<br>
하르필터란 흑백 사각형이 서로 붙어 있는 형태로 구성된 필터이며, 아래와 같은 예다.
<br>

![image](https://user-images.githubusercontent.com/87363461/203923978-df612431-41e1-4a45-b99e-9596532694f4.png)


<br>

하르 필터 향태에서 흰색 영역 픽셀 값은 모두 더하고, 검은색 영역 픽셀 값은 모두 빼서 하나의 특징 값을 얻을 수 있다.
<br>
<br>
사람의 정면 얼굴 형태가 전형적으로 밝은 영역(이마, 미간, 볼 등)과 어두운 영역(눈썹, 입술 등)이 정해져 있기 때문에 하르 필터로 구한 특징 값은 얼굴을 판별하는 용도로 사용할 수 있다.
<br>
24 x 24 크기에서 다양한 하르 필터를 대략 18만개 생성할 수 있고, 픽셀의 합, 차 계산이 복잡하지는 않지만 시간이 오래 걸린다는 단점이 있다.
<br>
이러한 단점을 해결하기 위해 나온 것이 에이다부스트(adaboost) 알고리즘과 적분 영상(integral image)이다.
<br>
<br>
에이다부스트 알고리즘은 수많은 하르 필터 중에서 얼굴 검출에 효과적인 필터를 선별하는 역할을 수행한다.
<br>
아래가 대표적인 예이다.

<br>

![image](https://user-images.githubusercontent.com/87363461/203924064-bd7b6a58-a672-4a5f-850c-b0740bf361d2.png)

<br>

비올라와 존스는 대부분의 영상에 얼굴이 한 두개고 나머지는 얼굴이 아니라고 판단했다.
<br>
비올라 존스 알고리즘에서 케이스케이드 구조라는 새로운 방식을 도입하여 얼굴이 아닌 영역을 빠르게 걸러 내는 방식을 사용한다.
<br>
<br>
아래는 케스케이드 구조이다.
<br>

![image](https://user-images.githubusercontent.com/87363461/203924137-3edc0d7a-452e-4d5c-a326-21731bd4cbb5.png)

<br>

케스케이드 구조 1단계에서는 얼굴 검출에 가장 유용한 하르 필터 하나를 사용한다.
<br>
얼굴이 아니라고 판단되면 이후 하르 필터 계산은 수행하지 않는다.
<br>
<br>
1단계를 통과하면 2단계에서 하르 필터 다섯 개를 사용하여 얼굴인지 아닌지를 검사하고, 얼굴이 아니라고 판단되면 이후 단계의 검사는 수행하지 않는다.
<br>
이러한 방식으로 얼굴이 아닌 영역을 빠르게 제거하며, 얼굴 검출 동작을 빠르게 할 수 있는 성능이 있다.

## CascadeClassifier 클래스

OpenCV에서는 비올라 존스 알고리즘을 구현하여 객체를 분류할 수 있는 클래스를 제공한다.
<br>
CascadeClassifier 클래스는 미리 훈련된 객체 검출 분류기 XML 파일을 불러오는 기능과 주어진 영상에서 객체를 검출하는 기능으로 이루어져 있다.

```
class CascadeClassifier
{
public:
	CascadeClassifier();                          // 클래스의 기본 생성자
	CascadeClassifier(const String& filename);    // 파일 이름으로 받는 생성자
	~CascadeClassifier();                         // 클래스의 소멸자

	bool load(const String& filename);            // load() 멤버 함수로 분류기 XML 파일을 불러옴
	bool empty() const;                           // empty() 멤버 함수는 분류기가 정상적으로 불려왔는지 검사

	void detecMultiScale(InputArray image,        // 영상에서 객체 검출
		std::vector<Rect>& objects,
		double scaleFactor = 1.1,
		int minNeighbors = 3, int flags = 0,
		Size minSize = Size(),
		Size maxSize = Size());
	...
};
```
CascadeClassifier 클래스를 이용하여 객체를 검출하려면 먼저 CascadeClassifier 객체를 생성해야 한다.
<br>
객체를 생성한 후 미리 훈련된 분류기 정보를 불러올 수 있다. 분류기 정보는 XML 파일 형식으로 저장되어 있으며, CascadeClassifier::load() 멤버 함수를 이용하여 분류기 XML 파일을 불러올 수 있다.


```
void CascadeClassifier::load(const String& filename);

filename : 불러올 분류기 XML 파일 이름
```

 

불러올 XML 파일이 프로그램 실행 폴더에 있다면 파일 이름만 인자로 전달하면 된다.
<br>
만약 다른 폴더에 있다면 상대 경로 또는 절대 경로 형태의 문자열을 filename 인자로 전달한다.
<br>
<br>
OpenCV는 미리 훈련된 얼굴 검출, 눈 검출 등을 위한 분류기 XML 파일을 제공한다.
<br>
이러한 XML 파일은 %OPENCV_DIR%\etc\haarcascades 폴더에서 찾을 수 있다.

|XML 파일 이름|검출 대상|
|:---:|:---:|
|haarcascade_frontalface_default.xml|정면 얼굴 검출|
|haarcascade_frontalface_alt.xml|정면 얼굴 검출|
|haarcascade_frontalface_atl2.xml|정면 얼굴 검출|
|haarcascade_frontalface_alt_tree.xml|정면 얼굴 검출|
|haarcascade_profileface.xml|측면 얼굴 검출|
|haarcascade_smile.mxl|웃음 검출|
|haarcascade_eye.xml|눈 검출|
|haarcascade_eye_tree_eyeglasses.xml|눈 검출|
|haarcascade_lefteye_2splits.xml|눈 검출|
|haarcascade_righteye_2splits.xml|눈 검출|
|haarcascade_frontalcatface.xml|고양이 얼굴 검출|
|haarcascade_frontalcatface_extended.xml|고양이 얼굴 검출|
|haarcascade_fullbody.xml|사람의 전신 검출|
|haarcascade_upperbody.xml|사람의 상반신 검출|
|haarcascade_lowerbody.xml|사람의 하반신 검출|
|haarcascade_russian_plate_number.xml|러시아 자동차 번호판 검출|
|haarcascade_licence_plate_rus_16stages.xml|러시아 자동차 번호판 검출|

CascadeClassfier 객체를 생성한 후 XML 파일을 불러오기 위한 코드는 다음과 같다.

```
CascadeClassifier classifier("haarcascade_frontalface_default.xml");
```

객체를 생성 후, 동시에 XML 파일을 불러올 수 있는 생성자가 있어 한 줄로 표현할 수 있다.
<br>
XML 파일이 불렀으면 정상적으로 불러졌는지 확인해야 할 때는 CascadeClassifier::empty() 멤버 함수를 이용한다.

## 객체 검출 함수

XML 파일을 불러온 후 객체 검출은 CascadeClassifier::detectMultiScale() 멤버 함수를 이용하여 객체를 검출한다.

```
void CascadeClassifier::detecMultiScale(InputArray image, vector<Rect>& objects, double scaleFactor = 1.1, 
                                         int minNeighbors = 3, int flags = 0, Size,
                                         minSize = Size(), Size maxSize = Size());

image : 입력 영상으로 CV_8U 깊이의 행렬
objects : 검출된 객체의 사각형 좌표 정보
scaleFactor : 검색 윈도우 확대 비율로 1보다 커야 한다.
minNeightbors : 검출 영역으로 선택하기 위한 최소 검출 횟수
flags : 현재 사용하지 않는다.
minSize : 검출할 객체의 최소 크기
maxSize : 검출할 객체의 최대 크기
```

이 함수는 입력 영상 image에서 다양한 크기의 객체 사각형 영역을 검출할 수 있다.
<br>
만약 입력 영상이 3채널 컬러 영상이면 함수 내부에서 그레이스케일 형식으로 반환하여 객체를 검출한다.

### [캐스케이드 얼굴 검출 예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Cascade%20Classifier/FaceDetection.cpp)

### 실행 결과
![image](https://user-images.githubusercontent.com/87363461/203925051-86419dba-f687-49fd-8163-5f395b729020.png)

<br>

성공적으로 얼굴과 눈이 검출되는 것을 볼 수 있다.
