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

constexpr int maxn = 1e5 + 10;
constexpr int maxm = 200 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Packet {
    int w, d;

    bool operator<(const Packet &rhs) const {
        if (w != rhs.w)
            return w < rhs.w;

        return d < rhs.d;
    }
};

struct Node {
    int left, right;
    Packet max, assign;
};

int n, m, k;
Node tree[maxn * 4];
long long f[maxn][maxm], ans = oo;

void pushup(int x) {
    tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
}

void update(int x, const Packet &v) {
    tree[x].max = max(tree[x].max, v);
    tree[x].assign = max(tree[x].assign, v);
}

void pushdown(int x) {
    if (tree[x].assign.w == 0)
        return;

    update(x * 2, tree[x].assign);
    update(x * 2 + 1, tree[x].assign);
    tree[x].assign = {0, 0};
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r)
        return;

    int mid = (l + r) >> 1;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void assign(int x, int l, int r, const Packet &v) {
    if (l <= tree[x].left && tree[x].right <= r) {
        update(x, v);
        return;
    }

    int mid = (tree[x].left + tree[x].right) >> 1;
    pushdown(x);

    if (l <= mid)
        assign(x * 2, l, r, v);

    if (mid < r)
        assign(x * 2 + 1, l, r, v);

    pushup(x);
}

Packet query(int x, int p) {
    if (tree[x].left == tree[x].right)
        return tree[x].max;

    int mid = (tree[x].left + tree[x].right) >> 1;
    pushdown(x);

    if (p <= mid)
         return query(x * 2, p);
    else
        return query(x * 2 + 1, p);
}

int main() {
    n = read(), m = read(), k = read();

    build(1, 1, n);

    for (int i = 1; i <= k; ++i) {
        int s = read(), t = read(), d = read(), w = read();
        assign(1, s, t, {w, d});
    }

    for (int i = 1; i <= n + 1; ++i)
        for (int j = 0; j <= m; ++j)
            f[i][j] = oo;
    
    f[1][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            auto [w, d] = query(1, i);

            if (w == 0)
                f[i + 1][j] = min(f[i + 1][j], f[i][j]);
            else
                f[d + 1][j] = min(f[d + 1][j], f[i][j] + w);

            if (j < m)
                f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j]);
        }
    }

    for (int i = 0; i <= m; ++i)
        ans = min(ans, f[n + 1][i]);

    write(ans);
    return 0;
}