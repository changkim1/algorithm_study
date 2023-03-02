#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
1. 문제읽기
	- 자석의 개수는 4 개이며, 각 자석은 8 개의 날을 가지고 있다.
	- 자석을 회전시키는 횟수 K 는 1 이상 20 이하의 정수이다. ( 1 ≤ K ≤ 20 )
	- 자석을 회전시키는 방향은 시계방향이 1 로, 반시계 방향이 -1 로 주어진다.
	- 날의 자성은 N 극이 0 으로, S 극이 1 로 주어진다.
	- 각 자석의 날 자성정보는 빨간색 화살표 위치의 날부터 시계방향 순서대로 주어진다.
	  예를 들어, [Fig. 1] 의 1 번 자석의 자성정보는 0 0 1 0 0 1 0 0 과 같이 주어진다.

	- 하나의 자석이 1 칸 회전될 때, 붙어 있는 자석은 
	  서로 붙어 있는 날의 자성과 다를 경우에만 인력에 의해 반대 방향으로 1 칸 회전된다.

	- 4 개 자석의 자성 정보와 자석을 1 칸씩 K 번 회전시키려고 할 때,
	  K 번 자석을 회전시킨 후 획득하는 점수의 총 합을 출력하는 프로그램을 작성하라.
*/

/*
2. 아이디어
	- 간단한 단순 구현
	  -> 자성 다를경우 같은경우만 잘 나눌 것
	- 톱니 정보를 어디다가 저장할 것인가?
	  1)배열  2)벡터  3)큐(X)  4)string
	- 그냥 if문이나 switch문으로 구현해도 될듯
	- 나는 재귀로
*/

// 필요 인자들
int K; // 자석을 회전시키는 횟수 K
int ans; // K번 자석을 회전시킨 후 획득하는 점수의 총 합
int visited[5];
string Magnet[5]; // 자석정보 저장, 1~4번 사용

// 테스트 케이스마다 초기화
void reset() {
	ans = 0;
	for (int i = 1; i <= 4; i++) {
		Magnet[i].clear();
	}
}

// 값 입력받기, 0을 N으로 1을 S로 변환
void input() {
	cin >> K;
	int n;
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> n;
			if (n == 0)
				Magnet[i].push_back('N');
			else if (n == 1)
				Magnet[i].push_back('S');
		}
	}
}

// 시작부터 왼쪽으로 오른쪽으로 각각 퍼져나가는 dfs
void dfs(int M_num, int Spin_dir) {

	// 기저조건: 왼쪽으로는 1보다 클때까지 
	if (M_num > 1 && !visited[M_num - 1]) {
		// 자성이 다른경우 확인
		if (Magnet[M_num][6] != Magnet[M_num - 1][2]) {
				visited[M_num - 1] = 1;
				dfs(M_num - 1, Spin_dir * (-1));
		}
	}

	// 기저조건: 오른쪽으로는 4보다 작을때까지
	if (M_num < 4 && !visited[M_num + 1]) {
		// 자성이 다른경우 확인
		if (Magnet[M_num][2] != Magnet[M_num + 1][6]) {
			visited[M_num + 1] = 1;
			dfs(M_num + 1, Spin_dir * (-1));
		}
	}

	// 다음자석 회전 체크부터하고 끝난뒤에 자석 돌려주기
	// 1: 시계 
	if (Spin_dir == 1) {
		Magnet[M_num] = Magnet[M_num][7] + Magnet[M_num].substr(0, 7);
	}
	// -1: 반시계
	else if (Spin_dir == -1) {
		Magnet[M_num] = Magnet[M_num].substr(1, 7) + Magnet[M_num][0];
	}
}

// 점수체크 함수
void score_check() {
	int score = 1;
	for (int i = 1; i <= 4; i++) {
		if (Magnet[i][0] == 'S')
			ans += score;
		score *= 2;
	}
}

// 메인함수
int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// 테스트 케이스마다 초기화
		reset();

		// input
		input();

		// solve 
		// K번만큼 dfs 돌려주면 된다.
		for (int i = 0; i < K; i++) {
			int M_num, Spin_dir;
			cin >> M_num >> Spin_dir;
			
			memset(visited, 0, sizeof(visited));
			visited[M_num] = 1;
			dfs(M_num, Spin_dir);
		}
		// 모두 회전 후 점수 체크
		score_check();

		// output
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
