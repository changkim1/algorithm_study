#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;
vector<int> num;
string oper_path;

string opers = "+-*/";
int opers_num[4];
int opers_cnt[4];

int Min = 21e8, Max = -(21e8);

int	cal()
{
	int res = 0;
	res += num[0];
	for (int i = 0; i < oper_path.length(); i++)
	{
		if (oper_path[i] == '+')
			res += num[i+1];
		else if (oper_path[i] == '-')
			res -= num[i+1];
		else if (oper_path[i] == '*')
			res *= num[i+1];
		else if (oper_path[i] == '/')
			res /= num[i+1];
	}
	return res;
}

void	solve(int idx)
{
	if (idx == n - 1)
	{
		int tmp = cal();
		if (tmp < Min)
			Min = tmp;
		if (tmp > Max)
			Max = tmp;
		return ;
	}
	for (int i = 0; i < 4; i++)
	{
		if (opers_num[i] <= opers_cnt[i])
			continue ;
		oper_path.push_back(opers[i]);
		opers_cnt[i]++;
		solve(idx + 1);
		oper_path.pop_back();
		opers_cnt[i]--;
	}
}

int main(void)
{
	int nu;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> nu;
		num.push_back(nu);
	}
	for (int i = 0; i < 4; i++)
		cin >> opers_num[i];
	solve(0);
	cout << Max << '\n' << Min << '\n';
}