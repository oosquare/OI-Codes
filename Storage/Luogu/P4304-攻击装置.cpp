#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 300 + 10;

struct e {
    int to, next;
};

e edge[maxn * maxn * 10];
int head[maxn * maxn], uuid;
int match[maxn * maxn], vis[maxn * maxn];
int n, m, ans;
int dir[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
int ground[maxn][maxn];

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
    edge[++uuid] = {x, head[y]};
    head[y] = uuid;
}

bool vaild(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n && ground[x][y] == 0;
}

bool find(int x) {
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (vis[y])
            continue;
        vis[y] = true;
        if (!match[y] || find(match[y])) {
            match[y] = x;
            return true;
        }
    }
    return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%1d", &ground[i][j]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!vaild(i, j)) {
                ++m;
                continue;
            }
            for (int k = 0; k < 8; ++k) {
                int ni = i + dir[k][0], nj = j + dir[k][1];
                if (!vaild(ni, nj))
                    continue;
                link(n * (i - 1) + j,  n * (ni - 1) + nj);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            memset(vis, 0, sizeof(vis));
            if (vaild(i, j) && (i + j) % 2 && find(n * (i - 1) + j))
                ++ans;
        }
        
    }
    printf("%d\n", n * n - ans - m);
    return 0;
}