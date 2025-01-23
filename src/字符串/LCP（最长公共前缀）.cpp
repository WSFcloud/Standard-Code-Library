#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
constexpr int L = 2E6 + 10;
int len[L];
int lnk[L];
int nxt[L][26];
int f[L];
int tot = 1;
vector<int> adj[L];

int extend(int p, int c) {
    if (nxt[p][c]) {
        int q = nxt[p][c];
        if (len[q] == len[p] + 1) {
            return q;
        }
        int r = ++tot;
        len[r] = len[p] + 1;
        lnk[r] = lnk[q];
        copy(nxt[q], nxt[q] + 26, nxt[r]);
        lnk[q] = r;
        while (nxt[p][c] == q) {
            nxt[p][c] = r;
            p = lnk[p];
        }
        return r;
    }
    int cur = ++tot;
    len[cur] = len[p] + 1;
    while (!nxt[p][c]) {
        nxt[p][c] = cur;
        p = lnk[p];
    }
    lnk[cur] = extend(p, c);
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(nxt[0], nxt[0] + 26, 1);
    len[0] = -1;
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
        int p = 1;
        for (auto c : S[i]) {
            p = extend(p, c - 'a');
            if (f[p] != -1) {
                if (f[p] == 0) {
                    f[p] = i + 1;
                } else if (f[p] != i + 1) {
                    f[p] = -1;
                }
            }
        }
    }
    for (int i = 1; i <= tot; i++) {
        adj[lnk[i]].push_back(i);
    }
}