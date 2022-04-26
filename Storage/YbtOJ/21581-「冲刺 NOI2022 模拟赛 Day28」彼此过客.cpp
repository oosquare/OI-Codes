#include <iostream>
#include <vector>

constexpr int MAX_N = 1000000 + 10;
constexpr int INF = 0x3f3f3f3f;

struct Node {
    int left, right;
    int max, add;
};

int n, k;
int a[MAX_N];
Node seg[MAX_N * 4];
std::vector<int> tree[MAX_N];
int dfn[MAX_N], sze[MAX_N], timer;
int st[MAX_N], top;

void pushup(int x) { seg[x].max = std::max(seg[x * 2].max, seg[x * 2 + 1].max); }

void update(int x, int v) {
    seg[x].max += v;
    seg[x].add += v;
}

void pushdown(int x) {
    if (!seg[x].add)
        return;

    update(x * 2, seg[x].add);
    update(x * 2 + 1, seg[x].add);
    seg[x].add = 0;
}

void build(int x, int l, int r) {
    seg[x].left = l;
    seg[x].right = r;

    if (l == r) {
        seg[x].max = -INF;
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void modify(int x, int p, int v) {
    if (seg[x].left == seg[x].right) {
        seg[x].max = v;
        return;
    }

    pushdown(x);
    int mid = (seg[x].left + seg[x].right) / 2;

    if (p <= mid)
        modify(x * 2, p, v);
    else
        modify(x * 2 + 1, p, v);

    pushup(x);
}

void add(int x, int l, int r, int v) {
    if (l <= seg[x].left && seg[x].right <= r) {
        update(x, v);
        return;
    }

    pushdown(x);
    int mid = (seg[x].left + seg[x].right) / 2;

    if (l <= mid)
        add(x * 2, l, r, v);

    if (mid < r)
        add(x * 2 + 1, l, r, v);

    pushup(x);
}

void link(int x, int y) { tree[x].push_back(y); }

void dfs(int x) {
    dfn[x] = ++timer;
    sze[x] = 1;

    for (int y : tree[x]) {
        dfs(y);
        sze[x] += sze[y];
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("passerby.in", "r", stdin);
    std::freopen("passerby.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    a[n + 1] = -INF;

    for (int i = 1; i <= n + 1; ++i) {
        while (top && a[st[top]] >= a[i]) {
            link(i, st[top]);
             --top;
        }

        st[++top] = i;
    }

    dfs(n + 1);
    build(1, 1, n + 1);

    for (int i = 1; i <= k; ++i) {
        modify(1, dfn[i], 0);
        add(1, dfn[i], dfn[i] + sze[i] - 1, 1);
    }

    for (int i = k + 1; i <= n; ++i) {
        std::cout << seg[1].max << " ";
        modify(1, dfn[i - k], -INF);
        modify(1, dfn[i], 0);
        add(1, dfn[i], dfn[i] + sze[i] - 1, 1);
    }

    std::cout << seg[1].max << std::endl;
    return 0;
}
