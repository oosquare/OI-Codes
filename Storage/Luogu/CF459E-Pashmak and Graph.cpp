#include <cstdio>
#include <vector>
#include <queue>
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

constexpr int maxn = 3e5 + 10;

struct Edge {
    int from, to, length, id;
};

int n, m;
Edge edges[maxn];
int f[maxn], g[maxn], ans;

int main() {
    n = read(), m = read();

    for (int i = 1; i <= m; ++i) {
        auto &[s, t, v, id] = edges[i];
        s = read(), t = read(), v = read();
        id = i;
    }

    sort(edges + 1, edges + 1 + m, [](const Edge &lhs, const Edge &rhs) {
        return lhs.length < rhs.length;
    });

    for (int l = 1, r = 1; l <= m; l = r + 1, r = l) {
        while (edges[r + 1].length == edges[l].length)
            ++r;

        for (int i = l; i <= r; ++i) {
            auto [from, to, length, id] = edges[i];
            f[id] = max(f[id], g[from] + 1);
        }

        for (int i = l; i <= r; ++i) {
            auto [from, to, length, id] = edges[i];
            g[to] = max(g[to], f[id]);
        }
    }

    for (int i = 1; i <= m; ++i)
        ans = max(ans, f[i]);

    write(ans);
    return 0;
}