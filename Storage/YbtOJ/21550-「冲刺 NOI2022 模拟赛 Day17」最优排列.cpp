#include <iostream>
#include <set>
#include <vector>

constexpr int N = 200000 + 5;
constexpr int INFINITY = 0x3f3f3f3f;

struct Range {
    int l, r;
};

struct Node {
    int val, pos, add;
};

int n;
int a[N];
int t[N], pos[N];
Range ranges[N];
Node tree[N * 2];
std::multiset<int> now;
std::set<int> subtree[N * 2];
std::vector<int> buc[N];

void pushup(int x) {
    tree[x].val = tree[x * 2].val;
    tree[x].pos = tree[x * 2].pos;

    if (tree[x * 2 + 1].val < tree[x].val) {
        tree[x].val = tree[x * 2 + 1].val;
        tree[x].pos = tree[x * 2 + 1].pos;
    }
}

void update(int x, int v) {
    tree[x].val += v;
    tree[x].add += v;
}

void pushdown(int x) {
    if (tree[x].add == 0)
        return;

    update(x * 2, tree[x].add);
    update(x * 2 + 1, tree[x].add);
    tree[x].add = 0;
    return;
}

void build(int x, int l, int r) {
    if (l == r) {
        tree[x].pos = l;
        tree[x].val = l - pos[l];
        return;
    }

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

int find(int x, int l, int r, int fl, int fr) {
    if (fl > fr || tree[x].val > 0)
        return n + 1;
    
    if (fl <= l && r <= fr)
        return tree[x].pos;

    int mid = (l + r) / 2, res = n + 1;
    pushdown(x);

    if (fl <= mid)
        res = find(x * 2, l, mid, fl, fr);

    if (res == n + 1 && mid < fr)
        res = find(x * 2 + 1, mid + 1, r, fl, fr);
    
    return res;
}

void add(int x, int l, int r, int al, int ar, int v) {
    if (al <= l && r <= ar) {
        tree[x].add += v;
        tree[x].val += v;
        return;
    }

    int mid = (l + r) / 2;
    pushdown(x);

    if (al <= mid)
        add(x * 2, l, mid, al, ar, v);
    
    if (mid < ar)
        add(x * 2 + 1, mid + 1, r, al, ar, v);

    pushup(x);
}

void insert(int x, int l, int r, int p, int id) {
    subtree[x].insert(id);

    if (l == r)
        return;

    int mid = (l + r) / 2;

    if (p <= mid)
        insert(x * 2, l, mid, p, id);
    else
        insert(x * 2 + 1, mid + 1, r, p, id);
}

void remove(int x, int l, int r, int p, int id) {
    subtree[x].erase(id);

    if (l == r)
        return;
    
    int mid = (l + r) / 2;

    if (p <= mid)
        remove(x * 2, l, mid, p, id);
    else
        remove(x * 2 + 1, mid + 1, r, p, id);
}

int query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return subtree[x].begin() == subtree[x].end() ? INFINITY : *subtree[x].begin();
    
    int mid = (l + r) / 2, res = INFINITY;

    if (ql <= mid)
        res = query(x * 2, l, mid, ql, qr);
    
    if (mid < qr)
        res = std::min(res, query(x * 2 + 1, mid + 1, r, ql, qr));
    
    return res;
}

void check() {
    for (int i = 1; i <= n; ++i) {
        for (auto it : buc[i])
            now.insert(ranges[it].r);

        if (now.begin() != now.end() && (*now.begin()) >= i) {
            now.erase(now.begin());
        } else {
            std::cout << -1 << std::endl;
            std::exit(0);
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("prophesy.in", "r", stdin);
    std::freopen("prophesy.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        auto &[l, r] = ranges[i];
        std::cin >> l >> r;
        ++t[l];
        ++pos[r];
        buc[l].push_back(i);
    }
    
    for (int i = 1; i <= n; ++i) {
        t[i] += t[i - 1];
        pos[i] += pos[i - 1];
    }

    check();
    build(1, 1, n);

    for (int i = 1; i <= n; ++i) {
        int p = find(1, 1, n, i, n);

        for (auto it : buc[i])
            insert(1, 1, n, ranges[it].r, it);

        a[i] = query(1, 1, n, i, p);
        remove(1, 1, n, ranges[a[i]].r, a[i]);

        if (i < ranges[a[i]].r)
            add(1, 1, n, i, ranges[a[i]].r - 1, -1);
    }

    for (int i = 1; i <= n; ++i)
        std::cout << a[i] << " ";

    return 0;
}
