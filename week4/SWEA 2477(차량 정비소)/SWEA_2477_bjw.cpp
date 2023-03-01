#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
고객이 이용한 접수 창구 번호, 정비 창구 번호로 지갑 놓고 간 고객을 특정하려고 함
각 창구의 담장자 별로 처리 시간이 다르다
고객이 정비소 도착 시 빈 접수 창구에 가서 고장 접수함
없으면 기다림

-접수 창구의 우선 순위
고객 번호가 낮은 순
창구 번호가 작은 순

-정비 창구의 우선 순위
먼저 온 고객
동시 접수한 고객이 2명 이상일 시 이용했던 접수 창구 번호가 작은 순
창구 번호가 작은 순
 */

/* 구하는 것
지갑을 분실한 고객과 같은 접수 창구와 같은 정비 창구를 이용한
고객들의 고객 번호들의 총합
없으면 -1 출력
 */

/* 아이디어
그냥 개빡구현하는 개빡치는 문제다.
시간 갱신하면서 각 시각에 어떤 상황이 되는지를 시뮬레이션 한다.

필요한 큐들
-접수 창구 손님 진입 우선순위 큐->정비소 도착 시간 기록,해당 시간 돼야 빠져나올 수 있도록 함
-비는 접수 창구 우선순위 큐
-정비 창구 손님 진입 우선순위 큐->접수 끝나는 시간 기록,해당 시간 돼야 빠져나올 수 있도록 함
-비는 정비 창구 우선순위 큐

각 접수 창구 별로 처리 종료 시각을 저장할 배열 필요

입력 시 그냥 접수 창구 진입 큐에 손님 다 넣기
대기 또는 해당 시간에 접수 끝나는 사람들 순서에 맞게 빈 창구에 넣기
정비 창구도 마찬가지

한 사이클
-빈 접수 창구 골라내기
-현재 창구 들어갈 수 있는 사람 최대한 넣기
-정비 창구에 대해서도 위 과정 반복
-정비 끝난 손님 정보로 ans 갱신

손님 정보 구조체 만들기
-손님 번호
-현재 들어간 창구 끝나는 시간
-들어간 접수 창구 번호
-들어간 정비 창구 번호
 */

// 변수
struct Info // 손님 정보
{
    int num;     // 손님 번호
    int endTime; // 현재 들어간 창구 끝나는 시간
    int recNum;  // 들어간 접수 창구 번호
    int repNum;  // 들어간 정비 창구 번호
};

struct Reception_cmp // 접수 창구 진입 큐 정렬 기준
{
    bool operator()(Info a, Info b) const
    {
        return a.num > b.num;
    }
};

struct Repair_cmp // 정비 창구 진입 큐 정렬 기준
{
    bool operator()(Info a, Info b) const
    {
        if (a.endTime == b.endTime)
        {
            return a.recNum > b.recNum;
        }
        return a.endTime > b.endTime;
    }
};
int n;                                                             // 접수 창구
int m;                                                             // 정비 창구
int a[10];                                                         // 접수 창구 직원 처리시간
int b[10];                                                         // 정비 창구 직원 처리시간
int k;                                                             // 차량 정비소 방문 고객 수
priority_queue<Info, vector<Info>, Reception_cmp> enter_reception; // 접수 창구 진입 큐
priority_queue<Info, vector<Info>, Repair_cmp> enter_repair;       // 정비 창구 진입 큐
priority_queue<Info, vector<Info>, Repair_cmp> out_repair;         // 종료 대기 큐
int reception_status[10] = {0};                                    // 접수 창구 상태
int repair_status[10] = {0};                                       // 정비 창구 상태
priority_queue<int, vector<int>, greater<int>> empty_reception;    // 빈 접수 창구 큐
priority_queue<int, vector<int>, greater<int>> empty_repair;       // 빈 정비 창구 큐
int A;                                                             // 지갑 두고간 고객이 이용한 접수 창구
int B;                                                             // 지갑 두고간 고객이 이용한 정비 창구
int ans;                                                           // 정답

