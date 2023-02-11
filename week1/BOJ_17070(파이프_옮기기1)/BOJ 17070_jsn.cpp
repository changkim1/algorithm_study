#include <iostream>
#include <queue>
using namespace std;
int arr[16][16];
int N;
struct Node {
	int y;
	int x;
};
int ydir[] = {1,0,1};//대각선, 가로, 세로
int xdir[] = {1,1,0};//대각선, 가로, 세로
Node a, b;
int answer = 0;
bool xandy(Node after) {
	bool my_bool = true;
	for (int t = 0; t < 3; t++) {
		int ny = after.y + ydir[t];
		int nx = after.x + xdir[t];
		if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
			my_bool = false;
		}
		if (arr[ny][nx] == 1) {
			my_bool = false;
		}
	}
	return my_bool;
}
bool onlyX(Node after) {
	bool my_bool = true;
	int ny = after.y;
	int nx = after.x + 1;
	if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
		my_bool = false;
	}
	if (arr[ny][nx] == 1) {
		my_bool = false;
	}
	return my_bool;
}
bool onlyY(Node after){
	bool my_bool = true;
	int ny = after.y + 1;
	int nx = after.x;
	if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
		my_bool = false;
	}
	if (arr[ny][nx] == 1) {
		my_bool = false;
	}
	return my_bool;

}
void bfs() {
	queue<Node>after;
	queue<Node>before;
	before.push(a);
	after.push(b);
	while (!after.empty()) {
		Node Nbefore = before.front();
		before.pop();
		Node Nafter = after.front();
		after.pop();
		//cout << Nafter.y << ' ' << Nafter.x << endl;
		if (Nafter.y == N - 1 and Nafter.x == N - 1)
		{
			answer++;
		}
		if (Nafter.x - Nbefore.x == 1) {
			if (Nafter.y - Nbefore.y == 1) {//대각선상태 -> 3개 다 가능
				if (xandy(Nafter)) {//대각선으로 가는 것 
					after.push({ Nafter.y + 1,Nafter.x + 1 });
					before.push({ Nafter.y,Nafter.x });
				}
				if (onlyX(Nafter)) {//가로로 가는것
					after.push({ Nafter.y, Nafter.x + 1 });
					before.push({ Nafter.y, Nafter.x });
				}
				if (onlyY(Nafter)) {//세로로 가는 것
					after.push({ Nafter.y + 1,Nafter.x });
					before.push({ Nafter.y, Nafter.x });
				}
			}
			else if(Nafter.y == Nbefore.y ){//가로상태 -> 대각선, 가로 만 가능
				if (xandy(Nafter)) {//대각선으로 가는 것 
					after.push({ Nafter.y + 1,Nafter.x + 1 });
					before.push({ Nafter.y,Nafter.x });
				}
				if (onlyX(Nafter)) {//가로로 가는것
					after.push({ Nafter.y, Nafter.x + 1 });
					before.push({ Nafter.y, Nafter.x });
					
				}
			}
		}
		else if(Nafter.y - Nbefore.y == 1){//세로상태 -> 대각선, 세로만 가능
			if (xandy(Nafter)) {//대각선으로 가는 것 
				after.push({ Nafter.y + 1,Nafter.x + 1 });
				before.push({ Nafter.y,Nafter.x });

			}
			if (onlyY(Nafter)) {//세로로 가는 것
				after.push({ Nafter.y + 1,Nafter.x });
				before.push({ Nafter.y, Nafter.x });

			}
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	a.x = 0;
	a.y = 0;
	b.x = 1;
	b.y = 0;
	bfs();
	cout << answer;
}
