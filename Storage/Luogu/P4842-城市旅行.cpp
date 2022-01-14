#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 5e4 + 10;

class LinkCutTree {
public:
    void init(int x, int key) {
        tree[x].key = tree[x].sum = tree[x].ans = tree[x].lans = tree[x].rans = key;
        tree[x].size = tree[x].cnt = tree[x].lcnt = tree[x].rcnt = 1;
    }

    void link(int x, int y) {
        makeRoot(x);

        if (findRoot(y) != x)
            tree[x].fa = y;
    }

    void cut(int x, int y) {
        makeRoot(x);

        if (findRoot(y) == x && tree[y].fa == x && !tree[y].ls) {
            tree[x].rs = tree[y].fa = 0;
            pushup(x);
        }
    }

    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }

    void add(int x, int y, int v) {
        updateAdd(split(x, y), v);
    }

    pair<long long, long long> query(int x, int y) {
        y = split(x, y);
        return {tree[y].ans, 1ll * tree[y].size * (tree[y].size + 1) / 2};
    }

private:
    struct Node {
        int ls, rs, fa, size;
        bool rev;
        long long key, sum, add, ans, lans, rans, cnt, lcnt, rcnt;

        int &operator[](int x) {
            return (x == 0 ? ls : rs);
        }
    };

    Node tree[maxn];
    int st[maxn];

    void pushup(int x) {
        const int ls = tree[x].ls, rs = tree[x].rs;
        tree[x].size = tree[ls].size + 1 + tree[rs].size;
        tree[x].sum = tree[ls].sum + tree[x].key + tree[rs].sum;
        tree[x].ans =
            tree[ls].ans + tree[ls].rans * (tree[rs].size + 1) +
            tree[rs].ans + tree[rs].lans * (tree[ls].size + 1) +
            tree[x].key * (tree[ls].size + 1) * (tree[rs].size + 1);
        tree[x].lans =
            tree[ls].lans +
            (tree[ls].sum + tree[x].key) * (tree[rs].size + 1)  + tree[rs].lans;
        tree[x].rans =
            tree[rs].rans +
            (tree[rs].sum + tree[x].key) * (tree[ls].size + 1) + tree[ls].rans;
        tree[x].cnt =
            tree[ls].cnt + tree[ls].rcnt * (tree[rs].size + 1) +
            tree[rs].cnt + tree[rs].lcnt * (tree[ls].size + 1) +
            (tree[ls].size + 1) * (tree[rs].size + 1);
        tree[x].lcnt =
            tree[ls].lcnt +
            (tree[ls].size + 1) * (tree[rs].size + 1) + tree[rs].lcnt;
        tree[x].rcnt =
            tree[rs].rcnt +
            (tree[rs].size + 1) * (tree[ls].size + 1) + tree[ls].rcnt;
    }

    void updateReverse(int x) {
        tree[x].rev ^= 1;
        swap(tree[x].ls, tree[x].rs);
        swap(tree[x].lans, tree[x].rans);
        swap(tree[x].lcnt, tree[x].rcnt);
    }

    void updateAdd(int x, int v) {
        tree[x].key += v;
        tree[x].sum += 1ll * tree[x].size * v;
        tree[x].add += v;
        tree[x].ans += tree[x].cnt * v;
        tree[x].lans += tree[x].lcnt * v;
        tree[x].rans += tree[x].rcnt * v;
    }

    void pushdown(int x) {
        if (tree[x].rev) {
            if (tree[x].ls)
                updateReverse(tree[x].ls);

            if (tree[x].rs)
                updateReverse(tree[x].rs);

            tree[x].rev = false;
        }

        if (tree[x].add) {
            if (tree[x].ls)
                updateAdd(tree[x].ls, tree[x].add);

            if (tree[x].rs)
                updateAdd(tree[x].rs, tree[x].add);

            tree[x].add = 0;
        }
    }

    int which(int x) {
        return tree[tree[x].fa].rs == x;
    }

    bool isRoot(int x) {
        return tree[tree[x].fa].ls != x && tree[tree[x].fa].rs != x;
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
        int top = 0;
        st[++top] = x;

        for (int y = x; !isRoot(y); y = tree[y].fa)
            st[++top] = tree[y].fa;

        while (top)
            pushdown(st[top--]);

        for (int y; y = tree[x].fa, !isRoot(x); rotate(x))
            if (!isRoot(y))
                rotate(which(x) == which(y) ? y : x);
    }

    void access(int x) {
        for (int y = 0; x; y = x, x = tree[x].fa) {
            splay(x);
            tree[x].rs = y;
            pushup(x);
        }
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        updateReverse(x);
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

    int split(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        return y;
    }
};

long long gcd(long long x, long long y) {
    return (y == 0 ? x : gcd(y, x % y));
}

int n, m;
LinkCutTree lct;



int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        lct.init(i, a);
    }

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        lct.link(x, y);
    }

    for (int i = 1; i <= m; ++i) {
        int op, x, y, d;
        cin >> op >> x >> y;

        if (op == 1) {
            lct.cut(x, y);
        } else if (op == 2) {
            lct.link(x, y);
        } else if (op == 3) {
            cin >> d;

            if (lct.connected(x, y))
                lct.add(x, y, d);
        } else {
            if (lct.connected(x, y)) {
                auto [sum, cnt] = lct.query(x, y);
                auto d = gcd(sum, cnt);
                cout << sum / d << "/" << cnt / d << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}
