#include <iostream>
#include <cstring>
using namespace std;

constexpr int MAX_N = 1e6 + 10;
constexpr int INFINITY = 0x3f3f3f3f;

class SuffixArray {
public:
    int n;
    int sa[MAX_N], rk[MAX_N], height[MAX_N];

    void push(int c) {
        str[++n] = c;
    }

    void preprocess() {
        preprocess(str, n, 256);
    }
private:
    int str[MAX_N];
    bool t[MAX_N * 5];

    inline bool islms(int i, bool * t) {
        return i > 0 && t[i] && !t[i - 1];
    }

    template <typename T> void sort(T s, int * sa, int len, int sigma, int sz, bool * t, int * b, int * cb, int * p) {
        memset(b, 0, sizeof(int) * sigma);
        memset(sa, -1, sizeof(int) * len);

        for (int i = 0; i < len; i++)
            b[(int) s[i]]++;

        cb[0] = b[0];

        for (int i = 1; i < sigma; i++)
            cb[i] = cb[i - 1] + b[i];

        for (int i = sz - 1; i >= 0; i--)
            sa[--cb[(int) s[p[i]]]] = p[i];

        for (int i = 1; i < sigma; i++)
            cb[i] = cb[i - 1] + b[i - 1];

        for (int i = 0; i < len; i++)
            if (sa[i] > 0 && !t[sa[i] - 1])
                sa[cb[(int) s[sa[i] - 1]]++] = sa[i] - 1;

        cb[0] = b[0];

        for (int i = 1; i < sigma; i++)
            cb[i] = cb[i - 1] + b[i];

        for (int i = len - 1; i >= 0; i--)
            if (sa[i] > 0 && t[sa[i] - 1])
                sa[--cb[(int) s[sa[i] - 1]]] = sa[i] - 1;
    }

    template <typename T> void sais(T s, int * sa, int len, bool * t, int * b, int * b1, int sigma) {
        int i, j, x, p = -1, cnt = 0, sz = 0, * cb = b + sigma;

        for (t[len - 1] = 1, i = len - 2; i >= 0; i--)
            t[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && t[i + 1]);

        for (i = 1; i < len; i++)
            if (t[i] && !t[i - 1])
                b1[sz++] = i;

        sort(s, sa, len, sigma, sz, t, b, cb, b1);

        for (i = sz = 0; i < len; i++)
            if (islms(sa[i], t))
                sa[sz++] = sa[i];

        for (i = sz; i < len; i++)
            sa[i] = -1;

        for (i = 0; i < sz; i++) {
            for (x = sa[i], j = 0; j < len; j++) {
                if (p == -1 || s[x + j] != s[p + j] || t[x + j] != t[p + j]) {
                    cnt++, p = x;
                    break;
                } else if (j > 0 && (islms(x + j, t) || islms(p + j, t)))
                    break;
            }

            sa[sz + (x >>= 1)] = cnt - 1;
        }

        for (i = j = len - 1; i >= sz; i--)
            if (sa[i] >= 0)
                sa[j--] = sa[i];

        int * s1 = sa + len - sz, * b2 = b1 + sz;

        if (cnt < sz)
            sais(s1, sa, sz, t + len, b, b1 + sz, cnt);
        else
            for (i = 0; i < sz; i++)
                sa[s1[i]] = i;

        for (i = 0; i < sz; i++)
            b2[i] = b1[sa[i]];

        sort(s, sa, len, sigma, sz, t, b, cb, b2);
    }

    template <typename T> void preprocess(T s, int len, int sigma) {
        sais(s + 1, sa, len + 1, t, rk, height, sigma), rk[0] = 0;

        for (int i = 1; i <= len; ++i)
            rk[++sa[i]] = i;

        for (int i = 1, j = 0; i <= len; ++i) {
            if (j)
                --j;

            while (s[i + j] == s[sa[rk[i] - 1] + j])
                ++j;

            height[rk[i]] = j;
        }
    }
};

