#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
1. 문제읽기
	- 초기 상태에서 줄기 세포가 분포된 영역의 넓이는 
	  세로 크기 N, 가로 크기 M이며 N, M은 각각 1 이상 50 이하의 정수(1≤N≤50, 1≤M≤50)
	- 배양 시간은 K시간으로 주어지며 K는 1 이상 300 이하의 정수(1≤K≤300)
	- 줄기 세포의 생명력 X는 1 이상 10 이하의 정수(1≤X≤10)

	- X시간 동안 비활성 상태이고 X시간이 지나는 순간 활성 상태
	- X시간 동안 살아있을 수 있으며 X시간이 지나면 세포는 죽게 된다.
	- 세포가 죽더라도 소멸되는 것은 아니고 죽은 상태로 해당 그리드 셀을 차지하게 된다.
	- 생명력 수치가 높은 줄기 세포가 해당 그리드 셀을 혼자서 차지
	- 배양 용기의 크기는 무한하다고 가정

	- K시간 후 살아있는 줄기 세포(비활성 상태 + 활성 상태)의 총 개수를 구하는 프로그램
*/

/*
2. 아이디어
	- 미생물 문제, 원자소멸 문제에서 아이디어들 따왔음
	- 구현문제
	- 배양지가 무한해 보이지만 사실 범위 정해져있음
	- 세포들 상태 저장할 구조체 벡터 하나 만들고
	  세포들 위치 저장할 지도 DAT 하나 만들고
	  우선순위 큐로 생명력 높은거부터 뽑아오자
	- BFS 느낌으로 구현하면 될듯
*/

struct Cell_info {
	int y;
	int x;
	int Life; // 생명력
	int Timer; // 세포마다 시간을 체크함
	// Timer가 -1부터는 활성화상태,
	// Timer가 -Life가 되면 죽음

	// 우선순위큐 생명력 기준으로 내림차순 정렬
	bool operator < (Cell_info Next) const {

		if (Life > Next.Life)
			return false;
		if (Life < Next.Life)
			return true;
		return false;
	}
};

// 필요 인자들
int N; // 세로
int M; // 가로
int K; // 배양 시간
int ans; // 죽은세포를 카운트해서 전체세포에서 빼버리자.
int Dead_num; // 죽은세포 수
vector<Cell_info> Stem_cell; // 전체세포 저장 벡터
priority_queue<Cell_info> Active_cell; // 활성화된 세포만 저장할 pq

int Map[350][350];
/*
	왜 350 ?
	초기 영역이 50이고
	생명력이1, K가300으로 가정하면 최대 상하좌우 300까지 퍼짐
	결국 최대 350
	시작지점을 150으로 잡아주자
*/

int diry[] = { -1, 0, 1, 0 };
int dirx[] = { 0, -1, 0, 1 };

// 테스트 케이스마다 초기화
void reset() {
	Dead_num = 0;
	Stem_cell.clear();
	memset(Map, 0, sizeof(Map));
}

// 값 입력받기, 0을 N으로 1을 S로 변환
void input() {
	cin >> N >> M >> K;
	// Map의 시작지점을 150부터
	for (int i = 150; i < 150 + N; i++) {
		for (int j = 150; j < 150 + M; j++) {
			cin >> Map[i][j];
			
			// 세포는 벡터에 넣기
			if (Map[i][j] > 0) {
				Stem_cell.push_back({ i, j, Map[i][j], Map[i][j] });
			}
		}
	}
}

// 벡터 확인하면서 세포들 Timer처리하고 활성화되면 큐에넣는 함수
void Check_cells() {
	int len = Stem_cell.size();
	for (int i = 0; i < len; i++) {
		// 타이머 하나 깎아주고
		Stem_cell[i].Timer--;
		// 타이머가 -1되면 비활성 -> 활성
		if (Stem_cell[i].Timer == -1)
			Active_cell.push(Stem_cell[i]);
		// 타이머가 -Life면 활성 -> 죽음
		// 이걸 따로 뺀다면 실행시간 감소가능할지도
		if (Stem_cell[i].Timer == -Stem_cell[i].Life)
			Dead_num++;
	}
}

// 우선순위 큐로 세포들 배양시키는 함수
void Grow() {

	while (!Active_cell.empty()) {

		Cell_info now = Active_cell.top();
		Active_cell.pop();

		for (int i = 0; i < 4; i++) {

			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];

			// 범위체크는 필요없음
			// 대신 Map이 0인지 확인
			if (Map[ny][nx] != 0)
				continue;

			// 통과하면 벡터와 Map에 넣어줌
			Map[ny][nx] = now.Life;
			Stem_cell.push_back({ ny, nx, now.Life, now.Life });
		}
	}
}

// 메인함수
int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// 테스트 케이스마다 초기화
		reset();

		// input
		input();

		// solve -> K시간돌려줌
		for (int i = 1; i <= K; i++) {
			// 벡터 확인하면서 세포들 Timer처리하고 활성화되면 큐에넣음
			Check_cells();
			// 넣은 큐로 bfs 비스무리하게
			Grow();
		}

		// output -> 전체세포 - 죽은세포
		ans = Stem_cell.size() - Dead_num;
		cout << "#" << tc << " " << ans << endl;
	}

	return 0;
}
