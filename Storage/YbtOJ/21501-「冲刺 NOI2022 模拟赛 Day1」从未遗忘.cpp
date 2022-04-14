#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

constexpr int MAX_N = 2e5 + 10;
constexpr unsigned long long MOD = 9606826076640600000ull;

struct Node {
    int ls, rs, fa;
    bool rev;
    unsigned long long key, max, csum, sum, vsum;

    int & operator[](int x) {
        return (x == 0 ? ls : rs);
    }
};

int n, q;
unsigned long long a[MAX_N];
Node tree[MAX_N];
int stk[MAX_N];

unsigned long long add(unsigned long long x, unsigned long long y) {
    // __int128 res = (__int128) x + (__int128) y;

    // if (res >= MOD)
    //     res -= MOD;

    // return (unsigned long long) res;
    unsigned long long y1 = y >> 1;
    unsigned long long y2 = y - y1;
    x += y1;

    if (x >= MOD)
        x -= MOD;

    x += y2;

    if (x >= MOD)
        x -= MOD;

    return x;
}

unsigned long long sub(unsigned long long x, unsigned long long y) {
    __int128 res = (__int128) x - (__int128) y;

    if (res < 0)
        res += MOD;

    return (unsigned long long) res;
}

long long calc(long long x) {
    constexpr double EPS = 1e-12;
    long double y = pow(x, 0.3333333333);
    long long z = (long long) y;

    if (y - z - 0.2 < -EPS)
        return z;

    if (y - z - 0.3 < -EPS)
        return z + 1;

    if (y - z - 0.6 < -EPS)
        return z;

    return z + 1;
}

void pushup(int x) {
    tree[x].max = max(max(tree[tree[x].ls].max, tree[tree[x].rs].max), tree[x].key);
    tree[x].csum = add(add(tree[tree[x].ls].csum, tree[tree[x].rs].csum), tree[x].key);
    tree[x].sum = add(add(add(tree[tree[x].ls].sum, tree[tree[x].rs].sum), tree[x].key), tree[x].vsum);
}

void update(int x) {
    tree[x].rev = !tree[x].rev;
    swap(tree[x].ls, tree[x].rs);
}

void pushdown(int x) {
    if (tree[x].rev) {
        tree[x].rev = false;

        if (tree[x].ls)
            update(tree[x].ls);

        if (tree[x].rs)
            update(tree[x].rs);
    }
}

inline int which(int x) {
    return (tree[tree[x].fa].rs == x ? 1 : 0);
}

inline bool isRoot(int x) {
    return (tree[tree[x].fa].ls != x && tree[tree[x].fa].rs != x);
}

void rotate(int x) {
    int y = tree[x].fa, z = tree[y].fa, k = which(x), w = tree[x][k ^ 1];

    if (!isRoot(y))
        tree[z][which(y)] = x;

    tree[x][k ^ 1] = y;
    tree[y][k] = w;
    tree[x].fa = z;
    tree[y].fa = x;

    if (w)
        tree[w].fa = y;

    pushup(y);
    pushup(x);
}

void splay(int x) {
    int top = 1;
    stk[top] = x;

    for (int y = x; !isRoot(y); y = tree[y].fa)
        stk[++top] = tree[y].fa;

    while (top)
        pushdown(stk[top--]);

    for (int y; y = tree[x].fa, !isRoot(x); rotate(x))
        if (!isRoot(y))
            rotate(which(x) == which(y) ? y : x);
}

void access(int x) {
    for (int y = 0; x; y = x, x = tree[x].fa) {
        splay(x);
        tree[x].vsum = add(tree[x].vsum, tree[tree[x].rs].sum);
        tree[x].rs = y;
        tree[x].vsum = sub(tree[x].vsum, tree[y].sum);
        pushup(x);
    }
}

void makeRoot(int x) {
    access(x);
    splay(x);
    update(x);
}

int findRoot(int x) {
    access(x);
    splay(x);
    pushdown(x);

    while (tree[x].ls) {
        x = tree[x].ls;
        pushdown(x);
    }

    splay(x);
    return x;
}

void init(int x, unsigned long long key) {
    tree[x].key = tree[x].csum = tree[x].sum = tree[x].max = key;
}

bool connected(int x, int y) {
    makeRoot(x);
    return findRoot(y) == x;
}

void link(int x, int y) {
    makeRoot(x);

    if (findRoot(y) != x) {
        makeRoot(y);
        tree[x].fa = y;
        tree[y].vsum = add(tree[y].vsum, tree[x].sum);
        tree[y].sum = add(tree[y].sum, tree[x].sum);
    }
}

void cut(int x, int y) {
    makeRoot(x);

    if (findRoot(y) == x && tree[y].fa == x && !tree[y].ls) {
        tree[x].rs = tree[y].fa = 0;
        pushup(x);
    }
}

int split(int x, int y) {
    makeRoot(x);
    access(y);
    splay(y);
    return y;
}

void apply(int x) {
    if (!x || tree[x].max <= 2)
        return;

    pushdown(x);
    tree[x].key = calc(tree[x].key);
    apply(tree[x].ls);
    apply(tree[x].rs);
    pushup(x);
}

inline void modify(int x, int y) {
    if (connected(x, y))
        apply(split(x, y));
}

inline unsigned long long query(int x) {
    makeRoot(x);
    splay(x);
    return tree[x].sum;
}

inline unsigned long long query(int x, int y) {
    if (!connected(x, y))
        return add(query(x), query(y));

    return tree[split(x, y)].csum;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("unforgettable.in", "r", stdin);
    freopen("unforgettable.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        init(i, a[i]);
    }

    cin >> q;

    for (int i = 1; i <= q; ++i) {
        int op1, op2, x, y;
        cin >> op1 >> op2 >> x;

        if (op1 == 1) {
            cin >> y;

            if (op2 == 1) {
                modify(x, y);
            } else if (op2 == 2) {
                cut(x, y);
            } else {
                link(x, y);
            }
        } else {
            if (op2 == 1) {
                cin >> y;
                cout << query(x, y) << endl;
            } else {
                cout << query(x) << endl;
            }
        }
    }

    return 0;
}
