#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
탈주범은 터널로만 이동 가능
시간 당 1의 거리 이동 가능
탈출 뒤 1시간 뒤에 있을 수 있는 곳이 맨홀 뚜껑 위치다.
0시간 뒤가 아님.
 */

/* 구하는 것
 */

/* 아이디어
BFS+하드코딩
터널 구조물 별로 하드코딩
 */

// 변수
int n;                                                      // 세로
int m;                                                      // 가로
int r, c;                                                   // 맨홀 뚜껑 위치
int l;                                                      // 탈출 소요 시간
int MAP[50][50] = {0};                                      // 지하 터널 지도
pair<int, int> dir[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; // 방향배열(상좌하우)
int tunnel[8][4] = {                                        // 터널 타입
//   상 좌 하 우
    {0, 0, 0, 0}, // 터널 타입은 1부터 시작하므로 indec 0은 사용하지 않음
    {1, 1, 1, 1}, // 상좌하우
    {1, 0, 1, 0}, // 상하
    {0, 1, 0, 1}, // 좌우
    {1, 0, 0, 1}, // 상우
    {0, 0, 1, 1}, // 하우
    {0, 1, 1, 0}, // 좌하
    {1, 1, 0, 0}  // 상좌
};

// 함수
void input(); // 입력
void BFS();
void solve();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    for (int i = 1; i <= t; ++i)
    {
        cout << '#' << i << ' ';
        solve();
    }
    return 0;
}

void input()
{
    cin >> n >> m >> r >> c >> l;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> MAP[i][j];
        }
    }
}

void BFS()
{
    int visited[50][50] = {0};
    queue<pair<pair<int, int>, int>> que; // 인자: 좌표(y,x),시간
    int ans = 0;

    que.push({{r, c}, 1});
    visited[r][c] = 1;

    while (!que.empty())
    {
        int y = que.front().first.first;
        int x = que.front().first.second;
        int cnt = que.front().second;
        int origin_tunnel_type = MAP[y][x];
        que.pop();

        if (cnt <= l)
        {
            ans++;
        }
        else
        {
            break;
        }

        for (int i = 0; i < 4; ++i)
        {
            // 갈 수 없는 방향의 경우 continue
            if (!tunnel[origin_tunnel_type][i])
            {
                continue;
            }

            // 다음으로 진행할 좌표
            int ny = y + dir[i].first;
            int nx = x + dir[i].second;

            // 다음 좌표의 터널 타입
            int new_tunnel_type = MAP[ny][nx];

            // 다음 좌표가 맵 밖을 벗어나거나 이미 방문한 곳인 경우 continue
            if (ny < 0 || ny >= n || nx < 0 || nx >= m || visited[ny][nx])
            {
                continue;
            }

            // 다음 좌표의 터널로 이동할 수 없는 경우 continue
            if (!tunnel[new_tunnel_type][(i + 2) % 4])
            {
                continue;
            }

            visited[ny][nx] = 1;
            que.push({{ny, nx}, cnt + 1});
        }
    }

    cout << ans << '\n';
}

void solve()
{
    input();
    BFS();
}