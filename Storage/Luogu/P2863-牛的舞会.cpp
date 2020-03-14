#include <bits/stdc++.h>
using namespace std;

struct e {
    int to, next;
};

constexpr int maxn = 10000 + 5;
constexpr int maxm = 50000 + 5;
e edge[maxm];
int uuid, n, m, head[maxn], timer, ans;
int dfn[maxn], low[maxn], stk[maxn], top;
int idx[maxn], sze[maxn], scc;

inline void link(int x, int y) {
    edge[++uuid] = {y, head[x]}; head[x] = uuid;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++timer;
    stk[++top] = x;
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!idx[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if (low[x] == dfn[x]) {
        idx[x] = ++scc;
        ++sze[scc];
        while (stk[top] != x) {
            ++sze[scc];
            idx[stk[top]] = scc;
            --top;
        }
        --top;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
            link(a, b);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= scc; ++i)
        if (sze[i] > 1)
            ++ans;
    printf("%d\n", ans);
    return 0;
}