#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

constexpr int MAXN = 1000 + 10;
constexpr int INFINITY = 0x3f3f3f3f;

namespace NetworkFlow {

struct Edge {
    int to, next, cap;
};

Edge graph[MAXN * 100];
int head[MAXN], tot = 1;
int cur[MAXN], dis[MAXN];
int source, sink;

void clear(int n) {
    memset(head, 0, sizeof head);
    tot = 1;
    source = n + 1;
    sink = n + 2;
}

int link(int x, int y, int c) {
    graph[++tot] = { y, head[x], c };
    head[x] = tot;
    graph[++tot] = { x, head[y], 0 };
    head[y] = tot;
    return tot - 1;
}

bool bfs() {
    memset(dis, 0, sizeof dis);
    queue<int> q;
    dis[source] = 1;
    q.push(source);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cur[x] = head[x];

        for (int i = head[x]; i; i = graph[i].next) {
            int y = graph[i].to;

            if (graph[i].cap <= 0 || dis[y])
                continue;

            dis[y] = dis[x] + 1;
            q.push(y);
        }
    }

    return dis[sink];
}

int dfs(int x, int a) {
    if (x == sink)
        return a;

    int res = 0, tmp;

    for (int& i = cur[x], y; y = graph[i].to, i; i = graph[i].next) {
        if (graph[i].cap <= 0 || dis[y] != dis[x] + 1)
            continue;

        tmp = dfs(y, min(graph[i].cap, a - res));

        if (tmp > 0) {
            graph[i].cap -= tmp;
            graph[i ^ 1].cap += tmp;
            res += tmp;

            if (res == a)
                break;
        }
    }

    if (res != a)
        dis[x] = 0;

    return res;
}

int dinic() {
    int res = 0;

    while (bfs())
        res += dfs(source, INFINITY);

    return res;
}

} // namespace NetworkFlow

namespace EulerGraph {

struct Edge {
    int to, next;
    bool del;
};

Edge graph[MAXN * 100];
int head[MAXN], tot;

void link(int x, int y) {
    graph[++tot] = { y, head[x], false };
    head[x] = tot;
}

void dfs(int x, vector<int>& seq) {
    for (int i = head[x]; i; i = graph[i].next) {
        if (graph[i].del)
            continue;

        int y = graph[i].to;
        graph[i].del = true;
        dfs(y, seq);
        seq.push_back(i);
    }
}

vector<int> solve() {
    vector<int> res;
    dfs(1, res);
    reverse(res.begin(), res.end());
    return res;
}

} // namespace EulerGraph

struct Edge {
    int from, to, val, rval;
};

int n, m, l, r, ans;
Edge edges[MAXN * 100];
int deg[MAXN], id[MAXN * 100];

bool check(int mid) {
    for (int i = 1; i <= n; ++i)
        deg[i] = 0;

    NetworkFlow::clear(n);

    for (int i = 1; i <= m; ++i) {
        --deg[edges[i].from];
        ++deg[edges[i].to];

        if (edges[i].rval <= mid) 
            id[i] = NetworkFlow::link(edges[i].to, edges[i].from, 1);
    }

    int k = 0;

    for (int i = 1; i <= n; ++i) {
        if (deg[i] > 0) {
            NetworkFlow::link(NetworkFlow::source, i, deg[i] / 2);
            k += deg[i] / 2;
        } else if (deg[i] < 0) {
            NetworkFlow::link(i, NetworkFlow::sink, -deg[i] / 2);
        }
    }

    int res = NetworkFlow::dinic();
    return res == k;
}

void build() {
    check(ans);

    for (int i = 1; i <= m; ++i) {
        if (edges[i].rval <= ans) {
            if (NetworkFlow::graph[id[i]].cap)
                EulerGraph::link(edges[i].from, edges[i].to);
            else
                EulerGraph::link(edges[i].to, edges[i].from);
        } else {
            EulerGraph::link(edges[i].from, edges[i].to);
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("euler.in", "r", stdin);
    freopen("euler.out", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        auto& [from, to, val, rval] = edges[i];
        cin >> from >> to >> val >> rval;

        if (val > rval) {
            swap(from, to);
            swap(val, rval);
        }
        
        l = max(l, val);
        r = max(r, rval);

        ++deg[from];
        ++deg[to];
    }

    for (int i = 1; i <= n; ++i) {
        if (deg[i] % 2) {
            cout << "NIE" << endl;
            return 0;
        }
    }

    while (l < r) {
        int mid = (l + r - 1) / 2;

        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    
    ans = r;
    build();
    auto res = EulerGraph::solve();

    cout << ans << endl;

    for (int i : res)
        cout << i << " ";

    cout << endl;
    return 0;
}
