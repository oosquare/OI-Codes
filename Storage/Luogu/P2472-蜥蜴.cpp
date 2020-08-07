#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1000 + 10;
constexpr int maxm = 16000 + 10;

struct e {
    int to, next, capacity;
};

e edge[maxm * 2];
int head[maxn], uuid = 1;
int cur[maxn], dis[maxn];
int r, c, d, source, sink, cnt, ground[maxn][maxn];
char pos[maxn][maxn];
int id[maxn][maxn];


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
        int f = DFS(y, min(edge[i].capacity, a - res), sink);
        if (f > 0) {
            edge[i].capacity -= f;
            edge[i ^ 1].capacity += f;
            res += f;
            if (a == res)
                break;
        }
    }
    if (a != res)
        dis[x] = 0;
    return res;
}

bool check(int x, int y) {
    if (min(min(x - 1, y - 1), min(r - x, c - y)) < d)
    	return true;
    return false;
}

bool vaild(int x, int y) {
    if (1 <= x && x <= r && 1 <= y && y <= c)
        return true;
    return false;
}

int Dinic(int source, int sink) {
    int res = 0;
    while (BFS(source, sink)) {
        res += DFS(source, 0x3f3f3f3f, sink);
	}
    return res;
}

int distance(int x, int y, int a, int b) {
    return pow((x - a), 2) + pow((y - b), 2);
}

void build() {
    source = 1, sink = 2;
    int nextid = 2;
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            id[i][j] = ++nextid;
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            if (ground[i][j] > 0 && check(i, j))
                link(id[i][j] + r * c, sink, 0x3f3f3f3f);
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            for (int k = 1; k <= r; ++k) {
                for (int l = 1; l <= c; ++l) {
                    if (i == k && j == l)
                        continue;
                    if (ground[i][j] > 0 && ground[k][l] > 0 && distance(i, j, k, l) <= d * d)
                        link(id[i][j] + r * c, id[k][l], 0x3f3f3f3f);
                }
            }
        }
    }
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
        	if (ground[i][j] > 0)
            link(id[i][j], id[i][j] + r * c, ground[i][j]);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            if (pos[i][j] == 'L')
                link(source, id[i][j], 1), ++cnt;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    scanf("%d%d%d", &r, &c, &d);
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            scanf("%1d", &ground[i][j]);
    for (int i = 1; i <= r; ++i)
        scanf("%s", pos[i] + 1);
    
    build();
    printf("%d\n", cnt - Dinic(source, sink));
    return 0;
}