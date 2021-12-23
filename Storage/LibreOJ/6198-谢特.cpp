#include <iostream>
#include <cstring>
#include <algorithm>
#include <tuple>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Node {
    int next[2];
    bool end;

    int &operator[](int x) {
        return next[x];
    }
};

int n, w[maxn];
char str[maxn];
int sa[maxn * 2], rk[maxn * 2], height[maxn * 2];
int cnt[maxn * 2], id[maxn * 2], old[maxn * 2], tmp[maxn * 2];
int fa[maxn], sze[maxn], l[maxn], r[maxn];
tuple<int, int, int> ord[maxn];
int root[maxn], uuid;
Node trie[maxn * 100];
int ans;

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess() {
    int m = 127;

    for (int i = 1; i <= n; ++i)
        ++cnt[rk[i] = str[i]];

    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = n; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;

    for (int w = 1, p;; w *= 2, m = p) {
        p = 0;

        for (int i = n; i > n - w; --i)
            id[++p] = i;

        for (int i = 1; i <= n; ++i)
            if (sa[i] > w)
                id[++p] = sa[i] - w;

        for (int i = 1; i <= m; ++i)
            cnt[i] = 0;

        for (int i = 1; i <= n; ++i)
            ++cnt[tmp[i] = rk[id[i]]];

        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];

        for (int i = n; i >= 1; --i)
            sa[cnt[tmp[i]]--] = id[i];

        swap(old, rk);
        p = 0;

        for (int i = 1; i <= n; ++i)
            rk[sa[i]] = (equal(sa[i - 1], sa[i], w) ? p : ++p);

        if (p == n) {
            for (int i = 1; i <= n; ++i)
                sa[rk[i]] = i;

            break;
        }
    }

    for (int i = 1, j = 0; i <= n; ++i) {
        if (j)
            --j;

        while (str[i + j] == str[sa[rk[i] - 1] + j])
            ++j;

        height[rk[i]] = j;
    }

    height[0] = height[n + 1] = 0;
}

void insert(int rt, int num) {
    int x = rt;

    for (int i = 31; i >= 0; --i) {
        int c = ((num >> i) & 1);

        if (!trie[x][c])
            trie[x][c] = ++uuid;

        x = trie[x][c];
    }

    trie[x].end = true;
}

int calc(int rt, int num) {
    int x = rt, res = 0;

    for (int i = 31; i >= 0; --i) {
        int c = ((num >> i) & 1);

        if (trie[x][c ^ 1]) {
            x = trie[x][c ^ 1];
            res |= (1 << i);
        } else if (trie[x][c]) {
            x = trie[x][c];
        } else {
            break;
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> (str + 1);

    preprocess();

    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        root[i] = ++uuid;
        insert(root[i], w[sa[i]]);
        fa[i] = i;
        sze[i] = 1;
        l[i] = r[i] = i;
    }

    for (int i = 2; i <= n; ++i)
        ord[i - 1] = {i - 1, i, height[i]};

    sort(ord + 1, ord + n, [](auto lhs, auto rhs) {
        return get<2>(lhs) > get<2>(rhs);
    });

    for (int i = 1; i < n; ++i) {
        auto [x, y, h] = ord[i];
        x = find(x);
        y = find(y);

        if (sze[x] > sze[y])
            swap(x, y);

        int res = 0;

        for (int i = l[x]; i <= r[x]; ++i)
            res = max(res, calc(root[y], w[sa[i]]));

        ans = max(ans, h + res);

        for (int i = l[x]; i <= r[x]; ++i)
            insert(root[y], w[sa[i]]);

        sze[y] += sze[x];
        l[y] = min(l[y], l[x]);
        r[y] = max(r[y], r[x]);
        fa[x] = y;
    }

    cout << ans << endl;
    return 0;
}