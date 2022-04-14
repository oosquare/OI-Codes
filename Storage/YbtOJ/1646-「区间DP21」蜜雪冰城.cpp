#include <bits/stdc++.h>
using namespace std;

namespace IO {

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
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

template <typename T = int> void writeln(T x) {
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

template <typename T = int> void writesp(T x) {
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
    putchar(' ');
}

template <typename T = int> void write(T x, char blank[]) {
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
    for (int i = 0; blank[i] != '\0'; ++i)
        putchar(blank[i]);
}

} // namespace IO

constexpr int maxn = 50 + 5;
constexpr int maxm = 4000 + 5;

int n, m, a[maxm], b[maxm], c[maxm], cnt[maxm];
vector<int> val;
int f[maxn][maxn][maxm], maxf[maxn][maxn][maxm], from[maxn][maxn][maxm], frompos[maxn][maxn][maxm];

void update(int l, int r, int mid) {
    for (int i = 1; i <= val.size(); ++i)
        cnt[i] = 0;
    for (int i = 1; i <= m; ++i)
        if (l <= a[i] && b[i] <= r && a[i] <= mid && mid <= b[i])
            ++cnt[c[i]];
}

void DFS(int l, int r, int pos) {
    using namespace IO;
    int fr = from[l][r][pos];
    if (l <= fr - 1)
        DFS(l, fr - 1, frompos[l][fr - 1][pos]);
    writesp(val[pos - 1]);
    if (fr + 1 <= r)
        DFS(fr + 1, r, frompos[fr + 1][r][pos]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("baddream.in", "r", stdin);
    freopen("baddream.out", "w", stdout);
#endif
    using namespace IO;
    n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        a[i] = read(), b[i] = read(), c[i] = read();
        val.push_back(c[i]);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 1; i <= m; ++i)
        c[i] = lower_bound(val.begin(), val.end(), c[i]) - val.begin() + 1;
    for (int i = n; i >= 1; --i) {
        for (int j = i; j <= n; ++j) {
            for (int k = i; k <= j; ++k) {
                update(i, j, k);
                int sum = 0;
                for (int l = val.size(); l >= 1; --l) {
                    sum += cnt[l];
                    int newans = sum * val[l - 1] + maxf[i][k - 1][l] + maxf[k + 1][j][l];
                    if (newans > f[i][j][l] || !f[i][j][l]) {
                        f[i][j][l] = newans;
                        from[i][j][l] = k;
                    }
                }
            }
            for (int k = val.size(); k >= 1; --k) {
                if (f[i][j][k] > maxf[i][j][k + 1] || !maxf[i][j][k + 1]) {
                    maxf[i][j][k] = f[i][j][k];
                    frompos[i][j][k] = k;
                } else {
                    maxf[i][j][k] = maxf[i][j][k + 1];
                    frompos[i][j][k] = frompos[i][j][k + 1];
                }
            }
        }
    }
    writeln(maxf[1][n][1]);
    DFS(1, n, frompos[1][n][1]);
    return 0;
}
