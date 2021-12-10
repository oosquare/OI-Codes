#include <iostream>
#include <algorithm>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
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

using ll = long long;

constexpr ll oo = 0x3f3f3f3f3f3f3f3f;
constexpr int maxn = 1e5 + 10;

struct Node {
    int left, right;
    ll min, add;
};

int n, m;
ll h[maxn], sum[maxn];
int st[maxn], top, las[maxn];
Node tree[maxn * 4];
ll f[maxn];

void pushup(int x) {
    tree[x].min = min(tree[x * 2].min, tree[x * 2 + 1].min);
}

void update(int x, ll v) {
    tree[x].min += v;
    tree[x].add += v;
}

void pushdown(int x) {
    if (tree[x].add == 0)
        return;

    update(x * 2, tree[x].add);
    update(x * 2 + 1, tree[x].add);
    tree[x].add = 0;
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r) {
        // tree[x].min = oo;
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void add(int x, int l, int r, ll v) {
    if (l <= tree[x].left && tree[x].right <= r) {
        update(x, v);
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;
    pushdown(x);

    if (l <= mid)
        add(x * 2, l, r, v);

    if (mid < r)
        add(x * 2 + 1, l, r, v);

    pushup(x);
} 

ll query(int x, int l, int r) {
    if (l <= tree[x].left && tree[x].right <= r)
        return tree[x].min;

    int mid = (tree[x].left + tree[x].right) / 2;
    ll res = 0x3f3f3f3f3f3f3f3f;
    pushdown(x);

    if (l <= mid)
        res = min(res, query(x * 2, l, r));

    if (mid < r)
        res = min(res, query(x * 2 + 1, l, r));

    return res;
}

void dfs(int x) {
    if (tree[x].left == tree[x].right) {
        cout << tree[x].min << " ";
        return;
    }

    dfs(x * 2);
    dfs(x * 2 + 1);
}

void print() {
    dfs(1);
    cout << endl;
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        sum[i] = sum[i - 1] + h[i];
    }

    build(1, 0, n);

    for (int i = 1; i <= n; ++i) {
        while (top > 0 && h[st[top]] < h[i]) {
            add(1, st[top - 1], st[top] - 1, -h[st[top]]);
            --top;
        }

        st[++top] = i;
        add(1, st[top - 1], i - 1, h[i]);

        int j = lower_bound(sum, sum + 1 + i - 1, sum[i] - m) - sum;
        f[i] = query(1, j, i - 1);
        add(1, i, i, f[i]);
    }

    write(f[n]);
    return 0;
}