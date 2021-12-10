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

void write(const char *str, char sep = '\n') {
    while (*str != '\0')
        putchar(*str++);

    putchar(sep);
}

constexpr int maxn = 500000 + 10;

int n, m;
char str[maxn];
vector<int> tree[maxn];
int timer, dfn[maxn], rev[maxn], dep[maxn], sze[maxn], son[maxn];
int cnt[maxn];
vector<pair<int, int>> querys[maxn];
bool ans[maxn];

void link(int x, int y) {
    tree[x].push_back(y);
}

void preprocess(int x, int fa) {
    sze[x] = 1;
    dep[x] = dep[fa] + 1;
    dfn[x] = ++timer;
    rev[timer] = x;

    for (int y : tree[x]) {
        preprocess(y, x);
        sze[x] += sze[y];

        if (sze[son[x]] < sze[y])
            son[x] = y;
    }
}

void solve(int x, bool keep) {
    for (int y : tree[x]) {
        if (y == son[x])
            continue;

        solve(y, false);
    }

    if (son[x])
        solve(son[x], true);

    cnt[dep[x]] ^= (1 << (str[x] - 'a'));

    for (int y : tree[x]) {
        if (y == son[x])
            continue;

        for (int i = dfn[y]; i < dfn[y] + sze[y]; ++i)
            cnt[dep[rev[i]]] ^= (1 << (str[rev[i]] - 'a'));
    }

    for (auto [h, id] : querys[x]) {
        int sum = 0;

        for (int i = 0; i < 26; ++i)
            sum += ((cnt[h] >> i) & 1);

        if (sum <= 1)
            ans[id] = true;
    }

    if (!keep)
        for (int i = dfn[x]; i < dfn[x] + sze[x]; ++i)
            cnt[dep[rev[i]]] ^= (1 << (str[rev[i]] - 'a'));
}

int main() {
    n = read(), m = read();

    for (int i = 2; i <= n; ++i) {
        int p = read();
        link(p, i);
    }

    for (int i = 1; i <= n; ++i) {
        str[i] = getchar();

        while (str[i] < 'a' || 'z' < str[i])
            str[i] = getchar();
    }

    for (int i = 1; i <= m; ++i) {
        int x = read(), h = read();
        querys[x].push_back({h, i});
    }

    preprocess(1, 0);
    solve(1, false);

    for (int i = 1; i <= m; ++i)
        write(ans[i] ? "Yes" : "No");
    
    return 0;
}