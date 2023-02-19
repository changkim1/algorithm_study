#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
n은 숫자 개수
계산은 항상 왼쪽에서 오른쪽으로
 */

/* 구하는 것
연산자 카드로 수식 썼을 때 최대값과 최소값의 차이
 */

/* 아이디어
DFS
 */

// 변수

// 숫자 개수
int n;
// 숫자
int num[12];
// 연산자
int oper[4];
// 최대값
int MAX;
// 최소값
int MIN;

// 함수

// 입력
void input();
void DFS(int result, int idx);
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
    cin >> n;

    for (int i = 0; i < 4; ++i)
    {
        cin >> oper[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }

    // 최대값, 최소값 초기화
    MIN = INT_MAX;
    MAX = INT_MIN;
}

void DFS(int result, int idx)
{
    if (idx == n)
    {
        MIN = min(MIN, result);
        MAX = max(MAX, result);

        return;
    }

    for (int i = 0; i < 4; ++i)
    {
        if (!oper[i])
            continue;

        oper[i] -= 1;

        switch (i)
        {
        case 0:
            DFS(result + num[idx], idx + 1);
            break;
        case 1:
            DFS(result - num[idx], idx + 1);
            break;
        case 2:
            DFS(result * num[idx], idx + 1);
            break;
        case 3:
            DFS(result / num[idx], idx + 1);
            break;
        }

        oper[i] += 1;
    }
}

void solve()
{
    input();
    DFS(num[0], 1);
    cout << MAX - MIN << '\n';
}