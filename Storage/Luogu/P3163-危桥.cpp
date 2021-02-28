#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 60;
constexpr int maxm = 5000;

struct e {
    int to, next, capacity;
};

e edge[maxm];
int uuid = 1, head[maxn], cur[maxn], dis[maxn];
int n, a1, a2, an, b1, b2, bn, source = 1, sink = 2;
char matrix[maxn][maxn];

void link(int x, int y, int c) {
    edge[++uuid] = {y, head[x], c};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

bool BFS(int source, int sink) {
    memset(dis, 0, sizeof(dis));
    queue<int> q;
    q.push(source);
    dis[source] = 1;
    cur[source] = head[source];
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y])
                continue;
            dis[y] = dis[x] + 1;
            cur[y] = head[y];
            q.push(y);
        }
    }
    return dis[sink];
}

int DFS(int x, int a, int s) {
    if (x == s)
        return a;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (edge[i].capacity <= 0 || dis[y] != dis[x] + 1)
            continue;
        int tmp = DFS(y, min(edge[i].capacity, a - res), s);
        if (tmp > 0) {
            edge[i].capacity -= tmp;
            edge[i ^ 1].capacity += tmp;
            res += tmp;
            if (res == a)
                break;
        }
    }
    if (res != a)
        dis[x] = 0;
    return res;
}

int Dinic(int source, int sink) {
    int res = 0;
    while (BFS(source, sink))
        res += DFS(source, 0x3f3f3f3f, sink);
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    while (scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn) != EOF) {
        a1 += 3, a2 += 3, b1 += 3, b2 += 3;
        for (int i = 1; i <= n; ++i)
            scanf("%s", matrix[i] + 1);

        memset(head, 0, sizeof(head));
        uuid = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j)
                    continue;
                if (matrix[i][j] == 'O')
                    link(i + 2, j + 2, 2);
                else if (matrix[i][j] == 'N')
                    link(i + 2, j + 2, 0x3f3f3f3f);
            }
        }
        link(source, a1, an * 2);
        link(source, b1, bn * 2);
        link(a2, sink, an * 2);
        link(b2, sink, bn * 2);
        int res1 = Dinic(source, sink);

        memset(head, 0, sizeof(head));
        uuid = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j)
                    continue;
                if (matrix[i][j] == 'O')
                    link(i + 2, j + 2, 2);
                else if (matrix[i][j] == 'N')
                    link(i + 2, j + 2, 0x3f3f3f3f);
            }
        }
        link(source, a1, an * 2);
        link(source, b2, bn * 2);
        link(a2, sink, an * 2);
        link(b1, sink, bn * 2);
        int res2 = Dinic(source, sink);

        printf("%s\n", (res1 == 2 * (an + bn) && res2 == 2 * (an + bn)) ? "Yes" : "No");
    }
    return 0;
}