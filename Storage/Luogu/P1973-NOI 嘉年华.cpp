#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

constexpr int maxn = 400 + 5;
constexpr int oo = 0x3f3f3f3f;

struct Activity {
    double start, end;
};

map<pair<double, double>, int> cnt;
int n, t;
Activity act[maxn];
int tot[maxn][maxn];
int f[maxn][maxn], g[maxn][maxn], h[maxn][maxn];
int ans;

void discretize() {
    vector<double> val;

    for (int i = 1; i <= n; ++i) {
        val.push_back(act[i].start);
        val.push_back(act[i].end);
    }

    sort(val.begin(), val.end());
    auto it = unique(val.begin(), val.end());
    val.erase(it, val.end());
    t = val.size();

    for (int i = 1; i <= n; ++i) {
        act[i].start = lower_bound(val.begin(), val.end(), act[i].start) - val.begin() + 1;
        act[i].end = lower_bound(val.begin(), val.end(), act[i].end) - val.begin() + 1;
    }
}

void preprocess() {
    for (int i = 1; i <= t; ++i)
        for (int j = i + 1; j <= t; ++j)
            for (int k = 1; k <= n; ++k)
                if (i <= act[k].start && act[k].end <= j)
                    ++tot[i][j];
}

inline int calc(int i, int j, int x, int y) {
    return min(x + y + tot[i][j], f[i][x] + g[j][y]);
}

void solve() {
    for (int i = 0; i <= t; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j] = g[i][j] = -oo;

    for (int i = 1; i <= t; ++i) {
        for (int j = 0; j <= tot[1][i]; ++j) {
            if (!j) {
                f[i][j] = tot[1][i];
            } else {
                for (int k = 1; k < i; ++k) {
                    f[i][j] = max(f[i][j], f[k][j] + tot[k][i]);

                    if (j >= tot[k][i])
                        f[i][j] = max(f[i][j], f[k][j - tot[k][i]]);
                }
            }
        }
    }

    for (int i = t; i >= 1; --i) {
        for (int j = 0; j <= tot[i][t]; ++j) {
            if (!j) {
                g[i][j] = tot[i][t];
            } else {
                for (int k = t; k > i; --k) {
                    g[i][j] = max(g[i][j], g[k][j] + tot[i][k]);

                    if (j >= tot[i][k])
                        g[i][j] = max(g[i][j], g[k][j - tot[i][k]]);
                }
            }
        }
    }

    for (int i = 1; i <= t; ++i) {
        for (int j = 1; j <= t; ++j) {
            h[i][j] = -oo;

            for (int x = 0, y = n; x <= n; ++x) {
                while (y > 0 && calc(i, j, x, y - 1) >= calc(i, j, x, y))
                    --y;

                h[i][j] = max(h[i][j], calc(i, j, x, y));
            }
        }
    }
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> act[i].start >> act[i].end;
        act[i].end += act[i].start;

        if (cnt[{act[i].start, act[i].end}])
            act[i].end -= cnt[{act[i].start, act[i].end}] * 0.0001;

        ++cnt[{act[i].start, act[i].end}];
    }

    discretize();
    preprocess();
    solve();

    for (int i = 0; i <= n; ++i)
        ans = max(ans, min(i, f[t][i]));

    cout << ans << endl;

    for (int i = 1; i <= n; ++i) {
        int res = -oo;

        for (int j = 1; j <= act[i].start; ++j)
            for (int k = act[i].end; k <= t; ++k)
                res = max(res, h[j][k]);

        cout << res << endl;
    }

    return 0;
}
