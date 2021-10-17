#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 100000 + 10;
constexpr int maxk = 300 + 10;
constexpr int mod = 19260817;

int n, k, a[maxn];
int f[2][maxn], sf[2][maxn], cnt[2][maxn], scnt[2][maxn];

int inv(int x) {
    int y = mod - 2, res = 1;
    for (; y; y /= 2) {
        if (y % 2)
            res = 1LL * res * x % mod;
        x = 1LL * x * x % mod;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        f[1][i] = a[i];
        sf[1][i] = (sf[1][i - 1] + f[1][i]) % mod;
        cnt[1][i] = 1;
        scnt[1][i] = scnt[1][i - 1] + cnt[1][i];
    }
    for (int i = 2; i <= k; ++i) {
        int now = i % 2, pre = now ^ 1;
        for (int j = 1; j <= n; ++j) {
            f[now][j] = 1LL * sf[pre][j] * a[j] % mod;
            sf[now][j] = (sf[now][j - 1] + f[now][j]) % mod;
            cnt[now][j] = scnt[pre][j];
            scnt[now][j] = (scnt[now][j - 1] + cnt[now][j]) % mod;
        }
    }
    cout << 1LL * sf[k % 2][n] * inv(scnt[k % 2][n]) % mod << endl;
    return 0;
}