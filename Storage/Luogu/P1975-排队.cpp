#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 2e4 + 10;

struct Node {
    int ls, rs;
    int sum;
};

int n, m, h[maxn], mx;
int arr[maxn];
vector<int> val;
Node tree[maxn * 100];
int uuid, root[maxn];
int ans;

void add(int &x, int l, int r, int p, int v) {
    if (!x)
        x = ++uuid;

    tree[x].sum += v;

    if (l == r)
        return;

    int mid = (l + r) / 2;

    if (p <= mid)
        add(tree[x].ls, l, mid, p, v);
    else
        add(tree[x].rs, mid + 1, r, p, v);
}

vector<int> move(const vector<int> &rt, int dir) {
    vector<int> res;

    if (dir == 0) {
        for (int x : rt)
            res.push_back(tree[x].ls);
    } else {
        for (int x : rt)
            res.push_back(tree[x].rs);
    }

    return res;
}

int query(const vector<int> &add, const vector<int> &del, int l, int r, int ql, int qr) {
    if (ql > qr)
        return 0;

    if (ql <= l && r <= qr) {
        int res = 0;

        for (int x : add)
            res += tree[x].sum;

        for (int x : del)
            res -= tree[x].sum;

        return res;
    }

    int mid = (l + r) / 2, res = 0;

    if (ql <= mid)
        res += query(move(add, 0), move(del, 0), l, mid, ql, qr);

    if (mid < qr)
        res += query(move(add, 1), move(del, 1), mid + 1, r, ql, qr);

    return res;
}

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v, int d) {
    for (; p <= n; p += lowbit(p))
        add(root[p], 1, mx, v, d);
}

void modify(int p, int v) {
    add(p, arr[p], -1);
    arr[p] = v;
    add(p, v, 1);
}

int queryLess(int l, int r, int v) {
    if (l > r)
        return 0;

    vector<int> add, del;

    for (; r; r -= lowbit(r))
        add.push_back(root[r]);

    for (--l; l; l -= lowbit(l))
        del.push_back(root[l]);

    return query(add, del, 1, mx, 1, v - 1);
}

int queryGreater(int l, int r, int v) {
    if (l > r)
        return 0;

    vector<int> add, del;

    for (; r; r -= lowbit(r))
        add.push_back(root[r]);

    for (--l; l; l -= lowbit(l))
        del.push_back(root[l]);

    return query(add, del, 1, mx, v + 1, mx);
}

void discretize() {
    for (int i = 1; i <= n; ++i)
        val.push_back(h[i]);

    sort(val.begin(), val.end());
    auto it = unique(val.begin(), val.end());
    val.erase(it, val.end());
    mx = val.size();

    for (int i = 1; i <= n; ++i)
        h[i] = lower_bound(val.begin(), val.end(), h[i]) - val.begin() + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> h[i];

    discretize();

    for (int i = 1; i <= n; ++i) {
        ans += queryGreater(1, i - 1, h[i]);
        arr[i] = h[i];
        add(i, h[i], 1);
    }

    cout << ans << endl;

    cin >> m;

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;

        if (h[x] == h[y]) {
            cout << ans << endl;
            continue;
        }

        if (x > y)
            swap(x, y);

        ans -= queryLess(x + 1, y - 1, h[x]);
        ans += queryGreater(x + 1, y - 1, h[x]);
        ans -= queryGreater(x + 1, y - 1, h[y]);
        ans += queryLess(x + 1, y - 1, h[y]);

        if (h[x] < h[y])
            ++ans;
        else
            --ans;

        modify(x, h[y]);
        modify(y, h[x]);
        swap(h[x], h[y]);
        cout << ans << endl;
    }

    return 0;
}