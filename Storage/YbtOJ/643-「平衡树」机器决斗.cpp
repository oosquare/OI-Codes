#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5 + 10;

typedef long long ll;

int ld[maxn], ra[maxn];
ll s[maxn];
ll ans, res;
int n, atk;
struct qs {
    int a, p;
} q[maxn];
bool operator<(qs x, qs y) { return x.p * y.a < x.a * y.p; }
inline void ck(ll &x, ll y) {
    if (x < y)
        x = y;
}
struct treap {
    struct node {
        ll x, y, lx, ly;
        node *p, *s[2];
        node() { p = s[0] = s[1] = 0; }
        bool getlr() { return p->s[1] == this; }
        node *link(int w, node *p) {
            s[w] = p;
            if (p)
                p->p = this;
            return this;
        }
    } * root;
    void rot(node *p) {
        node *q = p->p->p;
        p->getlr() ? p->link(0, p->p->link(1, p->s[0]))
                   : p->link(1, p->p->link(0, p->s[1]));
        if (q)
            q->link(q->s[1] == p->p, p);
        else
            (root = p)->p = 0;
    }
    void gget(node *p) {
        while (p->p && p->p->p)
            p->getlr() == p->p->getlr() ? (rot(p->p), rot(p))
                                        : (rot(p), rot(p));
        if (p->p)
            rot(p);
    }
    void gget(node *p, node *tar) {
        while (p->p != tar && p->p->p != tar)
            p->getlr() == p->p->getlr() ? (rot(p->p), rot(p))
                                        : (rot(p), rot(p));
        if (p->p != tar)
            rot(p);
    }
    void reset() {
        root = new node;
        root->x = 0;
        root->y = 0;
        root->lx = 0;
        root->ly = -1;
    }
    node *prev(node *p) {
        if (!p)
            return 0;
        gget(p);
        if (!p->s[0])
            return 0;
        node *q = p->s[0];
        for (; q->s[1]; q = q->s[1])
            ;
        gget(q);
        return q;
    }
    node *succ(node *p) {
        if (!p)
            return 0;
        gget(p);
        if (!p->s[1])
            return 0;
        node *q = p->s[1];
        for (; q->s[0]; q = q->s[0])
            ;
        gget(q);
        return q;
    }
    void insert(ll x, ll y) {
        node *p = root, *p1, *p2;
        while (p) {
            p1 = p;
            p = p->s[p->x < x];
        }
        p = new node;
        p->x = x;
        p->y = y;
        p1->link(p1->x < x, p);
        gget(p);
        if ((p1 = prev(p)) && (p2 = succ(p))) {
            if ((p2->x - p->x) * (p1->y - p->y) >=
                (p2->y - p->y) * (p1->x - p->x)) {
                gget(p1);
                gget(p2, p1);
                p2->s[0] = 0;
                return;
            }
        }
        while (p2 = prev(p1 = prev(p))) {
            if ((p->x - p1->x) * (p2->y - p1->y) >=
                (p->y - p1->y) * (p2->x - p1->x)) {
                gget(p2);
                gget(p, p2);
                p->s[0] = 0;
            } else
                break;
        }
        if (p1 = prev(p))
            p->lx = p1->x, p->ly = p1->y;
        while (p2 = succ(p1 = succ(p))) {
            if ((p->x - p1->x) * (p2->y - p1->y) >=
                (p->y - p1->y) * (p2->x - p1->x)) {
                gget(p2);
                gget(p, p2);
                p->s[0] = 0;
            } else
                break;
        }
        if (p1 = succ(p))
            p1->lx = p->x, p1->ly = p->y;
    }
    ll get(int k) {
        ll res = 0;
        node *p = root;
        while (p) {
            ck(res, p->y - k * p->x);
            p = p->s[p->y - k * p->x >= p->ly - k * p->lx];
        }
        return res;
    }
} tool1;

int main() {
    freopen("fittest.in", "r", stdin);
    freopen("fittest.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> atk;
    for (int i = 1; i <= n; i++) {
        cin >> q[i].a >> q[i].p;
        q[i].p = (q[i].p + atk - 1) / atk;
    }
    sort(q + 1, q + n + 1);
    ld[0] = 0;
    for (int i = 1; i <= n; i++)
        ld[i] = ld[i - 1] + q[i].p;
    ra[n + 1] = 0;
    for (int i = n; i; i--)
        ra[i] = ra[i + 1] + q[i].a;
    for (int i = 1; i <= n; i++)
        s[i] = (ld[i] - 1) * (ll)q[i].a + ra[i + 1] * (ll)q[i].p;
    ans = 0;
    for (int i = 1; i <= n; i++)
        ans += (ld[i] - 1) * (ll)q[i].a;
    res = 0;
    tool1.reset();
    for (int i = n - 1; i; i--) {
        tool1.insert(q[i + 1].a, s[i + 1]);
        ck(res, s[i] + tool1.get(q[i].p));
    }
    cout << ans - res << endl;
    return 0;
}
