#include <iostream>
#include <vector>
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
constexpr long long oo = 0x3f3f3f3f;

int n, q;
vector<int> tree[maxn], vtree[maxn];
int timer, dfn[maxn], dep[maxn], step[maxn][18];
int timer2, seq[maxn], selected[maxn];
int st[maxn], top;
long long f[maxn][2];

void link(vector<int> tree[], int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void preprocess(int x, int fa) {
    dfn[x] = ++timer;
    dep[x] = dep[fa] + 1;

    for (int i = 1; i <= 17; ++i)
        step[x][i] = step[step[x][i - 1]][i - 1];

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        step[y][0] = x;
        preprocess(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 17; i >= 0; --i)
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];

    if (x == y)
        return x;

    for (int i = 17; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }

    return step[x][0];
}

void build(int seq[], int tot) {
    sort(seq + 1, seq + 1 + tot, [](int lhs, int rhs) {
        return dfn[lhs] < dfn[rhs];
    });

    vtree[1].clear();
    st[top = 1] = 1;

    for (int i = 1; i <= tot; ++i) {
        if (seq[i] == 1)
            continue;

        int l = lca(seq[i], st[top]);

        if (l != st[top]) {
            while (dfn[l] < dfn[st[top - 1]]) {
                link(vtree, st[top], st[top - 1]);
                --top;
            }

            if (dfn[l] != dfn[st[top - 1]]) {
                vtree[l].clear();
                link(vtree, st[top], l);
                st[top] = l;
            } else {
                link(vtree, st[top], l);
                --top;
            }
        }

        vtree[seq[i]].clear();
        st[++top] = seq[i];
    }

    for (int i = 1; i < top; ++i)
        link(vtree, st[i], st[i + 1]);
}

void dfs(int x, int fa) {
    f[x][0] = f[x][1] = 0;

    if (selected[x] == timer2) {
        for (int y : vtree[x]) {
            if (y == fa)
                continue;

            dfs(y, x);

            f[x][0] += min(f[y][0] + 1, f[y][1]);
        }

        f[x][1] = oo;
    } else {
        long long sum = 1, delta = 0;

        for (int y : vtree[x]) {
            if (y == fa)
                continue;

            dfs(y, x);

            f[x][0] += f[y][1];
            delta = min(delta, f[y][0] - f[y][1]);
            sum += min(f[y][0], f[y][1]);
            f[x][1] += f[y][1];
        }

        f[x][0] += delta;
        f[x][0] = min(f[x][0], sum);
        f[x][1] = min(f[x][1], sum);
    }
}

int main() {
    n = read();

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        link(tree, x, y);
    }

    preprocess(1, 0);

    q = read();

    for (int i = 1; i <= q; ++i) {
        int k = read();
        timer2 = i;

        for (int j = 1; j <= k; ++j) {
            seq[j] = read();
            selected[seq[j]] = timer2;
        }

        bool invalid = false;

        for (int j = 1; j <= k; ++j) {
            if (selected[step[seq[j]][0]] == timer2) {
                invalid = true;
                break;
            }
        }

        if (invalid) {
            write(-1);
            continue;
        }

        build(seq, k);
        dfs(1, 0);
        write(min(f[1][0], f[1][1]));
    }

    return 0;
}