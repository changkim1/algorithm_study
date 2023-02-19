#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

struct node{
	int d;
	int c;
};

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int t;
int n, m, k;

vector<node> tmp;

node map[101][101];
int vis[101][101];

int isValid(int x, int y)
{
	return (x >= 0 && x < n && y >= 0 && y < n);
}

int DirMatching(int x, int y, int dir)
{
	if (map[y][x].d == dir + 1)
		return 1;
	else
		return 0;
}

int DirChange(int dir)
{
	if (dir == 1)
		return 2;
	else if (dir == 2)
		return 1;
	else if (dir == 3)
		return 4;
	else if (dir == 4)
		return 3;
	return 0;
}

void	pesticide_zone(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int bef_x = x + dx[i];
		int bef_y = y + dy[i];
		if (isValid(bef_x, bef_y) && DirMatching(bef_x, bef_y, i) && !vis[bef_y][bef_x])
		{
			map[y][x].c = map[bef_y][bef_x].c / 2;
			if (map[y][x].c == 0)
				map[y][x].d = 0;
			else
				map[y][x].d = DirChange(map[bef_y][bef_x].d);
			map[bef_y][bef_x] = {0, 0};
			vis[y][x] = 1;
		}
	}
}

void	normal_zone(int x, int y)
{
	tmp.clear();
	int Max = 0, dir, sum = 0;
	for (int i = 0; i < 4; i++)
	{
		int bef_x = x + dx[i];
		int bef_y = y + dy[i];
		if (isValid(bef_x, bef_y) && DirMatching(bef_x, bef_y, i) && !vis[bef_y][bef_x]) // 
		{
			tmp.push_back(map[bef_y][bef_x]);
			map[bef_y][bef_x] = {0, 0};
			vis[y][x] = 1;
		}
	}
	if (tmp.size() >= 2)
	{
		for (int i = 0; i < tmp.size(); i++)
		{
			if (tmp[i].c > Max)
			{
				Max = tmp[i].c;
				dir = tmp[i].d;
			}
			sum += tmp[i].c;
			printf("tmpi = %d\n", tmp[i].c);
		} // dir, sum 갱신 됐음.
		map[y][x] = {dir, sum};
	}
	else if (tmp.size() == 1)
		map[y][x] = tmp[0];
}

void	solve()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
				pesticide_zone(j, i);
			else
				normal_zone(j, i);
			printf("%d %d check\n", j, i);
			for (int k = 0; k < n; k++)
			{
				for (int o = 0; o < n; o++)
				{
					if (k == i && o == j)
						cout << 'C' << ' ';
					else
						cout << map[k][o].c << ' ';
				}
				cout << "         ";
				for (int o = 0; o < n; o++)
				{
					cout << vis[k][o] << ' ';
				}
				cout << endl;
			}
			cout << endl;
		}
	}
}

void init()
{
	memset(map, 0, sizeof(map));
	tmp.clear();
	memset(vis, 0, sizeof(vis));
}

int main()
{
	int sum;
	cin >> t;
	for (int z = 0; z < t; z++)
	{
		int x, y;
		sum = 0;
		init();
		cin >> n >> m >> k;
		for (int i = 0; i < k; i++)
		{
			cin >> y >> x;
			cin >> map[y][x].c >> map[y][x].d;
		}
		for (int i = 0; i < m; i++)
		{
			solve();
			memset(vis, 0, sizeof(vis));
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				sum += map[i][j].c;
		}
		printf("#%d %d\n", sum);
	}
}