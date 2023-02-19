#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N;//맵 크기
int K;//깍는 산 크기
int arr[8][8];
int new_arr[8][8];
int ydir[] = { 1,-1,0,0 };
int xdir[] = { 0,0,1,-1 };
struct Node {
    int y;
    int x;
};
int visited[8][8];
int max_value = 0;
vector<Node>v;
void track_path(int y, int x,int cost) {
     
    for (int t = 0; t < 4; t++) {
        int ny = y + ydir[t];
        int nx = x + xdir[t];
        if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
        if (arr[ny][nx] >= arr[y][x])continue;
        if (visited[ny][nx] == 1)continue;
        visited[ny][nx] = 1;
        track_path(ny, nx,cost+1);
        visited[ny][nx] = 0;
    }
    if (cost > max_value)
    {
        max_value = cost;
    }
}
void track() {
    for (int i = 0; i < v.size(); i++) {
        Node now = v[i];
        visited[now.y][now.x] = 1;
        track_path(now.y, now.x, 0);//i,j번에서 시작하는 경로
        visited[now.y][now.x] = 0;
    }
     
}
void solve() {
    int max_value = 0;
    int max_y = 0;
    int max_x = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j] > max_value) {
                max_value = arr[i][j];
                max_y = i;
                max_x = j;
                v.clear();
                v.push_back({ i,j });
            }
            else if (arr[i][j] == max_value)
            {
                v.push_back({ i,j });
            }
        }
    }
    track();
    //산 깍는 과정
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 1; k <= K; k++) {
                if (i == max_y && j == max_x)continue;
                arr[i][j] -= k;//산을 깍는 과정
                track();
                arr[i][j] += k;//산을 복원하는 과정
            }
        }
    }
 
}
int main() {
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> K;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> arr[i][j];
            }
        }
        solve();
        cout <<'#' << tc <<' '<< max_value+1 << endl;
        max_value = 0;
         
    }
}
