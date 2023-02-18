#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
1. 문제읽기
	- 시뮬레이션 문제 (미생물과 비슷)
	- 11*11 2차원 벡터 Map 만들어서 (1~10 사용)
	  빈 땅은 냅두고, 충전 범위 안은 성능 넣어줄 것
	  겹치는 부분 처리하기 위해 vector
	- floodfill로 map 채우기
	- 1초마다 두 이용자를 이동하며 상황 처리
*/


struct player {
	int x;
	int y;
	int dir[101]; // 0초부터 이동방향 기록
};

struct Node {
	int y;
	int x;
};

struct land {
	int power;
	int type;
};

bool cmp(land left, land right) {
	if (left.power > right.power)
		return true;
	if (left.power < right.power)
		return false;
	return false;
}

// 가만히: 0, 상: 1, 우: 2, 하: 3, 좌: 4
int diry[] = { 0,-1,0,1,0 };
int dirx[] = { 0,0,1,0,-1 };

// 필요 인자들
int M, A; // 이동시간, BC개수
vector<land> map[11][11]; // 지도 -> 출력과 몇번 배터리 기록
player a, b; // 사용자 a, b
int sum;

void reset() {
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			map[i][j].clear();
		}
	}
	sum = 0;
}

void bfs(int x, int y, int c, int p, int idx) {
	
	queue<Node>q;
	q.push({ y, x });

	int visited[11][11] = { 0, };
	visited[y][x] = 1;
	map[y][x].push_back({p,idx});

	int xdir[] = { 0, 0, -1, 1 };
	int ydir[] = { -1, 1, 0, 0 };

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 1 || nx < 1 || ny >= 11 || nx >= 11)
				continue;

			if (visited[ny][nx] != 0)
				continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;
			// bc가 닿는 범위까지만 채워줌
			if (visited[ny][nx] > c+1)
				continue;

			map[ny][nx].push_back({p,idx});
			q.push({ ny, nx });
		}
	}
}


void input() {
	cin >> M >> A;
	// 초기값 세팅
	a = { 1,1,{0, } }, b = { 10,10,{0, } };
	for (int i = 1; i <= M; i++) {
		cin >> a.dir[i];
	}
	for (int i = 1; i <= M; i++) {
		cin >> b.dir[i];
	}
	// BC input
	for (int i = 1; i <= A; i++) {
		// x좌표, y좌표, 범위, 성능
		int x, y, c, p;
		cin >> x >> y >> c >> p;
		bfs(x, y, c, p, i);
	}
}

void move(int time) {
	a.y += diry[a.dir[time]];
	a.x += dirx[a.dir[time]];
	b.y += diry[b.dir[time]];
	b.x += dirx[b.dir[time]];
}

void solve() {
	// 플레이어의 위치에 따라 상황 나눔
	// 1. 둘다 빈땅인 경우
	if (!map[a.y][a.x].size() && !map[b.y][b.x].size())
		return;
	// 2. b만 전력가능
	else if (!map[a.y][a.x].size() && map[b.y][b.x].size()) {
		// 정렬해서 최대파워
		sort(map[b.y][b.x].begin(), map[b.y][b.x].end(), cmp);
		sum += map[b.y][b.x][0].power;
	}
	// 3. a만 전력가능
	else if (map[a.y][a.x].size() && !map[b.y][b.x].size()) {
		// 정렬해서 최대파워
		sort(map[a.y][a.x].begin(), map[a.y][a.x].end(), cmp);
		sum += map[a.y][a.x][0].power;
	}
	// 4. a,b 둘다 전력가능
	else if (map[a.y][a.x].size() && map[b.y][b.x].size()) {
		// 같은 타입인지 판단
		int flag = 0;
		for (int i = 0; i < map[a.y][a.x].size(); i++) {
			for (int j = 0; j < map[b.y][b.x].size(); j++) {
				if (map[a.y][a.x][i].type == map[b.y][b.x][j].type)
					flag++;
			}
		}
		// 4-1. 다른 타입일때, 각각 sum에 더해줌
		if (flag == 0) {
			sort(map[a.y][a.x].begin(), map[a.y][a.x].end(), cmp);
			sort(map[b.y][b.x].begin(), map[b.y][b.x].end(), cmp);
			sum += map[a.y][a.x][0].power;
			sum += map[b.y][b.x][0].power;
		}
		// 4-2. 같은 타입이 껴있을 때, 최대인 경우를 구해서 더해줌
		else {
			int max = -21e8, tmp;
			for (int i = 0; i < map[a.y][a.x].size(); i++) {
				for (int j = 0; j < map[b.y][b.x].size(); j++) {
					tmp = 0;
					if (map[a.y][a.x][i].type == map[b.y][b.x][j].type) {
						tmp = map[a.y][a.x][i].power;
					}
					else {
						tmp = map[a.y][a.x][i].power + map[b.y][b.x][j].power;
					}
					if (tmp > max)
						max = tmp;
				}
			}
			sum += max;
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

		// solve -> 1초마다 갱신하며 플레이어 이동
		for (int T = 0; T <= M; T++) {
			move(T);
			solve();
		}

		// output
		cout << "#" << tc << " " << sum << endl;
	}

	return 0;
}