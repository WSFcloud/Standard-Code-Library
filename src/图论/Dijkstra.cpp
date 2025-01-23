#include <vector>
#include <queue>
#include <climits>
using namespace std;
const int INF = INT_MAX;
vector<int> dis, vis;
int n, m, s;
struct edge {
    int to, weight;
};
void dijkstra(vector<vector<edge>> graph) {
    dis.assign(n + 1, INF);
    vis.assign(n + 1, 0);
    dis[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = 1;
        for (auto &e : graph[u]) {
            auto v = e.to;
            auto w = e.weight;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
}