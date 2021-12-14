#include <cstdio>
#include <algorithm>
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

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxn = 1e5 + 10;

int n, a[maxn];
long long ans;

int main() {
    n = read();

    for (int i = 1; i <= n; ++i)
        a[i] = read();

    ans += 1ll * a[1] * (n - a[1] + 1);

    for (int i = 2; i <= n; ++i) {
        auto [x, y] = minmax(a[i - 1], a[i]);
        ans += 1ll * a[i] * (n - a[i] + 1) - 1ll * x * (n - y + 1);
    }

    write(ans);
    return 0;
}