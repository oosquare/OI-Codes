#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 50 + 10;

struct edge {
    int to, next;
};

edge graph[maxn * maxn * 100];
int uuid, head[maxn * maxn * 2];
int match[maxn * maxn * 2], vis[maxn * maxn * 2];
int n, m, tot1, tot2, ans;
char mapp[maxn][maxn];
int id[maxn][maxn][2];

void link(int x, int y) {
    graph[++uuid] = {y, head[x]};
    head[x] = uuid;
}

bool find(int x) {
    for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
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
#else
    freopen("bomb.in", "r", stdin);
    freopen("bomb.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> (mapp[i] + 1);
    for (int i = 1; i <= n; ++i) {
        int tmp[maxn], l = 0;
        tmp[++l] = 0;
        for (int j = 1; j <= m; ++j)
            if (mapp[i][j] == '#')
                tmp[++l] = j;
        tmp[++l] = m + 1;
        for (int j = 1; ++tot1, j < l; ++j)
            for (int k = tmp[j] + 1; k <= tmp[j + 1] - 1; ++k)
                id[i][k][0] = tot1;
        --tot1;
    }
    for (int i = 1; i <= m; ++i) {
        int tmp[maxn], l = 0;
        tmp[++l] = 0;
        for (int j = 1; j <= n; ++j)
            if (mapp[j][i] == '#')
                tmp[++l] = j;
        tmp[++l] = n + 1;
        for (int j = 1; ++tot2, j < l; ++j)
            for (int k = tmp[j] + 1; k <= tmp[j + 1] - 1; ++k)
                id[k][i][1] = tot2;
        --tot2;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (mapp[i][j] == '*')
                link(id[i][j][0], tot1 + id[i][j][1]);
    for (int i = 1; i <= tot1; ++i) {
        memset(vis, 0, sizeof(vis));
        if (find(i))
            ++ans;
    }
    cout << ans << endl;
    return 0;
}
