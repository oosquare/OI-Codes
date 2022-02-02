#include <iostream>
using namespace std;

constexpr int maxp = 300 + 5;
constexpr int maxv = 3000 + 5;

int p, v, mx;
int a[maxv], b[maxv], pre[maxv], suf[maxv];
int val[maxv][maxv], f[maxp][maxv], ans = 0x3f3f3f3f;

inline int queryPre(int l, int r) {
    return pre[r] - pre[l - 1] - (r - l + 1) * a[l];
}

inline int querySuf(int l, int r) {
    return suf[l] - suf[r + 1] - (r - l + 1) * b[r];
}

void dp(int l, int r, int pl, int pr, int i) {
    if (l > r)
        return;

    int mid = (l + r) / 2, pos = 0;

    for (int j = pl; j <= min(pr, mid - 1); ++j) {
        if (f[i][mid] > f[i - 1][j] + val[j][mid]) {
            f[i][mid] = f[i - 1][j] + val[j][mid];
            pos = j;
        }
    }

    dp(l, mid - 1, pl, pos, i);
    dp(mid + 1, r, pos, pr, i);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> v >> p;

    for (int i = 1; i <= v; ++i)
        cin >> a[i];

    for (int i = 1; i <= v; ++i)
        pre[i] = pre[i - 1] + a[i];

    for (int i = v; i >= 1; --i) {
        b[i] = a[v] - a[i];
        suf[i] = suf[i + 1] + b[i];
    }

    for (int i = 0; i < v; ++i) {
        for (int j = i + 1, k = i; j <= v; ++j) {
            while (k + 1 < j && queryPre(i, k) + querySuf(k + 1, j) >= queryPre(i, k + 1) + querySuf(k + 2, j))
                ++k;

            val[i][j] = queryPre(i, k) + querySuf(k + 1, j);
        }
    }

    for (int i = 0; i <= p; ++i)
        for (int j = 0; j <= v; ++j)
            f[i][j] = 0x3f3f3f3f;

    for (int i = 1; i <= v; ++i)
        f[1][i] = querySuf(1, i);

    for (int i = 2; i <= p; ++i)
        dp(i, v, 1, v - 1, i);

    for (int i = p; i <= v; ++i) {
        f[p][i] += queryPre(i, v);
        ans = min(ans, f[p][i]);
    }

    cout << ans << endl;
    return 0;
}