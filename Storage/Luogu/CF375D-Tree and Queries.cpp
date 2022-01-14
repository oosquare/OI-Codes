#include <cstdio>
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

using namespace std;

constexpr int maxn = 1e5 + 10;

int n, m, col[maxn];
vector<int> tree[maxn];
int arr[maxn], cnt[maxn];
int sze[maxn], son[maxn], timer, dfn[maxn], rev[maxn];
vector<pair<int, int>> qs[maxn];
int ans[maxn];

inline int lowbit(int x) {
    return x & (-x);
}

void add(int x, int v) {
    if (!x)
        return;

    for (; x <= n; x += lowbit(x))
        arr[x] += v;
}

int query(int x) {
    int res = 0;

    for (; x; x -= lowbit(x))
        res += arr[x];

    return res;
}

void clear(int x) {
    if (!x)
        return;

    for (; x <= n; x += lowbit(x))
        if (arr[x])
            arr[x] = 0;
        else
            return;
}

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void preprocess(int x, int fa) {
    sze[x] = 1;
    dfn[x] = ++timer;
    rev[timer] = x;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        preprocess(y, x);
        sze[x] += sze[y];

        if (sze[y] > sze[son[x]])
            son[x] = y;
    }
}

void solve(int x, int fa, bool keep) {
    for (int y : tree[x]) {
        if (y == fa || y == son[x])
            continue;

        solve(y, x, false);
    }

    if (son[x])
        solve(son[x], x, true);

    for (int y : tree[x]) {
        if (y == fa || y == son[x])
            continue;

        for (int i = dfn[y], e = dfn[y] + sze[y] - 1; i <= e; ++i) {
            int &c = cnt[col[rev[i]]];
            add(c, -1);
            ++c;
            add(c, 1);
        }
    }

    int &c = cnt[col[x]];
    add(c, -1);
    ++c;
    add(c, 1);

    for (auto [k, id] : qs[x]) {
        ans[id] = (k <= n ? query(n) - query(k - 1) : 0);
    }

    if (!keep) {
        for (int i = dfn[x], e = dfn[x] + sze[x] - 1; i <= e; ++i) {
            int &c = cnt[col[rev[i]]];
            clear(c);
            c = 0;
        }
    }
}


int main() {
    n = read(), m = read();

    for (int i = 1; i <= n; ++i)
        col[i] = read();

    for (int i = 1, x, y; i < n; ++i) {
        x = read(), y = read();
        link(x, y);
    }

    for (int i = 1, x, k; i <= m; ++i) {
        x = read(), k = read();
        qs[x].push_back({k, i});
    }

    preprocess(1, 0);
    solve(1, 0, true);

    for (int i = 1; i <= m; ++i)
        write(ans[i]);

    return 0;
}