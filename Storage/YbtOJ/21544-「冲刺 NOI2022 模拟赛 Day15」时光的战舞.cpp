#include <iostream>

constexpr int MAX_N = 300000 + 10;

int n, q, type;
char str[MAX_N];
int ans;

class SuffixAutomaton {
public:
    struct Node {
        int next[2], link, len;

        Node() : next{0, 0}, link{0}, len{0} {}

        int &operator[](int x) {
            return next[x];
        }
    };

    SuffixAutomaton() : total{1}, last{1} {}

    Node &operator[](int x) {
        return nodes[x];
    }

    int add(int c) {
        int x = create(), p = last;
        nodes[x].len = nodes[p].len + 1;
        last = x;

        for (; p && !nodes[p][c]; p = nodes[p].link)
            nodes[p][c] = x;

        if (!p) {
            nodes[x].link = 1;
        } else {
            int q = nodes[p][c];

            if (nodes[q].len == nodes[p].len + 1) {
                nodes[x].link = q;
            } else {
                int nq = create(q);
                nodes[nq].len = nodes[p].len + 1;
                nodes[x].link = nodes[q].link = nq;

                for (; p && nodes[p][c] == q; p = nodes[p].link)
                    nodes[p][c] = nq;
            }
        }

        return x;
    }

    int size() const {
        return total;
    }
private:
    Node nodes[MAX_N];
    int total, last;

    int create(int id = -1) {
        nodes[++total] = (id == -1 ? Node() : nodes[id]);
        return total;
    }
} sam;

int id[MAX_N];

class PresistentSegmentTree {
public:
    void init(int len) { length = len; }

    void copy(int now, int pre) {
        root[now] = root[pre];
    }

    void assign(int now, int p, int v) {
        assign(root[now], root[now], 1, length, p, v);
    }

    int query(int l, int r) {
        return query(root[r], 1, length, l, n);
    }
private:
    struct Node {
        int ls, rs;
        int val;
    };

    Node tree[MAX_N * 80];
    int root[MAX_N], total, length;

    void assign(int &now, int pre, int l, int r, int p, int v) {
        now = ++total;
        tree[now] = tree[pre];
        tree[now].val = std::max(tree[now].val, v);

        if (l == r)
            return;

        int mid = (l + r) / 2;

        if (p <= mid)
            assign(tree[now].ls, tree[pre].ls, l, mid, p, v);
        else
            assign(tree[now].rs, tree[pre].rs, mid + 1, r, p, v);
    }

    int query(int now, int l, int r, int ql, int qr) {
        if (!now)
            return 0;

        if (ql <= l && r <= qr)
            return tree[now].val;
        
        int mid = (l + r) / 2, res = 0;

        if (ql <= mid)
            res = std::max(res, query(tree[now].ls, l, mid, ql, qr));

        if (mid < qr)
            res = std::max(res, query(tree[now].rs, mid + 1, r, ql, qr));

        return res;
    }
} seg;

class LinkCutTree {
public:
    void link(int fa, int x) {
        tree[x].fa = fa;
    }

    void access(int x0, int rt) {
        int last = 0;

        for (int x = x0, y = 0; x; y = x, x = tree[x].fa) {
            splay(x);
            last = x;

            if (tree[x].key)
                seg.assign(rt, tree[x].key, sam[x].len);

            tree[x].rs = y;
        }

        update(last, rt);
    }
private:
    struct Node {
        int ls, rs, fa, key, assign;

        int &operator[](int x) {
            return (x == 0 ? ls : rs);
        }
    };

    Node tree[MAX_N];
    int stk[MAX_N];

    void update(int x, int v) {
        if (!x)
            return;

        tree[x].key = v;
        tree[x].assign = v;
    }

    void pushdown(int x) {
        if (!x || tree[x].assign == 0)
            return;

        update(tree[x].ls, tree[x].assign);
        update(tree[x].rs, tree[x].assign);
        tree[x].assign = 0;
    }

    bool isRoot(int x) {
        return (tree[tree[x].fa].ls != x && tree[tree[x].fa].rs != x);
    }

    int which(int x) {
        return (tree[tree[x].fa].rs == x ? 1 : 0);
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
} lct;

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("dance.in", "r", stdin);
    std::freopen("dance.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin >> n >> q >> type;
    std::cin >> (str + 1);
    
    for (int i = 1; i <= n; ++i)
        id[i] = sam.add((int) (str[i] - '0'));

    for (int i = 2; i <= sam.size(); ++i)
        lct.link(sam[i].link, i);
    
    seg.init(n);

    for (int i = 1; i <= n; ++i) {
        seg.copy(i, i - 1);
        lct.access(id[i], i);
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l ^= ans * type;
        r ^= ans * type;

        if (l > r)
            std::swap(l, r);

        ans = seg.query(l, r);
        std::cout << ans << std::endl;
    }

    return 0;
}
