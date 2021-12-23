#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr int maxn = 5e5 + 10;
constexpr int maxt = 3e6 + 10;
constexpr long long mod = 23333333333333333;
constexpr int oo = 0x3f3f3f3f;

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
        if (l > r)
            return oo;

        int s = logv[r - l + 1];
        return min(data[l][s], data[r - (1 << s) + 1][s]);
    }
private:
    int data[maxn][20], logv[maxn];
};

int n, m;
char str[maxn];
int t, seq[maxt];
int sa[maxn * 2], buf[2][maxn * 2], *rk = buf[0], *old = buf[1], height[maxn];
int cnt[maxn * 2], id[maxn * 2], tmp[maxn * 2];
Frame st[maxn];
SparseTable mi;
int top;
long long sum, ans;

bool equal(int x, int y, int w) {
    return old[x] == old[y] && old[x + w] == old[y + w];
}

void preprcoess() {
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

    height[n + 1] = 0;
}

void solve() {
    top = 0;
    sum = ans = 0;
    st[0] = {0, 0, 0};

    for (int i = 1; i <= t; ++i) {
        int p = seq[i];
        Frame frame = {p, mi.query(st[top].pos + 1, p), 1};

        while (top && st[top].val >= frame.val) {
            sum -= 1ll * st[top].val * st[top].cnt;
            frame.cnt += st[top].cnt;
            --top;
        }

        sum = sum + 1ll * frame.val * frame.cnt;
        st[++top] = frame;
        ans = (ans + sum) % mod;
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    cin >> (str + 1);
    preprcoess();
    mi.preprocess(height, n + 1);

    for (int i = 1; i <= m; ++i) {
        cin >> t;

        for (int j = 1; j <= t; ++j) {
            int a;
            cin >> a;
            seq[j] = rk[a];
        }

        if (t == 1) {
            cout << 0 << endl;
            continue;
        }

        sort(seq + 1, seq + 1 + t);

        t = unique(seq + 1, seq + 1 + t) - seq - 1;
        seq[t + 1] = n + 1;

        solve();
    }

    return 0;
}