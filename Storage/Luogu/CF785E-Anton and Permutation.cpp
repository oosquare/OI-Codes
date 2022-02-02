#include <cstdio>
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

void swap(int &x, int &y) {
    x ^= y ^= x ^= y;
}

constexpr int maxn = 2e5 + 10;

struct Node {
    int ls, rs;
    int sum;
};

int n, q, a[maxn];
int arr[maxn];
Node tree[maxn * 200];
int uuid, root[maxn];
int st[maxn * 10], top;
long long ans;

int alloc() {
    return (top ? st[top--] : ++uuid);
}

void gc(int &x) {
    if (tree[x].sum)
        return;

    tree[x].ls = tree[x].rs = 0;
    st[++top] = x;
    x = 0;
}

void add(int &x, int l, int r, int p, int v) {
    if (!x)
        x = alloc();

    tree[x].sum += v;

    if (l == r)
        return;

    int mid = (l + r) / 2;

    if (p <= mid) {
        add(tree[x].ls, l, mid, p, v);
        gc(tree[x].ls);
    } else {
        add(tree[x].rs, mid + 1, r, p, v);
        gc(tree[x].rs);
    }
}

int query(int x, int l, int r, int ql, int qr) {
    if (ql > qr || !x)
        return 0;

    if (ql <= l && r <= qr)
        return tree[x].sum;

    int mid = (l + r) / 2, res = 0;

    if (ql <= mid)
        res += query(tree[x].ls, l, mid, ql, qr);

    if (mid < qr)
        res += query(tree[x].rs, mid + 1, r, ql, qr);

    return res;
}

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v, int d) {
    for (; p <= n; p += lowbit(p))
        add(root[p], 1, n, v, d);
}

void modify(int p, int v) {
    add(p, arr[p], -1);
    arr[p] = v;
    add(p, v, 1);
}

int queryLess(int l, int r, int v) {
    if (l > r)
        return 0;

    int res = 0;

    for (; r; r -= lowbit(r))
        res += query(root[r], 1, n, 1, v - 1);

    for (--l; l; l -= lowbit(l))
        res -= query(root[l], 1, n, 1, v - 1);

    return res;
}

int queryGreater(int l, int r, int v) {
    if (l > r)
        return 0;

    int res = 0;

    for (; r; r -= lowbit(r))
        res += query(root[r], 1, n, v + 1, n);

    for (--l; l; l -= lowbit(l))
        res -= query(root[l], 1, n, v + 1, n);

    return res;
}

int main() {
    n = read(), q = read();

    for (int i = 1; i <= n; ++i) {
        a[i] = i;
        ans += queryGreater(1, i - 1, a[i]);
        arr[i] = a[i];
        add(i, a[i], 1);
    }

    for (int i = 1; i <= q; ++i) {
        int x = read(), y = read();

        if (a[x] == a[y]) {
            write(ans);
            continue;
        }

        if (x > y)
            swap(x, y);

        ans -= queryLess(x + 1, y - 1, a[x]);
        ans += queryGreater(x + 1, y - 1, a[x]);
        ans -= queryGreater(x + 1, y - 1, a[y]);
        ans += queryLess(x + 1, y - 1, a[y]);

        if (a[x] < a[y])
            ++ans;
        else
            --ans;

        modify(x, a[y]);
        modify(y, a[x]);
        swap(a[x], a[y]);
        write(ans);
    }

    return 0;
}