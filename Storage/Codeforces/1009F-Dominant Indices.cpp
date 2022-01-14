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

    static int st[25];
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

constexpr int maxn = 1e6 + 10;
 
struct Node {
    int ls, rs;
    int max, pos;
};
 
int n;
vector<int> tree[maxn];
int dep[maxn];
Node seg[maxn * 22];
int uuid, root[maxn];
int ans[maxn];
 
void pushup(int x) {
    if (seg[seg[x].ls].max >= seg[seg[x].rs].max) {
        seg[x].max = seg[seg[x].ls].max;
        seg[x].pos = seg[seg[x].ls].pos;
    } else {
        seg[x].max = seg[seg[x].rs].max;
        seg[x].pos = seg[seg[x].rs].pos;
    }
}
 
void add(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;
 
    if (l == r) {
        seg[x].max += v;
        seg[x].pos = l;
        return;
    }
 
    int mid = (l + r) / 2;
 
    if (p <= mid)
        add(seg[x].ls, l, mid, p, v);
    else
        add(seg[x].rs, mid + 1, r, p, v);
 
    pushup(x);
}
 
int merge(int x, int y, int l, int r) {
    if (!x || !y)
        return x ^ y;
 
    if (l == r) {
        seg[x].max += seg[y].max;
        return x;
    }
 
    int mid = (l + r) / 2;
    seg[x].ls = merge(seg[x].ls, seg[y].ls, l, mid);
    seg[x].rs = merge(seg[x].rs, seg[y].rs, mid + 1, r);
    pushup(x);
    return x;
}
 
pair<int, int> query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return {seg[x].max, seg[x].pos};
 
    int mid = (l + r) / 2;
    pair<int, int> res = {0, 0};
 
    if (ql <= mid) {
        auto res2 = query(seg[x].ls, l, mid, ql, qr);
 
        if (res2.first > res.first)
            res = res2;
    }
 
    if (mid < qr) {
        auto res2 = query(seg[x].rs, mid + 1, r, ql, qr);
 
        if (res2.first > res.first)
            res = res2;
    }
 
    return res;
}
 
void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}
 
void solve(int x, int fa) {
    dep[x] = dep[fa] + 1;
    add(root[x], 1, n, dep[x], 1);
 
    for (int y : tree[x]) {
        if (y == fa)
            continue;
 
        solve(y, x);
        root[x] = merge(root[x], root[y], 1, n);
    }
 
    ans[x] = query(root[x], 1, n, dep[x], n).second - dep[x];
}

int main() {
    n = read();

    for (int i = 1, x, y; i < n; ++i) {
        x = read(), y = read();
        link(x, y);
    }

    solve(1, 0);

    for (int i = 1; i <= n; ++i)
        write(ans[i]);

    return 0;
}