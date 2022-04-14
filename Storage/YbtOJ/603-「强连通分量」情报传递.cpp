#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 100100;
constexpr int maxm = 200100;
constexpr int maxb = 20000;

int n, m, qs;

struct edge {
    int u, v;
} e[maxm];

struct querys {
    int u, v;
} q[maxn];

int tot, head[maxn], ver[maxm], nxt[maxm];
int timer, dfn[maxn], low[maxn];
int top, s[maxn];
int scc, ins[maxn], c[maxn];
int totc, headc[maxn], verc[maxm], nxtc[maxm];
int deg[maxn];
int len;
querys seq[maxn];
int ttt, a[maxn];
bitset<maxb + 10> f[maxn];

void add(int u, int v) {
    ver[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    s[++top] = u, ins[u] = 1;

    for (int i = head[u]; i; i = nxt[i]) {
        int v = ver[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        scc++;
        int v;
        do {
            v = s[top--], ins[v] = 0, c[v] = scc;
        } while (u != v);
    }
}

void add_c(int u, int v) {
    verc[++totc] = v;
    nxtc[totc] = headc[u];
    headc[u] = totc;
    deg[v]++;
}

bool cmp(querys a, querys b) { return a.v < b.v; }

void topsort() {
    queue<int> q;
    for (int i = 1; i <= scc; i++)
        if (deg[i] == 0)
            q.push(i);
    while (q.size()) {
        int u = q.front();
        q.pop();
        a[++ttt] = u;
        for (int i = headc[u]; i; i = nxtc[i]) {
            int v = verc[i];
            if (--deg[v] == 0)
                q.push(v);
        }
    }
}

void calc() {
    for (int i = ttt; i >= 1; i--) {
        int u = a[i];
        for (int j = headc[u]; j; j = nxtc[j]) {
            int v = verc[j];
            f[u] |= f[v];
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
        if (c[u] == c[v])
            continue;
        add_c(c[u], c[v]);
    }

    topsort();
    cin >> qs;
    for (int i = 1; i <= qs; i++) {
        int u, v;
        cin >> u >> v;
        q[i] = {c[u], c[v]};
    }
    len = 0;
    for (int i = 1; i <= qs; i++)
        if (1 <= q[i].v && q[i].v <= maxb)
            seq[++len] = q[i];
    for (int i = 1; i <= scc; i++)
        f[i].reset();
    for (int i = 1; i <= maxb; i++)
        f[i][i] = 1;
    calc();
    for (int i = 1; i <= len; i++) {
        int u = seq[i].u, v = seq[i].v;
        if (f[u][v]) {
            cout << "NO" << endl;
            return;
        }
    }
    len = 0;
    for (int i = 1; i <= qs; i++)
        if (maxb + 1 <= q[i].v && q[i].v <= 2 * maxb)
            seq[++len] = q[i];
    for (int i = 1; i <= scc; i++)
        f[i].reset();
    for (int i = 1; i <= maxb; i++)
        f[i + maxb][i] = 1;
    calc();
    for (int i = 1; i <= len; i++) {
        int u = seq[i].u, v = seq[i].v;
        if (f[u][v - maxb]) {
            cout << "NO" << endl;
            return;
        }
    }
    len = 0;
    for (int i = 1; i <= qs; i++)
        if (2 * maxb + 1 <= q[i].v && q[i].v <= 3 * maxb)
            seq[++len] = q[i];
    for (int i = 1; i <= scc; i++)
        f[i].reset();
    for (int i = 1; i <= maxb; i++)
        f[i + 2 * maxb][i] = 1;
    calc();
    for (int i = 1; i <= len; i++) {
        int u = seq[i].u, v = seq[i].v;
        if (f[u][v - 2 * maxb]) {
            cout << "NO" << endl;
            return;
        }
    }
    len = 0;
    for (int i = 1; i <= qs; i++)
        if (3 * maxb + 1 <= q[i].v && q[i].v <= 4 * maxb)
            seq[++len] = q[i];
    for (int i = 1; i <= scc; i++)
        f[i].reset();
    for (int i = 1; i <= maxb; i++)
        f[i + 3 * maxb][i] = 1;
    calc();
    for (int i = 1; i <= len; i++) {
        int u = seq[i].u, v = seq[i].v;
        if (f[u][v - 3 * maxb]) {
            cout << "NO" << endl;
            return;
        }
    }
    len = 0;
    for (int i = 1; i <= qs; i++)
        if (4 * maxb + 1 <= q[i].v && q[i].v <= 5 * maxb)
            seq[++len] = q[i];
    for (int i = 1; i <= scc; i++)
        f[i].reset();

    for (int i = 1; i <= maxb; i++)
        f[i + 4 * maxb][i] = 1;

    calc();
    for (int i = 1; i <= len; i++) {
        int u = seq[i].u, v = seq[i].v;
        if (f[u][v - 4 * maxb]) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
    cout << m << endl;
    for (int i = 1; i <= m; i++)
        cout << e[i].u << " " << e[i].v << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("gplt.in", "r", stdin);
    freopen("gplt.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        e[i] = {u, v};
    }
    solve();
    return 0;
}
