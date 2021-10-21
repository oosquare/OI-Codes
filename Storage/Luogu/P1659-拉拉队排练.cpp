#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 2e6 + 10;
constexpr int mod = 19930726;

int n0, n, ans = 1;
ll k;
char raw[maxn], str[maxn * 2];
int r[maxn * 2], cnt[maxn];

void preprocess() {
    r[1] = 2;
    int mid = 1, mx = 2;

    for (int i = 2; i <= n; ++i) {
        if (mx >= i)
            r[i] = min(r[mid * 2 - i], mx - i + 1);
        else
            r[i] = 1;

        while (i - r[i] >= 0 && i + r[i] <= n + 1 && str[i - r[i]] == str[i + r[i]])
            ++r[i];

        if (i + r[i] - 1 > mx) {
            mid = i;
            mx = i + r[i] - 1;
        }
    }
}

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;
        x = 1ll * x * x % mod;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n0 >> k;
    cin >> (raw + 1);

    n = 2 * n0 - 1;
    for (int i = 1; i <= n0; ++i) {
        str[2 * i - 1] = raw[i];
        str[2 * i] = '#';
    }
    str[0] = '#';
    str[n + 1] = '#';
    str[n + 2] = '\0';

    preprocess();

    for (int i = 1; i <= n; ++i) {
        if (i % 2 == 1) {
            ++cnt[1];
            --cnt[r[i] / 2 + 1];
        }
    }

    for (int i = 1; i <= n; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = n0; i >= 1 && k > 0; --i) {
        if (i % 2 == 1) {
            ans = 1ll * ans * power(i, min(k, 1ll * cnt[(i + 1) / 2])) % mod;
            k -= min(k, 1ll * cnt[(i + 1) / 2]);
        }
    }

    if (k == 0)
        cout << ans << endl;
    else
        cout << -1 << endl;

    return 0;
}