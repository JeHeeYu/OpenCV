## 이벤트 처리 인터페이스

OpenCV는 영상 출력 창에서 발생하는 키보드 입력, 마우스 이벤트 등 사용자에게 전달하는 인터페이스를 제공하며.
<br>
이를 이용하면 프로그램 동작 시 사용자 입력을 실시간으로 처리하는 영상 처리 응용 프로그램을 만들 수 있다.

## 키보드 이벤트 처리 함수

### waitKey()
<pre>
int waitKey(int delay = 0);

delay : 키 입력을 기다릴 시간(ms 단위). delay <= 0 이면 무한 대기
반환값 : 눌러진 키 값. 지정한 시간 동안 키가 눌리지 않으면 -1 반환
</pre>

waitKey() 함수는 delay에 해당하는 밀리초 시간 동안 키 입력을 기다리다가, 키 입력이 있으면 아스키 코드(ASCII code) 값을 반환한다.
<br>
지정한 시간 동안 키 입력이 없으면 -1을 반환하며, 함수의 인자를 지정하지 않거나 0 또는 음수로 설정하면 무한히 대기한다.

<pre>
Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);

namedWindow("img");
imshow("img", img);

while(1) {
   if(waitKey() == 27)
      break;
}
</pre>

특정 키(Esc)를 눌렀을 때 창을 닫는 코드이다. (Esc 키는 아스키 코드로 27로 정의되어 있다.)
<br>
while(1) 문을 이용하여 무한 반복을 설정했고, if 조건문을 사용해 조건이 참인 경우에만 while 반복문을 빠져나올 수 있다.

<pre>
Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);

namedWindow("img");
imshow("img", img);

while(1) {

   int key_input = waitKey();

   if(key_input == 'a' || key_input == 'b') {
      img = ~img;
      imshow("img", img);
   }
   else if(key_input == 27 || key_input == 'c' || key_input == 'd') {
      break;
   }
}
</pre>

위 코드는, 여러 개의 특정 키를 눌렀을 때 창을 닫는 코드이다.
<br>
Esc, c, d 버튼을 누르면 창이 닫히고 종료된다.
<br>
a나 b를 입력할 때마다 영상을 반전시켜 보여준다.
<br>
<br>
이외의 키보드를 눌렀을 때 아무런 동작을 수행하지 않으며, 새로운 키 입력을 기다리게 된다.

## 마우스 이벤트 처리 함수

OpenCV에 의해 만들어진 창에서 마우스 클릭에 반응하거나, 마우스를 드래그하여 영상에 그림을 그리는 등의 동작을 수행할 수 있다.
<br>
응용 프로그램에서 마우스 이벤트를 처리하려면 먼저 마우스 콜백 함수를 등록하고, 이후 마우스 콜백 함수에 마우스 이벤트를 처리하는 코드를 추가해야 한다.

### setMouseCallback()
<pre>
void setMouseCallback(const String& winname, MouseCallback onMouse, void* userdata = 0_);

winname : 마우스 이벤트 처리를 할 창 이름
onMouse : 마우스 이벤트 처리를 위한 콜백 함수 이름
userdata : 콜백 함수에 전달할 사용자 데이터의 포인터
</pre>

setMouseCallback() 함수 인자는 winname 창에서 마우스 이벤트가 발생하면 onMouse로 등록된 콜백 함수가 자동으로 호출되도록 설정한다.
<br>
사용자가 마우스 콜백 함수에 전달하고 싶은 데이터를 void* 형식으로 전달하며, 콜백 함수에 전달할 사용자 데이터가 없다면 userdata 인자는 지정하지 않아도 된다.

<pre>
typedef void (*MouseCallback)(int event, int x, int y, int flags, void* userdata);

