#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int ydir[] = { 1,-1,0,0 };//하,상,우,좌
int xdir[] = { 0,0,1,-1 };
int N;//세로
int M;//가로
int R;//시작 세로
int C;//시작 가로
int L;//시간
int arr[50][50] = { 0 };
int t = 1;
queue<int>avaliable_direct;
struct Node {
	int y;
	int x;
};
vector<Node>avaliable_Node;

void avaliable(int y, int x) {

	int num = arr[y][x];
	if (num == 1) {
		avaliable_direct.push(0);
		avaliable_direct.push(1);
		avaliable_direct.push(2);
		avaliable_direct.push(3);
	}
	else if (num == 2) {
		avaliable_direct.push(0);
		avaliable_direct.push(1);
	}
	else if (num == 3) {
		avaliable_direct.push(2);
		avaliable_direct.push(3);
	}
	else if (num == 4) {
		avaliable_direct.push(1);
		avaliable_direct.push(2);
	}
	else if (num == 5) {
		avaliable_direct.push(0);
		avaliable_direct.push(2);
	}
	else if (num == 6) {
		avaliable_direct.push(0);
		avaliable_direct.push(3);
	}
	else if (num == 7) {
		avaliable_direct.push(1);
		avaliable_direct.push(3);
	}
}
bool ava_func(int y,int x ,int t) {
	if (t == 0) {//하로 가는 경로 -> 상이 연결되어 잇어야함
		if (arr[y][x] == 3 || arr[y][x] == 5 || arr[y][x] == 6)
			return false;
		else
			return true;
	}
	else if (t == 1) {//상으로 가는 경로 -> 하가 연결 되어 잇어야 함
		if (arr[y][x] == 3 || arr[y][x] == 4 || arr[y][x] == 7)
			return false;
		else
			return true;
	}
	else if (t == 2) {//우로 가는 경로 -> 좌가 연결 되어 잇어야함
		if (arr[y][x] == 2 || arr[y][x] == 4 || arr[y][x] == 5)
			return false;
		else
			return true;
	}
	else if (t == 3) {//좌로 가는 경로 -> 우가 연결 되어 있어야 함 
		if (arr[y][x] == 2 || arr[y][x] == 6 || arr[y][x] == 7)
			return false;
		else
			return true;
	}
	
}
void bfs() {
	int visited[50][50] = { 0 };

	queue<Node>q;
	q.push({ R,C });
	visited[R][C] = 1;
	avaliable_Node.push_back({ R,C });
	while (!q.empty() && t < L) {
		int length = q.size();
		
		for (int i = 0; i < length; i++) {
			Node start = q.front();
			q.pop();
			avaliable(start.y, start.x);
			while (!avaliable_direct.empty()) {
				int t = avaliable_direct.front();
				avaliable_direct.pop();
				int ny = start.y + ydir[t];
				int nx = start.x + xdir[t];

				if (ny < 0 || nx < 0 || ny >= N || nx >= M)continue;
				if (!ava_func(ny, nx, t))continue;

				if (arr[ny][nx] == 0)continue;
				if (visited[ny][nx] == 1)continue;
				visited[ny][nx] = 1;
				avaliable_Node.push_back({ ny,nx });
				q.push({ ny,nx });
				//cout << "ny:" << ny << " nx:" << nx << endl;
			}
		}
		t++;
	}
}
int main() {
	//freopen("input.txt", "r", stdin);
	int T; cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N >> M >> R >> C >> L;
		t = 1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> arr[i][j];
			}
		}
		bfs();
		cout <<'#'<<tc+1<<' ' << avaliable_Node.size() << endl;
		avaliable_Node.clear();	
	}
}
