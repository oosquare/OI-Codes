#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6 + 10;
constexpr int oo = 0x3f3f3f3f;

struct edge {
    int to, next, weight;
};

struct node {
    int key, dis, ls, rs;
};

edge graph[maxn];
int uuid, head[maxn], vis[maxn], dis[maxn];
node heap[maxn];
int uuid2, root[maxn];
vector<int> tree[3][maxn];
int dep[maxn], step[maxn][20];
int info[maxn][3];
int n, m, ans[maxn];

void link(int x, int y, int w) {
    graph[++uuid] = {y, head[x], w};
    head[x] = uuid;
}

void dijkstra(int s) {
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = true;
        for (int i = head[x], y; y = graph[i].to, i; i = graph[i].next) {
            if (dis[y] <= dis[x] + graph[i].weight)
                continue;
            dis[y] = dis[x] + graph[i].weight;
            q.push(make_pair(-dis[y], y));
        }
    }
}

void preprocess(int x, int fa) {
    dep[x] = dep[fa] + 1;
    for (int i = 0; step[x][i]; ++i)
        step[x][i + 1] = step[step[x][i]][i];
    for (int y : tree[0][x]) {
        if (y == fa)
            continue;
        step[y][0] = x;
        preprocess(y, x);
    }
}

int LCA(int x, int y) {
    if (x == y)
        return x;
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 17; i >= 0; --i) {
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];
        if (x == y)
            return x;
    }
    for (int i = 17; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }
    return step[x][0];
}

int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (heap[x].key > heap[y].key)
        swap(x, y);
    heap[x].rs = merge(heap[x].rs, y);
    if (heap[heap[x].ls].dis < heap[heap[x].rs].dis)
        swap(heap[x].ls, heap[x].rs);
    heap[x].dis = heap[heap[x].rs].dis + 1;
    return x;
}

int remove(int x) {
    return merge(heap[x].ls, heap[x].rs); 
}

int create(int key) {
    heap[++uuid2] = {key, 0, 0, 0};
    return uuid2;
}

void DFS(int x) {
    int u = 0;
    for (int y : tree[0][x]) {
        if (y == step[x][0])
            continue;
        DFS(y);
        u = merge(root[y], u);
    }
    for (int y : tree[1][x])
        u = merge(u, y);
    for (int y : tree[2][x])
        vis[y] = true;
    while (u && vis[u])
        u = remove(u);
    root[x] = u;
    ans[x] = !u ? -1 : heap[u].key - dis[x];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("pal.in", "r", stdin);
    freopen("pal.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m;
    heap[0].dis = -1;
    for (int i = 1; i <= m; ++i) {
        cin >> info[i][0] >> info[i][1] >> info[i][2];
        link(info[i][0], info[i][1], info[i][2]);
        link(info[i][1], info[i][0], info[i][2]);
    }
    dijkstra(1);
    for (int i = 1; i <= m; ++i) {
        if (dis[info[i][0]] == oo && dis[info[i][1]] == oo)
            continue;
        if (dis[info[i][0]] + info[i][2] == dis[info[i][1]])
            tree[0][info[i][0]].push_back(info[i][1]);
        else if (dis[info[i][1]] + info[i][2] == dis[info[i][0]])
            tree[0][info[i][1]].push_back(info[i][0]);
    }
    memset(vis, 0, sizeof(vis));
    memset(ans, -1, sizeof(ans));
    preprocess(1, 0);
    for (int i = 1; i <= m; ++i) {
        if (dis[info[i][0]] == oo && dis[info[i][1]] == oo)
            continue;
        if (dis[info[i][0]] + info[i][2] != dis[info[i][1]] &&
            dis[info[i][1]] + info[i][2] != dis[info[i][0]]) {
            int x = info[i][0], y = info[i][1], w = info[i][2], lca = LCA(x, y);
            int id = create(dis[x] + dis[y] + w);
            tree[1][x].push_back(id);
            tree[2][lca].push_back(id);
            id = create(dis[x] + dis[y] + w);
            tree[1][y].push_back(id);
            tree[2][lca].push_back(id);
            
        }
    }
    DFS(1);
    for (int i = 2; i <= n; ++i)
        cout << ans[i] << endl;
    return 0;
}
