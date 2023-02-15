#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int t;
int fee[4];
int month_plan[13];
int ans;

void	solve(int mon, int sum)
{
	if (mon > 12)
	{
		ans = min(ans, sum);
		// printf("solvesum = %d\n", ans);
		return ;
	}
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			sum += (fee[0] * month_plan[mon]);
			solve(mon + 1, sum);
			sum -= (fee[0] * month_plan[mon]);
		}
		else if (i == 1)
		{
			sum += fee[1];
			solve(mon + 1, sum);
			sum -= fee[1];
		}
		else if (i == 2)
		{
			sum += fee[2];
			solve(mon + 3, sum);
			sum -= fee[2];
		}
	}
}

int main(void)
{
	cin >> t;
	for (int a = 0; a < t; a++)
	{
		ans = (int)21e8;
		for (int i = 0; i < 4; i++)
			cin >> fee[i];
		for (int i = 1; i < 13; i++)
			cin >> month_plan[i];
		solve(1, 0);
		// printf("sum = %d\n", ans);
		ans = min(ans, fee[3]);
		printf("#%d %d\n", a + 1, ans);
	}
	
}