#include <bits/stdc++.h>
using namespace std;

int n, MIN = INT_MAX, MAX = INT_MIN;
int num[11];
int oper[4];

/* 결과값 갱신
idx는 DFS의 idx와 동일
op는 연산자 번호
sum은 반환할 결과값
*/
int renew_sum(int idx, int op, int sum)
{
    switch (op)
    {
    case 0:
        sum += num[idx + 1];
        break;

    case 1:
        sum -= num[idx + 1];
        break;

    case 2:
        sum *= num[idx + 1];
        break;

    case 3:
        sum /= num[idx + 1];
        break;
    }

    return sum;
}

/* 문제를 풀 DFS 함수
idx는 현재까지 쓰인 연산자의 개수
sum은 현재까지의 계산 결과
*/
void DFS(int idx, int sum)
{
    if (idx == n - 1)
    {
        MIN = min(MIN, sum);
        MAX = max(MAX, sum);

        return;
    }

    for (int i = 0; i < 4; ++i)
    {
        if (oper[i] > 0)
        {
            oper[i] -= 1;
            DFS(idx + 1, renew_sum(idx, i, sum));
            oper[i] += 1;
        }
    }
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> num[i];
    }
    for (int i = 0; i < 4; ++i)
    {
        cin >> oper[i];
    }
}

void solve()
{
    input();
    DFS(0, num[0]);
    cout << MAX << '\n'
         << MIN;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();

    return 0;
}