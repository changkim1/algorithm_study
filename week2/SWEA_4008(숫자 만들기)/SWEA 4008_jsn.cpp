#include <iostream>
#include <string>
using namespace std;
int N;//숫자 개수
int num_list[12];
char now_str_list[11];
int operator_list[4];
int oper_list[4];
string oper = "+-*/";
int min_value = 21e8;
int max_value = -21e8;
int oper_func() {
	int sum = num_list[0];
	for (int i = 0; i < N - 1; i++) {
		if (now_str_list[i] == '+')sum += num_list[i + 1];
		else if (now_str_list[i] == '-')sum -= num_list[i + 1];
		else if (now_str_list[i] == '*')sum *= num_list[i + 1];
		else if (now_str_list[i] == '/') sum /= num_list[i + 1];
	}
	return sum;
}
void dfs(int count) {
	if (count == N - 1)
	{
		/*for (int i = 0; i < n - 1; i++) {
			cout << now_str_list[i] << ' ';
		}cout << endl;*/
		int now_sum = oper_func();
		if (min_value > now_sum)min_value = now_sum;
		if (max_value < now_sum) max_value = now_sum;
		return;
	}
	for (int t = 0; t < 4; t++) {
		if (oper_list[t] == operator_list[t])continue;
		now_str_list[count] = oper[t];
		oper_list[t] += 1;
		dfs(count + 1);
		oper_list[t] -= 1;
	}
}
int main() {
	int T; cin >> T;
	for (int tc = 0; tc < T; tc++) {
		min_value = 21e8;
		max_value = -21e8;
		N = 0;//초기화
		cin >> N;
		for (int i = 0; i < 4; i++) {
			cin >> operator_list[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> num_list[i];
		}
		dfs(0);
		cout <<'#' << tc + 1 << ' '<<max_value - min_value << '\n';
	}

}
