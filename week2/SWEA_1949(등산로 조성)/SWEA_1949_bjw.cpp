#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
N*N의 지도
지도 한 칸마다 높이 값
k: 최대로 깎을 수 있는 깊이
깎을 때 높이는 0이 되어도 된다
무조건 높은 곳-> 낮은 곳으로만 등산로 건설 가능
높이 같아도 등산로 건설 불가
 */

/* 구하는 것
만들 수 있는 가장 긴 등산로 길이
 */

/* 아이디어
최대 높이 지형 찾기
공사 실행 가능한 경우:
    - 가려는 지형 높이 >=  현재 지형 높이
    - 가려는 지형 높이 <  현재 지형 높이 + k
    - 공사 한번도 안했어야 함
DFS 인자: 좌표, 등산로 길이,공사 여부
더 이상 못 갈 경우 최대 길이 갱신
*/

// 필요한 변수들

// 지도 한 변의 길이
int n;
// 최대로 깎을 수 있는 깊이
int k;
// 정답
int ans = 0;
// 지형 높이 최대값
int h = 0;
// 지도
int field[8][8];
// 방향 배열
pair<int, int> dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
// 방문 여부
int visited[8][8];

void input()
{
    // 변수 초기화
    ans = 0;
    h = 0;

    cin >> n >> k;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> field[i][j];
            // visited 모두 0으로 초기화
            visited[i][j] = 0;
            // 가장 높은 지형 높이값 찾기
            h = max(h, field[i][j]);

            /*
            ->높이 값을 계속 갱신해야 되기 때문에
            입력값들을 입력 받으면서 가장 높은 지형의 위치를
            동시에 저장할 수는 없다.
            */
        }
    }
}

/*
y,x: 좌표
len: 등산로 길이
flag: 공사 여부
*/
void DFS(int y, int x, int len, int flag)
{
    for (int i = 0; i < 4; ++i)
    {
        int ny = y + dir[i].first;
        int nx = x + dir[i].second;

        if (0 <= ny && ny < n &&
            0 <= nx && nx < n &&
            !visited[ny][nx])
        {

            visited[ny][nx] = 1;

            // 공사 진행 후 갈 수 있는 경우
            if (field[ny][nx] >= field[y][x] &&
                field[ny][nx] < field[y][x] + k &&
                !flag)
            {
                int tmp = field[ny][nx];

                // 깎을 지형를 현재 지형 높이-1 의 높이까지만 깎는다.
                // 더 깎아봤자 의미가 없기 때문
                field[ny][nx] = field[y][x] - 1;
                DFS(ny, nx, len + 1, 1);

                // 지형 높이 원래대로 돌려놓기
                field[ny][nx] = tmp;
            }
            // 공사 안하고 그냥 갈 수 있는 경우
            else if (field[ny][nx] < field[y][x])
            {
                DFS(ny, nx, len + 1, flag);
            }
            // 그냥 못가는 경우
            else
            {
                ans = max(len, ans);
            }

            visited[ny][nx] = 0;
        }
    }
}

void solve()
{
    input();

    // 지형이 가장 높은 지형일 때 등산로 찾기
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (h == field[i][j])
            {
                visited[i][j] = 1;
                DFS(i, j, 1, 0);
                visited[i][j] = 0;
            }
        }
    }

    cout << ans << '\n';
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
        cout << '#' << i << ' ';
        solve();
    }

    return 0;
}