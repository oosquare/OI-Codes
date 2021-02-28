#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

namespace IO {

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
    T x = 0;
    char c = mygetchar();
    while (c < '0' || '9' < c)
        c = mygetchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + c - '0';
        c = mygetchar();
    }
    return x;
}

} // namespace IO

struct querys {
    int type, l, r, x;
    ll a;
};

constexpr int maxn = 6e6 + 10;
constexpr int oo = 0x3f3f3f3f;

querys q[maxn], q1[maxn], q2[maxn];
ll tree[maxn];
vector<int> o[maxn];
int n, m, k, ans[maxn];

int lowbit(int x) { return x & (-x); }

void modify(int p, ll v) {
    for (; p <= m; p += lowbit(p))
        tree[p] += v;
}

ll query(int p) {
    ll res = 0;
    for (; p; p -= lowbit(p))
        res += tree[p];
    return res;
}

void BinarySolve(int ql, int qr, int l, int r) {
    if (ql > qr)
        return;
    if (l == r) {
        for (int i = ql; i <= qr; ++i)
            if (q[i].type == 2)
                ans[q[i].x] = l;
        return;
    }
    int mid = (l + r) / 2, len1 = 0, len2 = 0, len = ql - 1;
    for (int i = ql; i <= qr; ++i) {
        if (q[i].type == 1) {
            if (q[i].x <= mid) {
                if (q[i].l <= q[i].r)
                    modify(q[i].l, q[i].a), modify(q[i].r + 1, -q[i].a);
                else
                    modify(q[i].l, q[i].a), modify(1, q[i].a), modify(q[i].r + 1, -q[i].a);
                q1[++len1] = q[i];
            } else {
                q2[++len2] = q[i];
            }
        }
    }
    for (int i = ql; i <= qr; ++i) {
        if (q[i].type == 2) {
            ll t = 0;
            for (int j : o[q[i].x])
                t += query(j);
            if (q[i].a <= t) {
                q1[++len1] = q[i];
            } else {
                q2[++len2] = q[i];
                q2[len2].a -= t;
            }
        }
    }
    for (int i = 1; i <= len1; ++i) {
        if (q1[i].type == 1) {
            if (q1[i].l <= q1[i].r)
                modify(q1[i].l, -q1[i].a), modify(q1[i].r + 1, q1[i].a);
            else
                modify(q1[i].l, -q1[i].a), modify(1, -q1[i].a), modify(q1[i].r + 1, q1[i].a);
        }
    }
    for (int i = 1; i <= len1; ++i)
        q[++len] = q1[i];
    for (int i = 1; i <= len2; ++i)
        q[++len] = q2[i];
    BinarySolve(ql, ql + len1 - 1, l, mid);
    BinarySolve(ql + len1, qr, mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), m = read();
    for (int i = 1; i <= m; ++i)
        o[read()].push_back(i);
    for (int i = 1; i <= n; ++i)
        q[i] = {2, 0, 0, i, read<ll>()};
    k = read();
    for (int i = 1; i <= k; ++i) {
        int l = read(), r = read();
        ll a = read<ll>();
        q[i + n] = {1, l, r, i, a};
    }
    q[n + k + 1] = {1, 1, m, k + 1, oo};
    BinarySolve(1, n + k + 1, 1, k + 1);
    for (int i = 1; i <= n; ++i)
        if (1 <= ans[i] && ans[i] <= k)
            printf("%d\n", ans[i]);
        else
            printf("NIE\n");
    return 0;
}