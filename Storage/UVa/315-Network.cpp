#include <bits/stdc++.h>
using namespace std;

struct node {
    int to, nxt;
};

node e[200005];
int head[1001];
int dfn[1001], low[1001], cut[1001];
int tot, n, m, timer, cnt;

void link(int x, int y) {
    e[++tot].to = y; e[tot].nxt = head[x]; head[x] = tot;
}

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++timer;
    int children = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (u == fa)children++;
            if (u != fa && low[v] >= dfn[u]) cut[u] = 1;
        } else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (u == fa && children >= 2) cut[u] = 1;
}

void input() {
    int u, v;
    while (scanf("%d", &u) == 1 && u) {
        if (u == 0) break;
        while (1) {
            char c = getchar();
            if (c == '\n') break;
            scanf("%d", &v);
            link(u, v); link(v, u);
        }
    }
}

void solve() {
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cut[i]) {
            cnt++;
        }
    }
    printf("%d\n", cnt);
}

int main() {
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        memset(head, 0, sizeof(head));
        memset(cut, 0, sizeof(cut));
        memset(dfn, 0, sizeof(dfn));
        memset(cut, 0, sizeof(cut));
        timer = 0; tot = 0;
        input();
        solve();
    }
    return 0;
}