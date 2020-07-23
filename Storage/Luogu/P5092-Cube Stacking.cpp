#include <bits/stdc++.h>
using namespace std;

namespace IO {

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * s;
}

template <typename T = int> void writeln(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int> void writesp(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    if (x == 0)
        stk[++top] = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top)
        putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

constexpr int maxn = 30000 + 10;

struct node {
    int key, l, r, f, size, priority;
};

node tree[maxn];
int uuid, root[maxn];
int father[maxn];
int n;

int &ls(int x) { return tree[x].l; }

int &rs(int x) { return tree[x].r; }

int &fa(int x) { return tree[x].f; }

void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
}

int merge(int x, int y) {
    if (!x || !y)
        return x ^ y;
    if (tree[x].priority > tree[y].priority) {
        rs(x) = merge(rs(x), y);
        fa(rs(x)) = x;
        pushup(x);
        return x;
    } else {
        ls(y) = merge(x, ls(y));
        fa(ls(y)) = y;
        pushup(y);
        return y;
    }
}

int query(int x) {
    int ans = tree[ls(x)].size + 1;
    while (fa(x)) {
        if (rs(fa(x)) == x) {
            ans += tree[ls(fa(x))].size + 1;
        }
        x = fa(x);
    }
    return ans - 1;
}

int find(int x) {
    return x == father[x] ? x : father[x] = find(father[x]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    srand(time(nullptr));
    for (int i = 1; i <= 30000; ++i) {
        father[i] = i;
        tree[i] = {i, 0, 0, 0, 1, rand()};
        root[i] = i;
    }
    n = read();
    while (n--) {
        char s[10];
        scanf("%s", s);
        if (s[0] == 'M') {
            int x = read(), y = read();
            int fx = find(x), fy = find(y);
            father[fx] = fy;
            root[fy] = merge(root[fy], root[fx]);
        } else {
            int x = read();
            writeln(query(x));
        }
    }
    return 0;
}