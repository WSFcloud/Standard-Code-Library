#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;
vector<vector<int>> dis;
int n, m;
void floyd(vector<vector<int>> &graph) {
    dis = graph;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}