#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cstring>
using namespace std;

/*
현재 시간을 기준으로 조건에 맞게
계속 최신화 해주기
하다가 지갑을 잃어버린 손님과 같은 접수창구인 사람만 따로 저장해둠
마지막에 정비창구 확인하면서 답 갱신
*/

int recept_time[11]; // 접수 창구 시간
int repair_time[11]; // 정비 창구 시간
int now; // 현재 시간

struct hum {
	int num; // 고객번호
	int arr_time; // 도착 시간
	int recept_num; // 접수 창구 번호
	int recept_start; // 접수 시작 시간
	int repair_num; // 정비 창구 번호
	int repair_start; // 정비 시작 시간
};

struct num_smaller_cmp {
	bool operator() (hum a, hum b) {
		if (a.arr_time == b.arr_time)
			return a.num > b.num;
		return a.arr_time > b.arr_time;
	}
};

struct recept_num_smaller {
	bool operator() (hum a, hum b) {
		if (a.recept_start + recept_time[a.recept_num] == b.recept_start + recept_time[b.recept_num])
			return a.recept_num > b.recept_num;
		return a.recept_start + recept_time[a.recept_num] > b.recept_start + recept_time[b.recept_num];
	}
};

struct recept_less_time {
	bool operator() (hum a, hum b) {
		return ((a.recept_start + recept_time[a.recept_num]) - now > (b.recept_start + recept_time[b.recept_num]) - now);
	}
};

struct repair_less_time {
	bool operator() (hum a, hum b) {
		return ((a.repair_start + repair_time[a.repair_num]) - now > (b.repair_start + repair_time[b.repair_num]) - now);
	}
};

int cli_compare(hum a, hum b) {
	return a.arr_time < b.arr_time;
}

priority_queue<hum, vector<hum>, num_smaller_cmp> recept_await; // 접수 대기
priority_queue<int, vector<int>, greater<int>> can_recept; // 접수 가능 창구
priority_queue<hum, vector<hum>, recept_less_time> recepting; // 접수 중 창구

priority_queue<hum, vector<hum>, recept_num_smaller> repair_await; // 정비 대기
priority_queue<int, vector<int>, greater<int>> can_repair; // 정비 가능 창구
priority_queue<hum, vector<hum>, repair_less_time> repairing; // 정비 중 창구

vector<hum> cli; // 고객 정보

int n, m, k, a, b, t;
int ans;

void init()
{
	cin >> n >> m;
	ans = 0;
	now = 0;
	cli.clear();
	memset(recept_time, 0, sizeof(recept_time));
	memset(repair_time, 0, sizeof(repair_time));
	while (!can_recept.empty())
		can_recept.pop();
	while (!can_repair.empty())
		can_repair.pop();
	for (int i = 1; i <= n; i++)
		can_recept.push(i); // 모든 창구가 일단은 비어있다고 넣어두기
	for (int j = 1; j <= m; j++)
		can_repair.push(j);
}

void input()
{
	int num;
	cin >> k >> a >> b;
	for (int i = 1; i <= n; i++)
		cin >> recept_time[i];
	for (int j = 1; j <= m; j++)
		cin >> repair_time[j];
	for (int i = 1; i <= k; i++) // 고객은 1번부터 k번까지
	{
		cin >> num;
		cli.push_back({i, num, 0, 0, 0, 0}); // 고객번호, 도착시간, 접수창구번호, 접수시작시간, 정비창구번호, 정비시작시간
	}
}

void	go_recept_await() {
	for (int i = 0; i < cli.size(); i++)
	{
		if (cli[i].arr_time == now && cli[i].recept_num == 0) // 지금 온 사람들 대기에 일단 넣기
			recept_await.push(cli[i]);
		else if (cli[i].arr_time > now)
			break ;
	}
}

