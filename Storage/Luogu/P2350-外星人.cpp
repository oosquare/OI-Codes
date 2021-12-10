#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
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
        x = -x;
        putchar('-');
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep); 
}

constexpr int maxp = 1e5 + 10;

int t, m;
int f[maxp], prime[maxp], tot;
bool notprime[maxp];

void preprocess(int n) {
    notprime[0] = notprime[1] = true;
    f[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!notprime[i]) {
            prime[++tot] = i;
            f[i] = f[i - 1];
        }

        for (int j = 1; j <= tot; ++j) {
            if (i * prime[j] > n)
                break;

            notprime[i * prime[j]] = true;
            f[i * prime[j]] = f[i] + f[prime[j]];

            if (i % prime[j] == 0)
                break;
        }
    }
}

void solve() {
    m = read();
    bool found = false;
    long long ans = 0;

    for (int i = 1; i <= m; ++i) {
        int p = read(), q = read();
        found |= (p == 2);
        ans += 1ll * f[p] * q;
    }

    ans += !found;
    write(ans);
}

int main() {
    ios::sync_with_stdio(false);
    preprocess(maxp - 10);
    t = read();

    while (t--)
        solve();

    return 0;
}