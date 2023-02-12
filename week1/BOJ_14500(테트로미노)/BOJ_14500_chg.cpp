#include <iostream>

using namespace std;

/*
1. 문제읽기
	- 경우의 수
	- DFS, 최대값이니깐 전부 탐색해야할듯?
	- 디저트카페 문제와 비슷
	- 5개 도형중에 4개는 모두 같고 ㅜ만 다름
*/

// 필요 인자들
int N, M; // 세로크기 가로크기
int arr[500][500];
int MAX = -21e8;
int visited[500][500];
int diry[] = { -1,0,1,0 };
int dirx[] = { 0,-1,0,1 };
// ㅜ모양 방향 정보 ㅜ ㅓ ㅗ ㅏ
int ey[4][4] = { {0, 0, 1, 0}, {0, -1, 0, 1}, {0, -1, 0, 0}, {0, -1, 0, 1} };
int ex[4][4] = { {0, -1, 0, 1}, {0, 0, -1, 0}, {0, 0, -1, 1}, {0, 0, 1, 0} };
int sum;


// 4가지 모양 체크 dfs
void dfs(int lv, int y, int x) {

	// 2. 기저 조건 -> 4개 더했으면 종료
	if (lv == 3) {

		if (sum > MAX)
			MAX = sum; // 최대값 비교
		
		return;
	}

	// 1. 다음 재귀로 어떻게
	// ny, nx로 갈 수 있는 곳이면 진입, 아니면 continue
	for (int i = 0; i < 4; i++) {

		int ny = y + diry[i];
		int nx = x + dirx[i];
		
		// 갈 수 있나 확인하고 간 적 있나 체크하고
		if (ny >= N || ny < 0 || nx >= M || nx < 0)
			continue;

		if (visited[ny][nx] == 1)
			continue;

		// 3. 기록 및 처리
		visited[ny][nx] = 1;
		sum += arr[ny][nx];
		dfs(lv + 1, ny, nx); // 다음 도형으로
		visited[ny][nx] = 0;
		sum -= arr[ny][nx];
	}

}


// ㅜ 모양 체크
void exc(int y, int x) {

	for (int i = 0; i < 4; i++) {

		sum = 0;
		for (int j = 0; j < 4; j++) {

			int ny = y + ey[i][j];
			int nx = x + ex[i][j];

			// 갈 수 있나 체크, 못가면 break
			if (ny >= N || ny < 0 || nx >= M || nx < 0)
				break;

			sum += arr[ny][nx];
		}
		if (sum > MAX)
			MAX = sum;
	}
}


int main() {

	// 필요하다면 초기화

	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	// solve -> 모든 점에서 dfs 탐색
	// ㅜ 모양은 따로
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			sum = 0; // 초기화

			visited[i][j] = 1; // 시작점 체크
			sum += arr[i][j]; // 시작점 더하기
			dfs(0, i, j); // 4가지 모양 dfs
			visited[i][j] = 0;
			sum -= arr[i][j]; 

			exc(i, j);
		}
	}

	// output
	cout << MAX;

	return 0;
}