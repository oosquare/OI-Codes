#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 500 + 10;

int n, k, p, f[maxn][maxn * 2];
int x[maxn * 2], y[maxn * 2];

int power(int x, int y) {
    int res = 1;
    while (y) {
        if (y % 2)
            res = 1LL * res * x % p;
        x = 1LL * x * x % p;
        y /= 2;
    }
    return res % p;
}

int inv(int x) {
    return power(x, p - 2);
}

int lagrange(int k) {//求答案
	for (int i = 0; i <= 2 * n; ++i) {
		x[i] = i;
		y[i] = f[n][i];
	}
    int ans = 0;
    for (int i = 0; i <= 2 * n; ++i) {
        int num = 1, den = 1;
        for (int j = 0; j <= 2 * n; ++j) {
            if (i == j)
                continue;
            num = 1LL * num * (k - x[j] + p) % p;
            den = 1LL * den * (x[i] - x[j] + p) % p;
        }
        ans = (1LL * ans + 1LL * y[i] * num % p * inv(den) % p) % p;
    }
    for (int i = 1; i <= n; ++i)
    	ans = 1LL * ans * i % p;//要记得乘n!
    return (ans + p) % p;
}
//DP求f[n][0]~f[n][2n]
void DP() {
    for (int i = 0; i <= 2 * n; ++i)
        f[0][i] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= 2 * n; ++j)
            f[i][j] = (f[i][j - 1] + 1LL * j * f[i - 1][j - 1]) % p;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("project.in", "r", stdin);
	freopen("project.out", "w", stdout);
#endif
    cin >> k >> n >> p;
    DP();
    cout << lagrange(k % p) << endl;
    return 0;
}