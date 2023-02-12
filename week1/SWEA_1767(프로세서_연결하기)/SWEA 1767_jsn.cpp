#include <iostream>
#include <vector>
#include <algu>
using namespace std;
int N;
int arr[12][12];
struct Node {
	int y;
	int x;
};
vector<Node>v;
int ydir[] = { 1,-1,0,0,};
int xdir[] = { 0,0,1,-1 };
int max_connected;
int min_cost = 1000000;
int my_len;
int cost;
void dfs(int count,int connected,int total_cost) {
	if (count == my_len) {
		if (connected >= max_connected && min_cost > total_cost) {
			max_connected = connected;
			min_cost = total_cost;
			//cout << "connected:" << connected << " total_cost:" << total_cost<<endl;

		}
		else if (connected > max_connected) {
			max_connected = connected;
			min_cost = total_cost;
			//cout << "connected:" << connected << " total_cost:" << total_cost<<endl;
		}
		
		return;
	}
	for (int i = 0; i < 4; i++) {
		int cost = 0;
		int ny = v[count].y;
		int nx = v[count].x;
		while (true) {
			ny += ydir[i];
			nx += xdir[i];
			cost++;
			
			if (arr[ny][nx] != 0) {
				cost = 0;
				break;
			}
			if (arr[ny][nx] == 0 && (ny == 0 || nx == 0 || ny >= N - 1 || nx >= N - 1))
			{
				break;
			}
		}
		if (cost)
		{
			ny = v[count].y;
			nx = v[count].x;
			while (true) {
				ny += ydir[i];
				nx += xdir[i];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N)
					break;
				arr[ny][nx] = 1;
			}
			dfs(count + 1, connected + 1, total_cost + cost);
			ny = v[count].y;
			nx = v[count].x;
			while (true) {
				ny += ydir[i];
				nx += xdir[i];
				if(nx < 0 || ny < 0 || nx >= N || ny >= N)
					break;
				arr[ny][nx] = 0;
			}
		}
		dfs(count + 1, connected, total_cost);
		//cout <<"cost :" << cost << " connected" << connected<<endl;
	}	
}

void solve() {
	my_len = v.size();
	dfs(0,0,0);
}
int main() {
	int T; cin >> T;
	for (int tc = 0; tc < T; tc++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				
				cin >> arr[i][j];
				if (arr[i][j] == 1) {
					if (i == 0 || i == N - 1 || j == 0 || j == N - 1)continue;
					v.push_back({ i,j });
				}
			}
		}

		solve();
		cout <<'#' << tc + 1 <<' ' << min_cost << endl;
		v.clear();
		min_cost = 10000000;
		max_connected = 0;
	}
}
