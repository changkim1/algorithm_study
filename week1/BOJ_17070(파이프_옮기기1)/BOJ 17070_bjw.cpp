#include <bits/stdc++.h>
using namespace std;

int n, ans = 0;
int board[16][16];

pair<int, int> dir[3] = {{0, 1}, {1, 1}, {1, 0}};

/* 모드(현재 파이프의 상태)
0: 가로
1: 대각선
2: 세로
*/
void DFS(pair<int, int> coor, int mode)
{
    int y = coor.first, x = coor.second;
    if (y == n - 1 && x == n - 1)
    {
        ++ans;
        return;
    }

    for (int i = 0; i < 3; ++i)
    {
        if (mode == 0 && i == 2 || mode == 2 && i == 0)
        {
            continue;
        }

        int ny = y + dir[i].first, nx = x + dir[i].second;

        if (0 <= ny && ny < n && 0 <= nx && nx < n)
        {
            if (i == 1)
            {
                int s = 0;
                for (int j = 0; j < 3; ++j)
                {
                    int my = y + dir[j].first, mx = x + dir[j].second;
                    if (board[my][mx])
                    {
                        s = 1;
                        break;
                    }
                }

                if (s)
                {
                    continue;
                }
            }
            else
            {
                if (board[ny][nx])
                    continue;
            }
            DFS({ny, nx}, i);
        }
    }
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> board[i][j];
        }
    }
}

void solve()
{
    input();
    // 본체는 두번째 칸
    DFS({0, 1}, 0);
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