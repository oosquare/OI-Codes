// 评测机 NMSL 爬
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 5000 + 10;
const int oo = 0x7fffffff;

struct e {
    int to, next, capacity, weight;
};

e edge[maxn * 100];
int head[maxn], uuid = 1, dis[maxn], vis[maxn], cur[maxn];
int n, k, source, sink, matrix[maxn][maxn];

void link(int x, int y, int c, int w) {
    edge[++uuid] = {y, head[x], c, w};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0, -w};
    head[y] = uuid;
}

bool SPFA() {
    for (int i = 1; i <= sink; ++i)
    	dis[i] = -oo;
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(source);
    dis[source] = 0;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        cur[x] = head[x];
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y] >= dis[x] + edge[i].weight)
                continue;
            dis[y] = dis[x] + edge[i].weight;
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != -oo;
}

int DFS(int x, int a, int &c) {
    if (x == sink)
        return a;
    vis[x] = true;
    int res = 0;
    for (int &i = cur[x], y; y = edge[i].to, i; i = edge[i].next) {
        if (vis[y] || edge[i].capacity <= 0 || dis[y] != dis[x] + edge[i].weight)
            continue;
        int f = DFS(y, min(edge[i].capacity, a - res), c);
        if (f > 0) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            res += f;
            c += f * edge[i].weight;
            if (res == a)
                break;
        }
    }
    if (res == a)
        vis[x] = false;
    return res;
}

int Dinic() {
    int cost = 0;
    while (SPFA())
        DFS(source, oo, cost);
    return cost;
}

int id(int i, int j) {
    return (i - 1) * n + j;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    source = n * n * 2 + 1;
    sink = source + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &matrix[i][j]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
        	link(id(i, j), id(i, j) + n * n, 1, matrix[i][j]);
        	link(id(i, j), id(i, j) + n * n, oo, 0);
            if (j < n)
            	link(id(i, j) + n * n, id(i, j + 1), oo, 0);
            if (i < n)
            	link(id(i, j) + n * n, id(i + 1, j), oo, 0);
        }
    }
    link(source, id(1, 1), k, 0);
    link(id(n, n) + n * n, sink, k, 0);
    
    printf("%d\n", Dinic());
    return 0;
}