#include <iostream>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxp = 100 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

int n, m, p, tot;
int d[maxn], t[maxn], h[maxn];
long long t2[maxn], cnt[maxn], sum[maxn];
long long f[maxn][maxp], ans = oo;
int q[maxn], fr, bk;

double slope(int i, int j, int t) {
    return 1.0 * ((f[j][t] + sum[j]) - (f[i][t] + sum[i])) / (cnt[j] - cnt[i]);
}

int main() {
    cin >> n >> m >> p;

    for (int i = 2; i <= n; ++i) {
        cin >> d[i];
        d[i] += d[i - 1];
    }

    for (int i = 1; i <= m; ++i) {
        cin >> h[i] >> t[i];
        t[i] -= d[h[i]];
    }

    sort(t + 1, t + 1 + m);

    for (int l = 1, r = 1; l <= m; l = r + 1, r = l) {
        while (r < m && t[r + 1] == t[l])
            ++r;

        t2[++tot] = t[l];
        cnt[tot] = r - l + 1;
    }

    for (int i = 1; i <= tot; ++i) {
        sum[i] = sum[i - 1] + cnt[i] * t2[i];
        cnt[i] += cnt[i - 1];
    }

    q[fr = bk = 1] = 0;

    for (int j = 1; j <= p; ++j) {
        for (int i = 1; i <= tot; ++i) {
            while (fr < bk && slope(q[fr], q[fr + 1], j - 1) <= t2[i])
                ++fr;

            int k = q[fr];
            f[i][j] = f[k][j - 1] + t2[i] * (cnt[i] - cnt[k]) - (sum[i] - sum[k]);
        }

        fr = 1;
        bk = 0;

        for (int i = 1; i <= tot; ++i) {
            while (fr < bk && slope(q[bk - 1], q[bk], j) >= slope(q[bk], i, j))
                --bk;

            q[++bk] = i;
        }
    }

    for (int i = 1; i <= p; ++i)
        ans = min(ans, f[tot][i]);

    cout << ans << endl;
    return 0;
}