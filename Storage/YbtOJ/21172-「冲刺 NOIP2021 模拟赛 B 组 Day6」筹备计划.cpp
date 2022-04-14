#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

#define int long long

namespace IO {

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B) ? EOF : *A++;
}

template <typename T = int>
T read() {
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

template <typename T = int>
void writeln(T x) {
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
    while (top) putchar(stk[top--] + '0');
    putchar('\n');
}

template <typename T = int>
void writesp(T x) {
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
    while (top) putchar(stk[top--] + '0');
    putchar(' ');
}

template <typename T = int>
void write(T x, char blank[]) {
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
    while (top) putchar(stk[top--] + '0');
    putchar('\n');
    for (int i = 0; blank[i] != '\0'; ++i) putchar(blank[i]);
}

}  // namespace IO

using ll = long long;

constexpr int maxn = 2e5 + 10;

int n, q;
ll a[maxn], tmp[maxn], all;

struct {
    int t, x, y;
} ops[maxn];

namespace Solver1 {

int ans[maxn];

struct SegmentTree {
    struct Node {
        ll sum;
        int assign = -1;
    };

    Node tree[maxn * 4];

    void pushup(int x) { tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum; }

    void update(int x, int l, int r, int v) {
        tree[x].assign = v;
        tree[x].sum = v * (r - l + 1);
    }

    void pushdown(int x, int l, int r) {
        if (tree[x].assign == -1)
            return;

        int mid = (l + r) / 2;
        update(x * 2, l, mid, tree[x].assign);
        update(x * 2 + 1, mid + 1, r, tree[x].assign);
        tree[x].assign = -1;
    }

    void build(int x, int l, int r, ll a[]) {
        if (l == r) {
            tree[x].sum = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, a);
        build(x * 2 + 1, mid + 1, r, a);
        pushup(x);
    }

    void assign(int x, int l, int r, int ml, int mr, int v) {
        if (ml <= l && r <= mr) {
            // cout << ml << ' ' << mr << ' ' << v << endl;
            update(x, l, r, v);
            return;
        }

        int mid = (l + r) / 2;
        pushdown(x, l, r);

        if (ml <= mid)
            assign(x * 2, l, mid, ml, mr, v);

        if (mid < mr)
            assign(x * 2 + 1, mid + 1, r, ml, mr, v);

        pushup(x);
    }

    void add(int x, int l, int r, int p, ll v) {
        if (l == r) {
            tree[x].sum += v;
            return;
        }

        int mid = (l + r) / 2;

        if (p <= mid)
            add(x * 2, l, mid, p, v);
        else
            add(x * 2 + 1, mid + 1, r, p, v);

        pushup(x);
    }

    ll query(int x, int l, int r, int ql, int qr) {
        if (ql > qr)
            return 0;
        // cout << "Query" << l << ' ' << r << ' ' << ql << ' ' << qr << endl;
        if (ql <= l && r <= qr) {
            // cout << "CNM" << ' ' << tree[x].sum << endl;
            return tree[x].sum;
        }

        int mid = (l + r) / 2;
        ll res = 0;
        pushdown(x, l, r);

        if (ql <= mid)
            res += query(x * 2, l, mid, ql, qr);

        if (mid < qr)
            res += query(x * 2 + 1, mid + 1, r, ql, qr);

        return res;
    }

    int find(int x, int l, int r, ll k) {
        if (l == r)
            return l;

        int mid = (l + r) / 2;

        if (tree[x * 2].sum >= k)
            return find(x * 2, l, mid, k);
        else
            return find(x * 2 + 1, mid + 1, r, k - tree[x * 2].sum);
    }

    int moveLeft(int x, int l, int r) {
        if (l == r)
            return tree[x].sum == 0 ? l : -1;

        int mid = (l + r) / 2;
        pushdown(x, l, r);

        if (tree[x * 2 + 1].sum < r - mid)
            return moveLeft(x * 2 + 1, mid + 1, r);
        else
            return moveLeft(x * 2, l, mid);
    }

    int moveRight(int x, int l, int r) {
        if (l == r)
            return tree[x].sum == 0 ? l : -1;

        int mid = (l + r) / 2;
        pushdown(x, l, r);

        if (tree[x * 2].sum < mid - l + 1)
            return moveRight(x * 2, l, mid);
        else
            return moveRight(x * 2 + 1, mid + 1, r);
    }

