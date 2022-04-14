#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 10000 + 10;
constexpr int maxm = 30000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Edge {
    int to, next, length;
};

Edge graph[maxm];
int uuid, head[maxn];
int w[maxn], dis[maxn], vis[maxn];
int n, m, l, r, ans, mid;

void link(int x, int y, int l) {
    graph[++uuid] = { y, head[x], l };
    head[x] = uuid;
}

bool check(int k) {
    priority_queue<pair<int, int>> q;
    fill(dis + 1, dis + 1 + n, oo);
    fill(vis + 1, vis + 1 + n, 0);
    dis[1] = w[1];
    q.push(make_pair(-dis[1], 1));
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            int ndis = max(dis[x] - graph[i].length, 0) + w[y];
            if (!(ndis < dis[y] && ndis <= k))
                continue;
            dis[y] = ndis;
            q.push(make_pair(-dis[y], y));
        }
    }
    return dis[n] <= k;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("peach.in", "r", stdin);
    freopen("peach.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= m; ++i) {
        int x, y, l;
        cin >> x >> y >> l;
        link(x, y, l);
    }
    l = max(w[1], w[n]), r = oo;
    while (l <= r) {
        mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
