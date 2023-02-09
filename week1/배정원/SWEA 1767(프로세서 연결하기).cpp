#include <bits/stdc++.h>
using namespace std;

int n;
// 전원 연결된 코어 개수
int cnt;
// 전선 길이 합
int sum;
// 전원 연결된 코어 최대 개수
int maxcnt;
// 정답
int ans;
// 프로세서
int board[12][12] = {0};
// 위 방향부터 시계방향
pair<int, int> dir[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
// 코어 위치
vector<pair<int, int>> core;

// 변수 초기화
void init()
{
    cnt = 0;
    sum = 0;
    maxcnt = 0;
    core.clear();
}

// 코어가 가장자리에 존재하는지 확인
int boundary(int y, int x)
{
    if (y == 0 || y == n - 1 || x == 0 || x == n - 1)
    {
        return 1;
    }

    return 0;
}

// 방향 d로 전선을 연결할 수 있는지 확인
int check(int y, int x, int d)
{
    int dirY = dir[d].first;
    int dirX = dir[d].second;

    for (int i = y, j = x; i < n && i >= 0 && j < n && j >= 0; i += dirY, j += dirX)
    {
        if (i == y && j == x)
        {
            continue;
        }

        if (board[i][j])
        {
            return 0;
        }
    }

    return 1;
}

/*
방향 d로 전선 설치 또는 삭제.
mode가 1일 때 설치, 0일 때 삭제
*/
void install(int y, int x, int d, int mode)
{
    int dirY = dir[d].first;
    int dirX = dir[d].second;

    for (int i = y, j = x; i < n && i >= 0 && j < n && j >= 0; i += dirY, j += dirX)
    {
        if (i == y && j == x)
        {
            continue;
        }

        board[i][j] = mode;

        if (mode)
        {
            sum += 1;
        }
        else
        {
            sum -= 1;
        }
    }
}

// 모든 코어에 대해 모든 경우 적용
void DFS(int idx)
{
    if (idx == core.size())
    {
        if (maxcnt < cnt)
        {
            maxcnt = cnt;
            ans = sum;
        }
        else if (maxcnt == cnt)
        {
            ans = min(ans, sum);
        }

        return;
    }

    int y = core[idx].first;
    int x = core[idx].second;

    for (int i = 0; i < 5; ++i)
    {
        // i=4는 전선 설치 안하는 경우임
        if (i != 4)
        {
            if (check(y, x, i))
            {
                install(y, x, i, 1);
                ++cnt;
            }
            else
            {
                continue;
            }
        }

        DFS(idx + 1);

        if (i != 4)
        {
            install(y, x, i, 0);
            --cnt;
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
            if (board[i][j])
            {
                if (boundary(i, j))
                {
                    ++cnt;
                }
                else
                {
                    core.push_back({i, j});
                }
            }
        }
    }
}

void solve()
{
    init();
    input();
    DFS(0);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;

    cin >> t;

    for (int i = 1; i <= t; ++i)
    {
        solve();
        cout << '#' << i << ' ' << ans << '\n';
    }

    return 0;
}