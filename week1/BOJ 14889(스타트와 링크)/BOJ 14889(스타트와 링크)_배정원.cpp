#include <bits/stdc++.h>
using namespace std;

int n, ans = 0;
int S[20][20];
int dat[20] = {0};

// 능력치 차이 반환
int power_diff()
{
    int start = 0, link = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (dat[i])
            {
                if (dat[j])
                {
                    start += S[i][j];
                }
            }
            else
            {
                if (!dat[j])
                {
                    link += S[i][j];
                }
            }
        }
    }

    return abs(start - link);
}

// 팀 나누기
void DFS(int idx, int cnt)
{
    // if(n-idx<n/2-cnt){
    //     return;
    // }

    if (cnt == n / 2)
    {
        ans = min(ans, power_diff());
        return;
    }

    for (int i = idx; i < n; ++i)
    {
        dat[i] = 1;
        DFS(i + 1, cnt + 1);
        dat[i] = 0;
    }
    // dat[idx] = 1;
    // DFS(idx + 1, cnt + 1);
    // dat[idx] = 0;

    // DFS(idx + 1, cnt);
}

void input()
{
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> S[i][j];
            ans += S[i][j];
        }
    }
}

void solve()
{
    input();
    DFS(0, 0);
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