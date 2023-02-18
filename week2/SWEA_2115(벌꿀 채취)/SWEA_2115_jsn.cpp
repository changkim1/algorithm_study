#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;//벌통의 크기
int M;//벌통의 개수
int C;//최대 양
int arr[10][10];
int total_cost;
int my_list[5];
int sum1 = 0;
int odd = 0;
struct Node{
    int y;
    int x;
    int cost;
     
};
bool cmp(Node left, Node right) {
    if (left.cost > right.cost)
        return true;
    if (left.cost < right.cost)
        return false;
    return false;
}
vector<Node>v;
int answer = 0;
void findComb(int y, int x, int level, int acc1, int acc2)
{
    if (level == M)
    {
        if (answer < acc2) answer = acc2;
        return;
    }
    // 지금 꿀 채취 안함
    findComb(y, x, level + 1, acc1, acc2);
    // 지금 꿀 채취함
    if (acc1 + arr[y][x + level] <= C)
        findComb(y, x, level + 1, acc1 + arr[y][x + level], acc2 + arr[y][x + level] * arr[y][x + level]);
}
void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - M + 1; j++) {
            int odd = 0;
            int sum1 = 0;
            findComb(i, j,0,0,0);
             
            v.push_back({ i,j,answer });
            answer = 0;
             
        }
    }
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < v.size() ; i++) {
        Node max1 = v[i];
        for (int j = i + 1; j < v.size(); j++) {
            Node max2 = v[j];
            if (max1.y == max2.y && max1.x + M > max2.x)continue;
            int cost = max1.cost + max2.cost;
            if (total_cost < cost)
                total_cost = cost;
        }
    }
}
int main() {
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> M >> C;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> arr[i][j];
            }
        }
        solve();
        for (int i = 0; i < v.size(); i++) {
            //cout << v[i].y << ' ' << v[i].x << ' ' << v[i].cost<<endl;
        }
        cout << '#' << tc << ' ' << total_cost << endl;
        total_cost = 0;
        v.clear();
    }
}
