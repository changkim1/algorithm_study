#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int M;//경로의 크기
int A;//충전기 개수
int visited[2][101];//A,B 의 경로
int Addapter[8][4];//y,x,충전범위, 처리량
int ydir[] = { 0,-1,0,1,0 }; //상우하좌

int xdir[] = { 0,0,1,0,-1 };
struct Node {
	int y;
	int x;
	int M;
	vector<int>object;
};
bool cmp(int left, int right) {
	if (left > right)
		return true;
	if (left < right)
		return false;
	return false;
	
}

Node time_addapter[2][102];
long long sum1;
void my_sum() {
	for (int t = 0; t <= M; t++) {
		int sum2 = 0;
		if (A > 1)
		{
			for (int i = 0; i < A; i++) {
				for (int j = 0; j < A; j++) {
					if (i == j)continue;
					int answer = time_addapter[0][t].object[i] + time_addapter[1][t].object[j];
					if (answer > sum2)
						sum2 = answer;
				}
			}
		}
		else {
			int answer = max(time_addapter[0][t].object[0], time_addapter[1][t].object[0]);
			sum2 = answer;
		}
		
		sum1 += sum2;
	}
}
void path(int y, int x, int t, int type) {
	if (t == M)
		return;
	int num = visited[type][t];
	int ny = y + ydir[num];
	int nx = x + xdir[num];
	time_addapter[type][t].y = ny;			
	time_addapter[type][t].x = nx;
	
	for (int a = 0; a < A; a++) {
		if (abs(ny - Addapter[a][0]) + abs(nx - Addapter[a][1]) <= Addapter[a][2])
		{
			time_addapter[type][t].object.push_back(Addapter[a][3]);
			time_addapter[type][t].M = a;
		}
		else {
			time_addapter[type][t].object.push_back(0);
			time_addapter[type][t].M = a;
		}
	}
	path(ny, nx, t + 1, type);
}

int main() {
	int t; cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		cin >> M >> A;
		for (int t = 0; t < M; t++) {
			cin >> visited[0][t];
		}
		for (int t = 0; t < M; t++) {
			cin >> visited[1][t];
		}
		for (int i = 0; i < A; i++) {
			cin >> Addapter[i][1] >> Addapter[i][0] >> Addapter[i][2] >> Addapter[i][3];
		}
		time_addapter[0][M].y = 1;
		time_addapter[0][M].x = 1;
		time_addapter[1][M].y = 10;
		time_addapter[1][M].x = 10;
		for (int a = 0; a < A; a++) {
			if (abs(1 - Addapter[a][0]) + abs(1 - Addapter[a][1]) <= Addapter[a][2])
			{
				time_addapter[0][M].object.push_back(Addapter[a][3]);
				time_addapter[0][M].M = a;
			}
			else {
				time_addapter[0][M].object.push_back(0);
				time_addapter[0][M].M = a;

			}
			if (abs(10 - Addapter[a][0]) + abs(10 - Addapter[a][1]) <= Addapter[a][2])
			{
				time_addapter[1][M].object.push_back(Addapter[a][3]);
				time_addapter[1][M].M = a;

			}
			else {
				time_addapter[1][M].object.push_back(0);
				time_addapter[1][M].M = a;

			}
		}
		path(1, 1, 0, 0);
		path(10, 10, 0, 1);
		my_sum();
		cout <<'#'<<tc<<' ' << sum1 << endl;
		sum1 = 0;
		for (int t = 0; t <= M; t++) {
			time_addapter[0][t].object.clear();
			time_addapter[1][t].object.clear();

		}
	}
}
