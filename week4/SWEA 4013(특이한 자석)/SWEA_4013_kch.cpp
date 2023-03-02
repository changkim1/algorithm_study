#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

/*
제일 윗쪽 날의 인덱스를 0으로 두고 양옆으로 -1, +1 로 둔다.
돌릴 때마다 제일 윗쪽 날의 인덱스만 갱신해준다.
하나가 돌면 그 양옆에 자석도 영향을 받음.
돌기 전에 양 옆의 자석들을 확인해주어야 함.
가장 처음 기준부터 시작해서 오른쪽으로 쭉, 왼쪽으로 쭉 자석 모두 확인해주기
	-> 재귀 사용하면 될듯?
	-> 자석 종류가 다를 때만 재귀 추가로 더 타는 식으로
	-> 재귀 다 타고나면 빠져나오면서 바꿔주기 (다음꺼에 영향 안 주게)
마지막에 기준 자석 인덱스 바꿔주기
이런 식으로 계속 반복
*/


struct rot_info {
	int num; // 회전시킬 날 번호
	int dir; // 회전시킬 방향
};

int zero_idx[4]; // 가장 윗쪽 날의 인덱스를 계속 갱신
int edge[4][8]; // 날 정보 저장할 배열
int score[4] = {1, 2, 4, 8}; // 귀찮으니까 하드코딩

int t, k, ans, rotate_flag;

vector<rot_info> info; // 회전 정보 저장할 벡터

void	init()
{
	memset(zero_idx, 0, sizeof(zero_idx));
	memset(edge, 0, sizeof(edge));
	info.clear();
	ans = 0;
}

void	input()
{
	rot_info tmp;
	int n, m;
	n = 4;
	m = 8;
	cin >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cin >> edge[i][j];
	}
	for (int i = 0; i < k; i++)
	{
		cin >> tmp.num >> tmp.dir;
		tmp.num = tmp.num - 1;
		info.push_back(tmp);
	}
}

void	side_rotate(rot_info now_info, int side)
{
	if (now_info.num == 0 && side == -1) // 제일 왼쪽 꺼가 돌아가는데 왼쪽 꺼 확인할 경우
		return ;
	if (now_info.num == 3 && side == 1) // 제일 오른쪽 꺼가 돌아가는데 오른쪽 꺼 확인할 경우
		return ;
	int side_zero = zero_idx[now_info.num + side];
	int my_zero = zero_idx[now_info.num];
	int side_check_idx = side == 1 ? 6 : 2; // 각 사이드마다 확인해야하는 인덱스가 다름
	int my_check_idx = 8 - side_check_idx; // 각 사이드마다 확인해야하는 인덱스가 다름
	if (edge[now_info.num + side][(side_zero + side_check_idx) % 8] != edge[now_info.num][(my_zero + my_check_idx) % 8])
	{
		// 같지 않으면 옆에 것도 반대로 돌려줘야함.
		side_rotate({now_info.num + side, now_info.dir * (-1)}, side); // 해당 방향 끝까지 확인
		zero_idx[now_info.num + side] = (side_zero + now_info.dir + 8) % 8;
	}
}

void	rotate_myself(rot_info info)
{
	int my_zero = zero_idx[info.num];
	zero_idx[info.num] = (my_zero + (info.dir * -1) + 8) % 8; // 내껀 무조건 돌리기
}

void	game_start()
{
	for (int i = 0; i < k; i++)
	{
		side_rotate(info[i], -1); // 왼쪽 껀 -1, 오른쪽 껀 +1 // 처음 회전한 애를 시작으로 다 돌려줘야함.
		side_rotate(info[i], 1); // 왼쪽 껀 -1, 오른쪽 껀 +1 // 처음 회전한 애를 시작으로 다 돌려줘야함.
		rotate_myself(info[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		if (edge[i][zero_idx[i]] == 1)
			ans += score[i];
	}
}

int main(void)
{
	cin >> t;
	for (int z = 0; z < t; z++)
	{
		init();
		input();
		game_start();
		printf("#%d %d\n", z + 1, ans);
	}
}