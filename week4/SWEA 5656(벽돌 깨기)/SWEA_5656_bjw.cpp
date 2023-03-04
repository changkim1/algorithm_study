#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
구슬 n번 쏨
구슬에 맞은 벽돌은 터짐
벽돌에 적힌 숫자만큼의 범위 내의 벽돌 다 터짐
->연쇄 반응 가능
벽돌 밑에 빈 공간이 있으면 테트리스마냥 밑으로 떨어짐
 */

/* 구하는 것
최대한 많은 벽돌을 깨뜨렸을 때 남은 벽돌의 개수
 */

/* 아이디어
![image](https://user-images.githubusercontent.com/87963766/222869406-76f0b372-4b3d-48a0-8660-29925648cb3d.png)

벽돌 쏠 곳 고르기
폭발
벽돌 내리기
 */

// 변수
int n;
int h, w;
int total = 0;                    // 전체 벽돌의 개수
int ans = 0;                      // 답
int MAP[15][12] = {0};            // 입력 받을 원상태의 벽돌 상태
int COPY[15][12] = {0};           // 발사 테스트를 진행할 배열
int visited[15][12] = {0};        // 폭파 진행 시 필요한 방문 배열
vector<int> sequence;             // 발사 시퀀스 저장
pair<int, int> dir[4] = {{-1, 0}, // 방향배열
                         {0, -1},
                         {1, 0},
                         {0, 1}};

// 함수

// 입력
void input()
{
    cin >> n >> w >> h;

    ans = 0;
    total = 0;

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 0)
                continue;

            total++;
        }
    }
}

// 원상태 맵 복사
void copyMap()
{
    for (int i = 0; i < h; ++i)
    {
        memcpy(COPY[i], MAP[i], sizeof(MAP[i]));
    }
}

// 좌표(y,x)의 벽돌 폭발. 해당 벽돌 폭발로 터진 총 벽돌 수 반환
// BFS로 풀자니 visited를 함수 실행할 때마다 선언해야 하는데
// 그거 때문에 실행시간이 오히려 늘어남
// 그래서 DFS로 풀음
int boom(int y, int x)
{
    int broken_bricks = 0;
    int num = COPY[y][x];

    visited[y][x] = 1;
    COPY[y][x] = 0;
    broken_bricks += 1;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 1; j < num; ++j)
        {
            int ny = y + dir[i].first * j;
            int nx = x + dir[i].second * j;

            // 범위 벗어난 경우
            if (ny < 0 || h <= ny || nx < 0 || w <= nx)
                break;

            // 이미 방문한 곳인 경우
            if (visited[ny][nx])
                continue;

            // 벽돌이 없는 경우
            if (COPY[ny][nx] == 0)
                continue;

            broken_bricks += boom(ny, nx);
        }
    }

    visited[y][x] = 0;

    return broken_bricks;
}

// 빈 공간 위에 있는 벽돌 모두 떨어뜨리기
// 밑에서부터 하나씩 아래로 떨어뜨리는 방식
void dropBlock()
{
    for (int i = 0; i < w; ++i)
    {
        // 이전에 떨어진 벽돌의 위치
        int under = h;
        for (int j = h - 1; j >= 0; --j)
        {
            if (COPY[j][i] == 0)
                continue;

            int tmp = COPY[j][i];
            COPY[j][i] = 0;

            COPY[under - 1][i] = tmp;
            under -= 1;
        }
    }
}

// 구슬 발사
int shoot()
{
    // 맵 복사
    copyMap();

    int broken_bricks = 0; // 이번 시퀀스 진행 후 남은 벽돌의 개수

    // 시퀀스에 맞춰 구슬 발사
    for (int i : sequence)
    {
        int y = 0; // 구슬을 발사 했을 때 벽돌과 처음 만나는 지점의 높이
        for (; y < h; ++y)
        {
            if (COPY[y][i] > 0)
                break;
        }

        // 해당 열에 벽돌 없을 시
        if (y == h)
            continue;

        broken_bricks += boom(y, i);
        dropBlock();
    }

    return broken_bricks;
}

// 모든 가능한 시퀀스들에 대해 시뮬레이션을 실행하는 DFS
void shootingSequence(int cnt)
{
    if (cnt == n)
    {
        ans = max(ans, shoot());
        return;
    }

    for (int i = 0; i < w; ++i)
    {
        sequence.push_back(i);
        shootingSequence(cnt + 1);
        sequence.pop_back();
    }
}

void solve()
{
    input();
    shootingSequence(0);
    // 남은 벽돌 개수 출력
    cout << total - ans << '\n';
}

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