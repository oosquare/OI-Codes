#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int mod = 1e9 + 7;

int n, m, a[maxn];
vector<int> graph[maxn];
int deg[maxn], rk[maxn], se[maxn];
bool vis[maxn];
int cnt[maxn], val[maxn], ans;
int st[maxn], top;

void link(int x, int y) {
    graph[x].push_back(y);
    graph[y].push_back(x);
    ++deg[x];
    ++deg[y];
}

int main() {
    freopen("fz.in", "r", stdin);
    freopen("fz.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    iota(se + 1, se + 1 + n, 1);
    sort(se + 1, se + 1 + n, [](int lhs, int rhs) {
        return deg[lhs] > deg[rhs];
    });

    for (int i = 1; i <= n; ++i) {
        int x = se[i];
        vis[x] = true;

        for (int y : graph[x]) {
            if (vis[y])
                continue;

            for (int z : graph[y]) {
                if (vis[z])
                    continue;

                ans = (ans + val[z] + 1ll * cnt[z] * a[y] % mod) % mod;
                val[z] = (1ll * val[z] + a[x] + a[y] + a[z]) % mod;
                ++cnt[z];
                st[++top] = z;
            }
        }

        while (top) {
            val[st[top]] = 0;
            cnt[st[top]] = 0;
            --top;
        }
    }

    cout << ans << endl;
    return 0;
}
