#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>

using namespace std;

constexpr int maxn = 2e5 + 10;

struct Frame {
    int pos, val, cnt;
};

class SparseTable {
public:
    void preprocess(int a[], int n) {
        logv[0] = -1;

        for (int i = 1; i <= n; ++i) {
            logv[i] = logv[i / 2] + 1;
            data[i][0] = a[i];
        }

        for (int j = 1; j <= 19; ++j)
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
                data[i][j] = min(data[i][j - 1], data[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        int s = logv[r - l + 1];
        return min(data[l][s], data[r - (1 << s) + 1][s]);
    }

private:
    int logv[maxn], data[maxn][20];
};

int n, q, k, l, s1[maxn], s2[maxn];
char str[maxn];
int sa[maxn * 2], buf[2][maxn * 2], *rk = buf[0], *old = buf[1], height[maxn];
int id[maxn * 2], cnt[maxn * 2], tmp[maxn * 2];
SparseTable mi;
Frame st[maxn];
int top;
int buc[maxn];
long long sum, ans;

bool equal(int x, int y, int w) {
    return (old[x] == old[y] && old[x + w] == old[y + w]);
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

void push(Frame frame, int lst) {
    while (top && st[top].val >= frame.val) {
        sum -= 1ll * st[top].val * st[top].cnt;
        frame.cnt += st[top].cnt;
        --top;
    }

    sum += 1ll * frame.val * frame.cnt;
    st[++top] = frame;
}

int lcp(int x, int y) {
    return (x == y ? n - sa[x] + 1 : mi.query(x + 1, y));
}

void solve() {
    sum = ans = 0;
    top = 0;

    for (int i = 1; i <= l; ++i)
        ++buc[s2[i]];

    for (int i = 1; i <= k; ++i)
        ans += 1ll * buc[s1[i]] * (n - sa[s1[i]] + 1);

    for (int i = 1; i <= l; ++i)
        --buc[s2[i]];

    int lst = 0;

    for (int i = 1, j = 0; i <= k; ++i) {
        while (j < l && s2[j + 1] < s1[i]) {
            ++j;
            Frame frame = {s2[j], lcp(st[top].pos, s2[j]), lst};
            push(frame, lst);
            lst = 1;
        }

        Frame frame = {s1[i], lcp(st[top].pos, s1[i]), lst};
        push(frame, lst);
        lst = 0;
        ans += sum;
    }

    sum = 0;
    top = 0;
    lst = 0;

    for (int i = k, j = l + 1; i >= 1; --i) {
        while (j > 1 && s2[j - 1] > s1[i]) {
            --j;
            Frame frame = {s2[j], lcp(s2[j], st[top].pos), lst};
            push(frame, lst);
            lst = 1;
        }

        Frame frame = {s1[i], lcp(s1[i], st[top].pos), lst};
        push(frame, lst);
        lst = 0;
        ans += sum;
    }

    cout << ans << endl;
}

void debug() {
    for (int i = 1; i <= n; ++i) {
        cout << setw(8) << left <<  "id = " + to_string(i);
        cout << setw(8) << left << "sa = "s + to_string(sa[i]);
        cout << setw(11) << left << "height = "s + to_string(height[i]);

        for (int j = sa[i]; j <= n; ++j)
            if (str[j] < 127)
                cout << (char)str[j];
            else
                cout << str[j] - 127;

        cout << endl;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    cin >> (str + 1);
    preprocess();
    mi.preprocess(height, n + 1);

    for (int i = 1; i <= q; ++i) {
        cin >> k >> l;

        for (int j = 1; j <= k; ++j) {
            int a;
            cin >> a;
            s1[j] = rk[a];
        }

        for (int j = 1; j <= l; ++j) {
            int a;
            cin >> a;
            s2[j] = rk[a];
        }

        sort(s1 + 1, s1 + 1 + k);
        sort(s2 + 1, s2 + 1 + l);

        solve();
    }

    return 0;
}