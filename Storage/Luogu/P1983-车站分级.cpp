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

constexpr int maxn = 1000 + 2;

struct e {
    int to, next;
};

bool suspend[maxn], connected[maxn][maxn];
int tmp[maxn];
e edge[maxn * maxn];
int head[maxn], uuid, in[maxn];
int f[maxn];
int n, m, ans;
queue<int> q;

void link(int x, int y) {
    edge[++uuid] = {y, head[x]};
    head[x] = uuid;
    ++in[y];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    m = read();
    for (int i = 1; i <= m; ++i) {
        memset(suspend, 0, sizeof(suspend));
        int t = read();
        for (int j = 1; j <= t; ++j) {
            tmp[j] = read();
            suspend[tmp[j]] = true;
        }
        for (int j = tmp[1]; j <= tmp[t]; ++j) {
            if (!suspend[j]) {
                for (int k = 1; k <= t; ++k) {
                    if (!connected[j][tmp[k]]) {
                        connected[j][tmp[k]] = true;
                        link(j, tmp[k]);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = 1;
        if (in[i] == 0)
            q.push(i);
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            f[y] = max(f[y], f[x] + 1);
            if (--in[y] == 0)
                q.push(y);
        }
        ans = max(ans, f[x]);
    }
    printf("%d\n", ans);
    return 0;
}