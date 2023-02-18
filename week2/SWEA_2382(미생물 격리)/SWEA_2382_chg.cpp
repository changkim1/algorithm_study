#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


/*
1. 문제읽기
	- 그냥 단순 구현하면 될거같음.
	1) 미생물 저장할 구조체 (y,x,미생물수,이동방향)
	2) 현재 상황 보여줄 2차원벡터 map
	3) 방향벡터
	4) 끝에가면 방향바뀌고 개수 절반
	5) 합쳐지는거 처리
*/

struct micro {
	// 세로위치, 가로위치, 미생물 수, 이동방향
	int y, x, num, dir;
};
vector<micro> com; // 군집 저장할 벡터
queue<micro> map[100][100]; // 셀 지도
// 이 map을 priority queue로 구현했더니 문제생김

// 상: 1, 하: 2, 좌: 3, 우: 4
int diry[] = { 0,-1,1,0,0 };
int dirx[] = { 0,0,0,-1,1 };

// 필요 인자들
int N, K, M; // 맵의 크기, 최초 군집의 개수, 격리 시간

void reset() {
	com.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			while (!map[i][j].empty())
				map[i][j].pop();
	}
}

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		micro tmp;
		cin >> tmp.y >> tmp.x >> tmp.num >> tmp.dir;
		com.push_back(tmp);
	}
	// 첫 상황 map은 필요없지만 오류 방지 위해 넣어줌
	for (int i = 0; i < com.size(); i++) {
		map[com[i].y][com[i].x].push(com[i]);
	}
}

void move() {
	for (int i = 0; i < com.size(); i++) {
		map[com[i].y][com[i].x].pop(); // map에서 미생물 빼고
		com[i].y += diry[com[i].dir];
		com[i].x += dirx[com[i].dir];
		map[com[i].y][com[i].x].push(com[i]); // 새로운 자리에 다시 넣어줌
	}
}

void merge() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int len = map[i][j].size();
			// cell 사이즈가 2이상이면 미생물 겹친것
			if (len >= 2) {
				// 미생물 합쳐주고 방향 최대 미생물로
				micro tmp = {i,j,0,0};
				int maxnum = -21e8;
				for (int k = 0; k < len; k++) {
					tmp.num += map[i][j].front().num;
					if (map[i][j].front().num > maxnum) {
						maxnum = map[i][j].front().num;
						tmp.dir = map[i][j].front().dir;
					}
					map[i][j].pop();
				}
				for (int k = 0; k < com.size(); k++) {
					if (com[k].y == i && com[k].x == j) {
						com.erase(com.begin() + k);
						k--;
					}
				}
				map[i][j].push(tmp);
				com.push_back(tmp);
			}
		}
	}
}

void checkBorder() {
	for (int i = 0; i < com.size(); i++) {
		// 위에 있을 경우
		if (com[i].y == 0) {
			com[i].num /= 2;
			com[i].dir = 2;
		}

		// 아래에 있을 경우
		else if (com[i].y == N - 1) {
			com[i].num /= 2;
			com[i].dir = 1;
		}

		// 왼쪽에 있을 경우
		else if (com[i].x == 0) {
			com[i].num /= 2;
			com[i].dir = 4;
		}

		// 오른쪽에 있을 경우
		else if (com[i].x == N - 1) {
			com[i].num /= 2;
			com[i].dir = 3;
		}

		// 숫자가 0이 되면 죽음
		if (com[i].num == 0) {
			map[com[i].y][com[i].x].pop();
			com.erase(com.begin() + i);
			i--;
		}
	}
}

int sum() {

	int total = 0;
	for (int i = 0; i < com.size(); i++) {
		total += com[i].num;
	}
	return total;
}

int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// 테스트 케이스마다 초기화
		reset();

		// input
		input();

		// solve -> 1초마다 갱신
		for (int i = 1; i <= M; i++) {
			move(); // 방향 토대로 미생물 움직임
			merge(); // 겹치는 미생물 확인 후 합병
			checkBorder(); // 가장자리 처리
		}

		// output
		int result = sum();
		cout << "#" << tc << " " << result << endl;
	}

	return 0;
}