class SparseTable {
public:
    void preprocess(int val[], int n) {
        log[0] = -1;

        for (int i = 1; i <= n; ++i) {
            log[i] = log[i / 2] + 1;
            data[i][0] = val[i];
        }

        for (int j = 1; j <= 20; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                data[i][j] = min(data[i][j - 1], data[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        if (l > r)
            return 0;
        int s = log[r - l + 1];
        return min(data[l][s], data[r - (1 << s) + 1][s]);
    }
private:
    int log[MAX_N], data[MAX_N][21];
};

struct Operation {
    int type, x;
    char c;
};

struct Range {
    int l, r;

    Range(int l = INFINITY, int r = -INFINITY) {
        this->l = l;
        this->r = r;
    }

    bool empty() const {
        return l > r;
    }
};

int n, m, q;
int tot;
char s[MAX_N], t[MAX_N];
Operation op[MAX_N];
SuffixArray sa;
SparseTable st;
Range now[MAX_N];
int las[MAX_N], cur, len[MAX_N];
bool state[MAX_N];
int sum[MAX_N];

int lcp(int l, int r) {
    if (l == r)
        return sa.n - sa.sa[l] + 1;

    if (l > r)
        swap(l, r);

    return st.query(l + 1, r);
}

Range find(int start, int len) {
    int pos = sa.rk[start + n + 1];
    int pl = pos, pr = pos;

    int l = 1, r = pos - 1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (lcp(mid, pos) >= len) {
            pl = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    l = pos + 1;
    r = sa.n;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (lcp(mid, pos) >= len) {
            pr = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return { pl, pr };
}

Range merge(const Range & lhs, const Range & rhs, int len) {
    if (lhs.empty() || rhs.empty())
        return Range();

    int pl = 0, pr = 0;
    auto [l, r] = lhs;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (sa.rk[sa.sa[mid] + len] >= rhs.l) {
            pl = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (!pl || sa.rk[sa.sa[pl] + len] > rhs.r)
        return Range();

    l = lhs.l;
    r = lhs.r;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (sa.rk[sa.sa[mid] + len] <= rhs.r) {
            pr = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (!pr || sa.rk[sa.sa[pr] + len] < rhs.l)
        return Range();

    return Range(pl, pr);
}

void filp(int x) {
    if (!state[x]) {
        state[x] = true;
        las[x] = cur + 1;
    } else {
        state[x] = false;

        if (las[x] <= cur) {
            Range rg = find(las[x], cur - las[x] + 1);
            now[x] = merge(now[x], rg, len[x]);
            len[x] += cur - las[x] + 1;
        }

        las[x] = cur + 1;
    }
}

int query(int x) {
    filp(x);
    filp(x);

    if (now[x].empty() || len[x] == 0)
        return 0;

    return sum[now[x].r] - sum[now[x].l - 1];
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("operator.in", "r", stdin);
    freopen("operator.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> n >> m >> q;
    cin >> (s + 1);

    for (int i = 1; i <= n; ++i)
        sa.push(s[i]);

    sa.push('#');
    tot = n + 1;

    for (int i = 1; i <= q; ++i) {
        auto & [type, x, c] = op[i];
        cin >> type;

        if (type == 2) {
            cin >> c;
            ++tot;
            t[tot - n - 1] = c;
            sa.push(c);
        } else {
            cin >> x;
        }
    }

    sa.preprocess();
    st.preprocess(sa.height, sa.n);

    for (int i = 1; i <= n; ++i)
        ++sum[sa.rk[i]];

    for (int i = 1; i <= sa.n; ++i)
        sum[i] += sum[i - 1];

    for (int i = 1; i <= m; ++i) {
        now[i] = Range(1, sa.n);
        las[i] = 1;
    }

    for (int i = 1; i <= q; ++i) {
        auto [type, x, c] = op[i];

        if (type == 1)
            filp(x);
        else if (type == 2)
            ++cur;
        else
            cout << query(x) << endl;
    }

    return 0;
}
