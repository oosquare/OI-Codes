#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

constexpr int MAX_N = 500 + 10;
constexpr int MAX_M = 1000000 + 10;

class Network {
public:
    void init(int n) {
        tot = 1;
        source = 0;
        sink = n + 1;

        for (int i = source; i <= sink; ++i)
            head[i] = 0;
    }

    void link(int x, int y, int c) {
        net[++tot] = { head[x], y, c };
        head[x] = tot;
        net[++tot] = { head[y], x, 0 };
        head[y] = tot;
        // std::cout << x << " " << y << " " << c << std::endl;
    }

    int getSource() { return source; }

    int getSink() { return sink; }

    int maxflow() {
        int res = 0;

        while (bfs())
            res += dfs(source, 0x3f3f3f3f);

        return res;
    }

    int check(int x) { return dis[x]; }

private:
    struct Edge {
        int next, to;
        int capacity;
    };

    Edge net[MAX_M];
    int tot, source, sink;
    int head[MAX_N], cur[MAX_N], dis[MAX_N];

    bool bfs() {
        std::queue<int> q;
        q.push(source);

        for (int i = source; i <= sink; ++i)
            dis[i] = 0;

        dis[source] = 1;
        
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            cur[x] = head[x];

            for (int i = head[x], y; y = net[i].to, i; i = net[i].next) {
                if (net[i].capacity <= 0 || dis[y])
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

        for (int &i = cur[x], y; y = net[i].to, i; i = net[i].next) {
            if (net[i].capacity <= 0 || dis[y] != dis[x] + 1)
                continue;

            int f = dfs(y, std::min(net[i].capacity, in - res));

            if (f > 0) {
                net[i].capacity -= f;
                net[i ^ 1].capacity += f;
                res += f;

                if (res == in)
                    break;
            }
        }

        if (res != in)
            dis[x] = 0;

        return res;
    }
};

int n, m1, m2;
int a[MAX_N];
std::vector<int> val;
int cnt;
std::vector<int> buc[MAX_N];
int fa[MAX_N];
int seq[MAX_N], tmp1[MAX_N], tmp2[MAX_N];
long long ans;
Network net;
bool graph[MAX_N][MAX_N];

int find(int x) { return (fa[x] == x ? x : fa[x] = find(fa[x])); }

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y)
        fa[x] = y;
    // std::cout << x << " - " << y << std::endl;
}

int slope(int id, int x) {
    int rk = (int) (std::upper_bound(buc[id].begin(), buc[id].end(), x) - buc[id].begin());
    return 2 * rk - (int) buc[id].size();
}

void solve(int l, int r, int sl, int sr) {
    if (sl > sr)
        return;

    if (l == r) {
        for (int i = sl; i <= sr; ++i)
            for (int j : buc[seq[i]])
                ans += std::abs(val[j] - val[l]);

        return;
    }

    int mid = (l + r) / 2;
    int it1 = 0, it2 = 0;

    net.init(cnt);

    for (int i = sl; i <= sr; ++i) {
        int s = slope(seq[i], mid);

        if (s <= 0)
            net.link(net.getSource(), i, -s);
        else
            net.link(i, net.getSink(), s);
    }

    for (int i = sl; i <= sr; ++i)
        for (int j = sl; j <= sr; ++j)
            if (graph[seq[i]][seq[j]])
                net.link(i, j, 0x3f3f3f3f);

    net.maxflow();
    // exit(0);

    for (int i = sl; i <= sr; ++i) {
        if (net.check(i))
            tmp2[++it2] = seq[i];
        else
            tmp1[++it1] = seq[i];
        
    }

    for (int i = 1; i <= it1; ++i)
        seq[sl + i - 1] = tmp1[i];

    for (int i = 1; i <= it2; ++i)
        seq[sl + it1 + i - 1] = tmp2[i];

    solve(l, mid, sl, sl + it1 - 1);
    solve(mid + 1, r, sl + it1, sr);
}

void discretize() {
    for (int i = 1; i <= n; ++i)
        val.push_back(a[i]);

    val.push_back(-1);

    std::sort(val.begin(), val.end());
    auto it = std::unique(val.begin(), val.end());
    val.erase(it, val.end());

    for (int i = 1; i <= n; ++i)
        a[i] = (int) (std::lower_bound(val.begin(), val.end(), a[i]) - val.begin());
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("balance.in", "r", stdin);
    std::freopen("balance.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m1 >> m2;

    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        fa[i] = i;
    }

    discretize();

    for (int i = 1; i <= m1; ++i) {
        int x, y;
        std::cin >> x >> y;
        merge(x, y);
    }

    for (int i = 1; i <= m2; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[find(x)][find(y)] = true;
    }

    for (int i = 1; i <= n; ++i)
        buc[find(i)].push_back(a[i]);

    for (int i = 1; i <= n; ++i) {
        if (i != find(i))
            continue;

        std::sort(buc[i].begin(), buc[i].end());
        seq[++cnt] = i;
        // for (int v : buc[i])
        //     std::cout << v << " ";
        // std::cout << std::endl;
    }
    // std::cout << "-----------\n";
    solve(1, (int) val.size() - 1, 1, cnt);
    std::cout << ans << std::endl;
    return 0;
}
