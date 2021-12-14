#include <cstdio>
#include <unordered_map>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';

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

constexpr int maxn = 300 + 10;

int n, g, l[maxn], c[maxn];
unordered_map<int, int> f[2];

void update(unordered_map<int, int> &f, int p, int v) {
    if (f.find(p) == f.end())
        f[p] = v;
    else
        f[p] = min(f[p], v);
}

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

int main() {
    n = read();

    for (int i = 1; i <= n; ++i)
        l[i] = read();

    for (int i = 1; i <= n; ++i)
        c[i] = read();

    g = l[1];

    for (int i = 2; i <= n; ++i)
        g = gcd(g, l[i]);

    if (g != 1) {
        write(-1);
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        int now = (i & 1), pre = (now ^ 1);
        f[now].clear();
        update(f[now], l[i], c[i]);

        for (auto [g, v] : f[pre]) {
            update(f[now], g, v);
            update(f[now], gcd(g, l[i]), v + c[i]);
        }
    }

    write(f[n & 1][1]);
    return 0;
}
