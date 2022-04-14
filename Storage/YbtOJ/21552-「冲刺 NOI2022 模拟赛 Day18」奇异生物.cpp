#include <iostream>
#include <algorithm>
#include <vector>

constexpr int MAX_N = 10000 + 10;
constexpr int MAX_M = 200 + 10;

struct Range {
    int l, r;
};

int n, m, w;
int h[MAX_N], p[MAX_M], a[MAX_M];
Range range[MAX_M];
int len;
int s[2 * MAX_M];
int f[2 * MAX_M][2 * MAX_M];

void discretize() {
    std::vector<int> val;

    for (int i = 1; i <= m; ++i) {
        val.push_back(range[i].l);
        val.push_back(range[i].r);
    }

    std::sort(val.begin(), val.end());
    auto it = std::unique(val.begin(), val.end());
    val.erase(it, val.end());
    len = (int) val.size();

    for (int i = 1; i <= m; ++i) {
        auto &[l, r] = range[i];
        l = (int) (std::lower_bound(val.begin(), val.end(), l) - val.begin() + 1);
        r = (int) (std::lower_bound(val.begin(), val.end(), r) - val.begin() + 1);
    }
}

int comb(int x) {
    return (x < 2 ? 0 : x * (x - 1) / 2);
}

int main() {
    std::freopen("strange.in", "r", stdin);
    std::freopen("strange.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    
    std::cin >> n >> m >> w;

    for (int i = 1; i <= n; ++i)
        std::cin >> h[i];
    
    for (int i = 1; i <= m; ++i)
        std::cin >> p[i] >> a[i];
    
    for (int i = 1; i <= m; ++i) {
        range[i] = { p[i], p[i] };

        for (int j = p[i]; j > 1; --j) {
            if (a[i] <= w - h[j])
                break;

            range[i].l = j - 1;
        }

        for (int j = p[i]; j < n; ++j) {
            if (a[i] <= w - h[j])
                break;

            range[i].r = j + 1;
        }
    }

    discretize();

    for (int i = len; i >= 1; --i) {
        for (int j = i; j <= len; ++j) {
            for (int k = i; k <= j; ++k)
                s[k] = 0;

            for (int k = 1; k <= m; ++k) {
                auto [l, r] = range[k];
                
                if (l < i || j < r)
                    continue;

                ++s[l];
                --s[r + 1];
            }

            for (int k = i; k <= j; ++k)
                s[k] += s[k - 1];

            for (int k = i; k <= j; ++k)
                f[i][j] = std::max(f[i][j], f[i][k - 1] + f[k + 1][j] + comb(s[k]));
        }
    }

    std::cout << f[1][len] << std::endl;
    return 0;
}
