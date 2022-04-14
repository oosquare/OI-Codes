#include <cstdio>
#include <algorithm>

template <typename T = int> T read() {
    T x = 0, s = 1;
    int c = std::getchar();

    for (; c < '0' || c > '9'; c = std::getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = std::getchar())
        x = x * 10 + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        std::putchar('0');
        std::putchar(sep);
        return;
    }

    static int st[50];
    int top = 0;

    if (x < 0) {
        std::putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        std::putchar(st[top--] + '0');

    std::putchar(sep);
}

constexpr int MOD = 1000000007;
constexpr int MAX_N = 100000 + 10;

struct Query {
    int n, m, a, id;

    bool operator<(const Query &rhs) const {
        return a < rhs.a;
    }
};

int mu[MAX_N], prime[MAX_N], notPrime[MAX_N];
int q, mx, tot;
Query qs[MAX_N];
int arr[MAX_N];
int ans[MAX_N];

inline int add(int x, int y) {
    x += y;
    return (x >= MOD ? x - MOD : x);
}

inline int sub(int x, int y) {
    x -= y;
    return (x < 0 ? x + MOD : x);
}

inline int lowbit(int x) { return x & (-x); }

void modify(int x, int y) {
    for (; x <= mx; x += lowbit(x))
        arr[x] = add(arr[x], y);
}

int query(int x) {
    int res = 0;

    for (; x; x -= lowbit(x))
        res = add(res, arr[x]);

    return res;
}

void preprocess(int n) {
    mu[1] = 1;
    notPrime[0] = notPrime[1] = true;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            mu[i] = -1;
        }

        for (int j = 1; j <= tot && 1ll * i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;
            mu[i * prime[j]] = i % prime[j] ? -mu[i] : 0;

            if (i % prime[j] == 0)
                break;
        }
    }
}

inline int square(int x, int y) {
    return (1ll * x * (x + 1) / 2 % MOD) * (1ll * y * (y + 1) / 2 % MOD) % MOD;
}

int calc(int n, int m) {
    int res = 0;

    if (n > m)
        std::swap(n, m);

    for (int l = 1, r; l <= n; l = r + 1) {
        r = std::min(n / (n / l), m / (m / l));
        res = add(res, 1ll * square(n / l, m / l) * sub(query(r), query(l - 1)) % MOD);
    }

    return res;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("sum.in", "r", stdin);
    std::freopen("sum.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    preprocess(MAX_N - 10);
    q = read();

    for (int i = 1; i <= q; ++i) {
        auto &[n, m, a, id] = qs[i];
        n = read();
        m = read();
        a = read();
        id = i;
        mx = std::max(mx, std::max(n, m));
    }

    std::sort(qs + 1, qs + 1 + q);

    for (int i = 1, now = 1; i <= q; ++i) {
        auto [n, m, a, id] = qs[i];

        for (; now <= a; ++now)
            for (int j = now; j <= mx; j += now)
                modify(j, (1ll * j * j / now % MOD * mu[j / now] % MOD + MOD) % MOD);

        ans[id] = calc(n, m);
    }

    for (int i = 1; i <= q; ++i)
        write(ans[i]);

    return 0;
}
