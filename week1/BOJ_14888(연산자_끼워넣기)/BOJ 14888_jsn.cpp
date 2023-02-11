#include <iostream>
using namespace std;
int N;
int list1[11];
int acc1[4] = {};
char list2[10];
char list3[10];
int visited[10];
int max_num = -1000000000;
int min_num = 1000000000;
int acc() {
	int num = list1[0];
	for (int i = 0; i < N-1; i++) {
		if (list3[i] == '+') {
			num += list1[i+1];
		}
		else if (list3[i] == '-') {
			num -= list1[i + 1];
		}
		else if (list3[i] == '*') {
			num *= list1[i + 1];
		}
		else if (list3[i] == '/') {
			num /= list1[i + 1];
		}
	}
	return num;
}
void dfs(int count) {
	if (count == N-1)
	{
		int sum1 = acc();
		if (min_num > sum1) {
			min_num = sum1;
		}
		if (max_num < sum1) {
			max_num = sum1;
		}
		return;
	}
	for (int i = 0; i < N-1; i++) {
		if (visited[i] == 1)continue;
		list3[count] = list2[i];
		visited[i] = 1;
		dfs(count + 1);
		visited[i] = 0;
	}
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> list1[i];
	}
	for (int i = 0; i < 4; i++) {
		cin >> acc1[i];
	}
	int k = 0;
	for (int i = 0; i < acc1[0]; i++) {
		list2[k] = '+';
		k++;
	}
	for (int i = 0; i < acc1[1]; i++) {
		list2[k] = '-';
		k++;
	}
	for (int i = 0; i < acc1[2]; i++) {
		list2[k] = '*';
		k++;
	}
	for (int i = 0; i < acc1[3]; i++) {
		list2[k] = '/';
		k++;
	}
	
	dfs(0);
	cout << max_num << '\n' << min_num;
}
