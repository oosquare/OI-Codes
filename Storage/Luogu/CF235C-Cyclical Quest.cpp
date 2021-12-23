#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <unordered_set>

using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxl = 3e6 + 10;
constexpr int oo = 0x3f3f3f3f;
constexpr int base = 97;

class SparseTable {
public:
    void preprocess(int a[], int n) {
        logv[0] = -1;

        for (int i = 1; i <= n; ++i) {
            logv[i] = logv[i / 2] + 1;
            data[i][0] = a[i];
        }

        for (int j = 1; j <= 21; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                data[i][j] = min(data[i][j - 1], data[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        if (l > r)
            return oo;

        int s = logv[r - l + 1];
        return min(data[l][s], data[r - (1 << s) + 1][s]);
    }
private:
    int data[maxl][22], logv[maxl];
};

int n, len[maxn], start[maxn], tlen;
char sbuf[maxl];
int str[maxl], col[maxl];
int sa[maxl], rk[maxl], height[maxl];
bool t[maxl * 2];
SparseTable mh;
int buc[maxl], sum[maxl], ans[maxn];
unordered_set<unsigned> st;
unsigned power[maxl], val[maxl];

inline bool islms(int i, bool *t) {
    return i > 0 && t[i] && !t[i - 1];
}

template <typename T> void sort(T s, int *sa, int len, int sigma, int sz, bool *t, int *b, int *cb, int *p) {
    memset(b, 0, sizeof(int) * sigma);
    memset(sa, -1, sizeof(int) * len);

    for (int i = 0; i < len; i++)
        b[s[i]]++;

    cb[0] = b[0];

    for (int i = 1; i < sigma; i++)
        cb[i] = cb[i - 1] + b[i];

    for (int i = sz - 1; i >= 0; i--)
        sa[--cb[s[p[i]]]] = p[i];

    for (int i = 1; i < sigma; i++)
        cb[i] = cb[i - 1] + b[i - 1];

    for (int i = 0; i < len; i++)
        if (sa[i] > 0 && !t[sa[i] - 1])
            sa[cb[s[sa[i] - 1]]++] = sa[i] - 1;

    cb[0] = b[0];

    for (int i = 1; i < sigma; i++)
        cb[i] = cb[i - 1] + b[i];

    for (int i = len - 1; i >= 0; i--)
        if (sa[i] > 0 && t[sa[i] - 1])
            sa[--cb[s[sa[i] - 1]]] = sa[i] - 1;
}

template <typename T> void sais(T s, int *sa, int len, bool *t, int *b, int *b1, int sigma) {
    int i, j, x, p = -1, cnt = 0, sz = 0, *cb = b + sigma;

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

    int *s1 = sa + len - sz, *b2 = b1 + sz;

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

        while (str[i + j] == str[sa[rk[i] - 1] + j])
            ++j;

        height[rk[i]] = j;
    }
}

int calc(int p, int len) {
    int l = 1, r = p - 1, pos = -1, res = 0;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (mh.query(mid + 1, p) >= len) {
            pos = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (pos != -1)
        res += sum[p] - sum[pos - 1];

    l = p + 1, r = tlen, pos = -1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (mh.query(p + 1, mid) >= len) {
            pos = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (pos != -1)
        res += sum[pos] - sum[p];

    return res;
}

void solve(int id) {
    for (int i = 1; i < len[id]; ++i)
        val[i] = val[i - 1] * base + str[start[id] + i - 1] - 'a';

    st.clear();

    for (int i = len[id]; i < 2 * len[id]; ++i) {
        val[i] = val[i - 1] * base + str[start[id] + i - 1] - 'a';
        unsigned tmp = val[i] - val[i - len[id]] * power[len[id]];

        if (st.find(tmp) == st.end()) {
            st.insert(tmp);
            ans[id] += buc[start[id] + i - len[id]];
        }
    }
}

void input() {
    scanf("%s", sbuf + 1);
    start[0] = 1;
    len[0] = strlen(sbuf + 1);

    for (int i = 1; i <= len[0]; ++i)
        str[++tlen] = sbuf[i];

    scanf("%d", &n);
    str[++tlen] = 127 + 0;
    col[tlen] = n + 1;

    for (int i = 1; i <= n; ++i) {
        start[i] = tlen + 1;
        scanf("%s", sbuf + 1);
        len[i] = strlen(sbuf + 1);

        for (int j = 1; j <= len[i]; ++j)
            str[++tlen] = sbuf[j];

        for (int j = 1; j < len[i]; ++j)
            str[++tlen] = sbuf[j];

        for (int j = start[i]; j <= tlen; ++j)
            col[j] = i;

        str[++tlen] = 127 + i;
        col[tlen] = n + 1;
    }
}

void debug() {
    for (int i = 1; i <= tlen; ++i) {
        cout << setw(8) << left <<  "id = " + to_string(i);
        cout << setw(8) << left << "sa = "s + to_string(sa[i]);
        cout << setw(11) << left << "height = "s + to_string(height[i]);
        cout << setw(8) << left << "col = "s + to_string(col[sa[i]]);

        for (int j = sa[i]; j <= tlen; ++j)
            if (str[j] < 127)
                cout << (char)str[j];
            else
                cout << str[j] - 127;

        cout << endl;
    }
}

int main() {
    power[0] = 1;

    for (int i = 1; i <= 1000000; ++i)
        power[i] = power[i - 1] * base;

    input();
    preprocess(str, tlen, 128 + n);
    mh.preprocess(height, tlen);

    for (int i = 1; i <= tlen; ++i)
        sum[i] = sum[i - 1] + (col[sa[i]] == 0);

    for (int i = 1; i <= tlen; ++i)
        if (col[sa[i]] != 0)
            buc[sa[i]] = calc(i, len[col[sa[i]]]);

    for (int i = 1; i <= n; ++i)
        solve(i);

    for (int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);

    return 0;
}