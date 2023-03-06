#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
1. 문제읽기
	-
*/

/*
2. 아이디어
	-
*/

struct Node {
	int y;
	int x;
	int power;
};

// 필요 인자들
int cnt;
int ans;
int N;
int Map[15][12];
int CMap[15][12];
int W, H;
int Path[4];
int total;

int diry[] = { -1, 0, 1, 0 };
int dirx[] = { 0, -1, 0, 1 };

// 테스트 케이스마다 초기화
void reset() {
	total = 0;
	ans = 0;
	memset(Map, 0, sizeof(Map));
}

// 값 입력받기
void input() {
	cin >> N >> W >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> Map[i][j];
			if (Map[i][j] != 0)
				total++;
		}
	}
}

void bfs(int col) {

	int y = -1;
	for (int i = 0; i < H; i++) {

		if (CMap[i][col] != 0) {
			y = i;
			break;
		}
	}

	if (y == -1)
		return;

	if (CMap[y][col] == 1) {
		CMap[y][col] = 0;
		cnt++;
		return;
	}

	queue<Node> Bomb;
	Bomb.push({ y, col, CMap[y][col] });
	int visited[15][12] = { 0 };

	while (!Bomb.empty()) {

		Node now = Bomb.front();
		Bomb.pop();

		CMap[now.y][now.x] = 0;
		cnt++;

		for (int i = 0; i < 4; i++) {

			for (int j = 1; j < now.power; j++) {

				int ny = now.y + diry[i] * j;
				int nx = now.x + dirx[i] * j;

				if (ny < 0 || nx < 0 || ny >= H || nx >= W)
					break;

				if (CMap[ny][nx] == 0)
					continue;

				if (visited[ny][nx] == 1)
					continue;

				if (CMap[ny][nx] == 1) {
					CMap[ny][nx] = 0;
					visited[ny][nx] = 1;
					cnt++;
					continue;
				}

				visited[ny][nx] = 1;
				Bomb.push({ ny, nx, CMap[ny][nx] });
			}

		}

	}

}

void gravity() {
	queue<int> q;
	for (int j = 0; j < W; j++) {

		for (int i = H - 1; i >= 0; i--) {
			if (CMap[i][j] != 0) {
				q.push(CMap[i][j]);
				CMap[i][j] = 0;
			}
		}
		int i = H - 1;
		while (!q.empty()) {
			CMap[i][j] = q.front();
			q.pop();
			i--;
		}
	}
}


void dfs(int lv) {

	if (lv == N) {

		memcpy(CMap, Map, sizeof(Map));
		cnt = 0;

		for (int i = 0; i < N; i++) {

			// 터뜨리고
			bfs(Path[i]);

			// 중력처리
			gravity();

		}

		if (cnt > ans)
			ans = cnt;

		return;
	}

	for (int i = 0; i < W; i++) {
		Path[lv] = i;
		dfs(lv + 1);
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
		dfs(0);

		// output
		cout << "#" << tc << " " << total - ans << endl;
	}

	return 0;
}