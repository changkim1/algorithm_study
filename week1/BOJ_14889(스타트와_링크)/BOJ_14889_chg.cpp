#include <iostream>
#include <vector>

using namespace std;

/*
1. 문제읽기
	- 경우의 수 (그중에서도 조합)
	- 입력(N)의 크기가 4 ~ 20
	- 재귀겠구나
	- N/2만 뽑으면 나머지는 다른팀
	- DFS와 Backtracking으로
*/

// 필요 인자들
int N; // 사람 수
int arr[21][21]; // 1부터 시작할 것
int MIN = 21e8;
int visited[21]; // 팀 표시 위한 dat (1: st팀, 0: li팀)
int tmp;


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

		for (int i = 0; i < N/2; i++) {
			for (int j = 0; j < N/2; j++) {
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
	for (int i = start+1; i <= N; i++) {

		// 3. 기록 및 처리
		visited[i] = 1; // st팀 뽑고 기록
		dfs(lv + 1, i);
		visited[i] = 0; // st팀 삭제
	}

}


int main() {

	// 필요하다면 초기화

	// input
	cin >> N;
	for (int i = 1; i <= N ; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

	// solve -> dfs 탐색
	 dfs(0, 0);

	// output
	 cout << MIN;

	return 0;
}