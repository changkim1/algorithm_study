#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

int n, t;
int dat[17]; // 요리팀 저장할 배열 0, 1로 팀 구분
int ans = 21e8;

int map[17][17]; // 요리별 시너지 저장

void	solve()
{
	int aval = 0; // a요리의 총 시너지 저장
	int bval = 0; // b요리의 총 시너지 저장
	for (int i = 0; i < n; i++) // i번 요리 기준
	{
		int val = 0;
		for (int j = 0; j < n; j++)
		{
			if (dat[i] == dat[j]) // 만약 i와 j가 같은 팀이라면
				val += map[i][j]; // val에 추가해주기 -> 한바퀴만 돌아도 어차피 j번이 기준이 될 때 i가 추가될 거기 때문에 괜찮음.
		}
		if (!dat[i])
			aval += val; // dat가 0이라면 a팀 시너지에 추가
		else
			bval += val; // 1이라면 b팀 시너지에 추가
	}
	int solve_res = abs(aval - bval);
	// for (int i = 0; i < n; i++)
	// 	cout << dat[i] << ' ';
	// cout << endl;
	// printf("a : %d b : %d res : %d ans : %d\n", aval, bval, solve_res, ans);
	if (ans > solve_res)
		ans = solve_res; // ans 갱신
}

void	make_team(int idx, int now)
{
	if (idx == n / 2) // 팀의 숫자가 전체의 반이 되면
	{
		solve(); // 계산하는 함수로 넘어가기
		return ;
	}
	for (int i = now + 1; i < n; i++)
	{
		dat[i] = 1; // dat에 1을 넣고 빼고 하는 식으로 팀을 구성하기
		make_team(idx + 1, i);
		dat[i] = 0;
	}
}

int main()
{
	cin >> t;
	for (int z = 0; z < t; z++)
	{
		ans = 21e8; // 최솟값 저장할 변수
		memset(dat, 0, sizeof(dat)); 
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cin >> map[i][j];
		}
		make_team(0, -1);
		printf("#%d %d\n", z + 1, ans);
	}

}