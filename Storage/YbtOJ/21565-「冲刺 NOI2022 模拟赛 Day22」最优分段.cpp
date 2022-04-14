#include <deque>
#include <iostream>

constexpr int MAX_N = 20000 + 10;

int n, k;
int a[MAX_N];
long long buf[2][MAX_N], *f = buf[0], *g = buf[1];

long double slope(int i, int j) {
    return ((long double) (g[j] - g[i])) / (j - i);
}

struct Segment {
    long long k, b;

    Segment(long long k = 0, long long b = 0x3f3f3f3f3f3f3f3f) : k(k), b(b) {}

    long long calc(int x) const { return k * x + b; }
};

class PersistentLiChaoSegmentTree {
public:
    void init(int n) {
        len = n;
        tot = 0;

        for (int i = 0; i <= n; ++i)
            root[i] = 0;
    }

    void insert(int now, int pre, Segment s) {
        root[now] = create(root[pre]);
        insert(root[now], 1, len, s);
    }

    long long query(int now, int p) { return query(root[now], 1, len, p); }

private:
    struct Node {
        int ls, rs;
        Segment seg;

        Node() : ls(0), rs(0), seg() {}
    };

    Node tree[MAX_N * 70];
    int len, tot, root[MAX_N];

    int create(int id = 0) {
        tree[++tot] = (id == 0 ? Node() : tree[id]);
        return tot;
    }

    void insert(int x, int l, int r, Segment &s) {
        if (l == r) {
            if (s.calc(l) < tree[x].seg.calc(l))
                tree[x].seg = s;

            return;
        }

        int mid = (l + r) / 2;

        if (s.k > tree[x].seg.k) {
            if (s.calc(mid) < tree[x].seg.calc(mid)) {
                insert(tree[x].rs = create(tree[x].rs), mid + 1, r, tree[x].seg);
                tree[x].seg = s;
            } else {
                insert(tree[x].ls = create(tree[x].ls), l, mid, s);
            }
        } else {
            if (s.calc(mid) < tree[x].seg.calc(mid)) {
                insert(tree[x].ls = create(tree[x].ls), l, mid, tree[x].seg);
                tree[x].seg = s;
            } else {
                insert(tree[x].rs = create(tree[x].rs), mid + 1, r, s);
            }
        }
    }

    long long query(int x, int l, int r, int p) {
        if (!x)
            return 0x3f3f3f3f3f3f3f3f;

        if (l == r)
            return tree[x].seg.calc(p);

        int mid = (l + r) / 2;

        if (p <= mid)
            return std::min(query(tree[x].ls, l, mid, p), tree[x].seg.calc(p));
        else
            return std::min(query(tree[x].rs, mid + 1, r, p), tree[x].seg.calc(p));
    }
};

class Dequeue {
public:
    std::deque<int> q;

    void merge(Dequeue &rhs) {
        int bk = (int) rhs.q.size() - 1;

        if (q.size() < rhs.q.size()) {
            for (int x : q) {
                while (0 < bk && slope(x, rhs.q[bk]) <= slope(rhs.q[bk], rhs.q[bk - 1])) {
                    --bk;
                    rhs.q.pop_back();
                }

                ++bk;
                rhs.q.push_back(x);
            }

            swap(q, rhs.q);
        } else {
            for (; bk != -1; --bk) {
                int x = rhs.q[bk];

                while (q.size() > 1 && slope(rhs.q[bk], q[0]) >= slope(q[0], q[1]))
                    q.pop_front();

                q.push_front(x);
            }
        }
    }

    int query(int k) {
        int l = 1, r = q.size() - 1;

        while (l <= r) {
            int mid = (l + r) / 2;

            if (slope(q[mid - 1], q[mid]) >= k)
                r = mid - 1;
            else
                l = mid + 1;
        }

        return q[l - 1];
    }
};

PersistentLiChaoSegmentTree tree;
Dequeue que[MAX_N];
int st[MAX_N], top;

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("seq.in", "r", stdin);
    std::freopen("seq.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    for (int i = 1, mx = 0; i <= n; ++i) {
        mx = std::max(mx, a[i]);
        f[i + 1] = 1ll * i * mx;
    }

    for (int i = 2; i <= k; ++i) {
        std::swap(f, g);
        tree.init(n);
        top = 0;

        for (int j = i; j <= n; ++j) {
            que[j].q.clear();
            que[j].q.push_back(j);

            while (top && a[st[top]] < a[j]) {
                que[j].merge(que[st[top]]);
                --top;
            }

            st[++top] = j;
            int p = que[j].query(a[j]);
            Segment s(a[j], g[p] - 1ll * (p - 1) * a[j]);
            tree.insert(j, st[top - 1], s);
            f[j + 1] = tree.query(j, j);
        }
    }

    std::cout << f[n + 1] << std::endl;
    return 0;
}
