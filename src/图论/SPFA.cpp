#include <vector>
#include <queue>
#include <climits>
using namespace std;
const int INF = INT_MAX;
vector<int> dis, vis, cnt; // cnt数组记录节点的进队次数，用于检测负环
queue<int> q;
int n, m, s;
struct edge {
    int to, weight;
};
bool spfa(vector<vector<edge>> &graph) {
    dis.assign(n + 1, INF);
    vis.assign(n + 1, 0);
    cnt.assign(n + 1, 0);
    dis[s] = 0;
    vis[s] = 1;
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
                if (cnt[v] > n - 1) {
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