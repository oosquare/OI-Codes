#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

template <typename T = int>
T read() {
    T x = 0, s = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

struct edge {
    int to, weight, next;
};

typedef long long ll;

const int maxn = 10000 + 5;
edge tree[maxn * 2];
int uuid, head[maxn];
ll f[maxn][3];
int idx[maxn];
int n;

void link(int x, int y, int w) {
    tree[++uuid] = {y, w, head[x]};
    head[x] = uuid;
}

void DFS1(int x, int fa) {
    ll res = 0, res2 = 0;
    for (int i = head[x], y, w; y = tree[i].to, w = tree[i].weight, i; i = tree[i].next) {
        if (y == fa)
            continue;
        DFS1(y, x);
        if (res <= f[y][0] + w) {
            res2 = res;
            res = f[y][0] + w;
            idx[x] = y;
        } else if (res2 < f[y][0] + w) {
            res2 = f[y][0] + w;
        } else if (res2 < f[y][1] + w) {
            res2 = f[y][1] + w;
        }
    }
    f[x][0] = res;
    f[x][1] = res2;
}

void DFS2(int x, int fa) {
    for (int i = head[x], y, w; y = tree[i].to, w = tree[i].weight, i; i = tree[i].next) {
        if (y == fa)
            continue;
        if (idx[x] == y)
            f[y][2] = max(f[x][1] + w, f[x][2] + w);
        else
            f[y][2] = max(f[x][0] + w, f[x][2] + w);
        DFS2(y, x);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    while (scanf("%d", &n) != EOF) {
        memset(f, 0, sizeof(f));
        memset(head, 0, sizeof(head));
        uuid = 0;
        for (int i = 2; i <= n; ++i) {
            int x = read(), y = read();
            link(i, x, y);
            link(x, i, y);
        }
        DFS1(1, 0);
        DFS2(1, 0);
        for (int i = 1; i <= n; ++i)
            printf("%lld\n", max(f[i][0], f[i][2]));
    }
    
    return 0;
}
