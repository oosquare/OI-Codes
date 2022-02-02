#include <cstdio>
#include <vector>
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

constexpr int maxn = 5e4 + 10;
constexpr int mod = 1e9 + 7;

struct Node {
    int ls, rs;
    int sum, cnt;
};

int n, m;
Node tree[maxn * 200];
int uuid, root[maxn];
int a[maxn], v[maxn];
int ans;

inline void add(int &x, int y) {
    x += y;

    if (x >= mod)
        x -= mod;
}

inline void sub(int &x, int y) {
    x -= y;

    if (x < 0)
        x += mod;
}

void add(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    tree[x].sum = ((tree[x].sum + v) % mod + mod) % mod;
    tree[x].cnt = (tree[x].cnt + (v > 0 ? 1 : -1) + mod) % mod;

    if (l == r)
        return;

    int mid = (l + r) / 2;

    if (p <= mid)
        add(tree[x].ls, l, mid, p, v);
    else
        add(tree[x].rs, mid + 1, r, p, v);
}

vector<int> move(const vector<int> &rt, int dir) {
    vector<int> res;

    if (dir == 0) {
        for (int x : rt)
            res.push_back(tree[x].ls);
    } else {
        for (int x : rt)
            res.push_back(tree[x].rs);
    }

    return res;
}

pair<int, int> query(const vector<int> &add, const vector<int> &del, int l, int r, int ql, int qr) {
    if (ql > qr)
        return {0, 0};

    if (ql <= l && r <= qr) {
        pair<int, int> res = {0, 0};

        for (int x : add) {
            ::add(res.first, tree[x].sum);
            ::add(res.second, tree[x].cnt);
        }

        for (int x : del) {
            sub(res.first, tree[x].sum);
            sub(res.second, tree[x].cnt);
        }

        return res;
    }

    int mid = (l + r) / 2;
    pair<int, int> res = {0, 0};

    if (ql <= mid) {
        auto res2 = query(move(add, 0), move(del, 0), l, mid, ql, qr);
        ::add(res.first, res2.first);
        ::add(res.second, res2.second);
    }

    if (mid < qr) {
        auto res2 = query(move(add, 1), move(del, 1), mid + 1, r, ql, qr);
        ::add(res.first, res2.first);
        ::add(res.second, res2.second);
    }

    return res;
}

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int y, int z) {
    for (; x <= n; x += lowbit(x))
        add(root[x], 1, n, y, z);
}

int queryLess(int l, int r, int x) {
    if (l > r)
        return 0;

    vector<int> add, del;

    for (; r; r -= lowbit(r))
        add.push_back(root[r]);

    for (--l; l; l -= lowbit(l))
        del.push_back(root[l]);

    auto [sum, cnt] = query(add, del, 1, n, 1, a[x] - 1);
    return (sum + 1ll * cnt * v[x]) % mod;
}

int queryGreater(int l, int r, int x) {
    if (l > r)
        return 0;

    vector<int> add, del;

    for (; r; r -= lowbit(r))
        add.push_back(root[r]);

    for (--l; l; l -= lowbit(l))
        del.push_back(root[l]);

    auto [sum, cnt] = query(add, del, 1, n, a[x] + 1, n);
    return (sum + 1ll * cnt * v[x]) % mod;
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= n; ++i) {
        a[i] = read(), v[i] = read();
        add(i, a[i], v[i]);
        add(ans, queryGreater(1, i - 1, i));
    }

    for (int i = 1, x, y; i <= m; ++i) {
        x = read(), y = read();

        if (x == y) {
            write(ans);
            continue;
        }

        if (x > y)
            swap(x, y);

        sub(ans, queryLess(x + 1, y - 1, x));
        add(ans, queryGreater(x + 1, y - 1, x));
        sub(ans, queryGreater(x + 1, y - 1, y));
        add(ans, queryLess(x + 1, y - 1, y));

        if (a[x] < a[y])
            add(ans, v[x] + v[y]);
        else if (a[x] > a[y])
            sub(ans, v[x] + v[y]);

        add(x, a[x], -v[x]);
        add(y, a[y], -v[y]);
        swap(a[x], a[y]);
        swap(v[x], v[y]);
        add(x, a[x], v[x]);
        add(y, a[y], v[y]);
        write(ans);
    }

    return 0;
}