#include <iostream>
#include <vector>

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

constexpr int MAX_N = 200000 + 10;
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;

class PersistentSegmentTree {
public:
    void init(long long len) {
        this->len = len;
    }

    void add(int now, int pre, long long p) {
        add(root[now], root[pre], 0, len, p);
    }

    long long query(int rl, int rr, long long ql, long long qr, long long b) {
        return query(root[rr], root[rl - 1], 0, len, ql, qr, b);
    }
private:
    struct Node {
        int ls, rs;
        long long sum, cnt;
    };

    Node tree[MAX_N * 70];
    int root[MAX_N], tot;
    long long len;

    void add(int &now, int pre, long long l, long long r, long long p) {
        now = ++tot;
        tree[now] = tree[pre];
        tree[now].sum += p;
        tree[now].cnt += 1;

        if (l == r)
            return;

        long long mid = (l + r) / 2;

        if (p <= mid)
            add(tree[now].ls, tree[pre].ls, l, mid, p);
        else
            add(tree[now].rs, tree[pre].rs, mid + 1, r, p);
    }

    long long query(int a, int d, long long l, long long r, long long ql, long long qr, long long b) {
        if (!a && !d)
            return 0;

        if (ql <= l && r <= qr)
            return tree[a].sum - tree[d].sum - b * (tree[a].cnt - tree[d].cnt);

        long long mid = (l + r) / 2;
        long long res = 0;

        if (ql <= mid)
            res += query(tree[a].ls, tree[d].ls, l, mid, ql, qr, b);

        if (mid < qr)
            res += query(tree[a].rs, tree[d].rs, mid + 1, r, ql, qr, b);

        return res;
    }
};

int n, q;
std::vector<std::pair<int, int>> tree[MAX_N];
long long dis[MAX_N];
int sze[MAX_N];
int timer, dfn[MAX_N];
PersistentSegmentTree seg;

void link(int x, int y, int w) {
    tree[x].push_back({ y, w });
}

void dfs(int x) {
    dfn[x] = ++timer;
    seg.add(timer, timer - 1, dis[x]);
    sze[x] = 1;

    for (auto [y, w] : tree[x]) {
        dis[y] = dis[x] + w;
        dfs(y);
        sze[x] += sze[y];
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("distance.in", "r", stdin);
    std::freopen("distance.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    n = read();

    for (int i = 1; i < n; ++i) {
        int p = read(), w = read();
        link(p, i + 1, w);
    }

    seg.init(INF);
    dfs(1);

    std::cin >> q;

    for (int i = 1; i <= q; ++i) {
        int x = read(), k = read();
       write(seg.query(dfn[x], dfn[x] + sze[x] - 1, dis[x] + k, INF, dis[x]));
    }

    return 0;
}
