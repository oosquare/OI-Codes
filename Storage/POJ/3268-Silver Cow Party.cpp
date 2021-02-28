#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T>
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

const int maxn = 1000 + 10;
const int maxm = 100000 + 10;

struct g {
    struct e {
        int to, weight, next;
    } ee[maxm];
    int uuid, head[maxn], dis[maxn], vis[maxn];

    void link(int x, int y, int w) {
        ee[++uuid] = {y, w, head[x]};
        head[x] = uuid;
    }

    void shortest(int s) {
        memset(dis, 0x3f, sizeof(dis));
        dis[s] = 0;
        priority_queue<pair<int, int> > q;
        q.push(make_pair(0, s));
        while (!q.empty()) {
            int x = q.top().second;
            q.pop();
            if (vis[x])
                continue;
            vis[x] = true;
            for (int i = head[x], y, w; y = ee[i].to, w = ee[i].weight, i; i = ee[i].next) {
                if (dis[y] > dis[x] + w) {
                     dis[y] = dis[x] + w;
                    if (!vis[y])
                        q.push(make_pair(-dis[y], y));
                }
                   
            }
        }
    }
} g1, g2;

int n, m, x;

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read<int>();
    m = read<int>();
    x = read<int>();
    for (int i = 1; i <= m; ++i) {
        int a = read<int>(), b = read<int>(), c = read<int>();
        g1.link(a, b, c);
        g2.link(b, a, c);
    }
    g1.shortest(x);
    g2.shortest(x);
    int res = 0;
    for (int i = 1; i <= n; ++i)
        res = max(res, g1.dis[i] + g2.dis[i]);
    printf("%d\n", res);
    return 0;
}