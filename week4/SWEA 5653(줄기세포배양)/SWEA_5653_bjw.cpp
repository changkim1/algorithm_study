#include <bits/stdc++.h>
using namespace std;
 
/* 주어진 조건
세포는 네모네모하다.
각 세포는 생명력 수치가 존재함.
생명력 수치만큼 비활성 상태로 존재하며,
그 뒤에 다시 생명력 수치만큼 활성 상태로 존재한다.
그 뒤 세포는 죽는다.
죽어도 소멸되는 것이 아니라 그 공간을 그대로 차지한다.
 
활성화된 줄기 세포는 첫 1시간 동안 4방향으로 퍼진다.
이미 세포가 있는 곳에는 세포가 퍼지지 못함.
동시 번식 시 생명력 수치가 높은 줄기 세포가 해당 자리를 먹는다.
 */
 
/* 구하는 것
k시간 후 살아있는 줄기 세포의 총 개수
 */
 
/* 아이디어
전체 맵 크기: -149<=y,x<=200(0<=y,x<350)
우선 순위 큐에 세포 좌표 넣기
큐 내에서 세포는 상태가 바뀌는 시각 순으로 정렬됨
시간 진행시키며 사이클 돌리기
세포가 활성화 될 때 세포의 상태만 바꾸고 다시 큐에 집어넣는다.
세포가 죽은 경우 큐에 다시 넣지 않는다.
k시간 이후에 큐 사이즈가 곧 답이 된다.
우선 순위 큐 비교 연산자 설정을 통해 동시 번식 자동적으로 처리(형규님 아이디어)
 */
 
// 변수
struct Cell
{
    int y;         // y 좌표
    int x;         // x 좌표
    int life_span; // 생명력 수치
    int endTime;   // 상태 변하는 시간
    int active;    // 셀의 상태
                   //(-1: 죽음 / 0: 빈 셀 / 1: 비활성 / 2: 활성)
 
    bool operator<(Cell next) const
    {
        if (endTime == next.endTime)
        {
            return life_span < next.life_span;
        }
        return endTime > next.endTime;
    }
};
 
int n;                                                      // 세로
int m;                                                      // 가로
int k;                                                      // 끝나는 시간
Cell MAP[350][350] = {0};                                   // 배양 용기
priority_queue<Cell> living_cells;                          // 세포 상태 업데이트를 위한 우선순위 큐
queue<Cell> new_born;                                       // 번식용 큐
pair<int, int> dir[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; // 방향배열(상좌하우)
 
// 함수
 
// 초기화
void init()
{
    for (int i = 0; i < 350; ++i)
    {
        memset(MAP[i], 0, sizeof(MAP[i]));
    }
 
    while (!living_cells.empty())
    {
        living_cells.pop();
    }
 
    while (!new_born.empty())
    {
        new_born.pop();
    }
}
 
// 입력
void input()
{
    cin >> n >> m >> k;
 
    init();
 
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int tmp;
            cin >> tmp;
 
            int y = i + 150;
            int x = j + 150;
 
            if (tmp == 0)
                continue;
 
            MAP[y][x] = {y, x, tmp, tmp, 1};
            living_cells.push(MAP[y][x]);
        }
    }
}
 
// 세포 상태 갱신
void status_update(int cur_time)
{
    while (!living_cells.empty())
    {
        int y = living_cells.top().y;
        int x = living_cells.top().x;
        Cell cur_cell = MAP[y][x];
 
        // living_cell에 있는 큐에서 endTime==cur_time인 세포들만 꺼내기
        if (cur_cell.endTime != cur_time)
            break;
 
        living_cells.pop();
 
        // 비활성화된 상태면 활성화된 상태로 바꾸고 번식큐,리빙큐에 넣기
        if (cur_cell.active == 1)
        {
            cur_cell.active = 2;
            cur_cell.endTime = cur_time + cur_cell.life_span;
            living_cells.push(cur_cell);
            new_born.push(cur_cell);
        }
        // 활성화된 상태면 사망
        else if (cur_cell.active == 2)
        {
            cur_cell.active = -1;
        }
 
        // 세포 상태 업데이트
        MAP[y][x] = cur_cell;
    }
}
 
// 번식
void breeding(int cur_time)
{
    while (!new_born.empty())
    {
        int y = new_born.front().y;
        int x = new_born.front().x;
        Cell cur_cell = MAP[y][x];
 
        // end_time-cur_time==life_span-1인 세포만 꺼내서 번식 시키기
        //(전 사이클에서 번식큐에 들어온 세포)
        if (cur_cell.endTime - cur_time != cur_cell.life_span - 1)
            break;
 
        new_born.pop();
 
        // 퍼질 시
        for (int i = 0; i < 4; ++i)
        {
            int ny = y + dir[i].first;
            int nx = x + dir[i].second;
 
            // MAP 범위 벗어나면 패스
            // if (ny < 0 || 650 <= ny || nx < 0 || 650 <= nx)
            //     continue;
 
            Cell next_cell = MAP[ny][nx];
 
            // 근처 셀이 빈 셀이 아닌 경우
            // 우선 순위 큐 정렬 조건 때문에 동시 번식의 경우는 고려 안해도 된다.
            if (next_cell.active != 0)
                continue;
 
            // 빈 셀인 경우
            // 세포 생성
            MAP[ny][nx] = {ny, nx, cur_cell.life_span, cur_time + cur_cell.life_span, 1};
            // living_cell에 넣기
            living_cells.push(MAP[ny][nx]);
            continue;
        }
    }
}
 
void cycle(int cur_time)
{
    status_update(cur_time);
    breeding(cur_time);
}
 
void solve()
{
    input();
    for (int i = 1; i <= k; ++i)
    {
        cycle(i);
    }
    cout << living_cells.size() << '\n';
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