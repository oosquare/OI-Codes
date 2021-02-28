#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

constexpr int maxn = 100000 + 10;

struct g {
    struct e {
        int to, next;
    } edges[maxn];
    int head[maxn], uuid;

    void link(int x, int y) {
        edges[++uuid] = {y, head[x]};
        head[x] = uuid;
    }
} g1, g2;

int cnt[maxn], idx[maxn], scccnt;
int dfn[maxn], low[maxn], timer;
bool vis[maxn];
int f[maxn], father[maxn];
stack<int> stk;
int n;

void tarjan(g& gr, int x) {
    dfn[x] = low[x] = ++timer;
    stk.push(x);
    for (int i = gr.head[x]; i; i = gr.edges[i].next) {
        int y = gr.edges[i].to;
        if (!dfn[y]) {
            tarjan(gr, y);
            low[x] = min(low[x], low[y]);
        } else {
            if (!idx[y]) {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }
    if (low[x] == dfn[x]) {
        idx[x] = ++scccnt;
        cnt[scccnt] = 1;
        while (stk.top() != x) {
            ++cnt[scccnt];
            idx[stk.top()] = scccnt;
            stk.pop();
        }
        stk.pop();
    }
}

void build(g& g1, g& g2) {
    for (int i = 1; i <= n; ++i) {
        for (int j = g1.head[i]; j; j = g1.edges[j].next) {
            int k = g1.edges[j].to;
            if (idx[k] == idx[i])
                continue;
            g2.link(idx[k], idx[i]);
            father[idx[i]] = idx[k];
        }
    }
}

void DP(g& gr, int x, int fa) {
    f[x] = cnt[x] + f[fa];
    for (int i = gr.head[x]; i; i = gr.edges[i].next) {
        int y = gr.edges[i].to;
        DP(gr, y, x);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i <= n; ++i) {
        int x = read();
        g1.link(i, x);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(g1, i);
    build(g1, g2);
    for (int i = 1; i <= scccnt; ++i)
        if (!father[i])
            DP(g2, i, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", f[idx[i]]);
    return 0;
}