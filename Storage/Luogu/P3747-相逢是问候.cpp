#include <iostream>
using namespace std;

constexpr int MAXN = 5e4 + 10;
constexpr int INFINITY = 0x3f3f3f3f;

struct Node {
    int left, right;
    int cnt, sum;
};

int n, m, p, c;
int a[MAXN];
int seq[MAXN], g[MAXN], tot;
Node tree[MAXN * 4];
int p1[10001], p2[10001], p3[32][10001], p4[32][10001];

int gcd(int x, int y) {
    int t;

    while (y) {
        t = x;
        x = y;
        y = t % y;
    }

    return x;
}

int powerImpl(int x, int y) {
    if (y == INFINITY)
        return INFINITY;

    int res = 1;

    for (; y; y /= 2) {
        if (y % 2) {
            if (x == INFINITY || 1ll * res * x >= p)
                return INFINITY;

            res = res * x;
        }

        if (x == INFINITY || 1ll * x * x >= p)
            x = INFINITY;
        else
            x = x * x;
    }

    return res;
}

int power(int y) {
    int y1 = y % 10000, y2 = y / 10000;
    
    if (p1[y1] == INFINITY || p2[y2] == INFINITY || 1ll * p1[y1] * p2[y2] >= p)
        return INFINITY;
    
    return p1[y1] * p2[y2];
}

int power(int y, int id) {
    int y1 = y % 10000, y2 = y / 10000;
    return 1ll * p3[id][y1] * p4[id][y2] % seq[id];
}

int powerImpl(int x, int y, int p) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % p;

        x = 1ll * x * x % p;
    }

    return res;
}

int phi(int x) {
    int res = x;

    for (int i = 2; i * i <= x; ++i) {
        if (x % i)
            continue;

        res = res / i * (i - 1);

        while (x % i == 0)
            x /= i;
    }

    if (x > 1)
        res = res / x * (x - 1);

    return res;
}

void preprocess() {
    int x = p;

    while (seq[tot] != 1) {
        seq[++tot] = x;
        x = phi(x);
    }

    for (int i = 1; i <= tot; ++i)
        g[i] = gcd(seq[i], c);

    for (int i = 0; i <= 10000; ++i) {
        p1[i] = powerImpl(c, i);
        p2[i] = powerImpl(c, i * 10000);
    }

    for (int i = 1; i <= tot; ++i) {
        for (int j = 0; j <= 10000; ++j) {
            p3[i][j] = powerImpl(c, j, seq[i]);
            p4[i][j] = powerImpl(c, j * 10000, seq[i]);
        }
    }
}

pair<int, int> calc(int dep, int lim, int a) {
    if (dep == tot) {
        int prod = a;

        for (int i = lim; i >= dep; --i) {
            prod = power(prod);

            if (prod == INFINITY)
                return { 0, INFINITY };
        }

        return { 0, prod };
    }

    if (dep == lim + 1)
        return { a % seq[dep], a };

    auto [res, prod] = calc(dep + 1, lim, a);

    if (g[dep] == 1)
        res = power(res, dep);
    else if (prod >= seq[dep + 1])
        res = power(res + seq[dep + 1], dep);
    else
        res = power(prod, dep);

    prod = power(prod);
    return { res, prod };
}

inline void pushup(int x) {
    tree[x].sum = (tree[x * 2].sum + tree[x * 2 + 1].sum) % p;
    tree[x].cnt = min(tree[x * 2].cnt, tree[x * 2 + 1].cnt);
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r) {
        tree[x].sum = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void modify(int x, int l, int r) {
    if (tree[x].cnt >= tot || tree[x].right < l || r < tree[x].left)
        return;

    if (tree[x].left == tree[x].right) {
        ++tree[x].cnt;
        tree[x].sum = calc(1, tree[x].cnt, a[tree[x].left]).first;
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;

    if (l <= mid)
        modify(x * 2, l, r);

    if (mid < r)
        modify(x * 2 + 1, l, r);

    pushup(x);
}

int query(int x, int l, int r) {
    if (l <= tree[x].left && tree[x].right <= r)
        return tree[x].sum;

    int mid = (tree[x].left + tree[x].right) / 2, res = 0;

    if (l <= mid)
        res = (res + query(x * 2, l, r)) % p;

    if (mid < r)
        res = (res + query(x * 2 + 1, l, r)) % p;

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> p >> c;
    preprocess();

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    build(1, 1, n);

    for (int i = 1; i <= m; ++i) {
        int op, l, r;
        cin >> op >> l >> r;

        if (op == 0)
            modify(1, l, r);
        else
            cout << query(1, l, r) << endl;
    }

    return 0;
}