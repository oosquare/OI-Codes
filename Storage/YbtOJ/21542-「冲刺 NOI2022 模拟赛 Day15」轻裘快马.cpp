#include <iostream>
#include <algorithm>

namespace IO {

    inline char mygetchar() {
        static char ff[100000], *A = ff, *B = ff;
        return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B) ? EOF : *A++;
    }

    template <typename T = int>
    T read() {
        T x = 0, s = 1;
        char c = mygetchar();
        while (c < '0' || '9' < c) {
            if (c == '-')
                s = -1;
            c = mygetchar();
        }
        while ('0' <= c && c <= '9') {
            x = (x << 1) + (x << 3) + (c ^ 48);
            c = mygetchar();
        }
        return x * s;
    }

    template <typename T = int>
    void writeln(T x) {
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        static int stk[100];
        int top = 0;
        if (x == 0)
            stk[++top] = 0;
        while (x) {
            stk[++top] = x % 10;
            x /= 10;
        }
        while (top)
            putchar(stk[top--] + '0');
        putchar('\n');
    }

} // namespace IO

constexpr int MAX_N = 100000 + 10;
constexpr int MAX_K = 20 + 1;

class SparseTable {
public:
    int arr[MAX_N], mx[MAX_N][18], logv[MAX_N];

    void init(int len) {
        logv[0] = -1;

        for (int i = 1; i <= len; ++i) {
            mx[i][0] = arr[i];
            logv[i] = logv[i / 2] + 1;
        }

        for (int j = 1; j <= 17; ++j)
            for (int i = 1; i + (1 << j) - 1 <= len; ++i)
                mx[i][j] = std::max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        int s = logv[r - l + 1];
        return std::max(mx[l][s], mx[r - (1 << s) + 1][s]);
    }
};

int n, k, q;
int g[MAX_N][MAX_K];
int p[MAX_N], fa[MAX_N];
SparseTable st[MAX_K];

int find(int x) { return (x == fa[x] ? x : fa[x] = find(fa[x])); }

bool check(int idx, int last) {
    for (int i = 1; i <= k; ++i)
        if (st[i].query(idx + 1, last) > g[idx][i])
            return true;

    return false;
}

int get(int idx) {
    int ans = n + 1;
    int l = idx + 1, r = n;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (check(idx, mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return ans;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("gift.in", "r", stdin);
    std::freopen("gift.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), k = read();

    for (int i = 1; i <= n; ++i)
        p[i] = read();

    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= n; ++j)
            st[i].arr[j] = -0x3f3f3f3f;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j)
            g[i][j] = read();

        st[p[i]].arr[i] = g[i][p[i]];
    }

    for (int i = 1; i <= k; ++i)
        st[i].init(n);

    for (int i = 1; i <= n; ++i) {
        fa[i] = get(i);

        if (fa[i] == n + 1)
            fa[i] = i;
    }

    q = read();

    while (q--) {
        for (int i = 1; i <= k; ++i)
            g[0][i] = read();

        int p = get(0);

        if (p == n + 1)
            writeln(0);
        else
            writeln(find(p));
    }

    return 0;
}
