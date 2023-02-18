#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;


struct bc {
	int x, y;
	int c;
	int p;
};

struct hum {
	int x, y;
	vector<int> now_charge;
};

vector<int> map[11][11];
int n, m, t, bc_cnt;
int ans[101];
int fin_ans;

hum a;
hum b;
vector<int> a_dir;
vector<int> b_dir;

vector<bc> bat;

int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, -1, 0, 1, 0};

int cmp(int a, int b)
{
	return bat[a].p > bat[b].p;
}

void	init()
{
	fin_ans = 0;
	a = {0, 0};
	b = {9, 9};
	a_dir.clear();
	b_dir.clear();
	bat.clear();
	a_dir.push_back(0); // 0번째 time 에는 가만히 있는 상태에서 check
	b_dir.push_back(0);
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			map[i][j].clear();
	}
}

void	input()
{
	int tmp, x, y, c, p;
	cin >> m >> bc_cnt;
	for (int j = 0; j < m; j++)
	{
		cin >> tmp;
		a_dir.push_back(tmp);
	}
	for (int j = 0; j < m; j++)
	{
		cin >> tmp;
		b_dir.push_back(tmp);
	}
	for (int i = 0; i < bc_cnt; i++)
	{
		cin >> x >> y >> c >> p;
		bat.push_back({x - 1, y - 1, c, p});
	}
}

void	set_bc() {
	for (int b = 0; b < bat.size(); b++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if ((abs(bat[b].x - j) + (abs(bat[b].y - i)) <= bat[b].c))
					map[i][j].push_back(b); // c가 닿는 거리면 map에 해당 battery idx 저장
			}
		}
	}
}

/*
1. 벡터맵에 bc 정보 다 저장
2. 사람이 움직이는 좌표에 bc들을 다 now_charge에 저장 -> 다시 clear
3. A, B의 now_charge 들을 조합해서 가장 높은 조합을 ans 테이블에 저장
	-> 하나라도 size() 가 0이면 now_charge sort해서 0번 인덱스를 저장
4. ans 테이블 합 출력
*/

void	human_move(int time)
{
	a.x = a.x + dx[a_dir[time]];
	b.x = b.x + dx[b_dir[time]];
	a.y = a.y + dy[a_dir[time]];
	b.y = b.y + dy[b_dir[time]];
	for (int i = 0; i < map[a.y][a.x].size(); i++)
		a.now_charge.push_back(map[a.y][a.x][i]);
	for (int i = 0; i < map[b.y][b.x].size(); i++)
		b.now_charge.push_back(map[b.y][b.x][i]);
}

int 	cal(vector<int> path)
{
	if (path[0] == path[1])
		return bat[path[0]].p;
	else
		return bat[path[0]].p + bat[path[1]].p;
}

void	make_comb_and_cal(int time)
{
	vector<int> path;
	int res = 0, Max = 0;
	for (int i = 0; i < a.now_charge.size(); i++)
	{
		path.push_back(a.now_charge[i]);
		for (int j = 0; j < b.now_charge.size(); j++)
		{
			path.push_back(b.now_charge[j]);
			res = cal(path);
			if (res > Max)
				Max = res;
			path.pop_back();
		}
		path.pop_back();
	}
	path.clear();
	ans[time] = Max;
}

void	solve(int time)
{
	if (a.now_charge.size() == 0 && b.now_charge.size() == 0)
	{
		ans[time] = 0;
		return ;
	}
	else if (a.now_charge.size() == 0)
	{
		sort(b.now_charge.begin(), b.now_charge.end(), cmp); // 내림차순 정리
		ans[time] = bat[b.now_charge[0]].p;
		b.now_charge.clear();
	}
	else if (b.now_charge.size() == 0)
	{
		sort(a.now_charge.begin(), a.now_charge.end(), cmp); // 내림차순 정리
		ans[time] = bat[a.now_charge[0]].p;
		a.now_charge.clear();
	}
	else
	{
		make_comb_and_cal(time);
		a.now_charge.clear();
		b.now_charge.clear();
	}
}

int add_all_ans()
{
	int sum = 0;
	for (int j = 0; j <= m; j++)
		sum += ans[j];
	return sum;
}

int main(void)
{
	cin >> t;
	for (int z = 0; z < t; z++)
	{
		init();
		input();
		set_bc();
		for (int j = 0; j <= m; j++)
		{
			human_move(j);
			solve(j);
		}
		fin_ans = add_all_ans();
		printf("#%d %d\n", z + 1, fin_ans);
	}
}