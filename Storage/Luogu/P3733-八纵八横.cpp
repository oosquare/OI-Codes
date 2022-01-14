#include <iostream>
#include <vector>
#include <bitset>
#include <cstring>

using namespace std;

constexpr int maxn = 500 + 2;
constexpr int maxq = 1000 + 2;
constexpr int maxl = 1000 + 2;

int n, m, q;

struct Node {
    int left, right;
    vector<bitset<maxl>> edges;
};

struct Edge {
    int x, y;
    bitset<maxl> b;
};

struct LinearBasis {
    bitset<maxl> arr[maxl];

    void insert(bitset<maxl> x) {
        if (!x.count())
            return;

        for (int i = 999; i >= 0; --i) {
            if (!x[i])
                continue;

            if (arr[i].count()) {
                x ^= arr[i];
            } else {
                for (int j = i - 1; j >= 0; --j)
                    if (x[j])
                        x ^= arr[j];

                for (int j = 999; j > i; --j)
                    if (arr[j][i])
                        arr[j] ^= x;

                arr[i] = x;
                return;
            }
        }
    }

    bitset<maxl> query() {
        bitset<maxl> x;

        for (int i = 999; i >= 0; --i)
            if ((x[i] ^ arr[i][i]) > x[i])
                x ^= arr[i];

        return x;
    }
};

Node tree[maxq * 4];
vector<pair<int, bitset<maxl>>> graph[maxn];
bitset<maxl> dis[maxn];
bool vis[maxn];
LinearBasis basis;
bitset<maxl> init;
int tot, las[maxn + 50];
Edge edges[maxn + 50];
bool del[maxn + 50];
bitset<maxl> ans[maxq];

void link(int x, int y, const bitset<maxl> &b) {
    graph[x].push_back({y, b});
    graph[y].push_back({x, b});
}

void dfs(int x, int last) {
    vis[x] = true;

    for (const auto &[y, b] : graph[x]) {
        if (y == last)
            continue;

        if (!vis[y]) {
            dis[y] = dis[x] ^ b;
            dfs(y, x);
        } else {
            basis.insert(dis[x] ^ b ^ dis[y]);

            if (y == 1)
                init = dis[x] ^ b;
        }
    }
}

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r)
        return;

    int mid = (l + r) >> 1;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void assign(int x, int l, int r, const bitset<maxl> &b) {
    if (l <= tree[x].left && tree[x].right <= r) {
        tree[x].edges.push_back(b);
        return;
    }

    int mid = (tree[x].left + tree[x].right) >> 1;

    if (l <= mid)
        assign(x * 2, l, r, b);

    if (mid < r)
        assign(x * 2 + 1, l, r, b);
}

void solve(int x, LinearBasis basis) {
    for (const auto &b : tree[x].edges)
        basis.insert(b);

    if (tree[x].left == tree[x].right) {
        ans[tree[x].left] = basis.query();
        return;
    }

    solve(x * 2, basis);
    solve(x * 2 + 1, basis);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    build(1, 0, q);

    char tmp[maxl + 10];

    for (int i = 1; i <= m; ++i) {
        int x, y;
        bitset<maxl> b;
        cin >> x >> y >> tmp;
        int len = strlen(tmp);

        for (int j = 0; j < len; ++j)
            b[j] = (bool)(tmp[len - j - 1] - '0');

        link(x, y, b);
    }

    dfs(1, 0);

    for (int i = 1; i <= q; ++i) {
        cin >> tmp;

        if (tmp[1] == 'd') {
            ++tot;
            auto &[x, y, b] = edges[tot];

            cin >> x >> y >> tmp;
            int len = strlen(tmp);

            for (int j = 0; j < len; ++j)
                b[j] = (bool)(tmp[len - j - 1] - '0');

            las[tot] = i;
        } else if (tmp[1] == 'h') {
            int k;
            cin >> k >> tmp;
            auto &[x, y, b] = edges[k];
            int len = strlen(tmp);

            assign(1, las[k], i - 1, b ^ dis[x] ^ dis[y]);
            las[k] = i;
            b.reset();

            for (int j = 0; j < len; ++j)
                b[j] = (bool)(tmp[len - j - 1] - '0');
        } else {
            int k;
            cin >> k;
            auto &[x, y, b] = edges[k];
            assign(1, las[k], i - 1, b ^ dis[x] ^ dis[y]);
            del[k] = true;
        }
    }

    for (int i = 1; i <= tot; ++i) {
        if (!del[i]) {
            auto &[x, y, b] = edges[i];
            cerr << i << " " << las[i] << " " << n << endl;
            assign(1, las[i], q, b ^ dis[x] ^ dis[y]);
        }
    }

    solve(1, basis);

    for (int i = 0; i <= q; ++i) {
        int pos = -1;

        for (int j = 999; j >= 0; --j) {
            if (ans[i][j]) {
                pos = j;
                break;
            }
        }

        if (pos == -1) {
            cout << 0 << endl;
        } else {
            for (int j = pos; j >= 0; --j)
                cout << ans[i][j];

            cout << endl;
        }
    }

    return 0;
}