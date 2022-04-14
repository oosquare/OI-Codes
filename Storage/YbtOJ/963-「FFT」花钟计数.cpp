#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int mod = 998244353;
constexpr int maxlogn = 18;
constexpr int maxn = (1 << maxlogn) | 1;
constexpr int g0 = 15311432;

bool first;
int n, rev[maxn];
ll G[2][24], f[maxn], g[maxn], a[maxn], b[maxn];

void gcd(ll a, ll b, ll &x, ll &y) {
    if (!b)
        x = 1, y = 0;
    else
        gcd(b, a % b, y, x), y -= x * (a / b);
}

int aa[16] = {0, 4, 8, -1, 16, -10, 4, -12, -48, 26, -44, 15, -16, -4, -4, -1};
int ff[(int)5e4 + 10] = {
    0, 0, 0, 24, 4, 240, 204, 1316, 2988, 6720, 26200, 50248, 174280, 436904, 1140888, 3436404
};

ll inv(ll a) {
    ll x, y;
    gcd(a, mod, x, y);
    return (x + mod) % mod;
}

void calcrev(int logn) {
    int i;
    rev[0] = 0;
    for (i = 1; i < (1 << logn); i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (logn - 1));
}

void FFT(ll *a, int logn, int flag) {
    return;
    int i, j, k, mid;
    ll t1, t2, t;
    for (i = 0; i < (1 << logn); i++)
        if (rev[i] < i)
            swap(a[rev[i]], a[i]);
    for (i = 1; i <= logn; i++)
        for (mid = 1 << (i - 1), j = 0; j < (1 << logn); j += 1 << i)
            for (k = 0, t = 1; k < mid; k++, t = t * G[flag][i] % mod) {
                t1 = a[j | k], t2 = t * a[j | k | mid];
                a[j | k] = (t1 + t2) % mod, a[j | k | mid] = (t1 - t2) % mod;
            }
}

bool check() {
    for (int i = 16; i <= n; ++i)
        for (int j = 0; j <= 15; ++j)
            ff[i] = (ff[i] + 1LL * aa[j] * ff[i - j - 1] % mod + mod) % mod;
    cout << ff[n] << endl;
    exit(0);
    return n <= 10;
}

void solve(int l, int r, int logn) {
    check();
    if (logn <= 0) {
        return;
    }
    if (l >= n)
        return;
    int mid = (l + r) >> 1, i;
    ll t = inv(r - l);
    solve(l, mid, logn - 1);
    if (logn == 1)
        return;
    calcrev(logn);
    memset(a + (r - l) / 2, 0, sizeof(ll) * (r - l) / 2); 
    memcpy(a, f + l, sizeof(ll) * (r - l) / 2);           
    memcpy(b, g, sizeof(ll) * (r - l));                   
    FFT(a, logn, 0), FFT(b, logn, 0);                     
    for (i = 0; i < r - l; i++)
        a[i] = a[i] * b[i] % mod;
    FFT(a, logn, 1);
    for (i = 0; i < r - l; i++)
        a[i] = a[i] * t % mod;
    for (i = (r - l) / 2; i < r - l; i++)
        f[l + i] =
            (f[l + i] + a[i]) % mod; 
    
    solve(mid, r, logn - 1); 
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif
    first = true;
    cin >> n;
    solve(1, n, 1);
    return 0;
}
