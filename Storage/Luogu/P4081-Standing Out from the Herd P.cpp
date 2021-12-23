#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
#include <list>
using namespace std;

constexpr int maxn = 2e5 + 10;

class SteadyStack {
public:
    void push(int x) {
        while (!st.empty() && st.top() >= x)
            st.pop();

        st.push(x);
    }

    int top() {
        return (st.empty() ? 0 : st.top());
    }
private:
    stack<int, list<int>> st;
};

class SparseTable {
public:
    void preprocess(int a[], int n) {
        logv[0] = -1;

        for (int i = 1; i <= n; ++i)
            logv[i] = logv[i / 2] + 1;

        for (int i = 1; i <= n; ++i)
            data[i][0] = a[i];

        for (int j = 1; j <= 17; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                data[i][j] = min(data[i][j - 1], data[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        if (l > r)
            return 0x3f3f3f3f;

        int s = logv[r - l + 1];
        return min(data[l][s], data[r - (1 << s) + 1][s]);
    }
private:
    int data[maxn][18];
    int logv[maxn];
};

int n, len, dat[maxn * 2];
char str[maxn];
int sa[maxn * 4], buf[2][maxn * 4], *rk, height[maxn * 4];
int cnt[maxn * 4], id[maxn * 4], *old, tmp[maxn * 4];
int col[maxn * 2];
long long ans[maxn];
SteadyStack st[maxn];
SparseTable mi;
int las[maxn], pos[maxn];

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprocess(int dat[], int n, int m) {
    for (int i = 1; i <= m; ++i)
        cnt[i] = 0;

    for (int i = 1; i <= n; ++i)
        ++cnt[rk[i] = dat[i]];

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

        while (dat[i + j] == dat[sa[rk[i] - 1] + j])
            ++j;

        height[rk[i]] = j;
    }
}

void add(char str[], int id) {
    int start = len, l = strlen(str);

    for (int i = 0; i < l; ++i) {
        dat[++len] = str[i];
        col[len] = id;
    }

    dat[++len] = id + 127;
    preprocess(dat + start, l, 127);

    ans[id] = 1ll * l * (l + 1) / 2;

    for (int i = 1; i <= l; ++i)
        ans[id] -= height[i];
}

void remove(int id, int l, int p) {
    ans[id] -= max(l - min(st[id].top(), mi.query(las[id] + 1, p - 1)), 0);
    st[id].push(l);
}

int main() {
    rk = buf[0], old = buf[1];

    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str);
        add(str, i);
    }

    preprocess(dat, len, 127 + n);
    mi.preprocess(height, len);

    for (int i = 2; i <= len; ++i) {
        if (col[sa[i - 1]] != col[sa[i]]) {
            remove(col[sa[i - 1]], height[i], i);
            remove(col[sa[i]], height[i], i);
            las[col[sa[i - 1]]] = i - 1;
            las[col[sa[i]]] = i;
        }
    }

    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans[i]);

    return 0;
}