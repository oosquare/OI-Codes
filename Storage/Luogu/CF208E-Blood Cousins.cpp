#include <iostream>
#include <vector>
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

    static int st[21];
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

constexpr int maxn = 1e5 + 10;

int n, m;
vector<int> tree[maxn];
int timer, dfn[maxn], rev[maxn], dep[maxn], sze[maxn], son[maxn], step[maxn][18];
vector<pair<int, int>> querys[maxn];
int cnt[maxn], ans[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
}

void preprocess(int x) {
    dfn[x] = ++timer;
    rev[timer] = x;
    sze[x] = 1;

    for (int i = 1; i <= 17; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (int y : tree[x]) {
        step[y][0] = x;
        dep[y] = dep[x] + 1;
        preprocess(y);
        sze[x] += sze[y];

        if (sze[son[x]] < sze[y])
            son[x] = y;
    }
}

int father(int x, int k) {
    for (int i = 17; i >= 0; --i) {
        if ((1 << i) <= k) {
            k -= (1 << i);
            x = step[x][i];
        }
    }

    return x;
}

void solve(int x, bool keep) {
    for (int y : tree[x]) {
        if (y == son[x])
            continue;
        
        solve(y, false);
    }

    if (son[x])
        solve(son[x], true);
    
    ++cnt[dep[x]];
    
    for (int y : tree[x]) {
        if (y == son[x])
            continue;
        
        for (int i = dfn[y]; i < dfn[y] + sze[y]; ++i)
            ++cnt[dep[rev[i]]];
    }

    for (auto [p, id] : querys[x])
        ans[id] = cnt[dep[x] + p] - 1;
    
    if (!keep)
        for (int i = dfn[x]; i < dfn[x] + sze[x]; ++i)
            --cnt[dep[rev[i]]];
}

int main() {
    n = read();

    for (int i = 1; i <= n; ++i) {
        int p = read();
        link(p, i);
    }

    preprocess(0);
    m = read();

    for (int i = 1; i <= m; ++i) {
        int x = read(), p = read();
        
        if (dep[x] > p)
            querys[father(x, p)].push_back({p, i});
    }

    solve(0, true);

    for (int i = 1; i <= m; ++i)
        write(ans[i], ' ');
    
    return 0;
}