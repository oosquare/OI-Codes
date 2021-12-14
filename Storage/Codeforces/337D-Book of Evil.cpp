#include <cstdio>
#include <vector>
#include <iostream>
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

constexpr int maxn = 1e5 + 10;

int n, m, d;
vector<int> tree[maxn];
bool key[maxn];
int f[maxn][3], id[maxn], ans;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs1(int x, int fa) {
    f[x][0] = f[x][1] = f[x][2] = -0x3f3f3f3f;

    if (key[x])
        f[x][0] = 0;

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs1(y, x);

        if (f[x][0] <= f[y][0] + 1) {
            f[x][1] = f[x][0];
            f[x][0] = f[y][0] + 1;
            id[x] = y;
        } else if (f[x][1] <= f[y][0] + 1) {
            f[x][1] = f[y][0] + 1;
        }
    }
}

void dfs2(int x, int fa) {
    for (int y : tree[x]) {
        if (y == fa)
            continue;

        if (id[x] == y)
            f[y][2] = max(f[x][2] + 1, f[x][1] + 1);
        else
            f[y][2] = max(f[x][2] + 1, f[x][0] + 1);

        dfs2(y, x);
    }
}

int main() {
    n = read(), m = read(), d = read();

    for (int i = 1; i <= m; ++i) {
        int x = read();
        key[x] = true;
    }

    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        link(x, y);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    for (int i = 1; i <= n; ++i)
        if (max(f[i][0], f[i][2]) <= d)
            ++ans;

    write(ans);
    return 0;
}