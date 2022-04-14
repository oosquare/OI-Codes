#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>

constexpr int MAX_N = 100000 + 10;
constexpr int MOD = 1000000007;
constexpr int INFINITY = 0x3f3f3f3f;

int t, l[4], n;
int prime[MAX_N], mu[MAX_N], f[4][MAX_N], tot;
bool notPrime[MAX_N];

inline void add(int & x, int y) {
    x += y;

    if (x >= MOD)
        x -= MOD;
}

inline int positive(int x) {
    return (x < 0 ? x + MOD : x);
}

int gcd(int x, int y) {
    int t;

    while (y) {
        t = x;
        x = y;
        y = t % y;
    }

    return x;
}

int lcm(int x, int y) {
    int d = gcd(x, y);
    return (int) std::min(1ll * x / d * y, 1ll * INFINITY);
}

class Graph {
public:
    void link(int x, int y) {
        edges.push_back({ x, y });
        ++deg[x];
        ++deg[y];
    }

    void clear(int n) {
        edges.clear();

        for (int i = 1; i <= n; ++i) {
            graph[i].clear();
            deg[i] = 0;
            vis[i] = 0;
        }

        timer = 0;
    }

    int calc() {
        int res = 0;
        int ans = 0;
        build();

        std::vector<int> seq((std::vector<int>::size_type) n);

        for (int i = 1; i <= n; ++i)
            if (mu[i])
                seq.push_back(i);

        std::sort(seq.begin(), seq.end(), [this](int lhs, int rhs) { return deg[lhs] > deg[rhs]; });

        for (int x : seq) {
            ++timer;
            add(res, calc(x));

            for (int y : graph[x])
                vis[y] = timer;

            for (int y : graph[x]) {
                add(res, calc(x, y));

                for (int z : graph[y]) {
                    if (vis[z] != timer)
                        continue;

                    add(res, calc(x, y, z));
                    ++ans;
                }
            }
        }

        return res;
    }
private:
    struct Edge {
        int x, y;
    };

    std::vector<Edge> edges;
    std::vector<int> graph[MAX_N];
    int deg[MAX_N];
    int vis[MAX_N], timer;

    void build() {
        for (auto [x, y] : edges) {
            if (deg[x] > deg[y])
                graph[x].push_back(y);
            else
                graph[y].push_back(x);
        }
    }

    int calc(int x) {
        int res = 1ll * mu[x] * f[1][x] * f[2][x] % MOD * f[3][x] % MOD;
        return positive(res);
    }

    int calc(int x, int y) {
        int l = lcm(x, y);
        int res = 0;

        add(res, positive(1ll * mu[x] * f[1][y] * f[2][l] % MOD * f[3][l] % MOD));
        add(res, positive(1ll * mu[x] * f[1][l] * f[2][y] % MOD * f[3][l] % MOD));
        add(res, positive(1ll * mu[x] * f[1][l] * f[2][l] % MOD * f[3][y] % MOD));

        add(res, positive(1ll * mu[y] * f[1][x] * f[2][l] % MOD * f[3][l] % MOD));
        add(res, positive(1ll * mu[y] * f[1][l] * f[2][x] % MOD * f[3][l] % MOD));
        add(res, positive(1ll * mu[y] * f[1][l] * f[2][l] % MOD * f[3][x] % MOD));

        return res;
    }

    int calc(int x, int y, int z) {
        int lcm1 = lcm(x, y), lcm2 = lcm(y, z), lcm3 = lcm(x, z);
        int res = 0;

        add(res, 1ll * f[1][lcm1] * f[2][lcm2] % MOD * f[3][lcm3] % MOD);
        add(res, 1ll * f[1][lcm1] * f[2][lcm3] % MOD * f[3][lcm2] % MOD);
        add(res, 1ll * f[1][lcm2] * f[2][lcm1] % MOD * f[3][lcm3] % MOD);
        add(res, 1ll * f[1][lcm2] * f[2][lcm3] % MOD * f[3][lcm1] % MOD);
        add(res, 1ll * f[1][lcm3] * f[2][lcm1] % MOD * f[3][lcm2] % MOD);
        add(res, 1ll * f[1][lcm3] * f[2][lcm2] % MOD * f[3][lcm1] % MOD);

        res = res * mu[x] * mu[y] * mu[z];

        return positive(res);
    }
};

Graph graph;

void preprocess(int n) {
    notPrime[1] = true;
    mu[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            mu[i] = -1;
        }

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;

            if (i % prime[j]) {
                mu[i * prime[j]] = -mu[i];
            } else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}

void build() {
    graph.clear(n);

    for (int d = 1; d <= n; ++d) {
        for (int i = 1; i * d <= n; ++i) {
            if (mu[i * d] == 0)
                continue;

            for (int j = i + 1; 1ll * i * j * d <= n; ++j) {
                if (mu[j * d] == 0 || gcd(i, j) != 1)
                    continue;

                graph.link(i * d, j * d);
            }
        }
    }
}

void solve() {
    std::cin >> l[1] >> l[2] >> l[3];
    n = std::max(std::max(l[1], l[2]), l[3]);

    std::memset(f, 0, sizeof(f));

    for (int t = 1; t <= 3; ++t)
        for (int i = 1; i <= l[t]; ++i)
            for (int j = i; j <= l[t]; j += i)
                f[t][i] = (f[t][i] + (l[t] / j)) % MOD;

    build();
    std::cout << graph.calc() << std::endl;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("divsum.in", "r", stdin);
    std::freopen("divsum.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif

    std::ios::sync_with_stdio(false);

    preprocess(MAX_N - 10);

    std::cin >> t;

    while (t--)
        solve();

    return 0;
}
