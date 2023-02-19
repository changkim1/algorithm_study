#include <iostream>
#include <vector>
using namespace std;

struct grp {
    int x, y;
    int cnt;
    int dir;
};

int di[] = { 0,-1,1,0,0 };
int dj[] = { 0,0,0,-1,1 };

int N, M, K;
//군집 관리 벡터
vector<grp> v;
//군집 이동 맵
vector<int> map[100][100];

int main() {

    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; test_case++) {

        //사용할 변수 초기화
        int res = 0;
        v.clear();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                map[i][j].clear();
            }
        }

        //입력
        cin >> N >> M >> K;
        for (int i = 0; i < K; i++) {
            int x, y, cnt, dir;
            cin >> x >> y >> cnt >> dir;
            v.push_back({ x,y,cnt,dir });
        }

        //M시간 동안 반복
        while (M--) {

            //이동 맵 초기화
            for (int i = 0; i < K; i++) {
                if (v[i].cnt > 0) {
                    map[v[i].x][v[i].y].clear();
                }
            }

            //군집 이동 => 이동 맵에 저장
            for (int i = 0; i < K; i++) {
                grp tmp = v[i];

                if (tmp.cnt == 0) {
                    continue;
                }

                tmp.x += di[tmp.dir];
                tmp.y += dj[tmp.dir];

                //군집이 약품이 칠해진 셀에 도착할 경우
                if (tmp.x <= 0 || tmp.y <= 0 || tmp.x >= N - 1 || tmp.y >= N - 1) {
                    tmp.cnt /= 2;
                    if (tmp.dir % 2 == 0) {
                        tmp.dir--;
                    }
                    else {
                        tmp.dir++;
                    }
                }

                //군집에 미생물이 있을 경우만 이동 맵에 저장
                if (tmp.cnt > 0) {
                    map[tmp.x][tmp.y].push_back(i);
                }
                v[i] = tmp;
            }

            //이동 맵 => 군집 관리 벡터 저장
            for (int i = 0; i < K; i++) {

                if (v[i].cnt == 0) {
                    continue;
                }

                int x = v[i].x;
                int y = v[i].y;

                //한 지점에 2개 이상의 군집이 모여 있을 경우
                if (map[x][y].size() > 1) {

                    int sum = 0;
                    int maxGrp = 0;
                    int maxCnt = 0;

                    for (int j = 0; j < map[x][y].size(); j++) {
                        //총 미생물 수 구하기
                        sum += v[map[x][y][j]].cnt;

                        //미생물 수가 가장 많은 군집의 index를 찾기
                        if (v[map[x][y][j]].cnt > maxCnt) {
                            maxGrp = map[x][y][j];
                            maxCnt = v[map[x][y][j]].cnt;
                        }
                        v[map[x][y][j]].cnt = 0;
                    }
                    v[maxGrp].cnt = sum;
                }
            }
        }

        //결과 저장
        for (int i = 0; i < v.size(); i++) {
            if (v[i].cnt > 0) {
                res += v[i].cnt;
            }
        }

        //출력
        cout << "#" << test_case << " " << res << "\n";
    }
}
