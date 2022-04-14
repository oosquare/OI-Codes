#pragma GCC optimize("Ofast")
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

constexpr int MAX_N = 5e4 + 10;

class PersistentSegmentTree {
public:
    void init(int len) {
        this->len = len;
        power[0] = 1;

        for (int i = 1; i <= len; ++i)
            power[i] = power[i - 1] * BASE;
    }

    void modify(int now, int pre, int p, int v) {
        modify(root[now], root[pre], 1, len, p, v);
    }

    unsigned query(int l, int r) {
        return query(root[r], 1, len, l, r);
    }
private:
    struct Node {
        int ls, rs;
        unsigned sum;
    };

    static constexpr unsigned BASE = 10343;
    unsigned power[MAX_N];

    Node tree[MAX_N * 50];
    int len, tot, root[MAX_N];

    void modify(int & now, int pre, int l, int r, int p, int v) {
        now = ++tot;
        tree[now] = tree[pre];

        if (l == r) {
            tree[now].sum = v;
            return;
        }

        int mid = (l + r) / 2;

        if (p <= mid)
            modify(tree[now].ls, tree[pre].ls, l, mid, p, v);
        else
            modify(tree[now].rs, tree[pre].rs, mid + 1, r, p, v);
        
        tree[now].sum =
            tree[tree[now].ls].sum
            + tree[tree[now].rs].sum * power[mid - l + 1];
    }

    unsigned query(int now, int l, int r, int ql, int qr) {
        if (!now)
            return 0;

        if (ql <= l && r <= qr)
            return tree[now].sum;
        
        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(tree[now].ls, l, mid, ql, qr);
        else if (mid < ql)
            return query(tree[now].rs, mid + 1, r, ql, qr);
        else
            return query(tree[now].ls, l, mid, ql, mid)
                + query(tree[now].rs, mid + 1, r, mid + 1, qr) * power[mid - ql + 1];
    }
};

int n;
int a[MAX_N];
int prev[MAX_N], last[MAX_N];
std::vector<int> pos[MAX_N];
PersistentSegmentTree st;
int suf[MAX_N];
long long ans;

inline int hash(int l, int r) {
    return st.query(l, r);
}

inline int labelPos(int start, int val) {
    return *std::lower_bound(pos[val].begin(), pos[val].end(), start) - start + 1;
}

int lcp(int lhs, int rhs) {
    int l = 0, r = std::min(n - lhs + 1, n - rhs + 1), res = 0;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (hash(lhs, lhs + mid - 1) == hash(rhs, rhs + mid - 1)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return res;
}

bool less(int lhs, int rhs) {
    int res = lcp(lhs, rhs);

    if (res == std::min(n - lhs + 1, n - rhs + 1))
        return lhs > rhs;
    
    return labelPos(lhs, a[lhs + res]) < labelPos(rhs, a[rhs + res]);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("waterflow.in", "r", stdin);
    freopen("waterflow.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);

    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        pos[a[i]].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        prev[i] = (last[a[i]] != 0 ? last[a[i]] : i);
        last[a[i]] = i;
    }

    st.init(n);

    for (int i = 1; i <= n; ++i)
        st.modify(i, i - 1, prev[i], i - prev[i]);
    
    std::iota(suf + 1, suf + 1 + n, 1);
    std::stable_sort(suf + 1, suf + 1 + n, less);

    ans = 1ll * n * (n + 1) / 2;

    for (int i = 2; i <= n; ++i)
        ans -= lcp(suf[i - 1], suf[i]);
    
    std::cout << ans << std::endl;

    return 0;
}
