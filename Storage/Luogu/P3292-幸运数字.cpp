#include <iostream>
#include <vector>
using namespace std;

constexpr int maxn = 20000 + 10;

struct LinearBasis {
    long long a[62];

    LinearBasis() {
        for (int i = 0; i < 60; ++i)
            a[i] = 0;
    }

    void insert(long long x) {
        if (!x)
            return;

        for (int i = 59; i >= 0; --i) {
            if (((x >> i) & 1) == 0)
                continue;

            if (a[i]) {
                x ^= a[i];
            } else {
                for (int j = i - 1; j >= 0; --j)
                    if ((x >> j) & 1)
                        x ^= a[j];

                for (int j = 59; j > i; --j)
                    if ((a[j] >> i) & 1)
                        a[j] ^= x;

                a[i] = x;
                return;
            }
        }
    }

    void merge(const LinearBasis &rhs) {
        for (int i = 0; i < 60; ++i)
            insert(rhs.a[i]);
    }

    static LinearBasis merge(const LinearBasis &lhs, const LinearBasis &rhs) {
        LinearBasis res = lhs;
        res.merge(rhs);
        return res;
    }

    long long query() {
        long long res = 0;

        for (int i = 59; i >= 0; --i)
            res ^= a[i];

        return res;
    }
};

int n, q;
long long g[maxn];
vector<int> tree[maxn];
int dep[maxn], step[maxn][16];
LinearBasis basis[maxn][16];

void link(int x, int y) {
    tree[x].push_back(y);
    tree[y].push_back(x);
}

void preprocess(int x, int fa) {
    step[x][0] = fa;
    basis[x][0].insert(g[x]);
    basis[x][0].insert(g[fa]);
    dep[x] = dep[fa] + 1;

    for (int i = 1; i <= 15; ++i) {
        step[x][i] = step[step[x][i - 1]][i - 1];
        basis[x][i] = LinearBasis::merge(basis[x][i - 1], basis[step[x][i - 1]][i - 1]);
    }

    for (int y : tree[x]) {
        if (y == fa)
            continue;

        preprocess(y, x);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    for (int i = 15; i >= 0; --i)
        if (dep[step[x][i]] >= dep[y])
            x = step[x][i];

    if (x == y)
        return x;

    for (int i = 15; i >= 0; --i) {
        if (step[x][i] != step[y][i]) {
            x = step[x][i];
            y = step[y][i];
        }
    }

    return step[x][0];
}

LinearBasis split0(int x, int anc) {
    LinearBasis res;

    for (int i = 15; i >= 0; --i) {
        if (dep[step[x][i]] >= dep[anc]) {
            res.merge(basis[x][i]);
            x = step[x][i];
        }
    }

    return res;
}

LinearBasis split(int x, int y) {
    int l = lca(x, y);
    return LinearBasis::merge(split0(x, l), split0(y, l));
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        cin >> g[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }

    preprocess(1, 0);

    for (int i = 1; i <= q; ++i) {
        int x, y;
        cin >> x >> y;

        if (x == y)
            cout << g[x] << endl;
        else
            cout << split(x, y).query() << endl;
    }
    return 0;
}