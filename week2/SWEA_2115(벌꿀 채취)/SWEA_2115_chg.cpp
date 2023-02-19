#include <iostream>
#include <vector>

using namespace std;

/*
1. 문제읽기
	- 각 일꾼이 채취할 영역 for문으로 구하고
	- dfs로 그 영역 최대값 구하기
*/

// 필요 인자들
int max1, max2; // 각일꾼최대, 이익최대
int N, M, C; // 벌통의 크기, 벌통의 개수, 꿀의 최대 양
int hive[10][10]; // 벌통
vector<int> path;

void reset() {
	max2 = 0;
}

void input() {
	cin >> N >> M >> C;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> hive[i][j];
		}
	}
}

// 벌통 max 구하는 dfs
void dfs(int num, int sum, int y, int x) {

	// 기저 조건 -> 1. 합이 C넘으면 return, 2. M개 뽑으면 종료
	if (sum > C) {
		return;
	}
	if (num == M) {
		int tmp = 0;
		for (int i = 0; i < path.size(); i++) {
			tmp += path[i] * path[i];
		}
		if (tmp > max1)
			max1 = tmp;

		return;
	}

	// 다음 재귀로 어떻게. 각 벌통을 뽑을지(1), 뽑지 않을지로(0)
	for (int select = 0; select < 2; select++) {
		// 안뽑음
		if (select == 0) {
			dfs(num + 1, sum, y, x + 1);
		}
		// 뽑음
		else {
			path.push_back(hive[y][x]);
			dfs(num + 1, sum + hive[y][x], y, x + 1);
			path.pop_back();
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

		// solve -> 1. 각 구간 정하고, 그 구간마다 dfs최대값
		for(int i = 0; i< N; i++)
			for (int j = 0; j <= N - M; j++) {
				int profit = 0;
				// 일꾼1 구하기
				max1 = 0;
				dfs(0, 0, i, j);
				profit += max1;
				// 일꾼2는 일꾼1구간 이후로
				max1 = 0;
				// 일꾼1과 같은줄
				for (int l = j + M; l <= N - M; l++) {
					dfs(0, 0, i, l);
				}
				// 다른줄
				for (int k = i + 1; k < N; k++) {
					for (int l = 0; l <= N - M; l++) {
						dfs(0, 0, k, l);
					}
				}
				profit += max1;

				if (profit > max2)
					max2 = profit;
			}

		// output
		cout << "#" << tc << " " << max2 << endl;
	}

	return 0;
}