# 영상의 이동 변환(Translation Transformation)

영상의 이동 변환이란 영상을 가로나 세로 방향으로 일정 크기만큼 이동 시키는 연산을 의미한다.
<br>
시프트(shift) 연산 이라고도 한다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203901946-15130d80-237e-43fe-8ad6-4acedc4d89ff.png)

<br>
<br>
노란색으로 표현한 사각형이 w x h 크기의 원본 영상이다.
<br>
녹색으로 표현한 사각형은 가로 방향으로 a, 세로 방향으로 b 만큼 이동 변환 결과 영상이다.
<br>
<br>
위의 그림과 같이 영상을 x 방향으로 a 만큼, y 방향으로 b 만큼 이동하는 어파인 변환 행렬은 M과 같이 구할 수 있다.
<br>
<br>
![image](https://user-images.githubusercontent.com/87363461/203901979-eb0f0091-be73-4cec-8eb2-acc1c9e290df.png)
<br>
<br>
OpenCV에서 영상을 이동 변환하려면 2 x 3 형태의 실수 행렬을 만들고, 이를 warpAffine() 함수 인자로 전달한다.
