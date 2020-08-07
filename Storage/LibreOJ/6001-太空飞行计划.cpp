#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 120;

struct e {
    int to, next, capacity;
};

e edge[maxn * maxn * 10];
int uuid = 1, head[maxn], cur[maxn], dis[maxn], vis[maxn];
int n, m, source, sink, sum;
set<int> need[maxn];

void link(int x, int y, int c) {
    edge[++uuid] = {y, head[x], c};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0};
    head[y] = uuid;
}

bool BFS() {
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
            q.push(y);
            dis[y] = dis[x] + 1;
            cur[y] = head[y];
        }
    }
    return dis[sink];
}

int DFS(int x, int a) {
    if (x == sink)
        return a;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (edge[i].capacity <= 0 || dis[y] != dis[x] + 1)
            continue;
        int f = DFS(y, min(edge[i].capacity, a - res));
        if (f > 0) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            res += f;
            if (res == a)
                break;
        }
    }
    if (res != a)
        dis[x] = 0;
    return res;
}

int Dinic() {
    int res = 0;
    while (BFS())
        res += DFS(source, 0x3f3f3f3f);
    return res;
}

void DFS2(int x) {
    vis[x] = true;
    for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (edge[i].capacity > 0 && !vis[y]) {
            vis[y] = true;
            DFS2(y);
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%d", &m, &n);
    source = m + n + 1;
    sink = source + 1;
    for (int i = 1; i <= m; ++i) {
        int p;
        scanf("%d", &p);
        sum += p;
        link(source, i, p);
        char tools[10000];
        memset(tools, 0, sizeof tools);
        cin.getline(tools, 10000);
        int ulen = 0, tool;
        while (sscanf(tools + ulen, "%d", &tool) == 1) {
            link(i, m + tool, 0x3f3f3f3f);
            if (tool == 0)
                ulen++;
            else {
                while (tool) {
                    tool /= 10;
                    ulen++;
                }
            }
            ulen++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        int v;
        scanf("%d", &v);
        link(m + i, sink, v);
    }
    int ans = sum - Dinic();
    DFS2(source);
    vector<int> tmp;
    for (int i = 1; i <= m; ++i)
        if (dis[i])
            tmp.push_back(i);
    for (int i = 0; i < tmp.size(); ++i) {
        printf("%d", tmp[i]);
        if (i != tmp.size() - 1)
            printf(" ");
    }
    printf("\n");
    tmp.clear();
    for (int i = m + 1; i <= n + m; ++i)
        if (dis[i])
            tmp.push_back(i - m);
    for (int i = 0; i < tmp.size(); ++i) {
        printf("%d", tmp[i]);
        if (i != tmp.size() - 1)
            printf(" ");
    }
    printf("\n%d\n", ans);
    return 0;
}