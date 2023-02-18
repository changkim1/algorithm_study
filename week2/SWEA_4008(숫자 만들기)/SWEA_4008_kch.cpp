#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

int oper_num[4];
int oper_num_check[4];
vector<int> oper_path;
vector<int> num;

int n, t, res;
int Max = -21e8, Min = 21e8;

int cal()
{
	int sum = num[0];
	for (int i = 0; i < oper_path.size(); i++)
	{
		if (oper_path[i] == 0)
			sum += num[i + 1];
		else if (oper_path[i] == 1)
			sum -= num[i + 1];
		else if (oper_path[i] == 2)
			sum *= num[i + 1];
		else if (oper_path[i] == 3)
			sum /= num[i + 1];
	}
	return sum;
}

void	solve(int idx){
	if (idx == num.size() - 1)
	{
		res = cal();
		if (res > Max)
			Max = res;
		if (res < Min)
			Min = res;
		return ;
	}
	for (int i = 0; i < 4; i++)
	{
		if (oper_num_check[i] >= oper_num[i])
			continue ;
		oper_path.push_back(i);
		oper_num_check[i]++;
		solve(idx + 1);
		oper_path.pop_back();
		oper_num_check[i]--;
	}
}

void init()
{
	memset(oper_num, 0, sizeof(oper_num));
	memset(oper_num_check, 0, sizeof(oper_num_check));
	oper_path.clear();
	num.clear();
	Max = -21e8;
	Min = 21e8;
	res = 0;
}

int main()
{
	cin >>t ;
	for (int z = 0; z < t; z++)
	{
		init();
		int inp;
		cin >> n;
		for (int i = 0; i < 4; i++)
			cin >> oper_num[i];
		for (int i = 0; i < n; i++)
		{
			cin >> inp;
			num.push_back(inp);
		}
		solve(0);
		printf("#%d %d\n", z + 1, Max - Min);
	}
}