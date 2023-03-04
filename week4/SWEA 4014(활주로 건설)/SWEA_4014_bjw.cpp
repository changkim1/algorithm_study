#include <bits/stdc++.h>
using namespace std;

/* 주어진 조건
n*n의 절벽 지대 높이 정보
경사로의 길이 x가 주어짐
높이 차이가 1,
낮은 지형의 높이가 x만큼 연속될 때
경사로 설치 가능
경사로를 설치할 수 있는 열 또는 행은 활주로 건설 가능
 */

/* 구하는 것
활주로를 건설할 수 있는 경우의 수
 */

/* 아이디어
![image](https://user-images.githubusercontent.com/87963766/222869106-46f14281-4478-4969-9b08-ea2fbb5bc0f7.png)

prev_updown
cur_updown
위 두 변수로 현재 지형 상태 파악 가능

시작 지점에서 prev_updown=0,dist=1
높이값 같으면 dist 1씩 늘려주기

높이값 차이가 1보다 클 경우 활주로 건설 불가능

높이 변할 시 cur_updown 갱신 및 통과 여부 체크
높이가 올라가면 cur_updown=1
높이가 내려가면 cur_updown=1


1. 첫 내리막
prev_updown*cur_updown=0 && cur_updown==-1-> 통과

2. 첫 오르막
prev_updown*cur_updown=0 && cur_updown==1-> dist>=x면 통과

3. 2연속 오르막 또는 2연속 내리막
prev_updown*cur_updown=1 -> dist>=x면 통과

4. 내리막-오르막
prev_updown * cur_updown = -1 && prev_updown = -1 -> dist >= 2*x면 통과

5. 오르막-내리막
prev_updown * cur_updown = -1 && prev_updown = 1-> 통과

통과 후 cur_updown을 prev_updown값으로 갱신

마지막 인덱스는 반복문 내에서 다룰 수 없기에 끝나고 따로 처리해야함
여기서 내리막인 경우 dist>=x면 통과
 */

// 변수
int n; // 지도 한 변의 크기
int x; // 경사로 길이
int MAP[20][20];
int ans = 0;

// 함수

// 입력
void input()
{
    cin >> n >> x;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> MAP[i][j];
        }
    }
}

// mode == 0: row / mode == 1: col
int lineCheck(int mode, int idx)
{
    int prev_updown = 0;
    int cur_updown = 0;
    int dist = 1;

    for (int i = 1; i < n; ++i)
    {
        int prev_height;
        int cur_height;

        // 세로
        if (mode)
        {
            prev_height = MAP[i - 1][idx];
            cur_height = MAP[i][idx];
        }
        // 가로
        else
        {
            prev_height = MAP[idx][i - 1];
            cur_height = MAP[idx][i];
        }

        // 높이 같은 경우
        if (prev_height == cur_height)
        {
            ++dist;
            continue;
        }
        // 높이 차이가 1보다 클 경우
        else if (abs(prev_height - cur_height) > 1)
        {
            return 0;
        }
        // 높이가 내려갈 경우
        else if (prev_height > cur_height)
        {
            cur_updown = -1;
        }
        // 높이가 올라갈 경우
        else if (prev_height < cur_height)
        {
            cur_updown = 1;
        }

        int state = prev_updown * cur_updown; // 지형 상태 나타내는 변수

        // 통과 안되는 경우만 따짐

        if (state == 0 && cur_updown == 1 && dist < x)
        {
            return 0;
        }

        if (state == 1 && dist < x)
        {
            return 0;
        }

        if (state == -1 && prev_updown == -1 && dist < 2 * x)
        {
            return 0;
        }

        // 상태 변수 초기화
        prev_updown = cur_updown;
        dist = 1;
    }

    // 마지막 인덱스 처리
    if (prev_updown == -1 && dist < x)
        return 0;

    return 1;
}

void solve()
{
    // 초기화
    ans = 0;
    input();
    // 모든 행,열에 대해 체크
    for (int i = 0; i < n; ++i)
    {
        ans += lineCheck(0, i);
        ans += lineCheck(1, i);
    }
    cout << ans << '\n';
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
