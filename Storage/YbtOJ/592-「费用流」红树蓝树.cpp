#include <bits/stdc++.h>
using namespace std;

template <typename T>
void read(T &res) {
    char ch;
    bool flag = false;
    res = 0;
    while (ch = getchar(), !isdigit(ch) && ch != '-')
        ;
    ch == '-' ? flag = true : res = ch ^ 48;
    while (ch = getchar(), isdigit(ch)) res = res * 10 + ch - 48;
    flag ? res = -res : 0;
}

constexpr int N = 1005;
constexpr int M = 1e6 + 5;
constexpr int Maxn = 0x3f3f3f3f;

int uuid = 1, n, src, des, ans, q1, q0, rtx, rty;
bool vis[N], walk[N];
int fa1[N], fa2[N], w[N], dis[N];
int h[M], lim1[N], lim2[N];
int tag1[N], tag2[N], lst[N], nxt[M], cst[M], to[M], flw[M];
vector<int> v1[N], v2[N];

void link(int x, int y, int z, int w) {
    nxt[++uuid] = lst[x];
    lst[x] = uuid;
    to[uuid] = y;
    flw[uuid] = z;
    cst[uuid] = w;
    nxt[++uuid] = lst[y];
    lst[y] = uuid;
    to[uuid] = x;
    flw[uuid] = 0;
    cst[uuid] = -w;
}

bool SPFA() {
    for (int i = 1; i <= des; ++i) dis[i] = Maxn, walk[i] = false;
    dis[h[1] = src] = 0;
    int t = 0, w = 1, x, y;
    while (t < w) {
        vis[x = h[++t]] = false;
        for (int e = lst[x]; e; e = nxt[e])
            if (y = to[e], flw[e] > 0 && dis[y] > dis[x] + cst[e]) {
                dis[y] = dis[x] + cst[e];
                if (!vis[y])
                    vis[h[++w] = y] = true;
            }
    }
    return dis[des] < Maxn;
}

int Dinic(int x, int flow) {
    if (x == des) {
        ans += flow * dis[des];
        return flow;
    }
    walk[x] = true;
    int y, del, res = 0;
    for (int e = lst[x]; e; e = nxt[e])
        if (y = to[e], !walk[y] && flw[e] > 0 && dis[y] == dis[x] + cst[e]) {
            del = Dinic(y, min(flow - res, flw[e]));
            if (del) {
                flw[e] -= del;
                flw[e ^ 1] += del;
                res += del;
                if (flow == res)
                    break;
            }
        }
    return res;
}

void MCMF() {
    int res = 0;
    while (SPFA()) res += Dinic(src, Maxn);
}

void DFS1(int x) {
    for (int i = 0, im = v1[x].size(); i < im; ++i) {
        int y = v1[x][i];
        if (y == fa1[x])
            continue;
        fa1[y] = x;
        DFS1(y);
    }
}
void DFS2(int x) {
    for (int i = 0, im = v2[x].size(); i < im; ++i) {
        int y = v2[x][i];
        if (y == fa2[x])
            continue;
        fa2[y] = x;
        DFS2(y);
    }
}

void DFS3(int x, int &v) {
    for (int i = 0, im = v1[x].size(); i < im; ++i) {
        int y = v1[x][i];
        if (y == fa1[x])
            continue;
        if (tag1[y] != Maxn) {
            v -= tag1[y];
            continue;
        }
        DFS3(y, v);
    }
}

void DFS4(int x, int &v) {
    for (int i = 0, im = v2[x].size(); i < im; ++i) {
        int y = v2[x][i];
        if (y == fa2[x])
            continue;
        if (tag2[y] != Maxn) {
            v -= tag2[y];
            continue;
        }
        DFS4(y, v);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("w.in", "r", stdin);
    freopen("w.out", "w", stdout);
#endif
    read(n);
    read(rtx);
    read(rty);
    src = n << 1 | 1;
    des = src + 1;
    for (int i = 1; i <= n; ++i) read(w[i]);
    for (int i = 1, x, y; i < n; ++i) {
        read(x);
        read(y);
        v1[x].push_back(y);
        v1[y].push_back(x);
    }
    for (int i = 1, x, y; i < n; ++i) {
        read(x);
        read(y);
        v2[x].push_back(y);
        v2[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) tag1[i] = tag2[i] = Maxn;
    read(q0);
    for (int i = 1, x, y; i <= q0; ++i) {
        read(x);
        read(y);
        tag1[x] = y;
    }
    read(q1);
    for (int i = 1, x, y; i <= q1; ++i) {
        read(x);
        read(y);
        tag2[x] = y;
    }

    DFS1(rtx);
    DFS2(rty);
    for (int i = 1; i <= n; ++i) lim1[i] = tag1[i], lim2[i] = tag2[i];
    for (int i = 1; i <= n; ++i)
        if (lim1[i] != Maxn)
            DFS3(i, lim1[i]);
    for (int i = 1; i <= n; ++i)
        if (lim2[i] != Maxn)
            DFS4(i, lim2[i]);
    for (int i = 1; i <= n; ++i)
        if (lim1[i] < 0 || lim2[i] < 0)
            return puts("-1"), 0;
    for (int i = 1; i <= n; ++i) {
        int u, v;
        for (u = i; tag1[u] == Maxn; u = fa1[u])
            ;
        for (v = i; tag2[v] == Maxn; v = fa2[v])
            ;
        link(u, v + n, 1, -w[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (lim1[i] != Maxn)
            link(src, i, lim1[i], 0);
    for (int i = 1; i <= n; ++i)
        if (lim2[i] != Maxn)
            link(i + n, des, lim2[i], 0);
    MCMF();
    bool flag = false;
    for (int e = lst[src]; e; e = nxt[e])
        if (flw[e] > 0) {
            flag = true;
            break;
        }
    for (int e = lst[des]; e; e = nxt[e])
        if (flw[e ^ 1] > 0) {
            flag = true;
            break;
        }
    printf("%d\n", flag ? -1 : -ans);
    return 0;
}
