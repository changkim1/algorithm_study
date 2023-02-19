#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

/*
1. 문제읽기
	- 각타입 7개의 하드코딩이 먼저 필요할거고
	- 주어진 정보로 인접 리스트를 만들고
	- bfs로 시작노드부터 갈 수 있는 노드 넣으면서 보면될듯
*/

struct Node {
	int y;
	int x;
};

// 필요 인자들
int N = 0, M = 0; // 세로 크기, 가로 크기
int sy, sx; // 시작 맨홀 위치
int L; // 탈출 후 소요된 시간
int ans;
int map[50][50];
vector<Node> al[50][50];

// 파이프 타입 하드코딩
// 상 하 좌 우
int diry[] = { -1, 1, 0, 0 };
int dirx[] = { 0, 0, -1, 1 };

int type[8][4] = {
	// 상 하 좌 우 어디로 갈 수 있는지
	{0, 0, 0, 0,},
	{1, 1, 1, 1,},
	{1, 1, 0, 0,},
	{0, 0, 1, 1,},
	{1, 0, 0, 1,},
	{0, 1, 0, 1,},
	{0, 1, 1, 0,},
	{1, 0, 1, 0,},
};


void reset() {
	ans = 0;
	memset(map, 0, sizeof(map));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			al[i][j].clear();
		}
	}
}

void input() {
	cin >> N >> M >> sy >> sx >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}

void makeAl(int y, int x) {
	int ntype = map[y][x];
	if (ntype == 0)
		return;
	// 상하좌우 체크하면서 갈 수 있는지 확인
	for (int i = 0; i < 4; i++) {

		if (type[ntype][i] == 0)
			continue;

		int ny = y + diry[i];
		int nx = x + dirx[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= M)
			continue;

		// 걔가 연결되어 있는지 체크
		if (i == 0) {
			if (type[map[ny][nx]][1] == 0)
				continue;
		}
		else if (i == 1) {
			if (type[map[ny][nx]][0] == 0)
				continue;
		}
		else if (i == 2){
			if (type[map[ny][nx]][3] == 0)
				continue;
		}
		else if (i == 3){
			if (type[map[ny][nx]][2] == 0)
				continue;
		}

		// 모두 통과하면 가능한 곳, 저장
		al[y][x].push_back({ ny,nx });
	}
}

void bfs(int sy, int sx) {

	queue<Node>q;
	q.push({ sy, sx });

	int visited[50][50] = { 0, };
	visited[sy][sx] = 1;
	ans++;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < al[now.y][now.x].size(); i++) {
			Node next = al[now.y][now.x][i];

			if (visited[next.y][next.x] != 0)
				continue;

			int time = visited[now.y][now.x] + 1;
			if (time > L)
				continue;

			ans++;
			visited[next.y][next.x] = time;
			q.push(next);
		}
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

		// solve -> 1.al 만들고, 2.bfs 돌리기
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				makeAl(i, j);
			}
		}
		bfs(sy, sx);

		// output
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}