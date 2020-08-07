#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 150;
const int maxm = 100000;
const int oo = 0x3f3f3f3f;

struct e {
    int to, next, capacity, weight;
};

e edge[maxm];
int uuid = 1, head[maxn], dis[maxn], vis[maxn], cur[maxn];
int n, m, source, sink, casenum, cnt, ans;

void link(int x, int y, int c, int w) {
    edge[++uuid] = {y, head[x], c, w};
    head[x] = uuid;
    edge[++uuid] = {x, head[y], 0, -w};
    head[y] = uuid;
}

bool SPFA() {
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);
    queue<int> q;
    q.push(source);
    dis[source] = 0;
    vis[source] = true;
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
    return dis[sink] != oo;
}

int DFS(int x, int a, int &c) {
    if (x == sink) {
        ++cnt;
        if (cnt == 1 || cnt == 2)
            ans += dis[sink];
        return a;
    }
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

pair<int, int> Dinic() {
    int flow = 0, cost = 0;
    while (SPFA())
        flow += DFS(source, oo, cost);
    return make_pair(flow, cost);
}

int main() {
    while (scanf("%d%d", &n, &m) && n && m) {
        memset(head, 0, sizeof head);
        uuid = 1;
        ans = 0;
        cnt = 0;
        for (int i = 1; i <= m; ++i) {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            ++x, ++y;
            if (x != 1) 
            	link(x + n, y, 1, w);
            else
            	link(x, y, 1, w);
        }
        for (int i = 2; i < n; ++ i) {
            link(i, i + n, 1, 0);
        }
        source = 1;
        sink = n;
        pair<int, int> res = Dinic();
        printf("Instance #%d: ", ++casenum);
        if (res.first < 2)
            printf("Not possible\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}
