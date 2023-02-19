#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
n*n의 셀
k개의 미생물 군집
가장자리 셀들에 특수약품 있고 미생물 없음
각 미생물 군집의 위치, 군집 내 미생물 수, 이동방향 주어짐
1시간마다 이동 방향으로 이동
가장자리 도착 시 군집 내 미생물 절반 사망, 이동방향 반대로 바뀜
이동 후 군집이 합쳐질 수 있음.
이동 방향은 미생물 수가 많은 군집의 이동 방향
m시간 동안 미생물 군집들을 격리
 */

/* 구하는 것
m시간 후에 남아있는 미생물 수의 총합
 */

/* 아이디어
군집들의 정보(현재 위치,수,이동방향,시점)를 담은 벡터 생성
군집의 벡터 내 index가 군집의 넘버다.
순회하며 정보 갱신
가려는 셀에 군집이 있을 경우
    - 시점이 같을 경우: 맵의 군집 표시를 덮어버림
    - 해당 셀의 군집의 시점이 이동하는 군집의 시점+1인 경우:
        해당 셀의 군집은 이미 이동했다는 뜻이므로 합쳐진다.
군집이 합쳐지는 경우를 고려해 dat를 두어 dat가 1인 군집만 검사한다.
3개 이상의 군집이 병합되는 경우를 잘 처리해야 한다.
 */

// 변수

struct Colony
{
    // 현재 위치의 y좌표
    int y;
    // 현재 위치의 x좌표
    int x;
    // 군집 내 미생물 수
    int num;
    // 이동 방향
    int dir;
    /*
    한 사이클(1시간) 내에서 군집 병합 시
    가장 큰 군집의 미생물 수
    */
    int MAX;
};

int n;
// 미생물 군집 개수
int k;
// 격리 시간
int m;
// 군집의 위치 표시
int cell[100][100] = {0};
// 각 군집의 정보
vector<Colony> info;
// 군집의 존재 유무
vector<int> dat;
// 방향배열(상좌하우)
pair<int, int> direction[4] = {{-1, 0},
                               {0, -1},
                               {1, 0},
                               {0, 1}};

// 함수

// 초기화
void init();
// 입력
void input();
// 살아있는 미생물 수 총합 반환
int sum();
// 1시간 동안의 상태 변화 갱신
void cycle();
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

    // system("pause");
    return 0;
}

void init()
{
    info.clear();
    dat.clear();

    info.resize(k + 1);
    dat.resize(k + 1);

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            cell[i][j] = 0;
        }
    }
}

void input()
{
    cin >> n >> m >> k;

    init();

    for (int i = 1; i <= k; ++i)
    {
        int y;
        int x;
        int num;
        int dir;

        cin >> y >> x >> num >> dir;

        cell[y][x] = i; // 셀에 군집 넘버 표시

        if (dir == 2)
        {
            dir = 3;
        }
        else if (dir == 3)
        {
            dir = 2;
        }

        dir -= 1;

        info[i] = {y, x, num, dir, num};
        dat[i] = 1;
    }
}

int sum()
{
    int ret = 0;

    for (int i = 1; i <= k; ++i)
    {
        if (!dat[i])
        {
            continue;
        }

        ret += info[i].num;
    }

    return ret;
}

void cycle()
{
    for (int i = 1; i <= k; ++i)
    {
        // 병합되거나 소멸된 군집인 경우 continue
        if (!dat[i])
        {
            continue;
        }

        int y = info[i].y;
        int x = info[i].x;
        int num = info[i].num;
        int dir = info[i].dir;
        int MAX = info[i].MAX;

        int ny = y + direction[dir].first;
        int nx = x + direction[dir].second;
        // 이동할 좌표에 현재 존재하는 군집
        int nc = cell[ny][nx];

        // 원래 있던 셀의 군집 정보 삭제
        // 단, 앞의 군집이 해당 셀로 먼저 이동하지 않았을 경우에만
        if (cell[y][x] == i)
        {
            cell[y][x] = 0;
        }

        // 가장자리에 도달 예정인 경우
        if (ny == 0 || ny == n - 1 || nx == 0 || nx == n - 1)
        {
            dir = (dir + 2) % 4; // 이동 방향 반전
            num /= 2;            // 미생물 수 "타노스"
        }

        // 군집이 소멸된 경우
        if (num == 0)
        {
            dat[i] = 0;
            continue;
        }

        // 이동하려는 셀에 존재하는 군집 정보 갱신
        cell[ny][nx] = i;

        // 이동하려는 셀에 군집이 있고,
        // 해당 군집의 넘버가 작으면 해당 셀의 군집은
        // 이미 이동한 군집이므로 병합
        if (0 < nc && nc < i)
        {
            dat[nc] = 0;            // 원래 있던 셀 소멸
            num += info[nc].num;    // 미생물 수 병합
            if (info[nc].MAX > MAX) // 방향 갱신. 비교 시 반드시 MAX값으로 비교해야 한다.
            {
                dir = info[nc].dir;
                MAX = info[nc].MAX;
            }
        }

        // 정보 갱신
        info[i] = {ny, nx, num, dir, MAX};
    }

    // MAX값을 다음 사이클을 위해 초기화
    for (int i = 1; i <= k; ++i)
    {
        info[i].MAX = info[i].num;
    }
}

void solve()
{
    input();

    for (int i = 0; i < m; ++i)
    {
        cycle();
    }

    cout << sum() << '\n';
}