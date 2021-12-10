#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = getchar();

    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            s = -1;

    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';

    return x * s;
}

template <typename T> void write(T x, char sep = '\n') {
    if (x == 0) {
        putchar(x);
        putchar(sep);
        return;
    }

    static int st[50];
    int top = 0;

    if (x < 0) {
        putchar('-');
        x = -x;
    }

    while (x) {
        st[++top] = x % 10;
        x /= 10;
    }

    while (top)
        putchar(st[top--] + '0');

    putchar(sep);
}

constexpr int maxv = 300 + 10;
constexpr int maxn = 4e5 + 10;
constexpr int mod = 1e9 + 7;

int n, q;
bool notprime[maxv];
int tot, prime[maxv], inv[maxv];
long long a[maxn], tmp[maxn];
int cnt0[65][maxn];

int power(int x, int y) {
    int res = 1;

    for (; y; y >>= 1) {
        if (y & 1)
            res = 1ll * res * x % mod;

        x = 1ll * x * x % mod;
    }

    return res;
}

void preprocess(int n) {
    notprime[0] = notprime[1] = true;

    for (int i = 2; i <= n; ++i) {
        if (!notprime[i])
            prime[++tot] = i;

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notprime[i * prime[j]] = true;

            if (i % prime[j] == 0)
                break;
        }
    }

    for (int i = 1; i <= tot; ++i)
        inv[i] = power(prime[i], mod - 2);
}

class SegmentTree {
public:
    void build(int n, long long a[]) {
        build(1, 1, n, a);
    }

    void assign(int l, int r, long long v) {
        assign(1, l, r, v);
    }

    void multiply(int l, int r, int v) {
        multiply(1, l, r, v);
    }

    long long queryExist(int l, int r) {
        return queryExist(1, l, r);
    }

    int queryProd(int l, int r) {
        return queryProd(1, l, r);
    }
private:
    struct Node {
        int left, right;
        int prod, mul;
        long long exist, assign;

        int length() {
            return right - left + 1;
        }
    };

    Node tree[maxn * 4];

    void pushup(int x) {
        tree[x].exist = (tree[x * 2].exist | tree[x * 2 + 1].exist);
        tree[x].prod = (1ll * tree[x * 2].prod * tree[x * 2 + 1].prod) % mod;
    }

    void updateAssign(int x, long long v) {
        tree[x].assign |= v;
        tree[x].exist |= v;
    }

    void updateMul(int x, int v) {
        tree[x].mul = 1ll * tree[x].mul * v % mod;
        tree[x].prod = 1ll * tree[x].prod * power(v, tree[x].length()) % mod;
    }

    void pushdown(int x) {
        if (tree[x].mul != 1) {
            updateMul(x * 2, tree[x].mul);
            updateMul(x * 2 + 1, tree[x].mul);
            tree[x].mul = 1;
        }

        if (tree[x].assign != 0) {
            updateAssign(x * 2, tree[x].assign);
            updateAssign(x * 2 + 1, tree[x].assign);
            tree[x].assign = 0;
        }
    }

    void build(int x, int l, int r, long long a[]) {
        tree[x].left = l;
        tree[x].right = r;
        tree[x].mul = 1;

        if (l == r) {
            tree[x].prod = a[l];
            tree[x].exist = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(x * 2, l, mid, a);
        build(x * 2 + 1, mid + 1, r, a);
        pushup(x);
    }

    void assign(int x, int l, int r, long long v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            updateAssign(x, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            assign(x * 2, l, r, v);

        if (mid < r)
            assign(x * 2 + 1, l, r, v);

        pushup(x);
    }

    void multiply(int x, int l, int r, int v) {
        if (l <= tree[x].left && tree[x].right <= r) {
            updateMul(x, v);
            return;
        }

        int mid = (tree[x].left + tree[x].right) / 2;
        pushdown(x);

        if (l <= mid)
            multiply(x * 2, l, r, v);

        if (mid < r)
            multiply(x * 2 + 1, l, r, v);

        pushup(x);
    }

    long long queryExist(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].exist;

        int mid = (tree[x].left + tree[x].right) / 2;
        long long res = 0;
        pushdown(x);

        if (l <= mid)
            res |= queryExist(x * 2, l, r);

        if (mid < r)
            res |= queryExist(x * 2 + 1, l, r);

        return res;
    }

    int queryProd(int x, int l, int r) {
        if (l <= tree[x].left && tree[x].right <= r)
            return tree[x].prod;

        int mid = (tree[x].left + tree[x].right) / 2, res = 1;
        pushdown(x);

        if (l <= mid)
            res = 1ll * res * queryProd(x * 2, l, r) % mod;

        if (mid < r)
            res = 1ll * res * queryProd(x * 2 + 1, l, r) % mod;

        return res;
    }
};

SegmentTree prod, cnt;

int calc(int l, int r) {
    int res = prod.queryProd(l, r);
    long long s = cnt.queryExist(l, r);

    for (int i = 1; i <= tot; ++i)
        if ((s >> (i - 1)) & 1)
            res = 1ll * res * inv[i] % mod * (prime[i] - 1) % mod;

    return res;
}

int main() {
    preprocess(300);
    

    n = read(), q = read();

    for (int i = 1; i <= n; ++i)
        a[i] = read();

    prod.build(n, a);

    for (int i = 1; i <= n; ++i) {
        int x = a[i];

        for (int j = 1; j <= tot; ++j) {
            if (x % prime[j])
                continue;

            tmp[i] |= (1ll << (j - 1));

            while (x % prime[j] == 0)
                x /= prime[j];
        }
    }

    cnt.build(n, tmp);

    for (int i = 1; i <= q; ++i) {
        char s[20];
        int l, r, x;
        scanf("%s", s);
        l = read(), r = read();

        if (s[0] == 'M') {
            x = read();
            prod.multiply(l, r, x);
            long long s = 0;

            for (int j = 1; j <= tot; ++j) {
                bool v = false;

                while (x % prime[j] == 0) {
                    x /= prime[j];
                    v = true;
                }

                if (v)
                    s |= (1ll << (j - 1));
            }
            
            cnt.assign(l, r, s);
        } else {
            write(calc(l, r));
        }
    }

    return 0;
}