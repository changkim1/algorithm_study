#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

/*
1. 문제읽기
	- 스타트 링크팀 문제랑 완전히 일치
	- dfs로 절반만 뽑아서 비교
*/

// 필요 인자들
int N; // 사람 수
int arr[17][17]; // 1부터 시작할 것
int MIN = 21e8;
int visited[17]; // 팀 표시 위한 dat (1: st팀, 0: li팀)
int tmp;


void reset() {
	memset(arr, 0, sizeof(arr));
	MIN = 21e8;
}

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void dfs(int lv, int start) {

	// 2. 기저 조건 -> N/2명 뽑으면 종료
	if (lv == N / 2) {

		vector<int> st; // 스타트 팀원의 인덱스
		vector<int> li; // 링크 팀원의 인덱스
		int st_score = 0; // 스타트 팀의 점수
		int li_score = 0; // 링크 팀의 점수

		for (int i = 1; i <= N; i++) {
			// st팀 li팀 팀원들 인덱스 넣어줌
			if (visited[i] == 1)
				st.push_back(i);
			else
				li.push_back(i);
		}

		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				// st팀 li팀 각각 점수를 더해줌
				st_score += arr[st[i]][st[j]];
				li_score += arr[li[i]][li[j]];
			}
		}

		tmp = abs(st_score - li_score); // 두 팀의 점수차
		if (tmp < MIN) {
			MIN = tmp;
		}

		return;
	}

	// 1. 다음 재귀로 어떻게
	// 조합이니깐 다음것만 뽑기
	for (int i = start + 1; i <= N; i++) {

		// 3. 기록 및 처리
		visited[i] = 1; // st팀 뽑고 기록
		dfs(lv + 1, i);
		visited[i] = 0; // st팀 삭제
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

		// solve -> dfs 탐색
		dfs(0, 0);

		// output
		cout << "#" << tc << " " << MIN << endl;
	}

	return 0;
}