#include <bits/stdc++.h>
using namespace std;

typedef unsigned  ull;

struct node {
    char key;
    ull val;
    int l, r, size, priority;
};

const int maxn = 1000000 + 10;
const int mod = 27;
node tree[maxn];
int root, uuid;
unsigned seed;
int m;
ull power[maxn];
char str[maxn], cmd[3];
int stk[maxn];

#define ls(x) (tree[(x)].l)
#define rs(x) (tree[(x)].r)
#define myrandom() (seed = (seed * 413273), seed)
#define create(key) \
    ((tree[++uuid] = {(char)(key - 'a' + 1), (ull)(key - 'a' + 1), 0, 0, 1, myrandom() }), uuid)

namespace IO {
    static char buf[1 << 20], *fs, *ft;
    inline char gc() {
        return fs == ft ? ((ft = (fs = buf) + fread(buf, 1, 1 << 20, stdin)), (fs == ft ? EOF : *fs++)) : *fs++;
    }

    template <typename T>
	inline T read() {
		T x = 0, f = 1; char s = gc();
		while (s < '0'|| s > '9') { if (s == '-') f = -1; s = gc(); }
		while (s >= '0'&& s<= '9') { x = (x << 1) + (x << 3) + (s ^ 48); s = gc(); }
		return x * f;
	}
}

inline void pushup(int x) {
    tree[x].size = tree[ls(x)].size + tree[rs(x)].size + 1;
    tree[x].val = tree[rs(x)].val + (ull)tree[x].key * power[tree[rs(x)].size] +
                  tree[ls(x)].val * power[tree[rs(x)].size + 1];
}

void split(int root, int sze, int &x, int &y) {
    if (!root) {
        x = y = 0;
        return;
    }
    if (tree[ls(root)].size < sze) {
        x = root;
        split(rs(x), sze - tree[ls(x)].size - 1, rs(x), y);
    } else {
        y = root;
        split(ls(y), sze, x, ls(y));
    }
    pushup(root);
}

int merge(int x, int y) {
    if (!x || !y) return x ^ y;
    if (tree[x].priority < tree[y].priority) {
        rs(x) = merge(rs(x), y);
        pushup(x);
        return x;
    } else {
        ls(y) = merge(x, ls(y));
        pushup(y);
        return y;
    }
}

inline ull extract(int l, int r) {
    int x, y, z;
    ull ans;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    ans = tree[y].val;
    root = merge(merge(x, y), z);
    return ans;
}

inline void replace() {
    int pos = IO::read<int>(), x, y, z;
    char cc = IO::gc();
    split(root, pos - 1, x, y);
    split(y, 1, y, z);
    tree[y].key = tree[y].val = cc - 'a' + 1;
    root = merge(merge(x, y), z);
    IO::gc();
}

inline void insert() {
    int pos = IO::read<int>(), x, y;
    char cc = IO::gc();
    split(root, pos, x, y);
    root = merge(merge(x, create(cc)), y);
    IO::gc();
}

#define check(x, y, l) \
    (extract((x), ((x) + (l) - 1)) == extract((y), ((y) + (l) - 1)))

inline void query() {
    int n = tree[root].size;
    int s1 = IO::read<int>(), s2 = IO::read<int>(), l = 1, r = max(n - s1, n - s2) + 1,
        ans = 0;
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
        x = create(str[i]);
        last = 0;
        while (p && tree[stk[p]].key > tree[x].key) {
            pushup(stk[p]);
            last = stk[p];
            stk[p--] = 0;
        }
        if (p) rs(stk[p]) = x;
        ls(x) = last;
        stk[++p] = x;
    }
    while (p) pushup(stk[p--]);
    return stk[1];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    seed = 233;
    power[0] = 1;
    for (int i = 1; i < maxn; ++i) power[i] = power[i - 1] * mod;
    root = build();
    m = IO::read<int>();
    while (m--) {
        char cc = IO::gc();
        switch (cc) {
            case 'Q':
                query();
                break;
            case 'I':
                insert();
                break;
            case 'R':
                replace();
                break;
        }
    }
    return 0;
}