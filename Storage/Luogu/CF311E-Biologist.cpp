#include <iostream>
#include <queue>
using namespace std;

constexpr int MAX_N = 2e4 + 10;
constexpr int INFINITY = 0x3f3f3f3f;

class Network {
public:
    void init(int n) {
        tot = 1;
        source = 0;
        sink = n + 1;

        for (int i = 1; i <= n; ++i)
            head[i] = 0;
    }

    void link(int x, int y, int c) {
        net[++tot] = { head[x], y, c };
        head[x] = tot;
        net[++tot] = { head[y], x, 0 };
        head[y] = tot;
    }

    int getSource() {
        return source;
    }

    int getSink() {
        return sink;
    }

    int maxflow() {
        int res = 0;

        while (bfs())
            res += dfs(source, INFINITY);
        
        return res;
    }
private:
    struct Edge {
        int next, to, cap;
    };

    Edge net[MAX_N * 100];
    int head[MAX_N], cur[MAX_N], tot;
    int dis[MAX_N];
    int source, sink;

    bool bfs() {
        queue<int> q;

        for (int i = source; i <= sink; ++i)
            dis[i] = 0;

        dis[source] = 1;
        q.push(source);

        while (!q.empty()) {
            int x = q.front();
            q.pop();
            cur[x] = head[x];

            for (int i = head[x], y; y = net[i].to, i; i = net[i].next) {
                if (net[i].cap <= 0 || dis[y])
                    continue;

                dis[y] = dis[x] + 1;
                q.push(y);
            }
        }

        return dis[sink] != 0;
    }

    int dfs(int x, int in) {
        if (x == sink)
            return in;

        int res = 0;

        for (int & i = cur[x], y; y = net[i].to, i; i = net[i].next) {
            if (net[i].cap <= 0 || dis[y] != dis[x] + 1)
                continue;

            int f = dfs(y, min(net[i].cap, in - res));

            if (f > 0) {
                net[i].cap -= f;
                net[i ^ 1].cap += f;
                res += f;

                if (res == in)
                    break;
            }
        }

        if (res == in)
            dis[x] = 0;

        return res;
    }
};

Network net;
int n, m, g;
int val[MAX_N], cost[MAX_N];
int ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> g;
    net.init(n + m);
    
    for (int i = 1; i <= n; ++i)
        cin >> val[i];
    
    for (int i = 1; i <= n; ++i) {
        cin >> cost[i];
        
        if (val[i] == 0)
            net.link(i, net.getSink(), cost[i]);
        else
            net.link(net.getSource(), i, cost[i]);
    }

    for (int i = 1; i <= m; ++i) {
        int v, w, k, p, t;
        cin >> v >> w >> k;
        ans += w;

        for (int j = 1; j <= k; ++j) {
            cin >> p;

            if (v == 0)
                net.link(p, n + i, INFINITY);
            else
                net.link(n + i, p, INFINITY);
        }

        cin >> t;
        int c = w + (t == 1 ? g : 0);

        if (v == 0)
            net.link(n + i, net.getSink(), c);
        else
            net.link(net.getSource(), n + i, c);
    }

    ans -= net.maxflow();
    cout << ans << endl;
    return 0;
}