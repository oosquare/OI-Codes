#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar('0');
        putchar(sep);
        return;
    }

    static int st[50];
    int top = 0;

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 50000 + 10;
constexpr int maxm = 1000 + 10;
constexpr int mod = 10007;

int n, m, len[maxn], sum[maxn];
int ml, ans, f[2][maxn], sumf[2][maxn];

bool check(int l) {
    int cnt = 0, s = 0;

    for (int i = 1; i <= n; ++i) {
        if (s + len[i] > l) {
            ++cnt;
            s = len[i];
        } else {
            s += len[i];
        }
    }

    return cnt <= m; 
}

int divide() {
    int l = 0, r = 0, ans = 0;

    for (int i = 1; i <= n; ++i) {
        l = max(l, len[i]);
        r += len[i];
    }

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return ans;
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= n; ++i) {
        len[i] = read();
        sum[i] = sum[i - 1] + len[i];
    }

    ml = divide();

    f[0][0] = sumf[0][0] = 1;

    for (int i = 1; i <= n; ++i)
        sumf[0][i] = sumf[0][i - 1] + sumf[0][i];

    for (int i = 1; i <= m + 1; ++i) {
        int now = (i & 1), pre = (now ^ 1);
        sumf[now][0] = 0;

        for (int j = 1, k = 0; j <= n; ++j) {
            while (sum[j] - sum[k] > ml)
                ++k;

            f[now][j] = (sumf[pre][j - 1] - (k == 0 ? 0 : sumf[pre][k - 1]) + mod) % mod;
            sumf[now][j] = (sumf[now][j - 1] + f[now][j]) % mod;
        }

        ans = (ans + f[now][n]) % mod;
    }

    write(ml, ' ');
    write(ans);
    return 0;
};