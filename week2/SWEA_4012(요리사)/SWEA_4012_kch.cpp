#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

int n, t;
int dat[17];
int ans = 21e8;

int map[17][17];

void	solve()
{
	int aval = 0;
	int bval = 0;
	for (int i = 0; i < n; i++)
	{
		int val = 0;
		for (int j = 0; j < n; j++)
		{
			if (dat[i] == dat[j])
				val += map[i][j];
		}
		if (!dat[i])
			aval += val;
		else
			bval += val;
	}
	int solve_res = abs(aval - bval);
	// for (int i = 0; i < n; i++)
	// 	cout << dat[i] << ' ';
	// cout << endl;
	// printf("a : %d b : %d res : %d ans : %d\n", aval, bval, solve_res, ans);
	if (ans > solve_res)
		ans = solve_res;
}

void	make_team(int idx, int now)
{
	if (idx == n / 2)
	{
		solve();
		return ;
	}
	for (int i = now + 1; i < n; i++)
	{
		dat[i] = 1;
		make_team(idx + 1, i);
		dat[i] = 0;
	}
}

int main()
{
	cin >> t;
	for (int z = 0; z < t; z++)
	{
		ans = 21e8;
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