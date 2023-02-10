#include <iostream>

using namespace std;

/*
1. 문제읽기
	- 경우의 수
	- dfs로 완전탐색
	- 보호필름이랑 비슷?
*/

// 필요 인자들
int N; // 집의 크기
int map[16][16]; // 집의 상태
int path[11]; // 연산자 뭐뽑았는지 기록
int ans = 0;

// 파이프 끝 부분의 y좌표 x좌표 기록
// now는 현재 파이프의 상태 (0: 가로, 1: 세로, 2: 대각선)
void dfs(int y, int x, int now) {

	// 3. 파이프가 새로운 벽지 긁었나 판별
	if (now == 0) {
		if (map[y][x] == 1 || map[y][x - 1] == 1)
			return;
	}
	if (now == 1) {
		if (map[y][x] == 1 || map[y-1][x] == 1)
			return;
	}
	if (now == 2) {
		if (map[y][x] == 1 || map[y][x - 1] == 1 || map[y - 1][x] == 1 || map[y - 1][x - 1] == 1)
			return;
	}

	// 2. 기저 조건 -> 파이프가 목표에 도달하면 return
	if (y == N - 1 && x == N - 1) {
		ans++;

		return;
	}

	// 1. 다음 재귀로 어떻게
	// 가로냐 세로냐 대각선이냐에 따라 다르게
	// 벽을 넘어가는 경우 판별
	if (now == 0) {
		if (x + 1 < N) {
			dfs(y, x + 1, 0);
			if (y + 1 < N) {
				dfs(y + 1, x + 1, 2);
			}
		}
	}
	if (now == 1) {
		if (y + 1 < N) {
			dfs(y + 1, x, 1);
			if (x + 1 < N) {
				dfs(y + 1, x + 1, 2);
			}
		}
	}
	if (now == 2) {
		if (x + 1 < N) {
			dfs(y, x + 1, 0);
			if (y + 1 < N) {
				dfs(y + 1, x + 1, 2);
			}
		}
		if (y + 1 < N)
			dfs(y + 1, x, 1);
	}
}


int main() {

	// 필요하다면 초기화

	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	// solve -> dfs로 완전 탐색
	dfs(0, 1, 0);

	// output
	cout << ans;

	return 0;
}