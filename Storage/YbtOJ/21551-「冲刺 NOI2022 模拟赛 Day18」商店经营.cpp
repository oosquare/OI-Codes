#include <cstdio>

int read() {
    int x = 0;
    int c = std::getchar();

    for (; c < '0' || c > '9'; c = std::getchar())
        ;

    for (; '0' <= c && c <= '9'; c = std::getchar())
        x = x * 10 + c - '0';

    return x;
}

constexpr int MAX_N = 3000000 + 10;

struct Edge {
    int next, to;
};

int n, m;
int p[MAX_N], cnt[MAX_N];
Edge tree[MAX_N];
int head[MAX_N], tot;
int next[MAX_N];
long long ans;

void link(int x, int y) {
    tree[++tot] = { head[x], y };
    head[x] = tot;
}

void dfs(int x, int s) {
    if (cnt[x])
        s = x;
    
    next[x] = s;

    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next)
        dfs(y, s);
}

int find(int x) {
    if (x == -1 || next[x] == -1)
        return -1;
    
    if (cnt[next[x]])
        return next[x];
    else
        return next[x] = find(p[next[x]]);
}

int main() {
    std::freopen("shop.in", "r", stdin);
    std::freopen("shop.out", "w", stdout);

    n = read(), m = read();

    p[0] = -1;

    for (int i = 1; i < n; ++i) {
        p[i] = read();
        link(p[i], i);
    }

    for (int i = 1, c; i <= m; ++i) {
        c = read();
        ++cnt[c];
    }

    dfs(0, -1);

    for (int i = n - 1; i >= 0; --i) {
        int f = find(i);

        if (f != -1) {
            --cnt[f];
            ans += i;
        }
    }

    std::printf("%lld\n", ans);
    return 0;
}