    int findLeft(int x, int l, int r, int fl, int fr) {
        if (fl <= l && r <= fr)
            return moveLeft(x, l, r);

        int mid = (l + r) / 2, res = -1;
        pushdown(x, l, r);

        if (mid < fr)
            res = findLeft(x * 2 + 1, mid + 1, r, fl, fr);

        if (fl <= mid && res == -1)
            res = findLeft(x * 2, l, mid, fl, fr);

        return res;
    }

    int findRight(int x, int l, int r, int fl, int fr) {
        if (fl <= l && r <= fr)
            return moveRight(x, l, r);

        int mid = (l + r) / 2, res = -1;
        pushdown(x, l, r);

        if (fl <= mid)
            res = findRight(x * 2, l, mid, fl, fr);

        if (mid < fr && res == -1)
            res = findRight(x * 2 + 1, mid + 1, r, fl, fr);

        return res;
    }
};

SegmentTree pos, cnt, pre, suf;

inline void add(int x, int y) {
    all += y;
    cnt.add(1, 1, n, x, y);
    pre.add(1, 1, n, x, 1ll * x * y);
    suf.add(1, 1, n, x, 1ll * (n - x + 1) * y);
}

inline void assign(int l, int r, int v) { pos.assign(1, 1, n, l, r, v); }

inline ll calc(int t) {
    ll ans = 0;
    ans += pre.query(1, 1, n, 1, n) - pre.query(1, 1, n, 1, t - 1) - cnt.query(1, 1, n, t, n) * (t - 1);
    ans += suf.query(1, 1, n, 1, n) - suf.query(1, 1, n, t + 1, n) - cnt.query(1, 1, n, 1, t) * (n - t + 1);
    return ans;
}

inline int solve() {
    // int p = cnt.find(1, 1, n, (all + 1) / 2);
    // int pl = pos.findLeft(1, 1, n, 1, p);
    // int pr = pos.findRight(1, 1, n, p, n);
    // ll resl = pl == -1 ? 0x3f3f3f3f3f3f3f3f : calc(pl);
    // ll resr = pr == -1 ? 0x3f3f3f3f3f3f3f3f : calc(pr);

    // if (resl <= resr)
    //     return pl;
    // else
    //     return pr;

    if (all % 2) {
        int p = cnt.find(1, 1, n, (all + 1) / 2);

        if (pos.query(1, 1, n, p, p) == 0) {
            return p;
        } else {
            int pl = pos.findLeft(1, 1, n, 1, p);
            int pr = pos.findRight(1, 1, n, p, n);
            ll resl = pl == -1 ? 0x3f3f3f3f3f3f3f3f : calc(pl);
            ll resr = pr == -1 ? 0x3f3f3f3f3f3f3f3f : calc(pr);

            if (resl <= resr)
                return pl;
            else
                return pr;
        }
    } else {
        int p1 = cnt.find(1, 1, n, all / 2);
        int p2 = cnt.find(1, 1, n, all / 2 + 1);

        int l = p1, r = p2, pp = -1;
        // cout << p1 << " " << p2 << endl;

        while (l <= r) {
            int mid = (l + r) / 2;
            // cout << p1 << ' ' << mid << ' ' << pos.query(1, 1, n, p1, mid) << "caonimaknh" << endl;
            if (pos.query(1, 1, n, p1, mid) < mid - p1 + 1) {
                pp = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        if (pp != -1)
            return pp;

        int pl = pos.findLeft(1, 1, n, 1, p1);
        int pr = pos.findRight(1, 1, n, p2, n);
        ll resl = pl == -1 ? 0x3f3f3f3f3f3f3f3f : calc(pl);
        ll resr = pr == -1 ? 0x3f3f3f3f3f3f3f3f : calc(pr);

        if (resl <= resr)
            return pl;
        else
            return pr;
    }
}

void main() {
    cnt.build(1, 1, n, a);

    for (int i = 1; i <= n; ++i) tmp[i] = a[i] * i;

    pre.build(1, 1, n, tmp);

    for (int i = 1; i <= n; ++i) tmp[i] = a[i] * (n - i + 1);

    suf.build(1, 1, n, tmp);

    for (int i = 1; i <= q; ++i) {
        // cout << i << " : ";
        auto [op, x, y] = ops[i];

        if (op == 1)
            add(x, y);
        else if (op == 2)
            add(x, -y);
        else if (op == 3)
            assign(x, y, 0);
        else {
            // cout << "FUCKKNH" << endl;
            assign(x, y, 1);
        }
        // cout << endl;
        ans[i] = solve();
    }
}

} // Solver1

namespace Solver2 {

using namespace std;

const int N = 2e5 + 5;
int opt, x, y;
int ans[maxn];

#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
struct SEG {
    int s[N << 2], c[N << 2], lay[N << 2];
    inline void update(int p) {
        c[p] = c[ls(p)] + c[rs(p)], s[p] = s[ls(p)] + s[rs(p)];
    }
    inline void pushdown(int p, int l, int r) {
        if (lay[p]) {
            lay[ls(p)] = lay[rs(p)] = lay[p]--;
            int mid = (l + r) >> 1;
            c[ls(p)] = (mid - l + 1) * lay[p];
            c[rs(p)] = (r - mid) * lay[p];
            lay[p] = 0;
        }
    }
    inline void Ins(int p, int l, int r, int L, int R, int k) {
        if (L <= l && R >= r) {
            lay[p] = k + 1;
            c[p] = (r - l + 1) * k;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(p, l, r);
        if (L <= mid) Ins(ls(p), l, mid, L, R, k);
        if (R > mid) Ins(rs(p), mid + 1, r, L, R, k);
        update(p);
    }
    inline void Ins(int p, int l, int r, int delta, int k) {
        if (l == r) {
            s[p] += k;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(p, l, r);
        if (delta <= mid)
            Ins(ls(p), l, mid, delta, k);
        else
            Ins(rs(p), mid + 1, r, delta, k);
        update(p);
    }
    inline int Que1(int p, int l, int r, int k) {
        if (l == r) return c[p];
        int mid = (l + r) >> 1;
        pushdown(p, l, r);
        if (s[ls(p)] >= k)
            return Que1(ls(p), l, mid, k);
        else
            return Que1(rs(p), mid + 1, r, k - s[ls(p)]) + c[ls(p)];
    }
    inline int Que2(int p, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        pushdown(p, l, r);
        if (c[ls(p)] >= k)
            return Que2(ls(p), l, mid, k);
        else
            return Que2(rs(p), mid + 1, r, k - c[ls(p)]);
    }
} T;

struct BIT {
    int s1[N], s2[N];
    inline int lowbit(int x) { return x & (-x); }
    inline void Add(int x, int k) {
        for (int i = x; i <= n; i += lowbit(i)) {
            s1[i] += k * (n - x + 1), s2[i] += k;
        }
    }
    inline int Ask(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) {
            res += s1[i] - s2[i] * (n - x + 1);
        }
        return res;
    }
} T1, T2;

inline void Add(int x, int k) { T1.Add(x, k), T2.Add(n - x + 1, k); }
inline int Ask(int x) { return T1.Ask(x) + T2.Ask(n - x + 1); }

void main() {
    for (int i = 1; i <= n; ++i) {
        T.Ins(1, 0, n + 1, i, a[i]), Add(i, a[i]);
    }
    T.Ins(1, 0, n + 1, 1, n, 1);
    for (int i = 1; i <= q; ++i) {
        opt = ops[i].t, x = ops[i].x, y = ops[i].y;
        if (opt == 1)
            T.Ins(1, 0, n + 1, x, y), Add(x, y);
        else if (opt == 2)
            T.Ins(1, 0, n + 1, x, -y), Add(x, -y);
        else if (opt == 3)
            T.Ins(1, 0, n + 1, x, y, 1);
        else if (opt == 4)
            T.Ins(1, 0, n + 1, x, y, 0);

        int s = T.Que1(1, 0, n + 1, (T.s[1] + 1) >> 1);
        int l = T.Que2(1, 0, n + 1, s), r = T.Que2(1, 0, n + 1, s + 1);
        if (!l && r == n + 1)
            ans[i] = -1;
        else if (!l)
            ans[i] = r;
        else if (r == n + 1)
            ans[i] = l;
        else
            ans[i] = (Ask(l) <= Ask(r) ? l : r);
    }
}

} // namespace Solver2

signed main() {
    freopen("position.in", "r", stdin);
    freopen("position.out", "w", stdout);
    using namespace IO;
    n = read(), q = read();

    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        all += a[i];
    }

    for (int i = 1; i <= q; ++i) {
        // cout << i << " : ";
        ops[i].t = read(), ops[i].x = read(), ops[i].y = read();
    }

    Solver1::main();
    Solver2::main();

    bool same = true;

    for (int i = 1; i <= q; ++i) {
        if (Solver1::ans[i] != Solver2::ans[i]) {
            same = false;
            break;
        }
    }

    if (same) {
        for (int i = 1; i <= q; ++i) {
            writeln(Solver1::ans[i]);
        }
    } else {
        for (int i = 1; i <= q; ++i) {
            writeln(Solver2::ans[i]);
        }
    }

    return 0;
}
