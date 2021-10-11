#include <bits/stdc++.h>
using namespace std;

constexpr int maxk = 100 + 10;
constexpr int maxn = 15;
constexpr double eps = 1e-8;

int k, n, s[maxn + 10];
double p[maxn + 10];
double f[maxk][1 << maxn], ans;

inline int getBit(int status, int pos) {
    return (status >> (pos - 1)) & 1;
}

inline int setBit(int status, int pos, int val) {
    if (val == 1)
        status |= (1 << (pos - 1));
    else
        status &= ~(1 << (pos - 1));
    return status;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> k >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        int x;
        while (true) {
            cin >> x;
            if (x == 0)
                break;
            s[i] = setBit(s[i], x, 1);
        }
    }
    for (int i = k; i >= 1; --i) {
        for (int j = 0; j < (1 << n); ++j) {
            for (int x = 1; x <= n; ++x) {
                int nj = setBit(j, x, 1);
                if (j != nj) {
                    if ((s[x] & j) != s[x])
                        f[i][j] += f[i + 1][j] / n;
                    else
                        f[i][j] += (max(f[i + 1][nj] + p[x], f[i + 1][j])) / n;
                } else {
                    f[i][j] += (f[i + 1][nj] + (p[x] > eps ? p[x] : 0)) / n;
                }
            }
        }
    }
    cout << fixed << setprecision(6) << f[1][0] << endl;
    return 0;
}