#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
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
void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static int stk[100];
    int top = 0;
    while (x) {
        stk[++top] = x % 10;
        x /= 10;
    }
    while (top) 
        putchar(stk[top--] + '0');
}

typedef __int128 ll;

ll n, m, l, x, y;

ll power(ll x, ll k, ll mod) {
    ll res = 1;
    while (k) {
        if (k % 2)
            res = res * x % mod;
        x = x * x % mod;
        k /= 2;
    }
    return res;
}

ll exGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return 1;
    } else {
        int d = exGCD(b, a % b, x, y);
        int t = x;
        x = y;
        y = t - a / b * y;
        return d;
    }
}

bool solve(ll a, ll b, ll c, ll &x, ll &y) {
    ll d = exGCD(a, b, x, y);
    if (c % d)
        return false;
    ll k = c / d;
    x *= k;
    return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    bool res;
    n = read<ll>();
    m = read<ll>();
    l = read<ll>();
    res = solve(power(2, m, n + 1), n + 1, l, x, y);
    if (res)
        write((x % (n + 1) + (n + 1)) % (n + 1));
    return 0;
}