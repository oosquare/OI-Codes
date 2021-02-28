#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 150 + 10;
constexpr int maxm = 3e5 + 10;

struct edge {
    int to, next;
};

edge graph[maxm];
int uuid, timer, scc, top, head[maxn], dfn[maxn];
int low[maxn], cnt[maxn], idx[maxn], stk[maxn];
int n, m, q, l[maxn], r[maxn], u[maxn], v[maxn];

void tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    stk[++top] = x;
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!idx[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (low[x] == dfn[x]) {
        idx[x] = ++scc;
        ++cnt[scc];
        while (stk[top] != x) {
            ++cnt[scc];
            idx[stk[top]] = scc;
            --top;
        }
        --top;
    }
}

void link(int x, int y) {
    graph[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void solve(int l, int r) {
    memset(head, 0, sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(idx, 0, sizeof(idx));
    memset(cnt, 0, sizeof(cnt));
    uuid = timer = scc = top = 0;
    for (int i = l; i <= r; ++i)
        link(u[i], v[i]);
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    int ans = 0;
    for (int i = 1; i <= scc; ++i)
        ans += cnt[i] * (cnt[i] - 1) / 2;
    cout << ans << endl; 
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("friend.in", "r", stdin);
    freopen("friend.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i)
        cin >> u[i] >> v[i];
    for (int i = 1; i <= q; ++i)
        cin >> l[i] >> r[i];
    for (int i = 1; i <= q; ++i)
        solve(l[i], r[i]);
    return 0;
}