#include <iostream>

using namespace std;

/*
1. 문제읽기
	- 경우의 수 (최대, 최소)
	- 최대니깐 완전탐색
	- 최소는 backtracking
	- BOJ 14888과 동일
*/

// 필요 인자들
int N; // 수의 개수
int Num[12]; // 수의 배열
int Sign[4]; // 연산자의 배열
int MIN = 21e8;
int MAX = -21e8;
int path[12]; // 연산자 뭐뽑았는지 기록
int tmp;

void reset() {
	MIN = 21e8;
	MAX = -21e8;
}

void input() {
	cin >> N;
	for (int i = 0; i < 4; i++) {
		cin >> Sign[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> Num[i];
	}
}

void func(int lv) {

	// 2. 기저 조건 -> 연산자 N-1개 뽑으면 종료
	if (lv == N - 1) {
		tmp = Num[0];
		// path에서 하나씩 뽑아와서 각 부호에 맞는 연산
		for (int i = 0; i < N - 1; i++) {
			if (path[i] == 0) {
				tmp += Num[i + 1];
			}
			if (path[i] == 1) {
				tmp -= Num[i + 1];
			}
			if (path[i] == 2) {
				tmp *= Num[i + 1];
			}
			if (path[i] == 3) {
				tmp /= Num[i + 1];
			}
		}

		// 최대 최소 비교
		if (tmp > MAX)
			MAX = tmp;
		if (tmp < MIN)
			MIN = tmp;

		return;
	}

	// 1. 다음 재귀로 어떻게
	// 0개인 연산자는 넘기고 나머지중에 뽑기
	for (int i = 0; i < 4; i++) {

		if (Sign[i] == 0)
			continue; // 남은 개수가 없는 연산자는 패스

		// 3. 기록 및 처리
		path[lv] = i; // 뽑은 연산자 기록
		Sign[i]--; // 뽑은 연산자 1감소
		func(lv + 1);
		path[lv] = 0; // 기록 복원
		Sign[i]++;
	}

}


int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// 테스트 케이스마다 초기화
		reset();

		// input
		input();

		// solve -> 완전탐색
		func(0);

		// output
		cout << "#" << tc << " " << MAX-MIN << endl;
	}

	return 0;
}