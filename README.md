# SSAFY 9기 서울 21반 Algorithm_study

## 멤버

[정성남](https://github.com/jseongnam)
[김창희](https://github.com/changkim1)
[배정원](https://github.com/Baejw0111)
[최형규](https://github.com/ChoiHyeongGyu)

## 주차별 학습 문제

|주차|문제|
|:---:|:---:|
|[1주차](https://github.com/changkim1/algorithm_study/tree/main/week1)|[프로세서 연결하기](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4suNtaXFEDFAUf&&), [테트로미노](https://www.acmicpc.net/problem/14500), [연산자 끼워넣기](https://www.acmicpc.net/problem/14888), [스타트와 링크](https://www.acmicpc.net/problem/14889), [파이프 옮기기1](https://www.acmicpc.net/problem/17070)|
|[2주차](https://github.com/changkim1/algorithm_study/tree/main/week2)|[등산로 조성](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq), [수영장](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq), [탈주범 검거](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpLlKAQ4DFAUq), [벌꿀 채취](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V4A46AdIDFAWu), [미생물 격리](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl), [숫자 만들기](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeRZV6kBUDFAVH), [요리사](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeUtVakTMDFAVH), [무선 충전](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo)|
|3주차| A형 대비 민코딩 A형 기출 문제 풀이 |
|4주차|[점심 식사시간](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5-BEE6AK0DFAVl),[차량 정비소](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy&categoryId=AV6c6bgaIuoDFAXy&categoryType=CODE&&&),[특이한 자석](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeV9sKkcoDFAVH),[줄기세포배양](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRJ8EKe48DFAUo),[벽돌 깨기](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo&categoryId=AWXRQm6qfL0DFAUo&categoryType=CODE&problemTitle=5656&orderBy=FIRST_REG_DATETIME&selectCodeLang=ALL&select-1=&pageSize=10&pageIndex=1),[활주로 건설](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH)|

## 지키면 좋을 것들

### 주석

코드 작성 시 주석 꼼꼼히 달아주세요.
함수, 변수가 각각 어디에 쓰이는 변수인지 모두 주석을 달면 다른 사람이 코드 보기에도 편하고, 나중에 본인이 본인 코드 볼 때도 코드 읽기가 수월합니다.

다음과 같은 형식으로 주석을 다는 것을 권장드립니다.

```cpp
// 변수, 구조체

int a; //입력값을 받을 변수

// 함수

// 1을 반환하는 함수
int func()
{
    return 1;
}

// 설명이 필요한 부분
if(a==func)
    cout << "Equal!";
```
위와 같이 변수나 구조체의 경우에는 이름 옆에 주석을 달고, 함수나 설명이 필요한 부분에는 해당 부분 바로 위에 주석을 다는 방식을 추천합니다.

추가로, vscode에서는 코드 작성 시 위와 같이 주석을 달고 변수나 함수 이름 위에 커서를 올리면 아래와 같이 해당 요소에 대한 주석 내용을 보여주는 내장 기능이 존재합니다.
이런 기능을 잘 활용하려면 주석을 열심히 다는 게 좋겠죠.

- 주석 달기

![image](https://user-images.githubusercontent.com/87963766/219994888-0ce36b85-0a16-456f-ab21-4fa6754b0eb6.png)

- 결과

![image](https://user-images.githubusercontent.com/87963766/219995054-1580e604-6a59-4a7d-92f4-afe09ebcc755.png)


### 커밋 메세지 작성

커밋 시 나름의 일관된 형식을 지키면 다른 사람이 볼 때 어떤 것을 커밋했는 지 파악하기가 쉽습니다.
기업 같은 곳에서도 협업 시에 이런 것을 지키기 위해 **커밋 컨벤션**을 정해놓고 이에 따라 커밋 메세지를 작성하는 것을 권장합니다.

저희 스터디에서는 커밋 메세지를 다음과 같이 작성하는 것을 권장드립니다.

```
<initial> <subject>
<BLANK LINE>
<body>
```

- initial: 이름 이니셜
- subject: 커밋 제목
- body: 커밋 내용

예 1)
```
[bjw] Solve SWEA 0000

SWEA 0000 풀었음
```

예 2)
```
[bjw] Update Main README

지키면 좋을 것들에 대한 내용(주석 다는 방식, 커밋 컨벤션) 추가
```

여기서 subject 내용의 동사는 원형으로 쓰는 것을 권장드립니다.
예를 들어 파일을 업데이트를 한 경우, `Updated`를 쓰기 보다는 `Update`로 쓰는 것이 좋습니다.

커밋 내용을 쓰기가 애매하다면 굳이 작성하지 않아도 괜찮습니다.