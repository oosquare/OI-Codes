#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int N = 1e3 + 5, M = 1e5 + 5;
 
struct e {
    int to, next, capacity, weight;
};

e edge[M];
long long dis[N];
int uuid = 1, head[N], vis[N], cur[N];
int n, m, source, sink;

void link(int x, int y, int c, int w) {
    edge[++uuid] = {y, head[x], c, w};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0, -w};
    head[y] = uuid;
}

int SPFA() {
	for (int i = 1; i <= n + m + 2; ++i)
		dis[i] = 1e18, vis[i] = 0;
    queue<int> q;
    q.push(source);
    dis[source] = 0;
    cur[source] = head[source];
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        for (int i = head[x], y; y = edge[i].to, i; i = edge[i].next) {
            if (edge[i].capacity <= 0 || dis[y] <= dis[x] + edge[i].weight)
                continue;
            dis[y] = dis[x] + edge[i].weight;
            cur[y] = head[y];
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != 1e18;
}

int DFS(int x, int a, long long &c) {
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
            c += edge[i].weight * f;
            if (res == a)
                break;
        }
    }
    if (res == a)
        vis[x] = false;
    return res;
}

long long Dinic() {
    long long res = 0;
    while (SPFA())
        DFS(source, INT_MAX, res);
    return res;
}

signed main() {
/*    #ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif*/
    scanf("%lld%lld", &m, &n);
    source = m + n + 1;
    sink = m + n + 2;
    for (int i = 1; i <= n; ++i) {
    	int c;
        scanf("%lld", &c);
        link(m + i, sink, c, 0);
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int a;
            scanf("%lld", &a);
            if (a == 1)
                link(i, m + j, INT_MAX, 0);
        }
    }
    
    for (int i = 1; i <= m; ++i) {
        int s;
        scanf("%lld", &s);
        int t[7], w[7];
        t[0] = 0;
        for (int j = 1; j <= s; ++j)
            scanf("%lld", &t[j]);
        for (int j = 1; j <= s + 1; ++j)
            scanf("%lld", &w[j]);
        for (int j = 1; j <= s; ++j) {
            int c = t[j] - t[j - 1];
            link(source, i, c, w[j]);
        }
        link(source, i, INT_MAX, w[s + 1]);
    }
    printf("%lld\n", Dinic());
    return 0;
}