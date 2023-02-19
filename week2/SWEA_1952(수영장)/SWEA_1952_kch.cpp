#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int t;
int fee[4]; // 0 : 1일권 , 1 : 한달권, 2 : 3달권, 3 : 1년권
int month_plan[13]; // 몇 번 갈지 저장하는 배열
int ans;

void	solve(int mon, int sum) // mon = 해당 월에 fee를 path 처럼 저장하는 방식으로 (실제로는 해당 요금 지불 방식을 sum 에 더해주기만 함)
{
	if (mon > 12) // 12월이 넘어가면 최솟값 갱신
	{
		ans = min(ans, sum);
		// printf("solvesum = %d\n", ans);
		return ;
	}
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			sum += (fee[0] * month_plan[mon]); // 해당 mon 은 1일권을 산 것으로 하고, sum에 더해줌 (1일권 * 몇 번 갈지)
			solve(mon + 1, sum); // 다음 달로 가기
			sum -= (fee[0] * month_plan[mon]); // 빼주기
		}
		else if (i == 1)
		{
			sum += fee[1]; // 해당 mon 은 한달권을 산 것으로 하고, sum에 더해줌 (한달권 1개)
			solve(mon + 1, sum); // 다음 달로 가기
			sum -= fee[1]; // 빼주기
		}
		else if (i == 2)
		{
			sum += fee[2]; // 해당 mon 은 3달권을 산 것으로 하고, sum에 더해줌 (3달권 1개)
			solve(mon + 3, sum); // 3달권을 산 것이기 때문에 3달 뒤로 넘어가서 계산. 11, 12월일 경우에도 +3달 해줄 수 있음.
			sum -= fee[2]; // 빼주기
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
			cin >> fee[i]; // 요금 입력받기
		for (int i = 1; i < 13; i++)
			cin >> month_plan[i]; // 몇 번 갈지 입력받기
		solve(1, 0);
		// printf("sum = %d\n", ans);
		ans = min(ans, fee[3]); // 1일권, 한달권, 3달권을 사용했던 것들 중에 가장 싼 값과 1년치 이용권을 비교해서 갱신
		printf("#%d %d\n", a + 1, ans); // 최솟값 출력
	}
	
}