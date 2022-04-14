#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 1000 + 10;
constexpr long long INFINITY = 0x3f3f3f3f3f3f3f3f;

class Network {
public:
    void init() {
        tot = 1;
        source = 0;
        sink = MAX_N - 1;
    }

    void link(int x, int y, long long c) {
        net[++tot] = { head[x], y, c };
        head[x] = tot;
        net[++tot] = { head[y], x, 0ll };
        head[y] = tot;
    }

    long long maxflow() {
        long long res = 0;
        while (bfs()) res += dfs(source, INFINITY);
        return res;
    }

    int getSource() const { return source; }

    int getSink() const { return sink; }
private:
    struct Edge {
        int next, to;
        long long cap;
    };

    Edge net[MAX_N * 10];
    int tot, head[MAX_N];
    int cur[MAX_N], dis[MAX_N];
    int source, sink;

    bool bfs() {
        queue<int> q;
        q.push(source);
        for (int i = source; i <= sink; ++i) dis[i] = 0;
        dis[source] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            cur[x] = head[x];
            for (int i = head[x], y; y = net[i].to, i; i = net[i].next) {
                if (net[i].cap <= 0 || dis[y]) continue;
                dis[y] = dis[x] + 1;
                q.push(y);
            }
        }
        return dis[sink];
    }

    long long dfs(int x, long long in) {
        if (x == sink) return in;
        long long res = 0;
        for (int & i = cur[x], y; y = net[i].to, i; i = net[i].next) {
            if (net[i].cap <= 0 || dis[y] != dis[x] + 1) continue;
            long long f = dfs(y, min(net[i].cap, in - res));
            if (f > 0) {
                net[i].cap -= f;
                net[i ^ 1].cap += f;
                res += f;
                if (res == in) break;
            }
        }
        if (res != in) dis[x] = 0;
        return res;
    }
};

struct Edge {
    int to, cap;

    bool operator<(const Edge & rhs) const {
        return to < rhs.to;
    }
};

int n, m, k;
int c[MAX_N];
int fa[MAX_N];
Network net;
vector<Edge> edges[MAX_N];
vector<int> col[MAX_N];
int tot, id;

int find(int x) {
    return (x == fa[x] ? x : fa[x] = find(fa[x]));
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y)
        fa[x] = y;
}

void build(int l, int r, int fa) {
    for (int x = l; x < r; ) {
        if (x != l)
            col[c[x]].push_back(fa);

        if (edges[x].empty()) {
            net.link(fa, net.getSink(), INFINITY);
            
            for (int i = l + 1; i < r; ++i)
                col[c[i]].push_back(fa);
            
            return;
        } else {
            ++id;
            net.link(fa, id, edges[x].back().cap);
            net.link(id, fa, INFINITY);
            int y = edges[x].back().to;
            edges[x].pop_back();
            build(x, y, id);
            x = y;
        }
    }
}

void build() {
    net.init();

    for (int i = 2; i < n; ++i) {
        if (!c[find(i)])
            c[find(i)] = ++tot;
        c[i] = c[find(i)];
    }

    for (int i = 1; i <= n; ++i) sort(edges[i].begin(), edges[i].end());

    build(1, n, net.getSource());
    
    for (int i = 0; i <= tot; ++i) {
        for (int j = 0; j < (int) col[i].size() - 1; ++j) {
            net.link(col[i][j], col[i][j + 1], INFINITY);
            net.link(col[i][j + 1], col[i][j], INFINITY);
        }
    }
}

int main() {
    freopen("underground.in", "r", stdin);
    freopen("underground.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;

    for (int i = 1; i <= n; ++i)
        fa[i] = i;
        
    for (int i = 1; i <= m; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        edges[x].push_back({ y, c });
    }
    
    for (int i = 1; i <= k; ++i) {
        int x, y;
        cin >> x >> y;
        merge(x, y);
    }

    build();

    long long ans = net.maxflow();

    if (ans < INFINITY / 2)
        cout << ans << endl;
    else
        cout << -1 << endl;
    return 0;
}
