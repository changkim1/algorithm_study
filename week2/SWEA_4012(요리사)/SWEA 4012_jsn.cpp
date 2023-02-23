#include <iostream>
using namespace std;
int N;//가로 세로 길이(원소의 수)
int arr[16][16] = { 0 };
int dat[16];
int answer = 21e8;
int num = 1;
void dfs(int count,int start) {
	if (count == N / 2)
	{
		int result1 = 0;
		int result2 = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)continue;
				if (dat[i] == 1 && dat[j] == 1)result1 += arr[i][j];
				if (dat[i] == 0 && dat[j] == 0)result2 += arr[i][j];
			}
		}
		int my_num = abs(result1 - result2);
		if (answer > my_num)
			answer = my_num;
		return;
	}
	for (int i = start; i < N; i++) {
		if (dat[i] == 0) {
			dat[i] = 1;
			dfs(count + 1, i);
			dat[i] = 0;
		}
	}
}
int main() {
	int T; cin >> T;
	for (int tc = 0; tc < T; tc++) {
		answer = 21e8;
		cin >> N;
		for (int i = 0; i < N; i++) {
			dat[i] = 0;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> arr[i][j];
			}
		}
		dfs(0, 0);
		cout <<'#' << tc + 1 << ' ' << answer << endl;

	}
	
}
