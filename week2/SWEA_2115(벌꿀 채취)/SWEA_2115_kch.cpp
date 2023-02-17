#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

int ans;
int map[11][11];
int vis[11][11];
int n, m, c, t;

struct node {
    int x, y; // 꿀통 시작 위치
    int val; // 그 때의 값
};

bool compare(node a, node b)
{
    return a.val > b.val;
}
bool cmp(int a, int b)
{
    return a > b;
}
vector<node> v;
vector<int> tmp;
vector<int> htmp;
int flag = 0;
int Max;

int get_honey()
{
    int num = 0;
	int sum = 0;
    for (int i = 0; i < htmp.size(); i++)
    {
		if (sum + htmp[i] > c)
			break ;
		sum += htmp[i];
		num += (htmp[i] * htmp[i]);
    }
	return num;
}

void    gethtmp(int now)
{
    if (now == tmp.size() - 1)
    {
        if (Max < get_honey())
            Max = get_honey();
        return ;
    }
    for (int i = now + 1; i < tmp.size(); i++)
    {
        htmp.push_back(tmp[i]);
        gethtmp(i);
        htmp.pop_back();
    }
    return ;
}

int    get_max()
{
    int sum, num, honey;
    v.clear();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - m + 1; j++)
        {
            sum = 0;
            num = 0;
            tmp.clear();
            flag = 0;
            for (int k = 0; k < m; k++)
            {
                if (vis[i][j + k] == 1)
                {
                    flag = 1;
                    break;
                }
                tmp.push_back(map[i][j + k]);
            }
			
            if (flag == 1)
                continue;
			Max = 0;
            gethtmp(-1);
            if (!Max)
                continue;
            v.push_back({ j, i, Max });
        }
    }
    sort(v.begin(), v.end(), compare);
    for (int i = 0; i < m; i++)
        vis[v[0].y][v[0].x + i] = 1;
    honey = v[0].val;
    // printf("%d, %d = %d\n", v[0].x, v[0].y, v[0].val);
    return honey;
}

void    solve()
{
    int a_honey = get_max();
    int b_honey = get_max();
    if (ans < a_honey + b_honey)
        ans = a_honey + b_honey;
}

int main()
{

    // freopen("input.txt", "r", stdin); 
    cin >> t;
    for (int z = 0; z < t; z++)
    {
        ans = 0;
        memset(vis, 0, sizeof(vis));
        memset(map, 0, sizeof(map));
        cin >> n >> m >> c;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cin >> map[i][j];
        }
        solve();
        printf("#%d %d\n", z + 1, ans);
    }
}