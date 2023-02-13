#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/*
1. 문제읽기
	- dfs
	- 끝에 붙어있는 core들은 판단하지 않아도 될듯
	- 빈곳은 0, core는 1, 전선은 2로 표시할 계획
	- 전선을 연결하는 방법은 총 5가지,
		-> 상하좌우 + 아얘 연결 X
*/


struct pos {
	int y;
	int x;
} tmp;


// 필요 인자들
int N; // cell의 크기
int map[12][12]; // cell의 상태
int maxCore; // 최대한 많은 Core
int minLen; // 최대한 많은 Core일때 전선 길이의 합 최소
vector<pos> core; // core의 위치 기록
int diry[] = { -1,0,1,0 };
int dirx[] = { 0,-1,0,1 };



// 코어개수, 연결된 코어, 전선길이의 합 넘겨줄 것
void dfs(int lv, int coreNum, int lenSum) {

	// 2. 기저 조건 -> 코어 다 체크하면 return
	if (lv == core.size()) {
		
		// 4. 최대 최소 비교
		if (coreNum > maxCore) {
			maxCore = coreNum;
			minLen = lenSum;
		}

		if (coreNum == maxCore) {
			minLen = min(lenSum, minLen);
		}

		return;
	}

	// 1. 다음 재귀로 어떻게
	// 상하좌우 + 무설치로 각 코어마다 진행
	// 가는길에 core(1)나 전선(2)있으면 break;
	for (int i = 0; i < 5; i++) {
		// 무설치의 경우
		if (i == 4) {
			dfs(lv + 1, coreNum, lenSum);
			continue;
		}
		
		int ny = core[lv].y, nx = core[lv].x; // 체크하는 cell
		int cnt = 0; // 이번 시행에서 설치되는 전선개수
		while (1) {
			ny += diry[i];
			nx += dirx[i];
			cnt++;

			// 진행중에 core나 전선을 만나면 break
			if (map[ny][nx] == 1 || map[ny][nx] == 2) {
				cnt = 0;
				break;
			}

			// 끝에 도달하면 break
			if (ny == 0 || nx == 0 || ny == N - 1 || nx == N - 1) {
				break;
			}	
		}

		// 끝까지 갈 수 있는 경우에는 전선을 설치한다
		// 3. 여기가 기록과 dfs와 삭제 부분
		if (cnt > 0) {

			ny = core[lv].y, nx = core[lv].x;
			while (1) {
				ny += diry[i];
				nx += dirx[i];

				if (ny < 0 || nx < 0 || ny > N - 1 || nx > N - 1)
					break;

				map[ny][nx] = 2;
			}
			dfs(lv + 1, coreNum + 1, lenSum + cnt);
			ny = core[lv].y, nx = core[lv].x;
			while (1) {
				ny += diry[i];
				nx += dirx[i];

				if (ny < 0 || nx < 0 || ny > N - 1 || nx > N - 1)
					break;

				map[ny][nx] = 0;
			}
		}
	}
}


int main() {
	
	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// 테스트 케이스마다 초기화
		maxCore = -1;
		minLen = 21e8;
		memset(map, 0, sizeof(map));
		core.clear();

		// input
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];

				if (map[i][j] == 1) {
					// 가장자리 제외한 core 벡터에 넣기
					if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
						continue;

					tmp.y = i, tmp.x = j;
					core.push_back(tmp);
				}
			}
		}

		// solve -> dfs로 탐색
		// 코어개수, 연결된 코어, 전선길이의 합
		dfs(0, 0, 0);

		// output
		cout << "#" << tc << " " << minLen << endl;
	}

	return 0;
}