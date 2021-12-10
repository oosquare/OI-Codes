#include <iostream>
#include <algorithm>

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

constexpr int maxn = 2.5e5 + 10;
constexpr int oo = 0x3f3f3f3f;

int n, m;
vector<pair<int, long long>> tree[maxn], vtree[maxn];
int dfn[maxn], timer;
int dep[maxn], step[maxn][19], mi[maxn][19];
long long f[maxn];
int seq[maxn], key[maxn], timer2;
int st[maxn];

void link(vector<pair<int, long long>> tree[], int x, int y, int l) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void preprocess(int x, int fa) {
    dfn[x] = ++timer;
    dep[x] = dep[fa] + 1;

    for (int i = 1; i <= 18; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (int i = 1; i <= 18; ++i)
        mi[x][i] = min(mi[x][i - 1], mi[step[x][i - 1]][i - 1]);

    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;

        step[y][0] = x;
        mi[y][0] = l;
        preprocess(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 18; i >= 0; --i)
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];

    if (x == y)
        return x;

    for (int i = 18; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }

    return step[x][0];
}

int len(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    int res = oo;

    for (int i = 18; i >= 0; --i) {
        if (dep[step[x][i]] >= dep[y]) {
            res = min(res, mi[x][i]);
            x = step[x][i];
        }
    }

    return res;
}

void build(int seq[], int tot) {
    int top = 0;

    sort(seq + 1, seq + 1 + tot, [](int l, int r) {
        return dfn[l] < dfn[r];
    });

    st[++top] = 1;
    vtree[1].clear();

    for (int i = 1; i <= tot; ++i) {
        if (seq[i] == 1)
            continue;

        int l = lca(seq[i], st[top]);

        if (l != st[top]) {
            while (dfn[l] < dfn[st[top - 1]]) {
                link(vtree, st[top], st[top - 1], len(st[top], st[top - 1]));
                --top;
            }

            if (dfn[l] != dfn[st[top - 1]]) {
                vtree[l].clear();
                link(vtree, st[top], l, len(st[top], l));
                st[top] = l;
            } else {
                link(vtree, st[top], l, len(st[top], l));
                --top;
            }
        }

        vtree[seq[i]].clear();
        st[++top] = seq[i];
    }

    for (int i = 1; i < top; ++i)
        link(vtree, st[i], st[i + 1], len(st[i], st[i + 1]));
}

void dfs(int x, int fa) {
    f[x] = (vtree[x].size() == 1 && x != 1 ? oo : 0);

    for (auto [y, l] : vtree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);

        if (key[y] == timer2)
            f[x] += l;
        else
            f[x] += min(f[y], l);
    }
}

int main() {
    n = read();

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read(), w = read();
        link(tree, x, y, w);
    }

    preprocess(1, 0);

    m = read();

    for (int i = 1; i <= m; ++i) {
        cerr << endl;
        int k = read();
        timer2 = i;

        for (int j = 1; j <= k; ++j) {
            int t = read();
            key[t] = timer2;
            seq[j] = t;
        }

        build(seq, k);
        dfs(1, 0);
        write(f[1]);
    }

    return 0;
}