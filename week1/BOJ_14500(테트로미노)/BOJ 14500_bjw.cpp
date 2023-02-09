#include <bits/stdc++.h>
using namespace std;

int n, m, ans = 0;
int board[500][500] = {0};
int visited[500][500] = {0};
// 방향
pair<int, int> dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void DFS(int coor, int cnt, int sum)
{
    if (cnt == 4)
    {
        ans = max(sum, ans);
        return;
    }

    int y = coor / m, x = coor % m;
    for (int i = 0; i < 4; ++i)
    {
        int ny = y + dir[i].first, nx = x + dir[i].second;

        if (!visited[ny][nx] && 0 <= ny && ny < n && 0 <= nx && nx < m)
        {
            visited[ny][nx] = 1;
            sum += board[ny][nx];

            // T 미노 처리
            if (cnt == 2)
            {
                for (int j = 0; j < 4; ++j)
                {
                    int ny2 = y + dir[j].first, nx2 = x + dir[j].second;

                    if (!visited[ny2][nx2] && 0 <= ny2 && ny2 < n && 0 <= nx2 && nx2 < m)
                    {
                        visited[ny2][nx2] = 1;
                        DFS(ny2 * m + nx2, cnt + 2, sum + board[ny2][nx2]);
                        visited[ny2][nx2] = 0;
                    }
                }
            }

            DFS(ny * m + nx, cnt + 1, sum);
            sum -= board[ny][nx];
            visited[ny][nx] = 0;
        }
    }
}

// 입력
void input()
{
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> board[i][j];
        }
    }
}

void solve()
{
    input();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            visited[i][j] = 1;
            DFS(i * m + j, 1, board[i][j]);
            visited[i][j] = 0;
        }
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();

    return 0;
}