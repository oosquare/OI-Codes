#include <iostream>
#include <vector>
#include <deque>
using namespace std;

constexpr int maxn = 50000 + 10;
constexpr int maxp = 500 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Item {
    int w, v;
};

struct Node {
    int left, right;
    vector<Item> items;
};

int m, p;
Node tree[maxn * 4];
long long f[20][maxp], tmp[maxp];
pair<int, int> qs[maxn];
Item items[maxn];
int tot, tim[maxn];
deque<int> q;

void build(int x, int l, int r) {
    tree[x].left = l;
    tree[x].right = r;

    if (l == r)
        return;

    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
}

void assign(int x, int l, int r, const Item &item) {
    if (l <= tree[x].left && tree[x].right <= r) {
        tree[x].items.push_back(item);
        return;
    }

    int mid = (tree[x].left + tree[x].right) / 2;

    if (l <= mid)
        assign(x * 2, l, r, item);

    if (mid < r)
        assign(x * 2 + 1, l, r, item);
}

void solve(int x, int dep) {
    for (int i = 0; i < p; ++i)
        f[dep][i] = f[dep - 1][i];

    for (auto [w, v] : tree[x].items) {
        for (int i = 0; i < p; ++i)
            tmp[i] = f[dep][i];

        for (int i = 0; i < p; ++i)
            f[dep][i] = max(tmp[i], tmp[(i - w + p) % p] + v);
    }

    if (tree[x].left == tree[x].right) {
        auto [l, r] = qs[tree[x].left];

        if (l != -1 && r != -1) {
            long long res = -1;

            for (int i = l; i <= r; ++i)
                res = max(res, f[dep][i]);

            cout << res << endl;
        }

        return;
    }

    solve(x * 2, dep + 1);
    solve(x * 2 + 1, dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m;
    cin >> m >> p;
    build(1, 1, m);

    for (int i = 0; i < 20; ++i)
        for (int j = 1; j <= p; ++j)
            f[i][j] = -oo;

    for (int i = 1; i <= m; ++i)
        qs[i] = {-1, -1};

    for (int i = 1; i <= m; ++i) {
        char op[3];
        cin >> op;

        if (op[0] == 'I' && op[1] == 'F') {
            ++tot;
            auto &[w, v] = items[tot];
            cin >> w >> v;
            w %= p;
            tim[tot] = i;
            q.push_front(tot);
        } else if (op[0] == 'I' && op[1] == 'G') {
            ++tot;
            auto &[w, v] = items[tot];
            cin >> w >> v;
            w %= p;
            tim[tot] = i;
            q.push_back(tot);
        } else if (op[0] == 'D' && op[1] == 'F') {
            int id = q.front();
            q.pop_front();
            assign(1, tim[id], i - 1, items[id]);
        } else if (op[0] == 'D' && op[1] == 'G') {
            int id = q.back();
            q.pop_back();
            assign(1, tim[id], i - 1, items[id]);
        } else {
            int l, r;
            cin >> l >> r;
            qs[i] = {l, r};
        }
    }

    while (!q.empty()) {
        int id = q.back();
        q.pop_back();
        assign(1, tim[id], m, items[id]);
    }

    solve(1, 1);
    return 0;
}