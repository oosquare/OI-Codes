#include <cstdio>
#include <algorithm>
#include <map>
#include <utility>
#include <tuple>

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

constexpr int maxn = 200000 + 10;

int n;
map<pair<int, int>, int> mp;
vector<int> tree[maxn];
int f[maxn][2], ans;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void dfs(int x, int fa) {
    for (int y : tree[x]) {
        if (y == fa)
            continue;

        dfs(y, x);

        if (f[x][0] <= f[y][0] + 1)
            f[x][1] = exchange(f[x][0], f[y][0] + 1);
        else if (f[x][1] < f[y][0] + 1)
            f[x][1] = f[y][0] + 1;
    }
}

void add(int x, int y, int id) {
    pair p = minmax(x, y);

    if (mp.find(p) == mp.end())
        mp[p] = id;
    else
        link(mp[p], id);
}

int main() {
    n = read();

    for (int i = 1; i <= n - 2; ++i) {
        int a = read(), b = read(), c = read();
        add(a, b, i);
        add(b, c, i);
        add(a, c, i);
    }

    dfs(1, 0);

    for (int i = 1; i <= n - 2; ++i)
        ans = max(ans, f[i][0] + f[i][1]);

    write(ans + 1);
    return 0;
}