void	recepting_end_and_go_repair_await() {
	hum recepting_cli; // 접수하고 있는 사람
	int recepting_num; // 접수중인 창구 번호
	while (!recepting.empty()) {
		recepting_cli = recepting.top(); // 가장 시간이 적게 남은 사람
		if (recepting_cli.recept_start + recept_time[recepting_cli.recept_num] - now == 0) // 끝났으면
		{
			recepting_num = recepting_cli.recept_num; // 접수끝난 창구 번호
			recepting.pop(); // 접수중인 창구에서 빼주기
			can_recept.push(recepting_num); // 접수 가능한 창구로 다시 넣어주기
			repair_await.push(recepting_cli); // 접수 끝났으면 일단 정비대기로 넣어주기
		}
		else
			break ;
	}
}

void	go_recepting_and_go_repair_await() {
	hum await_hum; // 접수 대기하는 사람
	int recept_num; // 접수할 창구 번호
	recepting_end_and_go_repair_await(); // 끝난 애들 일단 빼주기
	if (recept_await.empty())
		return ;
	while (!can_recept.empty() && !recept_await.empty())
	{
		await_hum = recept_await.top(); // 기다리고 있는 애들 중에 우선순위 가장 높은 애
		recept_await.pop(); // 기다리고 있는 애 에서 빼주기
		recept_num = can_recept.top(); // 가능한 창구중에 가장 우선순위 높은 창구부터 배정
		can_recept.pop(); // 이제 가능한 창구 아님
		await_hum.recept_num = recept_num; // 창구 넣어주기
		await_hum.recept_start = now; // 시작시간 넣어주기
		recepting.push(await_hum); // 접수중인 거로 넣어주기
	}
}

void	repair_end_and_make_ans() {
	hum repairing_cli; // 정비 중인 고객
	int repairing_num; // 정비 중인 창구
	while (!repairing.empty())
	{
		repairing_cli = repairing.top(); // 정비 중인 고객 중에 시간이 가장 적게 남은 고객
		if (repairing_cli.repair_start + repair_time[repairing_cli.repair_num] - now == 0) // 정비 끝났으면
		{
			repairing_num = repairing_cli.repair_num; // 끝난 정비 창구 번호
			can_repair.push(repairing_num); // 정비 가능한 창구 복원
			repairing.pop(); // 정비 중인 창구 없애기
			if (repairing_cli.recept_num == a && repairing_cli.repair_num == b) // 지갑 잃어버린 애랑 똑같은 창구라면
				ans += repairing_cli.num;
		}
		else
			break;
	}
}

void	go_repairing() {
	hum await_hum; // 정비 대기하는 사람
	int repair_num; // 정비할 창구 번호
	repair_end_and_make_ans(); // 정비 끝난 애들 일단 빼주기
	if (repair_await.empty())
		return ;
	while (!can_repair.empty() && !repair_await.empty())
	{
		await_hum = repair_await.top(); // 기다리고 있는 애들 중에 가장 먼저 정비 받을 애
		repair_await.pop();
		repair_num = can_repair.top(); // 정비 가능한 창구 중에 가장 먼저 정비할 창구
		can_repair.pop(); // 정비 가능 창구 빼주기
		await_hum.repair_num = repair_num; // 정비 창구 이름
		await_hum.repair_start = now; // 정비 시작 시간
		repairing.push(await_hum); // 지금 정비 중인 거로 넣어주기
	}
}

int is_end()
{
	return (cli.back().arr_time < now && repairing.empty() && recept_await.empty() && recepting.empty()
			&& repair_await.empty());
}

void	game_start()
{
	while (!is_end())
	{
		go_recept_await();
		go_recepting_and_go_repair_await();
		go_repairing();
		now++;
	}
}

int main()
{
	cin >> t;
	for (int z = 0; z < t; z++)
	{
		init();
		input();
		sort(cli.begin(), cli.end(), cli_compare);
		game_start();
		if (ans == 0)
			ans = -1;
		printf("#%d %d\n", z + 1, ans);
	}
}