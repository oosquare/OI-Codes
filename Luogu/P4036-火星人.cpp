#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct node {
    char key; ull val; int l, r, size, priority;
};

const int maxn = 1000000 + 10;
const int mod = 27;
node tree[maxn]; int root, uuid, seed;
int m; ull power[maxn]; char str[maxn], cmd[3];
int stk[maxn];

#define ls(x) (tree[(x)].l)
#define rs(x) (tree[(x)].r)
#define myrandom() (seed = (int)(seed * 413273LL % 0x7fffffff), seed)

inline int create(char key) {
    key = key - 'a' + 1;
    tree[++uuid] = { key, (ull)key, 0, 0, 1, myrandom() }; return uuid;
}

inline void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    tree[x].val = tree[rs(x)].val + 
        (ull)tree[x].key * power[tree[rs(x)].size] + 
        tree[ls(x)].val * power[tree[rs(x)].size + 1];
}

void split(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    if (tree[ls(root)].size < sze) {
        x = root; split(rs(x), sze - tree[ls(x)].size - 1, rs(x), y);
    } else {
        y = root; split(ls(y), sze, x, ls(y));
    }
    pushup(root);
}

int merge(int x, int y) {
    if (!x||!y) return x ^ y;
    if (tree[x].priority < tree[y].priority) {
        rs(x) = merge(rs(x), y); pushup(x); return x;
    } else {
        ls(y) = merge(x, ls(y)); pushup(y); return y;
    }
}

inline ull extract(int l, int r) {
    int x, y, z; ull ans;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    ans = tree[y].val;
    root = merge(merge(x, y), z);
    return ans;
}

template <typename T>
T read() {
    T x = 0, s = 1; char c = getchar();
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

inline void replace() {
    int pos = read<int>(), x, y, z; scanf("%s", cmd);
    split(root, pos - 1, x, y);
    split(y, 1, y, z);
    tree[y].key = tree[y].val = cmd[0] - 'a' + 1;
    root = merge(merge(x, y), z);
}

inline void insert() {
    int pos = read<int>(), x, y; scanf("%s", cmd);
    split(root, pos, x, y);
    root = merge(merge(x, create(cmd[0])), y);
}

inline bool check(int x, int y, int l) {
    return extract(x, x + l - 1) == extract(y, y + l - 1);
}

inline void query() {
    int n = tree[root].size;
    int s1 = read<int>(), s2 = read<int>(), l = 1, r = max(n - s1, n - s2) + 1, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(s1, s2, mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", ans);
}

int build() {
    scanf("%s", str + 1);
    int len = strlen(str + 1);
    int p = 0, x, last;
    for (register int i = 1; i <= len; ++i) {
        x = create(str[i]); last = 0;
        while (p && tree[stk[p]].key > tree[x].key) {
            pushup(stk[p]);
            last = stk[p];
            stk[p--] = 0;
        }
        if (p)
            rs(stk[p]) = x;
        ls(x) = last;
        stk[++p] = x;
    }
    while (p)
        pushup(stk[p--]);
    return stk[1];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    seed = time(NULL);
    power[0] = 1;
    for (int i = 1; i < maxn; ++i)
        power[i] = power[i - 1] * mod;
    root = build();
    m = read<int>();
    while (m--) {
        scanf("%s", cmd);
        switch (cmd[0]) {
        case 'Q': query(); break;
        case 'I': insert(); break;
        case 'R': replace(); break;
        }
    }
    return 0;
}