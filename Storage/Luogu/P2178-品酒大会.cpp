#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr int maxn = 300000 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

struct Value {
    long long pmax, pmin, mmax, mmin;
    bool vpmax, vpmin, vmmax, vmmin, hasZero;

    Value() {
        clear();
    }

    void clear() {
        pmax = pmin = mmax = mmin = 0;
        vpmax = vpmin = vmmax = vmmin = hasZero = false;
    }

    void init(int x) {
        clear();

        if (x > 0) {
            pmax = pmin = x;
            vpmax = vpmin = true;
        } else if (x == 0) {
            hasZero = true;
        } else {
            mmax = mmin = x;
            vmmax = vmmin = true;
        }
    }

    Value merge(const Value &rhs) const {
        Value res;

        if (vpmax && rhs.vpmax)
            res.pmax = max(pmax, rhs.pmax);
        else if (vpmax && !rhs.vpmax)
            res.pmax = pmax;
        else if (!vpmax && rhs.vpmax)
            res.pmax = rhs.pmax;

        if (vpmin && rhs.vpmin)
            res.pmin = min(pmin, rhs.pmin);
        else if (vpmin && !rhs.vpmin)
            res.pmin = pmin;
        else if (!vpmin && rhs.vpmin)
            res.pmin = rhs.pmin;

        if (vmmax && rhs.vmmax)
            res.mmax = max(mmax, rhs.mmax);
        else if (vmmax && !rhs.vmmax)
            res.mmax = mmax;
        else if (!vmmax && rhs.vmmax)
            res.mmax = rhs.mmax;

        if (vmmin && rhs.vmmin)
            res.mmin = min(mmin, rhs.mmin);
        else if (vmmin && !rhs.vmmin)
            res.mmin = mmin;
        else if (!vmmin && rhs.vmmin)
            res.mmin = rhs.mmin;

        res.vpmax = vpmax || rhs.vpmax;
        res.vpmin = vpmin || rhs.vpmin;
        res.vmmax = vmmax || rhs.vmmax;
        res.vmmin = vmmin || rhs.vmmin;
        res.hasZero = hasZero || rhs.hasZero;

        return res;
    }

    long long calc(const Value &rhs) {
        long long res = -oo;

        if (vpmax && rhs.vpmax)
            res = max(res, pmax * rhs.pmax);

        if (vmmin && rhs.vmmin)
            res = max(res, mmin * rhs.mmin);

        if (vpmin && rhs.vmmax)
            res = max(res, pmin * rhs.mmax);

        if (vmmax && rhs.vpmin)
            res = max(res, mmax * rhs.pmin);

        if (hasZero || rhs.hasZero)
            res = max(res, 0ll);

        return res;
    }
};

struct UnionFindSet {
    int fa[maxn];
    long long sze[maxn];
    Value val[maxn];

    void init(int n, long long a[]) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
            sze[i] = 1;
            val[i].init(a[i]);
        }
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);

        if (x != y) {
            sze[y] += sze[x];
            val[y] = val[y].merge(val[x]);
            fa[x] = y;
        }
    }
};

struct HeightInformation {
    int x, y, h;

    bool operator<(const HeightInformation &rhs) {
        return h > rhs.h;
    }
};

int n;
char str[maxn];
int sa[maxn * 2], rk[maxn * 2], height[maxn * 2];
int id[maxn * 2], cnt[maxn * 2], old[maxn * 2], tmp[maxn * 2];
int a[maxn];
UnionFindSet rt;
HeightInformation ht[maxn];
long long sum[maxn], mx[maxn];
long long t[maxn];

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

        swap(rk, old);
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

    height[0] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> (str + 1);

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    preprocess();

    for (int i = 1; i <= n; ++i) {
        t[i] = a[sa[i]];
        mx[i] = -oo;
    }

    rt.init(n, t);

    for (int i = 2; i <= n; ++i)
        ht[i - 1] = {i - 1, i, height[i]};

    sort(ht + 1, ht + n);

    for (int i = 1; i < n; ++i) {
        auto [x, y, h] = ht[i];

        int fx = rt.find(x), fy = rt.find(y);
        sum[h] += rt.sze[fx] * rt.sze[fy];
        mx[h] = max(mx[h], rt.val[fx].calc(rt.val[fy]));
        rt.merge(fx, fy);
    }

    for (int i = n - 1; i >= 0; --i) {
        sum[i] += sum[i + 1];
        mx[i] = max(mx[i], mx[i + 1]);
    }

    for (int i = 0; i < n; ++i)
        cout << sum[i] << " " << (sum[i] ? mx[i] : 0) << endl;

    return 0;
}