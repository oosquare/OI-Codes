#include <iostream>
#include <cstring>
using namespace std;

constexpr int maxn = 2e5 + 10;
constexpr int oo = 0x3f3f3f3f;

struct SegmentTree {
    struct Node {
        int left, right;
        int min, max, assign;
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].min = min(tree[x * 2].min, tree[x * 2 + 1].min);
        tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
    }

    void build(int x, int l, int r, int *a = nullptr) {
        tree[x].left = l;
        tree[x].right = r;

        if (l == r) {
            if (a)
                tree[x].min = tree[x].max = a[l];

            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, a);
        build(x * 2 + 1, mid + 1, r, a);
        pushup(x);
    }

    void assign(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            tree[x].max = max(tree[x].max, v);
            tree[x].assign = max(tree[x].assign, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) >> 1;

        if (l <= mid)
            assign(x * 2, l, r, v);

        if (mid < r)
            assign(x * 2 + 1, l, r, v);

        pushup(x);
    }

    int queryMax(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].max;

        int mid = (tree[x].left + tree[x].right) >> 1, res = tree[x].assign;

        if (l <= mid)
            res = max(res, queryMax(x * 2, l, r));

        if (mid < r)
            res = max(res, queryMax(x * 2 + 1, l, r));

        return res;
    }

    int queryMin(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].min;

        int mid = (tree[x].left + tree[x].right) >> 1, res = oo;

        if (l <= mid)
            res = min(res, queryMin(x * 2, l, r));

        if (mid < r)
            res = min(res, queryMin(x * 2 + 1, l, r));

        return res;
    }
};

int n, k;
char str[maxn];
int dat[maxn], len;
int sa[maxn * 2], rk[maxn * 2], height[maxn * 2];
int cnt[maxn * 2], id[maxn * 2], old[maxn * 2], tmp[maxn * 2];
int pos[maxn];
SegmentTree mheight, lcp;
int buc[maxn], tot;
long long ans[maxn];

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess(int dat[], int len) {
    int m = len + 300;

    for (int i = 1; i <= len; ++i)
        ++cnt[rk[i] = dat[i]];

    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = len; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;

    for (int w = 1, p;; w *= 2, m = p) {
        p = 0;

        for (int i = len; i > len - w; --i)
            id[++p] = i;

        for (int i = 1; i <= len; ++i)
            if (sa[i] > w)
                id[++p] = sa[i] - w;

        for (int i = 1; i <= m; ++i)
            cnt[i] = 0;

        for (int i = 1; i <= len; ++i)
            ++cnt[tmp[i] = rk[id[i]]];

        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];

        for (int i = len; i >= 1; --i)
            sa[cnt[tmp[i]]--] = id[i];

        swap(rk, old);
        p = 0;

        for (int i = 1; i <= len; ++i)
            rk[sa[i]] = (equal(sa[i - 1], sa[i], w) ? p : ++p);

        if (p == len) {
            for (int i = 1; i <= len; ++i)
                sa[rk[i]] = i;

            break;
        }
    }

    for (int i = 1, j = 0; i <= len; ++i) {
        if (j)
            --j;

        while (dat[i + j] == dat[sa[rk[i] - 1] + j])
            ++j;

        height[rk[i]] = j;
    }

    height[1] = 0;
}

void add(int x) {
    if (buc[pos[sa[x]]] == 0)
        ++tot;

    ++buc[pos[sa[x]]];
}

void del(int x) {
    --buc[pos[sa[x]]];

    if (buc[pos[sa[x]]] == 0)
        --tot;
}

int main() {
    // ios::sync_with_stdio(false);

    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> (str + 1);
        int tlen = strlen(str + 1);

        if (k == 1) {
            cout << 1ll * tlen * (tlen + 1) / 2 << " ";
            continue;
        }

        for (int j = 1; j <= tlen; ++j) {
            dat[++len] = str[j] - 'a';
            pos[len] = i;
        }

        dat[++len] = 'z' + i;
    }

    if (k == 1)
        return 0;

    preprocess(dat, len);

    mheight.build(1, 1, len, height);
    lcp.build(1, 1, len);

    for (int i = 1, j = 0; i <= len; ++i) {
        while (j <= len && tot < k)
            add(++j);

        if (tot < k)
            break;

        int h = mheight.queryMin(1, i + 1, j);
        lcp.assign(1, i, j, h);
        del(i);
    }

    for (int i = 2; i <= len; ++i)
        lcp.assign(1, i, i, min(height[i], lcp.queryMax(1, i - 1, i - 1)));

    for (int i = 1; i <= len; ++i)
        ans[pos[sa[i]]] += lcp.queryMax(1, i, i);

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";

    cout << endl;
    return 0;
}