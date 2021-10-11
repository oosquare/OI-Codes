#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 30000 + 10;
constexpr int maxm = 5000 + 10;

struct Section {
    int a, b, c;

    bool operator<(const Section &rhs) const {
        return b < rhs.b;
    }
};

int n, m;
Section sec[maxm];
int tree[maxn];

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= n; p += lowbit(p))
        tree[p] += v;
}

int query(int p) {
    int res = 0;
    for (; p; p -= lowbit(p))
        res += tree[p];
    return res;
}

inline int query(int l, int r) {
    return query(r) - query(l - 1);
}

int find(int p, int v) {
    int l = 1, r = p, res = p + 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (query(mid, p) == v * (p - mid + 1)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return res - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
        cin >> sec[i].a >> sec[i].b >> sec[i].c;
    sort(sec + 1, sec + m + 1);
    for (int i = 1; i <= m; ++i) {
        auto [a, b, c] = sec[i];
        int now;
        while (query(a, b) < c) {
            now = c - query(a, b);
            int r = find(b, 1), l = find(r, 0);
            ++l;
            if (r - l + 1 > now)
                l = r - now + 1;
            for (int j = l; j <= r; ++j)
                add(j, 1);
        }
    }
    cout << query(n) << endl;
    return 0;
}