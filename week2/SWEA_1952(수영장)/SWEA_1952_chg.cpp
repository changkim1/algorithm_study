#include <iostream>
#include <algorithm>

using namespace std;

/*
1. 문제읽기
	- 경우의 수
	- DFS, 최소값이니깐 backtracking으로 경우의 수 줄이기
	- 달 기준으로 탐색
	- 12달 되면 종료
*/

// 필요 인자들
int MIN;
int price[4]; // 1일권, 한달권, 세달권, 1년권
int plan[12]; // 12개월 이용계획
int sum;

void reset() {
	sum = 0;
}

void input() {
	for (int i = 0; i < 4; i++) {
		cin >> price[i];
	}
	for (int i = 0; i < 12; i++) {
		cin >> plan[i];
	}
	MIN = price[3]; // MAX에 연간회원권을 넣고 시작
}

// 0을 1월로 봄
void dfs(int month) {

	// 기저 조건 -> 12월까지 탐색하면 종료
	if (month >= 12) {
		if (sum < MIN)
			MIN = sum; // 최소값 비교
		return;
	}

	// 다음 재귀로 어떻게. 1일권 1달권 3달권으로 나눠서 재귀
	// 1일권
	sum += price[0] * plan[month];
	dfs(month + 1);
	sum -= price[0] * plan[month];
	// 1달권
	sum += price[1];
	dfs(month + 1);
	sum -= price[1];
	// 3달권
	sum += price[2];
	dfs(month + 3);
	sum -= price[2];


	/*
	// 근데 이걸 다 갈 필요없이 비교해서 진입하면 될듯
	// 3달먼저 비교하고 1달 비교
	// 이방법은 실패, 비교하는데 예외가 3경우 생겨버림
	int tmp1 = 0, tmp2 = 0, tmpp = 0, tmp3 = 0;
	for (int i = month; i < month + 3; i++) {
		if (i >= 12) continue;
		tmp1 = price[0] * plan[i];
		tmp2 = price[1];
		tmpp += min(tmp1, tmp2);
	}
	tmp3 = price[2];

	// 3달권이 가장 싼 경우
	if (tmp3 < tmpp) {
		sum += tmp3;
		dfs(month + 3);
		sum -= tmp3;
	}

	else {
		tmp1 = price[0] * plan[month];
		tmp2 = price[1];
		// 1일권이 가장 싼 경우
		if (tmp1 <= tmp2) {
			sum += tmp1;
			dfs(month + 1);
			sum -= tmp1;
		}
		// 1달권이 가장 싼 경우
		else {
			sum += tmp2;
			dfs(month + 1);
			sum -= tmp2;
		}
	}
	*/
}

int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// 테스트 케이스마다 초기화
		reset();

		// input
		input();

		// solve -> DFS로 탐색
		dfs(0);

		// output
		cout << "#" << tc << " " << MIN << endl;
	}

	return 0;
}