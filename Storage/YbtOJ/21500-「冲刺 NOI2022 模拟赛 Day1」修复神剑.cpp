#include <iostream>
using namespace std;

constexpr int MAX_N = 1e6 + 10;
constexpr int MOD = 1e9 + 7;

int n, v, b, d;
int pow2[MAX_N], fac[MAX_N], inv[MAX_N];
int ans;

int power(int x, int y) {
    int res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = (int) (1ll * res * x % MOD);
        
        x = (int) (1ll * x * x % MOD);
    }

    return res;
}

void preprocess(int n) {
    pow2[0] = 1;

    for (int i = 1; i <= n; ++i)
        pow2[i] = 2 * pow2[i - 1] % MOD;
    
    fac[0] = 1;
    
    for (int i = 1; i <= n; ++i)
        fac[i] = (int) (1ll * fac[i - 1] * i % MOD);
    
    inv[n] = power(fac[n], MOD - 2);

    for (int i = n - 1; i >= 0; --i)
        inv[i] = (int) (1ll * inv[i + 1] * (i + 1) % MOD);
}

int comb(int n, int m) {
    if (n < m)
        return 0;

    return (int) (1ll * fac[n] * inv[m] % MOD * inv[n - m] % MOD);
}

int calc(int lef, int b, int d, int even) {
    if (abs(b - d) % 2 != (lef - even) % 2)
        return 0;
    
    int bm = ((n - b) - (n - d) + lef - even) / 2;
    int dm = (lef - even - (n - b) + (n - d)) / 2;

    if (bm < 0 || dm < 0)
        return 0;
    
    int t = (n - b) + (n - d) - bm - dm - 2 * even;

    if (t < 0 || t % 2)
        return 0;
    // cout << lef << " " << even << " " << t << " " << dm << " : ";
    // cout << 1ll * comb(lef + t / 2 - 1, lef - 1)
    //     * comb(lef - even, bm) % MOD
    //     * comb(lef, even) % MOD
    //     * pow2[even] % MOD << endl;
    return (int) (1ll * comb(lef + t / 2 - 1, lef - 1)
        * comb(lef - even, bm) % MOD
        * comb(lef, even) % MOD
        * pow2[even] % MOD);
}

int calc(int lef, int b, int d) {
    int res = 0;
    
    for (int i = 0; i <= lef; ++i)
        res = (res + calc(lef, b, d, i)) % MOD;
    
    return res;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("blacksky.in", "r", stdin);
    freopen("blacksky.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    cin >> n >> v >> b >> d;
    preprocess(n);
    ans = (ans + (calc(n - v, b, d) + calc(n - v - 1, b, d)) % MOD) % MOD;
    ans = (ans + (calc(n - b, v, d) + calc(n - b - 1, v, d)) % MOD) % MOD;
    ans = (ans + (calc(n - d, v, b) + calc(n - d - 1, v, b)) % MOD) % MOD;
    cout << 2 * ans % MOD << endl;
    return 0;
}
