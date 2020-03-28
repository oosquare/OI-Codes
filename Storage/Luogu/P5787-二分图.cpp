#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

struct operation {
    int x, y, next;
};

constexpr int maxn = 4e5 + 5;
int tree[maxn];
operation oplist[maxn << 4];
int uuid;
int fa[maxn], dep[maxn], stk[maxn][2], top;
bool ans[maxn];
int n, m, k;

inline void create(int &head, int x, int y) {
    int newnode = ++uuid;
    oplist[newnode] = {x,y,head};
    head = newnode;
}

void modify(int x, int l, int r, int ml, int mr, int mx, int my) {
    if (ml <= l && r <= mr) {
        create(tree[x], mx, my);
        return;
    }
    int mid = (l + r) >> 1;
    if (ml <= mid)
        modify(x << 1, l, mid, ml, mr, mx, my);
    if (mid < mr)
        modify(x << 1 | 1, mid + 1, r, ml, mr, mx, my);
}

inline int search(int x) {
    while (x != fa[x])
        x = fa[x];
    return x;
}

inline void merge(int x, int y) {
    if (x == y)
        return;
    if (dep[x] < dep[y])
        swap(x, y);
    
    ++top;
    stk[top][0] = y;
    stk[top][1] = dep[x] == dep[y];
    fa[y] = x;
    dep[x] += dep[x] == dep[y];
}

inline void undo(int id) {
    while (top > id) {
        dep[fa[stk[top][0]]] -= stk[top][1];
        fa[stk[top][0]] = stk[top][0];
        --top;
    }
}

void solve(int x, int l, int r, bool status) {
    int first = top;
    for (int i = tree[x]; i; i = oplist[i].next) {
        int fx = search(oplist[i].x), fy = search(oplist[i].y);
        if (fx == fy) {
            status = false;
        } else {
            merge(fx, search(oplist[i].y + n));
            merge(fy, search(oplist[i].x + n));
        }
    }
    if (l == r) {
        ans[l] = status;
    } else {
        int mid = (l + r) >> 1;
        solve(x << 1, l, mid, status);
        solve(x << 1 | 1, mid + 1, r, status);
    }
    undo(first);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    m = read();
    k = read();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read(), l = read(), r = read();
        modify(1, 1, k, l + 1, r, x, y);
    }
    for (int i = 1; i <= (n << 1); ++i) {
        fa[i] = i;
        dep[i] = 1;
    }
    solve(1, 1, k, true);
    for (int i = 1; i <= k; ++i)
        printf("%s\n", ans[i] ? "Yes" : "No");
    return 0;
}