event : MouseEventTypes로 정의된 열거형 상수 중 하나를 지정할 수 있다.
int x : 마우스 이벤트가 발생할 위치의 x 좌표
int y : 마우스 이벤트가 발생할 위치의 y 좌표
flags : 마우스 이벤트가 발생할 때 마우스 또는 키보드의 상태 정보를 담는다. MouseEventFlags 열거형 상수의 논리합 조합이 전달된다.
userdata : setMouseCallback() 함수에서 설정한 사용자 데이터의 포인터가 전달된다. (미 설정 시 0(NULL)이 전달됨)
</pre>

마우스 콜백 함수는 마우스 이벤트가 발생할 때 자동으로 호출되는 함수이며, 위와 같은 형식으로 정의되어 있다.
<br>
즉, 마우스 콜백 함수는 4개의 정수형과 1개의 void* 타입을 인자로 가지며, void를 반환형으로 사용해야 한다.
<br>
<br>
event 인자에는 MouseEventTypes 열거형 상수를 지정할 수 있다.

|MouseEventTypes 열거형 상수|값||설명
|:---:|:---:||:---:
|EVENT_MOUSEMOVE|0|마우스가 창 위에서 움직이는 경우|
|EVENT_LBUTTONDOWN|1|마우스 왼쪽 버튼을 누를 경우|
|EVENT_RBUTTONDOWN|2|마우스 오른쪽 버튼을 누를 경우|
|EVENT_MBUTTONDOWN|3|마우스 가운데 버튼을 누를 경우|
|EVENT_LBUTTONUP|4|마우스 왼쪽 버튼을 떼는 경우|
|EVENT_RBUTTONUP|5|마우스 오른쪽 버튼을 떼는 경우|
|EVENT_MBUTTONUP|6|마우스 가운데 버튼을 떼는 경우|
|EVENT_LBUTTONDBLCLK|7|마우스 왼쪽 버튼을 더블클릭 하는 경우|
|EVENT_RBUTTONDBLCLK|8|마우스 오른쪽 버튼을 더블클릭 하는 경우|
|EVENT_MBUTTONDBLCLK|9|마우스 가운데 버튼을 더블클릭 하는 경우|
|EVENT_MOUSEWHEEL|10|마우스 휠을 앞으로 돌리는 경우|
|EVENT_MOUSEHWEEL|11|마우스 휠을 좌우로 움직이는 경우|

flags 인자에는 MouserEventFlags 열거형 상수의 논리합 조합이 전달된다.

|MouseEventTypes 열거형 상수|값||설명
|:---:|:---:||:---:
|EVENT_FLAG_LBUTTON|1|마우스 왼쪽 버튼이 눌려 있음|
|EVENT_FLAG_RBUTTON|2|마우스 오른쪽 버튼이 눌려 있음|
|EVENT_FLAG_MBUTTON|4|마우스 가운데 버튼이 눌려 있음|
|EVENT_FLAG_CTRLKEY|8|Ctrl 키가 눌려 있음|
|EVENT_FALG_SHIFTKEY|16|Shift 키가 눌려 있음|
|EVENT_FALG_ALTKEY|32|Alt 키가 눌려 있음|

### [setMouseCallback() 예제 함수 코드](https://github.com/JeHeeYu/OpenCV/blob/main/EventInterface/EventInterface.cpp)

### 실행 결과

![image](https://user-images.githubusercontent.com/87363461/203700180-c7f2e330-8b57-4ce4-8cc5-68c62c8ec8ca.png)
<br>
<br>
on_mouse() 함수와 레나 영상을 전역 변수 img로 선언하여 사용한다.
<br>
switch - case 구문을 이용하여 다양한 마우스 이벤트를 처리한다.
<br>
<br>
사용자가 마우스 왼쪽 버튼을 누르면 "EVENT_LBUTONDOWN: 문자열과 마우스 버튼이 눌린 좌표를 출력하고,
<br>
마우스를 떼면 "EVENT_LBUTTONUP: 문자열과 마우스 좌표를 출력한다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203700247-9fa59500-74b6-4a3f-a101-d2c65773af43.png)
