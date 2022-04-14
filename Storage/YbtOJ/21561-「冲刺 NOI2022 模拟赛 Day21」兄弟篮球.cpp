#include <bit>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

constexpr int MAX_N = 50;

int n, m;
std::vector<std::pair<int, int>> graph[MAX_N];
int dis[MAX_N];
std::vector<int> a, b;
int ida[MAX_N], idb[MAX_N];
bool ina[MAX_N], inb[MAX_N];
int r1[MAX_N], r2[MAX_N][MAX_N];
int pos[(1 << 20) + 1];

template <typename T>
T lowbit(T x) {
    return x & (-x);
}

void link(int x, int y, int t) {
    graph[x].push_back({ y, t });
    graph[y].push_back({ x, t });
}

void partition() {
    std::queue<int> q;
    q.push(1);
    dis[1] = 1;

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (auto [y, t] : graph[x]) {
            if (dis[y])
                continue;

            dis[y] = dis[x] + 1;
            q.push(y);
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (dis[i] == 2) {
            a.push_back(i);
            ina[i] = true;
            ida[i] = (int) a.size() - 1;
        } else if (dis[i] == 3) {
            b.push_back(i);
            inb[i] = true;
            idb[i] = (int) b.size() - 1;
        }
    }

    for (auto [y, t] : graph[1])
        r1[ida[y]] = t;

    for (int i = 0; i < (int) a.size(); ++i)
        for (int j = 0; j < (int) b.size(); ++j)
            r2[i][j] = -1;

    for (int x : a)
        for (auto [y, t] : graph[x])
            if (inb[y])
                r2[ida[x]][idb[y]] = t;
}

namespace Solution1 {
    int f[MAX_N / 2][1 << 20];
    long long confirmed[1 << 20], valid[20];
    int ans;

    void main() {
        int tot = (int) a.size();

        for (int i = 0; i < tot; ++i) {
            for (int j = 0; j < (int) b.size(); ++j) {
                if (r2[i][j] == r1[i])
                    valid[i] |= (1ll << j);

                if (r2[i][j] != -1)
                    confirmed[1 << i] |= (1 << j);
            }
        }

        for (int s = 1; s < (1 << tot); ++s)
            confirmed[s] = confirmed[lowbit(s)] | confirmed[s ^ lowbit(s)];

        for (int s = 1; s < (1 << tot); ++s) {
            for (int ss = s; ss; ss -= lowbit(ss)) {
                int i = pos[lowbit(ss)];
                long long add = (confirmed[s] ^ confirmed[s ^ (1 << i)]) & valid[i];
                int cnt = std::__popcount((unsigned long long) add);

                if (!(s ^ (1 << i))) {
                    f[i][s] = std::max(f[i][s], cnt);
                    continue;
                }

                for (int ts = (s ^ (1 << i)); ts; ts -= lowbit(ts)) {
                    int j = pos[lowbit(ts)];
                    f[i][s] = std::max(f[i][s], f[j][s ^ (1 << i)] + cnt);
                }
            }
        }

        for (int i = 0; i < tot; ++i)
            ans = std::max(ans, f[i][(1 << tot) - 1]);

        for (int i = 0; i < tot; ++i)
            if (r1[i] == 0)
                ++ans;

        std::cout << ans << std::endl;
    }
} // namespace Solution1

namespace Solution2 {
    int confirmed[MAX_N], valid[MAX_N];
    int f[1 << 20], ans;

    void main() {
        int tot = (int) a.size();

        for (int i = 0; i < tot; ++i) {
            for (int j = 0; j < (int) b.size(); ++j) {
                if (r2[i][j] != -1)
                    confirmed[i] |= (1 << j);

                if (r2[i][j] == r1[i])
                    valid[i] |= (1 << j);
            }
        }

        for (int s = 0; s < (1 << (int) b.size()); ++s) {
            for (int i = 0; i < tot; ++i) {
                int ns = s | confirmed[i];
                f[ns] = std::max(f[ns], f[s] + std::__popcount((ns ^ s) & valid[i]));
            }
        }

        ans = f[(1 << (int) b.size()) - 1];

        for (int i = 0; i < tot; ++i)
            if (r1[i] == 0)
                ++ans;

        std::cout << ans << std::endl;
    }
} // namespace Solution2

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("brothers.in", "r", stdin);
    std::freopen("brothers.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    for (int i = 0; i < 20; ++i)
        pos[1 << i] = i;

    std::cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y, t;
        std::cin >> x >> y >> t;
        link(x, y, t);
    }

    partition();

    if (a.size() < b.size())
        Solution1::main();
    else
        Solution2::main();

    return 0;
}
