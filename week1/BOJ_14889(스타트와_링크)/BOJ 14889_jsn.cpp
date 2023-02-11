#include <iostream>
#include <math.h>
using namespace std;
int N;
int arr[20][20];
bool visited[21];
int answer = 100000000;
void dfs(int count,int po) {
	if (count == N / 2) {
		int sum1 = 0;
		int sum2 = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i] == true and visited[j] == true)sum1 += arr[i][j];
				if (visited[i] == false and visited[j] == false)sum2 += arr[i][j];
			}
		}
		int temp = abs(sum1 - sum2);
		if (answer > temp) {
			answer = temp;
			
		}
		return;
	}
	for (int i = po; i < N; i++) {
		visited[i] = true;
		dfs(count + 1, i+1);
		visited[i] = false;
	}
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	dfs(0,0);
	cout << answer;
}
