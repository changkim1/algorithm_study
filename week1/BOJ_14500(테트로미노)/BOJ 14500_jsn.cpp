#include <iostream>
using namespace std;
int arr[5][4][4] = {
	{{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}},

	{{1,1,0,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}},

	{{0,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
	{1,1,0,0}},

	{{1,0,0,0},
	{1,1,0,0,},
	{0,1,0,0,},
	{0,0,0,0} },

	{{1,1,1,0},
	{0,1,0,0},
	{0,0,0,0},
	{0,0,0,0}}
};
int arr2[500][500];
int N;
int M;
int temp[4][4][4];
int answer;
void rotate(int y, int x,int tc, int rot) {
	int n = 0; 
	int sum1 = 0;
	int sum2 = 0;
	bool my_bool = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[0][i][j] = arr[tc][i][j];
		}
	}
	while (n < rot) {
		n++;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				temp[n][i][j] = temp[n - 1][3-j][i];
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (temp[n - 1][i][j] == 1 && y + i >= 0 && x + j >= 0 && y + i < N && x + j < M)
			{
				//cout << "i:" << i << "j:" << j << endl;
				sum1 += arr2[y + i][x + j];
			}
			else if (temp[n - 1][i][j] == 1) {
				my_bool = true;
			}
		}
	}//cout << endl;
	if (my_bool) {
		sum1 = answer;
	}
	else if (answer < sum1) {
		answer = sum1;
	}
}
int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr2[i][j];
		}
	}
	for (int i = -5; i < N+5; i++) {
		for (int j = -5; j < M+5; j++) {
			for (int t = 0; t < 5; t++) {
				for (int s = 0; s < 4; s++) {
					rotate(i,j,t,s);
				}
			}
		}
	}
	cout << answer;
}
