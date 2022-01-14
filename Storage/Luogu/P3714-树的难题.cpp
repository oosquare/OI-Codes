#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 2e5 + 10;

struct Data {
    int val, col;

    Data() : val(-0x3f3f3f3f), col(0) {}

    bool operator<(const Data &rhs) const {
        return val < rhs.val;
    }
};

struct Node {
    int left, right;
    pair<Data, Data> data;
};

int n, m, bl, br, val[maxn];
Node seg[maxn * 4];
vector<pair<int, int>> tree[maxn];
int root, tot, sze[maxn], sze2[maxn];
int dis[maxn][2];
bool vis[maxn];
Data arr[maxn];
int ans = -0x3f3f3f3f;

int calc(const Data &a, const pair<Data, Data> &b) {
    return max(
               a.val + b.first.val - (a.col == b.first.col ? val[a.col] : 0),
               a.val + b.second.val - (a.col == b.second.col ? val[a.col] : 0)
           );
}

void pushup(int x) {
    Data tmp[4] = {seg[x * 2].data.first, seg[x * 2].data.second, seg[x * 2 + 1].data.first, seg[x * 2 + 1].data.second};
    sort(tmp, tmp + 4);
    seg[x].data.first = tmp[3];

    if (tmp[3].col != tmp[2].col)
        seg[x].data.second = tmp[2];
    else if (tmp[3].col != tmp[1].col)
        seg[x].data.second = tmp[1];
    else
        seg[x].data.second = tmp[0];
}

pair<Data, Data> pushup(const pair<Data, Data> &lhs, const pair<Data, Data> &rhs) {
    Data tmp[4] = {lhs.first, lhs.second, rhs.first, rhs.second};
    sort(tmp, tmp + 4);
    pair<Data, Data> res;
    res.first = tmp[3];

    if (tmp[3].col != tmp[2].col) {
        res.second = tmp[2];
        return res;
    }

    if (tmp[3].col != tmp[1].col) {
        res.second = tmp[1];
        return res;
    }

    if (tmp[3].col != tmp[0].col) {
        res.second = tmp[0];
        return res;
    }

    return res;
}

void build(int x, int l, int r) {
    seg[x].left = l;
    seg[x].right = r;

    if (l == r) {
        seg[x].data = {Data(), Data()};

        if (l == 0)
            seg[x].data.first.val = 0;

        return;
    }

    int mid = (l + r) >> 1;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    pushup(x);
}

void modify(int x, int p, const Data &v) {
    if (seg[x].left == seg[x].right) {
        if (seg[x].data.first.val <= v.val) {
            if (seg[x].data.first.col == v.col)
                seg[x].data.first = v;
            else
                seg[x].data.second = exchange(seg[x].data.first, v);
        } else if (seg[x].data.second.val < v.val) {
            if (seg[x].data.first.col != v.col)
                seg[x].data.second = v;
        }

        return;
    }

    int mid = (seg[x].left + seg[x].right) >> 1;

    if (p <= mid)
        modify(x * 2, p, v);
    else
        modify(x * 2 + 1, p, v);

    pushup(x);
}

pair<Data, Data> query(int x, int l, int r) {
    if (l <= seg[x].left && seg[x].right <= r)
        return seg[x].data;

    int mid = (seg[x].left + seg[x].right) >> 1;

    if (r <= mid)
        return query(x * 2, l, r);
    else if (mid < l)
        return query(x * 2 + 1, l, r);
    else
        return pushup(query(x * 2, l, r), query(x * 2 + 1, l, r));
}

void link(int x, int y, int c) {
    tree[x].push_back({y, c});
    tree[y].push_back({x, c});
}

void getRoot(int x, int fa) {
    sze[x] = 1;
    sze2[x] = 0;

    for (auto [y, c] : tree[x]) {
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

void getDistance(int x, int fa) {
    dis[x][0] = dis[x][1] = 0;

    for (auto [y, c] : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getDistance(y, x);

        if (dis[x][0] <= dis[y][0] + 1)
            dis[x][1] = exchange(dis[x][0], dis[y][0] + 1);
        else if (dis[x][1] < dis[y][0] + 1)
            dis[x][1] = dis[y][1] + 1;
    }
}

void getValue(int x, int fa, int d, int w, int rc, int nc) {
    Data tmp;
    tmp.val = w;
    tmp.col = rc;
    arr[d] = max(arr[d], tmp);

    for (auto [y, c] : tree[x]) {
        if (y == fa || vis[y])
            continue;

        getValue(y, x, d + 1, w + (c == nc ? 0 : val[c]), rc, c);
    }
}

void solve(int x) {
    getDistance(x, 0);
    vis[x] = true;

    if (dis[x][0] + dis[x][1] < bl)
        return;

    build(1, 0, dis[x][0] + dis[x][1]);

    for (auto [y, c] : tree[x]) {
        if (vis[y])
            continue;

        getDistance(y, x);

        for (int i = 1; i <= dis[y][0] + 1; ++i)
            arr[i] = Data();

        getValue(y, x, 1, val[c], c, c);

        for (int i = 1; i <= dis[y][0] + 1; ++i) {
            if (br - i < 0 || bl - i > dis[x][0] + dis[x][1])
                continue;

            int res = calc(arr[i], query(1, max(bl - i, 0), min(br - i, dis[x][0] + dis[x][1])));
            ans = max(ans, res);
        }

        for (int i = 1; i <= dis[y][0] + 1; ++i)
            modify(1, i, arr[i]);
    }

    for (auto [y, c] : tree[x]) {
        if (vis[y])
            continue;

        tot = sze[y];
        root = 0;
        getRoot(y, x);
        solve(root);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> bl >> br;

    for (int i = 1; i <= m; ++i)
        cin >> val[i];

    for (int i = 1; i < n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        link(x, y, c);
    }

    tot = n;
    getRoot(1, 0);
    solve(root);
    cout << ans << endl;
    return 0;
}