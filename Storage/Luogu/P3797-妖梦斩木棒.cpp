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

constexpr int maxn = 200000 + 10;

struct node {
    int sum;
    char status[2];
};

node tree[maxn];
int n, m;

inline int ls(int x) { return x * 2; }

inline int rs(int x) { return x * 2 + 1; }

inline char select(int x, char y, char z) {
    return x ? y : (y == 'X' ? z : y);
}

node pushup(node l, node r) {
    node x = {0, {0, 0}};
    x.sum = l.sum + r.sum;
    if (l.status[1] == '(' && r.status[0] == ')')
        ++x.sum;
    x.status[0] = select(l.sum, l.status[0], r.status[0]);
    x.status[1] = select(r.sum, r.status[1], l.status[1]);
    return x;
}

void modify(int x, int l, int r, int p, char t) {
    if (l == r && r == p) {
        tree[x].status[0] = tree[x].status[1] = t;
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid)
        modify(ls(x), l, mid, p, t);
    else
        modify(rs(x), mid + 1, r, p, t);
    tree[x] = pushup(tree[ls(x)], tree[rs(x)]);
}

node query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[x];
    int mid = (l + r) / 2;
    if (qr <= mid)
        return query(ls(x), l, mid, ql, qr);
    else if (mid < ql)
        return query(rs(x), mid + 1, r, ql, qr);
    else
        return pushup(
            query(ls(x), l, mid, ql, mid),
            query(rs(x), mid + 1, r, mid + 1, qr)
        );
}

void build(int x, int l, int r) {
    tree[x] = {0, {'X', 'X'}};
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(ls(x), l, mid);
    build(rs(x), mid + 1, r);
}

void print(int x, int l, int r) {
    printf("{%d %d %d} : {%d, {%c, %c}}\n", x, l, r, tree[x].sum, tree[x].status[0], tree[x].status[1]);
    if (l == r)
        return;
    int mid = (l + r) / 2;
    print(ls(x), l, mid);
    print(rs(x), mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    using namespace IO;
    n = read();
    m = read();
    build(1, 1, n);
    modify(1, 1, n, 1, '(');
    modify(1, 1, n, n, ')');
    while (m--) {
        int t = read();
        if (t == 1) {
            int x = read();
            char y[10];
            scanf("%s", y);
            modify(1, 1, n, x, y[0]);
        } else {
            int x = read(), y = read();
            writeln(query(1, 1, n, x, y).sum);
        }
    }
    return 0;
}