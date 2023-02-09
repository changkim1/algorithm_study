#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

int map[17][17];
int dep[17][17];

int dx[3] = {1, 0, 1};
int dy[3] = {0, 1, 1};

struct node{
	int y, x;
	int stat; // 0 가로, 1 세로, 2 대각선
};

int n;

queue<node> q;

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> map[i][j];
	}
	q.push({0, 1, 0});
	while (!q.empty())
	{
		node now = q.front();
		q.pop();
		// printf("now = %d %d %d\n", now.x, now.y, now.stat);
		for (int i = 0; i < 3; i++)
		{
			if (now.stat == 0)
			{
				if (i == 1)
					continue ;
			}
			else if (now.stat == 1)
			{
				if (i == 0)
					continue ;
			}
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];
			if (!map[ny][nx] && nx >= 0 && nx < n && ny >= 0 && ny < n)
			{
				if (i == 2)
				{
					if (!map[ny-1][nx] && !map[ny][nx - 1])
					{
						q.push({ny, nx, i});
						dep[ny][nx]++;
					}
				}
				else{
					q.push({ny, nx, i});
					dep[ny][nx]++;
				}
			}
		}
	}
	cout << dep[n-1][n-1];
}