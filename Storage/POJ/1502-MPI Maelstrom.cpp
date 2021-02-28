#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

template <typename T>
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

struct e {
    int to, weigth, next;
};

const int maxn = 100 + 5;
e edge[maxn * maxn];
int head[maxn], dis[maxn], vis[maxn], uuid, n;
priority_queue<pair<int, int> > q;

void link(int x, int y, int w) {
    edge[++uuid] = {y, w, head[x]};
    head[x] = uuid;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    n = read<int>();
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            char str[50];
            scanf("%s", str);
            if (str[0] == 'x')
                continue;
            int v = atoi(str);
            link(i, j, v);
            link(j, i, v);       
        }
    }
    memset(dis, 0x3f, sizeof(dis));
    q.push(make_pair(0, 1));
    dis[1] = 0;
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x], y, w; y = edge[i].to, w = edge[i].weigth, i; i = edge[i].next) {
            if (dis[y] > dis[x] + w) {
                dis[y] = dis[x] + w;
                if (vis[y])
                    continue;
                q.push(make_pair(-dis[y], y));
            }
        }
    }
    printf("%d\n", *max_element(dis + 1, dis + 1 + n));
    return 0;
}