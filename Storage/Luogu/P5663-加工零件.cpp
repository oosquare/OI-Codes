#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int oo = 0x3f3f3f3f;
constexpr int even = 0;
constexpr int odd = 1;

struct Edge {
    int to, next;
};

int n, m, q;
Edge graph[maxn * 2];
int head[maxn], uuid;
int dis[2][maxn];
bool vis[2][maxn];

void link(int x, int y) {
    graph[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void BFS() {
    queue<pair<int, int>> q;
    q.push(make_pair(1, even));
    memset(dis, 0x3f, sizeof(dis));
    dis[even][1] = 0;
    vis[even][1] = true;
    while (!q.empty()) {
        int x = q.front().first, type = q.front().second;
        q.pop();
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (vis[!type][y])
                continue;
            dis[!type][y] = dis[type][x] + 1;
            vis[!type][y] = true;
            q.push(make_pair(y, !type));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        link(a, b);
        link(b, a);
    }
    BFS();
    // for (int i = 1; i <= n; ++i)
    //     cout << i << " : even = " << dis[even][i] << " odd = " << dis[odd][i] << endl; 
    for (int i = 1; i <= q; ++i) {
        int a, l;
        cin >> a >> l;
        cout << (l >= dis[l % 2][a] ? "Yes" : "No") << endl;
    }
    return 0;
}