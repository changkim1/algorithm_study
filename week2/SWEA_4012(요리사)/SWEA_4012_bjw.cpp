#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
n개의 식재료
식재료들을 반으로 나누어 2개의 요리를 함
두 음식의 맛의 차이가 최소가 되도록 재료를 배분해야 함
재료간 시너지 있음
 */

/* 구하는 것
두 음식 간의 맛의 차이가 최소가 될때 그 값
 */

/* 아이디어
백준의 "스타트와 링크" 문제와 사실상 같은 문제임
 */

// 변수

// 식재료 수
int n;
// 시너지
int S[16][16];
// 각 음식에 들어가는 재료를 구분할 dat
int dat[16];
// 답
int ans;

// 함수

// 입력
void input();
// 최소값 계산
int diff();
// idx는 식재료,cnt는 지금까지 고른 식재료 수
void DFS(int idx, int cnt);
void solve();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cout << '#' << i << ' ';
        solve();
    }
    return 0;
}

void input()
{
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        dat[i] = 0;
        for (int j = 0; j < n; ++j)
        {
            cin >> S[i][j];
        }
    }

    ans = INT_MAX;
}

int diff()
{
    int a = 0;
    int b = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        if (dat[i])
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (!dat[j])
                    continue;
                a += S[i][j] + S[j][i];
            }
        }
        else
        {
            for (int j = i; j < n; ++j)
            {
                if (dat[j])
                    continue;
                b += S[i][j] + S[j][i];
            }
        }
    }

    return abs(a - b);
}

void DFS(int idx, int cnt)
{
    if (idx == n)
    {
        return;
    }

    if (cnt == n / 2)
    {
        ans = min(ans, diff());
        return;
    }

    // 식재료 선택하는 경우
    dat[idx] = 1;
    DFS(idx + 1, cnt + 1);
    dat[idx] = 0;

    // 식재료 선택 안하는 경우
    DFS(idx + 1, cnt);
}

void solve()
{
    input();
    DFS(0, 0);
    cout << ans << '\n';
}