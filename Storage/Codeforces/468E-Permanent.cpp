#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

constexpr int MAX_N = 100000 + 10;
constexpr int MAX_K = 50 + 10;
constexpr int MOD = 1000000007;

int n, k, arr[MAX_K][MAX_K];
int x[MAX_K], y[MAX_K], w[MAX_K], cntx[MAX_K], cnty[MAX_K], maxx, maxy;
int fac[MAX_N];
std::unordered_map<long long, int> f[MAX_K], g[MAX_K];
int ans;

void add(int &x, int y) {
    x += y;
    
    if (x >= MOD)
        x -= MOD;
}

void preprocess() {
    fac[0] = 1;

    for (int i = 1; i <= n; ++i)
        fac[i] = (int) (1ll * fac[i - 1] * i % MOD);
}

void discretize(int arr[], int &max) {
    std::vector<int> val;

    for (int i = 1; i <= k; ++i)
        val.push_back(arr[i]);

    std::sort(val.begin(), val.end());
    auto it = std::unique(val.begin(), val.end());
    val.erase(it, val.end());

    for (int i = 1; i <= k; ++i)
        arr[i] = (int) (std::lower_bound(val.begin(), val.end(), arr[i]) - val.begin() + 1);

    max = (int) val.size();
}

int main() {
    std::ios::sync_with_stdio(false);

    std::cin >> n >> k;
    preprocess();

    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= k; ++j)
            arr[i][j] = -1;

    for (int i = 1; i <= k; ++i) {
        std::cin >> x[i] >> y[i] >> w[i];
        w[i] = (w[i] - 1 + MOD) % MOD;
    }

    discretize(x, maxx);
    discretize(y, maxy);

    for (int i = 1; i <= k; ++i) {
        ++cntx[x[i]];
        ++cnty[y[i]];
        arr[x[i]][y[i]] = w[i];
    }

    f[0][0] = 1;
        
    while (true) {
        int p = -1;

        for (int i = 1; i <= maxy; ++i)
            if (cnty[i] && (p == -1 || cnty[p] > cnty[i]))
                p = i;

        if (p == -1)
            break;

        for (int i = 1; i <= maxx; ++i) {
            if (arr[i][p] == -1 || !cntx[i]) 
                continue;

            cntx[i] = 0;
            long long all = ((1ll << maxy) - 1) << 1;
            std::vector<int> idx;

            for (int j = 1; j <= maxy; ++j) {
                if (arr[i][j] == -1)
                    continue;

                idx.push_back(j);
                --cnty[j];

                if (!cnty[j])
                    all &= (~(1ll << j));
            }

            for (int j = 0; j <= k; ++j) {
                for (auto [s, v] : f[j]) {
                    add(g[j][s & all], v);

                    for (int t : idx) {
                        if ((s >> t) & 1)
                            continue;
                        
                        add(g[j + 1][(s | (1ll << t)) & all], (int) (1ll * v * arr[i][t] % MOD));
                    }
                }
            }

            for (int j = 0; j <= k; ++j) {
                std::swap(f[j], g[j]);
                g[j].clear();
            }
        }
    }

    for (int i = 0; i <= k; ++i)
        for (auto [s, v] : f[i])
            add(ans, (int) (1ll * v * fac[n - i] % MOD));

    std::cout << ans << std::endl;
    return 0;
}
