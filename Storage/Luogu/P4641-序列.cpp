#include <bits/stdc++.h>
using namespace std;

constexpr int maxs = (1 << 16) + 10;
constexpr int maxn = 1e5 + 10;

class SegmentTree {
public:
    SegmentTree(int n = 0) : size(n) {}

    void init(int n, int arr[]) {
        size = n;
        build(1, 1, n, arr);
    }

    int query(int l, int r) {
        ++l;
        ++r;
        return query(1, l, r);
    }

private:
    struct Node {
        int left, right;
        int sum;
    };
    Node tree[maxs * 4];
    int size;

    void pushup(int x) {
        tree[x].sum = tree[x * 2].sum + tree[x * 2 + 1].sum;
    }

    void build(int x, int l, int r, int arr[]) {
        tree[x].left = l;
        tree[x].right = r;
        if (l == r) {
            tree[x].sum = arr[l - 1];
            return;
        }
        int mid = (l + r) / 2;
        build(x * 2, l, mid, arr);
        build(x * 2 + 1, mid + 1, r, arr);
        pushup(x);
    }

    int query(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].sum;
        int mid = (tree[x].left + tree[x].right) / 2, res = 0;
        if (l <= mid)
            res += query(x * 2, l, r);
        if (mid < r)
            res += query(x * 2 + 1, l, r);
        return res;
    }
};

int n, m;
long long ans;
SegmentTree tree[16];
int mod[16], l[16], r[16];
int arr[maxn], tmp[maxn];

void preprocess() {
    for (int k = 0; k < 16; ++k) {
        mod[k] = (1 << (k + 1));
        l[k] = (1 << k);
        r[k] = (1 << (k + 1)) - 1;
        memset(tmp, 0, sizeof(tmp));
        for (int i = 1; i <= n; ++i)
            ++tmp[arr[i] % mod[k]];
        tree[k].init((1 << (k + 1)), tmp);
    }
}

void add(int x) {
    for (int i = 0; i < 16; ++i) {
        l[i] = ((l[i] - x) % mod[i] + mod[i]) % mod[i];
        r[i] = ((r[i] - x) % mod[i] + mod[i]) % mod[i];
    }
}

int query(int x) {
    if (x >= 16)
        return 0;
    if (l[x] <= r[x])
        return tree[x].query(l[x], r[x]);
    else
        return tree[x].query(0, r[x]) + tree[x].query(l[x], mod[x] - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    preprocess();
    for (int i = 1; i <= m; ++i) {
        char op;
        int x;
        cin >> op >> x;
        if (op == 'A')
            add(x);
        else
            ans += query(x);
    }
    cout << ans << endl;
    return 0;
}