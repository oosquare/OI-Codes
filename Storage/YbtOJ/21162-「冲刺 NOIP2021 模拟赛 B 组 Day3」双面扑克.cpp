#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxk = 1e5 + 10;
constexpr int maxq = 1e5 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Segment {
    int id, left, right;

    bool operator<(const Segment &rhs) const {
        if (right != rhs.right)
            return right < rhs.right;

        return id < rhs.id;
    }
};

int n, k, q, tot;
int fa[maxn], maxId[maxn], minId[maxn];
bool isGraph[maxn];
Segment seg[maxn + maxq];
int arr[maxn], ans[maxn];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= n; p += lowbit(p))
        arr[p] += v;
}

int query(int p) {
    int res = 0;

    for (; p; p -= lowbit(p))
        res += arr[p];

    return res;
}

int main() {
    freopen("yy.in", "r", stdin);
    freopen("yy.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> k;
    iota(fa + 1, fa + 1 + n, 1);
    fill(minId + 1, minId + 1 + n, oo);

    for (int i = 1; i <= k; ++i) {
        int x, y, fx, fy;
        cin >> x >> y;
        fx = find(x);
        fy = find(y);

        if (fx != fy)
            fa[fx] = fy;
        else
            isGraph[fx] = true;
    }

    cin >> q;

    for (int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        seg[++tot] = {i, l, r};
    }

    for (int i = 1; i <= n; ++i) {
        int fi = find(i);
        maxId[fi] = max(maxId[fi], i);
        minId[fi] = min(minId[fi], i);
    }

    for (int i = 1; i <= n; ++i) {
        if (find(i) != i || isGraph[i])
            continue;

        seg[++tot] = {0, minId[i], maxId[i]};
    }

    sort(seg + 1, seg + 1 + tot);

    for (int i = 1; i <= tot; ++i) {
        auto [id, left, right] = seg[i];

        if (!id)
            add(left, 1);
        else
            ans[id] = query(right) - query(left - 1);
    }

    for (int i = 1; i <= q; ++i)
        cout << (ans[i] ? "No" : "Yes") << endl;

    return 0;
}
