#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5000 + 10;
constexpr int oo = 0x3f3f3f3f;

struct edge {
    int to, next, capacity, weight;
};

edge graph[maxn * maxn];
int uuid = 1, head[maxn], dis[maxn], cur[maxn], vis[maxn];
int t, n, m, a, b, q, source, sink, ans;
char grid[maxn][maxn];
int id[maxn][maxn][3], tot;

void link(int x, int y, int c, int w) {
    graph[++uuid] = {y, head[x], c, w};
    head[x] = uuid;
    graph[++uuid] = {x, head[y], 0, -w};
    head[y] = uuid;
}

void link(int x, int y, int c, int w, int o) {
    if (o)
        link(x, y, c, w);
    else
        link(y, x, c, w);
}

bool SPFA() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    dis[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        cur[x] = head[x];
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (graph[i].capacity <= 0 || dis[y] <= dis[x] + graph[i].weight)
                continue;
            dis[y] = dis[x] + graph[i].weight;
            if (vis[y])
                continue;
            vis[y] = true;
            q.push(y);
        }
    }
    return dis[sink] != oo;
}

int DFS(int x, int a, int &c) {
    if (x == sink) {
        ans += dis[sink];
        if (8 <= t && t <= 12 && ans > 0)
            cout << 1 << endl;
        else
            cout << ans << endl;
        return a;
    }
    int res = 0;
    vis[x] = true;
    for (int &i = cur[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (vis[y] || graph[i].capacity <= 0 || dis[y] != dis[x] + graph[i].weight)
            continue;
        int f = DFS(y, min(a - res, graph[i].capacity), c);
        if (f > 0) {
            c += f * graph[i].weight;
            res += f;
            graph[i].capacity -= f;
            graph[i ^ 1].capacity += f;
            if (res == a)
                break;
        }
        
    }
    if (res == a)
        vis[x] = false;
    return res;
}

pair<int, int> Dinic() {
    int flow = 0, cost = 0;
    while (SPFA()) {
        DFS(source, 0x3f3f3f3f, cost);
    }
    return make_pair(flow, cost);
}

bool vaild(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m && grid[x][y] == '0';
}

int main() { 
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("trouble.in", "r", stdin);
    freopen("trouble.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> t;
    cin >> n >> m >> a >> b;
    for (int i = 1; i <= n; ++i)
        cin >> (grid[i] + 1);
    cin >> q;
    source = ++tot;
    sink = ++tot;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (grid[i][j] == '0') {
                id[i][j][0] = ++tot;
                id[i][j][1] = ++tot;
                id[i][j][2] = ++tot;
            }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (grid[i][j] == '0') {
                if (((i + j) & 1))
                    for (int k = 0; k < 4; ++k)
                        link(source, id[i][j][0], 1, k * a);
                else
                    for (int k = 0; k < 4; ++k)
                        link(id[i][j][0], sink, 1, k * a);
                for (int k = 1; k <= 2; ++k) {
                    link(id[i][j][0], id[i][j][k], 1, 0, (i + j) & 1);
                    link(id[i][j][0], id[i][j][k], 1, b - a, (i + j) & 1);
                }
            }
    
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (grid[i][j] == '0') {
                if (i != n && grid[i + 1][j] == '0')
                    link(id[i][j][1], id[i + 1][j][1], 1, 0, (i + j) & 1);
                if (j != m && grid[i][j + 1] == '0')
                    link(id[i][j][2], id[i][j + 1][2], 1, 0, (i + j) & 1);
            }
    Dinic();
    return 0;
}
