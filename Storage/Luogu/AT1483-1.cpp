#include <bits/stdc++.h>
#define re register
#define maxn 14

typedef long long ll;

ll dp[maxn][10][10];
ll L, R;
ll ans[10][2];
int a[maxn], num;

inline ll quick(ll a, ll b) {
    ll s = 1;
    while (b) {
        if (b & 1)
            s *= a;
        b >>= 1;
        a *= a;
    }
    return s;
}

inline void solve(ll x, int pd) {
    memset(dp, 0, sizeof(dp));
    num = 0;
    memset(a, 0, sizeof(a));
    while (x) {
        a[++num] = x % 10;
        x /= 10;
    }
    for (re int i = 0; i <= 9; i++)
        dp[1][i][i] = 1;
    for (re int i = 2; i <= num; i++)
        for (int j = 0; j <= 9; j++) {
            for (re int k = 0; k <= 9; k++) {
                for (re int p = 0; p <= 9; p++)
                    dp[i][j][p] += dp[i - 1][k][p];
            }
            dp[i][j][j] += quick(10, i - 1);
        }
    for (re int i = 1; i < num; i++)
        for (re int j = 1; j <= 9; j++)
            for (re int k = 0; k <= 9; k++)
                ans[k][pd] += dp[i][j][k];
    for (re int i = 1; i < a[num]; i++)
        for (re int k = 0; k <= 9; k++)
            ans[k][pd] += dp[num][i][k];
    for (re int i = num - 1; i >= 1; i--) {
        for (re int j = 0; j < a[i]; j++) {
            for (re int k = 0; k <= 9; k++)
                ans[k][pd] += dp[i][j][k];
        }
        for (re int p = num; p > i; p--)
            ans[a[p]][pd] += a[i] * quick(10, i - 1);
    }
}

int main() {
    scanf("%lld", &R);
    solve(R + 1, 0), solve(1, 1);
    printf("%lld\n", ans[1][0] - ans[1][1]);
    return 0;
}