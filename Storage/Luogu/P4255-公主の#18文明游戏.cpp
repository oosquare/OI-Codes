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

constexpr int maxn = 400000 + 10;
constexpr int mod = 19260817;
constexpr int maxv = 1e6 + 10;

using MapType = unordered_map<int, int>;

struct Operation {
    int type, x, n, c;
};

int n, m, q;
int edges[maxn][2];
int fa[maxn], sze[maxn];
int fac[maxv], inv[maxv];
Operation op[maxn];
MapType s[maxn];
bool linked[maxn];
vector<int> ans;

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(MapType &lhs, MapType &rhs) {
    if (lhs.size() < rhs.size())
        swap(lhs, rhs);

    for (auto [k, v] : rhs)
        lhs[k] += v;

    rhs.clear();
} 

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    
    if (fx == fy)
        return;

    merge(s[fx], s[fy]);
    fa[fy] = fx;
    sze[fx] += sze[fy];
}

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = 1ll * res * x % mod;

        x = 1ll * x * x % mod;
    }

    return res;
}

void preprocess() {
    fac[0] = 1;
    
    for (int i = 1; i < maxv; ++i)
        fac[i] = 1ll * fac[i - 1] * i % mod;

    inv[maxv - 1] = power(fac[maxv - 1], mod - 2);

    for (int i = maxv - 2; i >= 0; --i)
        inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;
}

int comb(int n, int m) {
    if (n < m)
        return 0;

    return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int inve(int x) {
    return power(x, mod - 2);
}

int main() {
    using namespace IO;
    n = read(), m = read(), q = read();

    for (int i = 1; i <= n; ++i) {
        int x = read(), y = read();
        fa[i] = i;
        sze[i] = x;
        s[i][y] += x;
    }

    for (int i = 1; i <= m; ++i) {
        edges[i][0] = read(), edges[i][1] = read();
        linked[i] = true;
    }

    for (int i = 1; i <= q; ++i) {
        auto &[t, x, n, c] = op[i];
        t = read();

        if (t == 1) {
            x = read(), n = read(), c = read();
            s[x][c] += n;
            sze[x] += n;
        } else if (t == 2) {
            x = read();
            linked[x] = false;
        } else {
            x = read(), n = read(), c = read();
        }
    }

    for (int i = 1; i <= m; ++i)
        if (linked[i])
            merge(edges[i][0], edges[i][1]);

    preprocess();

    for (int i = q; i >= 1; --i) {
        auto [t, x, n, c] = op[i];

        if (t == 1) {
            s[find(x)][c] -= n;
            sze[find(x)] -= n;
        } else if (t == 2) {
            linked[x] = true;
            merge(edges[x][0], edges[x][1]);
        } else {
            int cnt1 = sze[find(x)];
            int cnt2 = s[find(x)][c];
            ans.push_back(1ll * comb(cnt2, n) * inve(comb(cnt1, n)) % mod);
        }
    }

    for (int i = ans.size() - 1; i >= 0; --i)
        writeln(ans[i]);

    return 0;
}