// 함수

// 초기화
void init()
{
    while (!empty_reception.empty())
    {
        empty_reception.pop();
    }
    while (!empty_repair.empty())
    {
        empty_repair.pop();
    }
    ans = 0;
}

// 입력
void input()
{
    cin >> n >> m >> k >> A >> B;

    init();

    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }

    for (int i = 1; i <= m; ++i)
    {
        cin >> b[i];
    }

    for (int i = 1; i <= k; ++i)
    {
        int tmp;
        cin >> tmp;

        enter_reception.push({i, tmp, -1, -1});
    }
}

// 정비소에 사람 도착, 접수 창구에 손님 넣기
void costomer_arrive(int cur_time)
{
    // 접수 과정 끝난 창구 골라내기
    for (int i = 1; i <= n; ++i)
    {
        if (cur_time == reception_status[i])
        {
            reception_status[i] = 0; // 다음 테스트 케이스 시작 시 초기화를 염두한 코드
            empty_reception.push(i);
        }
    }

    // 지금 도착한 손님들 또는 대기 중인 손님들 빈 창구로 넣기
    while (!empty_reception.empty() &&
            !enter_reception.empty() &&
            enter_reception.top().endTime <= cur_time)
    {
        int cur_reception = empty_reception.top();
        empty_reception.pop();

        // 접수 창구 상태 갱신
        reception_status[cur_reception] = cur_time + a[cur_reception];

        Info cur_customer = enter_reception.top();
        enter_reception.pop();

        // 손님 정보 갱신
        cur_customer.endTime = cur_time + a[cur_reception];
        cur_customer.recNum = cur_reception;

        enter_repair.push(cur_customer);
    }
}

// 접수 창구->정비 창구
void reception_to_repair(int cur_time)
{
    // 정비 과정 끝난 창구 골라내기
    for (int i = 1; i <= m; ++i)
    {
        if (cur_time == repair_status[i])
        {
            repair_status[i] = 0; // 다음 테스트 케이스 시작 시 초기화를 염두한 코드
            empty_repair.push(i);
        }
    }

    // 접수 방금 끝난 손님들 또는 대기 중인 손님들 처리
    while (!empty_repair.empty() &&
            !enter_repair.empty() &&
            enter_repair.top().endTime <= cur_time)
    {
        int cur_repair = empty_repair.top();
        empty_repair.pop();

        // 정비 창구 상태 갱신
        repair_status[cur_repair] = cur_time + b[cur_repair];

        Info cur_customer = enter_repair.top();
        enter_repair.pop();

        // 손님 정보 갱신
        cur_customer.endTime = cur_time + b[cur_repair];
        cur_customer.repNum = cur_repair;

        out_repair.push(cur_customer);
    }
}

void out(int cur_time)
{
    while (!out_repair.empty() && out_repair.top().endTime == cur_time)
    {
        Info cur_customer = out_repair.top();
        out_repair.pop();

        // cout<<cur_customer.num<<' '<<cur_customer.recNum<<' '<<cur_customer.repNum<<'\n';

        // ans 갱신
        if (cur_customer.recNum == A && cur_customer.repNum == B)
        {
            ans += cur_customer.num;
        }
    }
}

// 손님 관리 큐 비었는지 여부 반환
bool every_queue_empty()
{
    return enter_reception.empty() && enter_repair.empty() && out_repair.empty();
}

void cycle(int cur_time)
{
    costomer_arrive(cur_time);
    reception_to_repair(cur_time);
    out(cur_time);
}

void solve()
{
    input();

    int cur_time = 0;
    while (!every_queue_empty())
    {
        cycle(cur_time);
        cur_time++;
    }

    if (ans == 0)
    {
        cout << -1 << '\n';
    }
    else
    {
        cout << ans << '\n';
    }
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
