#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 1.5e5 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Segment {
    long long k, b;

    long long calc(int x) const {
        return k * x + b;
    }
};

class LiChaoSegmentTree {
public:
    void init(int len) {
        uuid = 0;
        root = 0;
        this->len = len;
    }

    void insert(const Segment &s) {
        insert(root, 0, len, s);
    }

    long long query(int p) {
        return query(root, 0, len, p);
    }

private:
    struct Node {
        int ls, rs;
        Segment seg;
    };

    Node tree[maxn * 50];
    int root, uuid, len;

    int create() {
        ++uuid;
        tree[uuid].ls = tree[uuid].rs = 0;
        return uuid;
    }

    void insert(int &x, int l, int r, const Segment &s) {
        if (!x) {
            x = create();
            tree[x].seg = s;
            return;
        }

        if (s.calc(l) > tree[x].seg.calc(l) && s.calc(r) > tree[x].seg.calc(r)) {
            tree[x].seg = s;
            return;
        }

        if (s.calc(l) <= tree[x].seg.calc(l) && s.calc(r) <= tree[x].seg.calc(r))
            return;

        int mid = (l + r) / 2;

        if (l == r) {
            if (s.calc(l) > tree[x].seg.calc(l))
                tree[x].seg = s;

            return;
        }

        if (s.k > tree[x].seg.k) {
            if (s.calc(mid) < tree[x].seg.calc(mid)) {
                insert(tree[x].ls, l, mid, tree[x].seg);
                tree[x].seg = s;
            } else {
                insert(tree[x].rs, mid + 1, r, s);
            }
        } else if (s.k < tree[x].seg.k) {
            if (s.calc(mid) < tree[x].seg.calc(mid)) {
                insert(tree[x].rs, mid + 1, r, tree[x].seg);
                tree[x].seg = s;
            } else {
                insert(tree[x].ls, l, mid, s);
            }
        } else {
            if (s.b < tree[x].seg.b)
                tree[x].seg = s;
        }
    }

    long long query(int x, int l, int r, int p) {
        if (!x)
            return -oo;

        if (l == r)
            return tree[x].seg.calc(p);

        int mid = (l + r) / 2;

        if (p <= mid)
            return max(tree[x].seg.calc(p), query(tree[x].ls, l, mid, p));
        else
            return max(tree[x].seg.calc(p), query(tree[x].rs, mid + 1, r, p));
    }
};

int n, a[maxn];
vector<int> tree[maxn];
int tot, root, sze[maxn], sze2[maxn], dis[maxn];
bool vis[maxn];
LiChaoSegmentTree seg;
long long ans;

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getRoot(y, x);
        sze[x] += sze[y];
        sze2[x] = max(sze2[x], sze[y]);
    }

    sze2[x] = max(sze2[x], tot - sze[x]);

    if (!root || sze2[x] < sze2[root])
        root = x;
}

void getInformation(int x, int fa) {
    sze[x] = 1;
    dis[x] = 1;

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getInformation(y, x);
        sze[x] += sze[y];
        dis[x] = max(dis[x], dis[y] + 1);
    }
}

void calc(int x, int fa, int dep, long long dis, long long sum) {
    ans = max(ans, sum + seg.query(dep));
    ans = max(ans, sum);

    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        calc(y, x, dep + 1, dis + a[y], sum + dis + a[y]);
    }
}

void update(int x, int fa, int dep, long long dis, long long sum) {
    seg.insert({dis, sum});
    ans = max(ans, sum);
    
    for (int y : tree[x]) {
        if (y == fa || vis[y])
            continue;

        update(y, x, dep + 1, dis + a[y], sum + 1ll * (dep + 1) * a[y]);
    }
}

void solve(int x) {
    vis[x] = true;
    getInformation(x, 0);
    seg.init(dis[x]);
    seg.insert({a[x], a[x]});

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        calc(y, x, 1, a[y], a[y]);
        update(y, x, 2, a[x] + a[y], a[x] + 2 * a[y]);
    }

    reverse(tree[x].begin(), tree[x].end());
    seg.init(dis[x]);
    seg.insert({a[x], a[x]});

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        calc(y, x, 1, a[y], a[y]);
        update(y, x, 2, a[x] + a[y], a[x] + 2 * a[y]);
    }

    for (int y : tree[x]) {
        if (vis[y])
            continue;

        root = 0;
        tot = sze[y];
        getRoot(y, x);
        solve(root);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    tot = n;
    getRoot(1, 0);
    solve(root);
    cout << ans << endl;
    return 0;
};