#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

/*
bfs + pq 쓰면 될듯.
pq 기준은 (초기시간 + 생명력 - now) ( == 활성화되기 까지 남은 시간)
*/

struct cell {
	int x, y;
	int plant_time;
	int life;
};

int time_now; // 현재 시간

struct cmp {
	bool operator()	(cell a, cell b) {
		return (a.life + a.plant_time - time_now > b.life + b.plant_time - time_now);
	} // 활성되기까지 남은 시간을 기준으로 pq 만들기
};

int lx, rx, ty, by;
vector<cell> map[1000][1000];
priority_queue<cell, vector<cell>, cmp> pq;

set<pair<int, int>> v_coo;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int n, m, k, ans, t;

int compare(cell a, cell b){
	return a.life > b.life;
}

void	init()
{
	time_now = 0;
	ans = 0;
	memset(map, 0, sizeof(map));
	while(!pq.empty())
		pq.pop();
	lx = 501;
	rx = -501;
	ty = 501;
	by = -501;
}

void	input()
{
	int num;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> num;
			if (num != 0) // 일단 심어진 애들은 다 넣어주기
			{
				map[i + 500][j + 500].push_back({j+500, i+500, 0, num});
				pq.push({j + 500, i + 500, 0, num}); // 심어진 좌표, 시작 시간, 생명력, 남은 시간
			}
		}
	}
}

void	bfs()
{
	while (!pq.empty())
	{
		cell now = pq.top();
		if (now.life + now.plant_time - time_now > 0)
			return ;
		pq.pop();
		for (int i = 0; i < 4; i++) // 배양 시키기
		{
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];
			if (map[ny][nx].empty() || map[ny][nx][0].plant_time == time_now + 1)
			{ // 배양하려는 곳의 시작 시간이 지금과 같거나 0 (동일한 시각이거나 아직 안뿌림)
				// 일단 갱신될 좌표랑 뿌려진 세포의 생명력을 담아두자.
				v_coo.insert({nx, ny}); // 중복 없이 저장함
				map[ny][nx].push_back({nx, ny, time_now + 1, now.life});
			}
		}
		
	}
}

void	make_life()
{
	for (auto iter = v_coo.begin(); iter != v_coo.end(); iter++) {
		pair<int, int> now = *iter;
		sort(map[now.second][now.first].begin(), map[now.second][now.first].end(), compare);
		pq.push(map[now.second][now.first][0]);
		lx = min(lx, now.first);
		rx = max(rx, now.first);
		by = max(by, now.second);
		ty = min(ty, now.second);
	}
}

int main(void)
{
	cin >> t;
	for (int z = 0; z < t; z++)
	{
		init();
		input();
		for (int i = 1; i <= k; i++)
		{
			time_now = i;
			bfs();
			make_life();
			v_coo.clear();
		}
		for (int i = ty; i <= by; i++)
		{
			for (int j = lx; j <= rx; j++)
			{
				if (!map[i][j].empty())
				{
					if (map[i][j][0].plant_time + map[i][j][0].life + map[i][j][0].life - 1 >= time_now)
					{
						if (map[i][j][0].plant_time <= time_now)
							ans++;
					}
				}
			}
		}
		printf("#%d %d\n", z + 1, ans);
	}
}