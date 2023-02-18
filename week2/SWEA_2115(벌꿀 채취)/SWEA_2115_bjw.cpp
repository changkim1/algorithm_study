#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
n*n 개의 벌통
일꾼 2명
각 일꾼은 가로로 연속되는 m개의 벌통을 선택 가능
겹치면 안됨
한 명당 채취할 수 있는 꿀 최대 양은 c
수익은 각 꿀의 양의 제곱의 합
m칸의 꿀의 총량이 c를 넘어가면 총량이 c를 넘어가지 않도록
일부만 선택해야 한다
 */

/* 구하는 것
얻을 수 있는 최대 수익
 */

/* 아이디어
재귀로 벌통 m개씩 훑기
 */

// 변수들
int n;
int m;                   // 선택 가능한 벌통 개수
int c;                   // 한 명당 채취할 수 있는 꿀 최대 양
int ans;                 // 출력할 답
int honey[10][10] = {0}; // 벌통 당 꿀의 양

// 함수

void input();                          // 입력
int max_earn(int coor);                /*
                                        꿀 채취량 총량이 c를 넘지 않으면서
                                        꿀을 채취했을 때의 최대 수익 계산
                                        coor=y*n+x 의 식으로 계산되는 값으로,
                                        좌표를 1개의 숫자로 나타내기 위한 값이다.
                                        */
void DFS(int coor, int sum, int harv); // 문제에서 요구하는 최대 수익을 얻는 경우 찾는 DFS
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
    cin >> n >> m >> c;
    ans = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> honey[i][j];
        }
    }
}

int max_earn(int coor)
{
    int ret = 0;
    int total = 0; // 채취한 꿀 총량
    int earn = 0;  // 채취한 꿀로 얻는 수익
    int y = coor / n;
    int x = coor % n;
    vector<int> harvested; // m개의 벌통에 들어있는 꿀의 양 저장

    for (int i = x; i < x + m; ++i)
    {
        int cur = honey[y][i];
        harvested.push_back(cur);
        total += cur;
        earn += cur * cur;
    }

    // 모든 꿀통의 꿀 총량이 c보다 작을 경우 함수 끝내기
    if (total <= c)
    {
        return earn;
    }

    sort(harvested.begin(), harvested.end(), greater<int>()); // 내림차순으로 정렬

    for (int i = 0; i < harvested.size(); ++i) // 문제에서 주어진 조건 충족할 때 최대 수익 갱신
    {
        total = 0;
        earn = 0;

        for (int j = i; j < harvested.size(); ++j)
        {
            int cur = harvested[j];
            if (total + cur > c)
            {
                continue;
            }

            total += cur;
            earn += cur * cur;

            if (total == c)
            {
                break;
            }
        }

        if (earn < ret)
        {
            return ret;
        }

        ret = max(ret, earn);
    }

    return ret;
}

void DFS(int coor, int sum, int harv)
{
    if (harv == 2)
    {
        ans = max(ans, sum);
        return;
    }

    if (coor >= n * n)
    {
        return;
    }

    int y = coor / n;
    int x = coor % n;

    // 채취 안 하는 경우
    DFS(coor + 1, sum, harv);

    // 해당 위치로부터 가로로 m개의 벌통이 존재하지 않을 경우
    // 채취가 불가능 하므로 다음 위치로 넘어간다
    if (x + m > n)
    {
        return;
    }

    // 채취 하는 경우
    DFS(coor + m, sum + max_earn(coor), harv + 1);
}

void solve()
{
    input();
    DFS(0, 0, 0);
    cout << ans << '\n';
}