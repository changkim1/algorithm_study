#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
이용권 4개: 1일 1달 3달(해를 걸칠 수는 없음) 1년
 */

/* 구하는 것
 */

/* 아이디어
DFS
1달 이상의 요금제는 달 단위로 적용되기 때문에
그냥 달마다 요금제를 어떻게 적용할 것인지 정하면 된다.
 */

// 변수

// 답
int ans = 0;
// 요금
int fee[4];
// 이용 계획
int table[12];

// 함수

// 입력
void input();
void DFS(int month, int sum);
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
    for (int i = 0; i < 4; ++i)
    {
        cin >> fee[i];
    }

    for (int i = 0; i < 12; ++i)
    {
        cin >> table[i];
    }

    // ans 초기화(1년 이용권)
    // 이렇게 하면 DFS에서 1년 이용권의 경우를 고려하지 않아도 된다.
    ans = fee[3];
}

void DFS(int month, int sum)
{
    if (month >= 12)
    {
        ans = min(sum, ans);

        return;
    }

    // 1일 이용권 적용
    DFS(month + 1, sum + table[month] * fee[0]);
    // 1달 이용권 적용
    DFS(month + 1, sum + fee[1]);
    // 3달 이용권 적용
    DFS(month + 3, sum + fee[2]);
}

void solve()
{
    input();
    DFS(0, 0);
    cout << ans << '\n';
}