#include <iostream>

constexpr int MAX_N = 200000 + 10;
constexpr int INF = 0x3f3f3f3f;

class SegmentTree {
public:
    void build(int n, int v) { build(1, 1, n, v); }

    void modify(int p, int v) { modify(1, p, v); }

    int query(int l, int r) { return query(1, l, r); }

private:
    struct Node {
        int left, right;
        int max;
    };

    Node tree[MAX_N * 4];

    void build(int x, int l, int r, int v) {
        tree[x].left = l;
        tree[x].right = r;
        tree[x].max = v;

        if (l == r)
            return;

        int mid = (l + r) / 2;
        build(x * 2, l, mid, v);
        build(x * 2 + 1, mid + 1, r, v);
    }

    void modify(int x, int p, int v) {
        if (tree[x].left == tree[x].right) {
            tree[x].max = v;
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;

        if (p <= mid)
            modify(x * 2, p, v);
        else
            modify(x * 2 + 1, p, v);

        tree[x].max = std::max(tree[x * 2].max, tree[x * 2 + 1].max);
    }

    int query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].max;

        int mid = (tree[x].left + tree[x].right) / 2;
        int res = -INF;

        if (l <= mid)
            res = std::max(res, query(x * 2, l, r));

        if (mid < r)
            res = std::max(res, query(x * 2 + 1, l, r));

        return res;
    }
};

int n;
int p[MAX_N];
int mx[MAX_N], val[MAX_N];
SegmentTree odd, even;
int cnt[MAX_N];
int ans[MAX_N];

bool check(int p, int v) {
    if (v < 0)
        return false;

    if (v % 2)
        return (odd.query(p, n) >= v);
    else
        return (even.query(p, n) >= v);
}

int main() {
#ifndef ONLINE_JUDGE
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
        mx[i] = std::max(mx[i - 1], p[i]);
        val[i] = (mx[i] == p[i] ? 2 : 1);
    }

    for (int i = n; i >= 1; --i)
        cnt[i] = cnt[i + 1] + (val[i] == 2);

    odd.build(n, -INF);
    even.build(n, 0);

    for (int i = n; i >= 1; --i) {
        int oddMax = odd.query(p[i], n);
        int evenMax = even.query(p[i], n);

        if (val[i] == 1) {
            odd.modify(p[i], evenMax + val[i]);
            even.modify(p[i], oddMax + val[i]);
        } else {
            odd.modify(p[i], oddMax + val[i]);
            even.modify(p[i], evenMax + val[i]);
        }
    }

    int cntX = 0, cntY = 0, maxX = 0, maxY = 0;

    for (int i = 1; i <= n; ++i) {
        odd.modify(p[i], -INF);
        even.modify(p[i], 0);
        int co = (maxX < p[i]);

        if (check(maxY, (cntX + co) - cntY + cnt[i + 1]) || check(maxX, cntY - (cntX + co) + cnt[i + 1])) {
            ans[i] = 0;

            if (maxX < p[i]) {
                ++cntX;
                maxX = p[i];
            }
        } else {
            ans[i] = 1;

            if (maxY < p[i]) {
                ++cntY;
                maxY = p[i];
            }
        }
    }

    if (cntX != cntY) {
        std::cout << -1 << std::endl;
        return 0;
    }

    for (int i = 1; i <= n; ++i)
        std::cout << ans[i];
    
    return 0;
}