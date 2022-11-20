## 샤프닝(sharpening)이란
샤프닝이란 블러링과 반대되는 개념으로, 초점이 잘 맞은 사진처럼 사물의 윤곽이 뚜렷하고 선명한 느낌이 나도록
<br>
영상을 변경하는 필터링 기법이다.
<br>
<br>
이미 촬영된 사진을 초점이 잘 맞은 사진처럼 보이게끔 변경하려면 영상 에지 근방에서 픽셀 값의 명암비가 커지도록 해야한다.
<br>
<br>
샤프닝을 구현하기 위해서는 블러링된 영상을 사용해야 한다.
<br>
부드러워진 영상을 날카로운 영상으로 생성하는 것인데, 여기서 블러링이 적용된 영상을 날카롭지 않아 언샤프(unsharp)라고 하며,
<br>
언샤프한 영상을 이용하여 역으로 날카로운 영상을 생성하는 필터를 언샤프 마스크 필터라고 한다.
<br>
<br>
언샤프 마스크의 과정으로, x축은 픽셀 좌표의 이동, y축은 픽셀 값을 나타낸다.
<br>
<br>
<img src="https://user-images.githubusercontent.com/87363461/202885256-497e67d7-8f0f-46e2-b174-618b94111be8.JPG" width="400" height="250">
<br>
<br>
영상의 에지 부근에서 픽셀 값이 증가하는 그래프이다.
<br>
<br>
<img src="https://user-images.githubusercontent.com/87363461/202885265-fc544934-da20-4003-9767-67c0cc42194e.JPG" width="400" height="250">
<br>
<br>
블러링을 적용하여 부드럽게 변한 결과의 그래프이다.
<br>
<br>
<img src="https://user-images.githubusercontent.com/87363461/202885277-c165c4e3-d3d1-4a7c-819b-c7691dbbc8ff.JPG" width="400" height="250">
<br>
<br>
입력 영상에서 블러링된 영상을 뺀 결과의 그래프이다.
<br>
입력 함수 값이 증가하기 시작하는 부분에서는 음수 값을 가지고,
<br>
입력 함수 값 증가가 멈추는 부근에서는 양수 값을 가진다.
<br>
<br>
<img src="https://user-images.githubusercontent.com/87363461/202885314-3355614f-5375-42a1-8e10-25b18709ee9b.JPG" width="400" height="250">
<br>
<br>
샤프닝이 적용된 결과 영상의 그래프이다.
<br>
OpenCV는 언샤프 마스크 필터를 위한 함수를 따로 제공하지 않는다.
<br>
<br>
### [예제 코드](https://github.com/JeHeeYu/OpenCV/blob/main/Sharpening/Sharpening.cpp)
<br>
<br>

## 실행 결과
<img src="https://user-images.githubusercontent.com/87363461/202885404-ff4a34ac-6b80-4678-b302-ff87be77af4a.JPG" width="600" height="400">
<br>
1 ~ 5 sigma의 값에 의해 생성된 언샤프 마스크 필터링 결과 영상이다.
<br>
기존 영상에 비해 경계 구분이 좀 더 뚜렷하게 구분된다.
<br>
날카로운 성분에 대한 가중치 alpha 값의 변화에 따라 결과가 달라진다.
