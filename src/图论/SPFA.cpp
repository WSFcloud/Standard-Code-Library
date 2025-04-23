#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;
int n, m, s = 1;
struct edge {
    int to, weight;
};
bool spfa(vector<vector<edge>> graph) {
    // cnt数组记录节点的进队次数，用于检测负环
    vector<int> dis(n + 1, INF), vis(n + 1, 0), cnt(n + 1, 0);
    dis[s] = 0;
    vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        // 遍历该节点的所有邻接边
        for (auto &e : graph[u]) {
            auto v = e.to;
            auto w = e.weight;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) {
                    return false; // 负环存在，返回false
                }
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return true;
}