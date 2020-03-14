#include <bits/stdc++.h>
using namespace std;

struct e {
    int to, next;
};

constexpr int maxn = 1e6 + 5;
constexpr int maxm = 1e6 + 5;
e edge[maxm];
int uuid, n, m, root, ans, head[maxn], fa[maxn], dep[maxn];

void DFS(int x, int fa) {
    dep[x] = dep[fa] + 1;
    ans = max(ans, dep[x]);
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        DFS(y, x);
    }
}

inline void link(int x, int y) {
    edge[++uuid] = {y, head[x]}; head[x] = uuid;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (x) {
            link(i, x);
            fa[x] = i;
        }
        if (y) {
            link(i, y);
            fa[y] = i;
        }
    }
    while (fa[++root]);
    DFS(root, 0);
    printf("%d\n",ans);
    return 0;
}