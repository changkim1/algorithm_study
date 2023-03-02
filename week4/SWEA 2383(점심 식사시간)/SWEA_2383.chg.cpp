#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
1. 문제읽기
	- 방의 한 변의 길이 N은 4 이상 10 이하의 정수이다. (4 ≤ N ≤ 10)
	- 사람의 수는 1 이상 10 이하의 정수이다. (1 ≤ 사람의 수 ≤ 10)
	- 계단의 입구는 반드시 2개이며, 서로 위치가 겹치지 않는다.
	- 계단의 길이는 2 이상 10 이하의 정수이다. (2 ≤ 계단의 길이 ≤ 10)
	- 초기에 입력으로 주어지는 사람의 위치와 계단 입구의 위치는 서로 겹치지 않는다.

	- 이동 시간(분) = | PR - SR | + | PC - SC |
	- 계단 입구에 도착하면, 1분 후 아래칸으로 내려 갈 수 있다.
	- 계단 위에는 동시에 최대 3명까지만 올라가 있을 수 있다.
*/

/*
2. 아이디어
	- 일단 시행시간이 넉넉함 (3초)
	- 무조건 가까운 계단으로 가면안됨, 멀리 가는 경우도 가능
	- 완전탐색으로 모든 경우 살펴야할듯
	- 계단이 두개니깐 각자 사람이 1번 2번 선택하는 경우로 나눈다
	- 비트연산자 or 재귀
*/

struct Stair {
	int y; // y좌표
	int x; // x좌표
	int len; // 길이
}stair_info[2]; // 계단 정보 저장

// 필요 인자들
int N; // 방의 길이
int P; // 사람의 수
int Map[10][10]; // 지도
int ans;
int visited[11]; // 사람 몇번계단 체크
int P_len[2][11]; // 각 사람 계단까지 거리 몇인지

// 테스트 케이스마다 초기화
void reset() {
	memset(Map, 0, sizeof(Map));
	memset(visited, 0, sizeof(visited));
	memset(P_len, 0, sizeof(P_len));
	P = 0;
	ans = 21e8;
}

// 값 입력받기, 받으면서 사람수, 계단
void input() {
	cin >> N;
	int type = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			// 사람 수 카운트, 거리구하기
			if (Map[i][j] == 1)
				P++;
			// 계단 정보 입력
			if (Map[i][j] >= 2)
				stair_info[type++] = { i, j, Map[i][j] };
		}
	}
}

// 계단 - 사람 거리구하는 함수
void calc() {
	int P_num = 1;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (Map[y][x] == 1) {
				for (int k = 0; k < 2; k++) {
					// 그냥 대기시간 1분도 더해줌
					int movingtime = abs(y - stair_info[k].y) + abs(x - stair_info[k].x) + 1;
					P_len[k][P_num] = movingtime;
				}
				P_num++;
			}
		}
	}
}

// 각 경우 계산 함수
void solve() {
	// 시간마다 P_num 1씩 줄이다가 0되면 그건 계단 들어간것
	// P_len[visited[i]][1]
	// 상태 처리할 dat도 하나 만들자
	// 계단은 벡터로
	vector<int> stair0;
	vector<int> stair1;

	int P_lenc[2][11]; // 바보같이 원본을 수정해서 그냥 복사하나 만듦
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 11; j++) {
			P_lenc[i][j] = P_len[i][j];
		}
	}

	int time = 0;
	int cnt = 0;
	int stat[11] = { 0 }; // 0이면 이동, 1이면 계단도착, 2면 계단들어감
	while (1) {
		time++;

		// 계단0 처리
		for (int i = 0; i < stair0.size(); i++) {
			stair0[i]--;
		}
		// 내림차순 정렬하고 0 체크
		sort(stair0.begin(), stair0.end(), greater<int>());
		int tmpSize = stair0.size();
		for (int i = tmpSize - 1; i >= 0; i--) {
			if (stair0[i] == 0) {
				stair0.pop_back();
				cnt++;
			}
		}
		// 계단1 처리
		for (int i = 0; i < stair1.size(); i++) {
			stair1[i]--;
		}
		// 내림차순 정렬하고 0 체크
		sort(stair1.begin(), stair1.end(), greater<int>());
		tmpSize = stair1.size();
		for (int i = tmpSize - 1; i >= 0; i--) {
			if (stair1[i] == 0) {
				stair1.pop_back();
				cnt++;
			}
		}

		if (cnt == P)
			break;

		// 이동부터
		for (int i = 1; i <= P; i++) {
			if (stat[i] == 0) {
				P_lenc[visited[i]][i] -= 1;
				if (P_lenc[visited[i]][i] == 0)
					stat[i] = 1;
			}
		}

		// 1인거 체크해서 계단 넣기
		for (int i = 1; i <= P; i++) {
			if (stat[i] == 1) {
				// 계단 꽉차있으면 불가능
				if (visited[i] == 0) {
					if (stair0.size() == 3)
						continue;
					stat[i] = 2;
					stair0.push_back(stair_info[0].len);
				}
				if (visited[i] == 1) {
					if (stair1.size() == 3)
						continue;
					stat[i] = 2;
					stair1.push_back(stair_info[1].len);
				}
			}
		}
	}
	if (time < ans)
		ans = time;
}

// 조합 함수
void combi(int lv) {
	
	// P명 다 뽑으면 계산
	if (lv > P) {
		solve();
		return;
	}

	for (int i = 0; i < 2; i++) {
		if (i == 0)
			combi(lv + 1);
		else if (i == 1) {
			visited[lv] = 1;
			combi(lv + 1);
			visited[lv] = 0;
		}
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
		
		// 계단부터 각 사람들 거리 구해줌
		calc();

		// solve -> 계단 선택하는 모든 경우 만들고
		// 그거 모두 구현
		combi(1);

		// output
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
