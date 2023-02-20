#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
BC의 위치, 충전범위, 성능이 주어짐
충전 범위 겹치면 둘 중 하나를 선택해야함
한 BC에 두 명의 사용자가 접속하면 성능이 분배됨
총 이동시간 m
BC의 개수 a
m시간 동안의 이동 정보
 */

/* 구하는 것
모든 사용자가 충전한 양의 합의 최대값
 */

/* 아이디어
BFS로 각 시간의 상태를 우선순위 큐에 넣는다
큐에는 (A의 상태,B의 상태,시간)이 들어간다
여기서 사용자의 상태는 좌표값과 현재 충전량이 들어가야 한다.
매번 큐에서 원소를 뽑을 때마다 A,B와 BC들 간의 거리를 구해서
경우의 수를 고려해야 한다.
또한 BC의 정보를 담은 벡터도 따로 두어야 할 것이다.
사용자는 지도의 양 끝에서 출발함
우선순위 큐는 각 사용자의 충전량의 총합이 큰 게 먼저 온다.
시점이 m에 다다르면 BFS 종료
 */

// ------------------변수------------------

struct User // 사용자의 상태
{
    int y;   // y좌표
    int x;   // x좌표
    int sum; // 현재까지의 충전량
};

// BC의 정보
struct BC
{
    int y; // y좌표
    int x; // x좌표
    int c; // 충전 범위
    int p; // 성능
};

struct Status // 시점 t에서의 상태
{
    User statA; // 사용자 A의 상태
    User statB; // 사용자 B의 상태
    int t;      // 시점

    bool operator<(Status next) const
    {
        return statA.sum + statB.sum < next.statA.sum + next.statB.sum;
        return false;
    }
};

int m; // 총 이동시간
int a; // BC의 개수
pair<int, int> dir[5] = {{0, 0},
                         {-1, 0},
                         {0, 1},
                         {1, 0},
                         {0, -1}}; // 방향배열(정지,상우하좌)
vector<BC> bc_list;                // BC들의 정보를 담을 벡터
vector<int> A_move, B_move;        // A,B의 이동정보
priority_queue<Status> pq;         // 시점 별 상태를 담을 큐(A의 상태,B의 상태,시점)

// ------------------함수------------------

// 초기화
void init();
// 입력
void input();
// 특정 BC(num)와의 거리
int dist(int num, int y, int x);
// 사용자가 특정 BC(num)의 범위 내에 있는 지 여부를 반환
bool inside(int num, int y, int x);
// 다음 시점에 올수 있는 모든 상황 계산
void nextSituation(Status nStat);
void BFS();
void solve();

// ------------------main------------------

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

//------------------함수 정의------------------

void init()
{
    // 벡터 비우기
    bc_list.clear();
    A_move.clear();
    B_move.clear();

    // 벡터 크기 초기화
    bc_list.resize(a);
    A_move.resize(m);
    B_move.resize(m);

    // 큐 비우기
    while (!pq.empty())
    {
        pq.pop();
    }
}

void input()
{
    cin >> m >> a;

    init();

    // A 이동 경로
    for (int i = 0; i < m; ++i)
    {
        cin >> A_move[i];
    }

    // B 이동 경로
    for (int i = 0; i < m; ++i)
    {
        cin >> B_move[i];
    }

    // BC 정보
    for (int i = 0; i < a; ++i)
    {
        int y;
        int x;
        int c;
        int p;

        cin >> x >> y >> c >> p;

        bc_list[i] = {y, x, c, p};
    }
}

int dist(int num, int y, int x)
{
    return abs(bc_list[num].y - y) + abs(bc_list[num].x - x);
}

bool inside(int num, int y, int x)
{
    return dist(num, y, x) <= bc_list[num].c;
    return false;
}

void nextSituation(Status nStat)
{
    User nA = nStat.statA; // A의 다음 시점의 상태
    User nB = nStat.statB; // B의 다음 시점의 상태
    int t = nStat.t + 1;   // 다음 시점

    vector<int> inA(a); // 각 BC의 범위에 A가 들어가는 지 여부 저장
    vector<int> inB(a); // 각 BC의 범위에 B가 들어가는 지 여부 저장

    int sA = 1; // A가 어떤 BC 범위 안에도 있지 않으면 1
    int sB = 1; // B가 어떤 BC 범위 안에도 있지 않으면 1

    for (int i = 0; i < a; ++i)
    {
        if (inside(i, nA.y, nA.x))
        {
            sA = 0;
            inA[i] = 1;
        }
        if (inside(i, nB.y, nB.x))
        {
            sB = 0;
            inB[i] = 1;
        }
    }

    // 아래 반복문 내에서 임시적으로 쓰일 상태 변수들
    User tmpA = nA, tmpB = nB;

    // 모든 가능한 경우의 수들을 적용
    if (sA)
    {
        if (sB)
        {
            pq.push({nA, nB, t});
        }
        else
        {
            for (int i = 0; i < a; ++i)
            {
                if (!inB[i])
                    continue;

                tmpB = nB;
                tmpB.sum += bc_list[i].p;
                pq.push({nA, tmpB, t});
            }
        }
    }
    else
    {
        for (int i = 0; i < a; ++i)
        {
            if (!inA[i])
                continue;

            tmpA = nA;

            if (sB)
            {
                tmpA.sum += bc_list[i].p;
                pq.push({tmpA, nB, t});
            }
            else
            {
                for (int j = 0; j < a; ++j)
                {
                    if (!inB[j])
                        continue;

                    tmpA = nA;
                    tmpB = nB;

                    // 같은 BC일 경우 성능 분배
                    if (i == j)
                    {
                        tmpA.sum += bc_list[i].p / 2;
                        tmpB.sum += bc_list[j].p / 2;
                    }
                    else
                    {
                        tmpA.sum += bc_list[i].p;
                        tmpB.sum += bc_list[j].p;
                    }
                    pq.push({tmpA, tmpB, t});
                }
            }
        }
    }
}

void BFS()
{
    pq.push({{1, 1, 0}, {10, 10, 0}, -1});

    while (!pq.empty())
    {
        User A = pq.top().statA; // A의 상태
        User B = pq.top().statB; // B의 상태
        int t = pq.top().t;      // 시점

        pq.pop();

        // 현재 원소의 시점이 m일 시
        // 충전량 총합이 최대인 경우일 것이므로 함수 종료
        if (t == m)
        {
            cout << A.sum + B.sum << '\n';
            return;
        }

        User nA; // A의 다음 시점의 상태
        User nB; // B의 다음 시점의 상태
        if (t == -1)
        {
            nA = A;
            nB = B;
        }
        else
        {
            nA = {A.y + dir[A_move[t]].first,
                  A.x + dir[A_move[t]].second,
                  A.sum};

            nB = {B.y + dir[B_move[t]].first,
                  B.x + dir[B_move[t]].second,
                  B.sum};
        }

        nextSituation({nA, nB, t});
    }
}

void solve()
{
    input();
    BFS();
}