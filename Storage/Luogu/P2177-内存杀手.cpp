#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 300 + 10;
constexpr int mod = 998244353;
constexpr int base1 = 258 + 1e9 + 7;
constexpr int base2 = 97 + 1e9 + 9;

using ll = long long;

int n, m;
ll mat[2][maxn][maxn], h[2][maxn][maxn], power1[maxn], power2[maxn];
char tmp[maxn];

int calc(int w, int x1, int y1, int x2, int y2) {
    ll res = h[w][x2][y2] -
             h[w][x1 - 1][y2] * power1[x2 - x1 + 1] % mod -
             h[w][x2][y1 - 1] * power2[y2 - y1 + 1] % mod +
             h[w][x1 - 1][y1 - 1] * power1[x2 - x1 + 1] % mod * power2[y2 - y1 + 1] % mod;
    return (res + mod) % mod;
}

bool check(int x, int y, int a) {
    int r = (a + 1) / 2;
    if (a % 2) {
        int x1 = x - r + 1, y1 = y - r + 1;
        int x2 = x + r - 1, y2 = y + r - 1;
        int rx1 = n - x1 + 1, ry1 = m - y1 + 1;
        int rx2 = n - x2 + 1, ry2 = m - y2 + 1;
        // printf("x = %d, y = %d, a = %d, r = %d\n", x, y, a, r);
        // printf("x1 = %d, y1 = %d, x2 = %d, y2 = %d\n", x1, y1, x2, y2);
        // printf("rx1 = %d, ry1 = %d, rx2 = %d, ry2 = %d\n", rx1, ry1, rx2, ry2);
        // printf("calc1 = %d, calc2 = %d\n", calc(0, x1, y1, x2, y2), calc(1, rx2, ry2, rx1, ry1));
        // printf("\n");
        return calc(0, x1, y1, x2, y2) == calc(1, rx2, ry2, rx1, ry1);
    } else {
        int x1 = x - r + 1, y1 = y - r + 1;
        int x2 = x + r, y2 = y + r;
        int rx1 = n - x1 + 1, ry1 = m - y1 + 1;
        int rx2 = n - x2 + 1, ry2 = m - y2 + 1;
        // printf("x = %d, y = %d, a = %d, r = %d\n", x, y, a, r);
        // printf("x1 = %d, y1 = %d, x2 = %d, y2 = %d\n", x1, y1, x2, y2);
        // printf("rx1 = %d, ry1 = %d, rx2 = %d, ry2 = %d\n", rx1, ry1, rx2, ry2);
        // printf("calc1 = %d, calc2 = %d\n", calc(0, x1, y1, x2, y2), calc(1, rx2, ry2, rx1, ry1));
        // printf("\n");
        return calc(0, x1, y1, x2, y2) == calc(1, rx2, ry2, rx1, ry1);        
    }
}

bool check(int a) {
    int r = (a + 1) / 2;
    if (a % 2) {
        for (int i = r; i + r - 1 <= n; ++i)
            for (int j = r; j + r - 1 <= m; ++j)
                if (check(i, j, a))
                    return true;
        return false;
    } else {
        for (int i = r; i + r <= n; ++i)
            for (int j = r; j + r <= m; ++j)
                if (check(i, j, a))
                    return true;
        return false;
    }
}

void preprocess() {
    power1[0] = power2[0] = 1;
    for (int i = 1; i <= max(n, m); ++i) {
        power1[i] = power1[i - 1] * base1 % mod;
        power2[i] = power2[i - 1] * base2 % mod;
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            h[0][i][j] = (h[0][i][j - 1] * base2 + mat[0][i][j]) % mod;
            h[1][i][j] = (h[1][i][j - 1] * base2 + mat[1][i][j]) % mod;            
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            h[0][i][j] = (h[0][i - 1][j] * base1 + h[0][i][j]) % mod;
            h[1][i][j] = (h[1][i - 1][j] * base1 + h[1][i][j]) % mod;
        }
    }
}

void divide() {
    int l = 1, r = min(n, m) / 2 + 1, ans1 = -1, ans2 = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid * 2)) {
            ans1 = mid * 2;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    l = 1, r = min(n, m) / 2 + 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid * 2 + 1)) {
            ans2 = mid * 2 + 1;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << max(ans1, ans2) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> (tmp + 1);
        for (int j = 1; j <= m; ++j) {
            mat[0][i][j] = tmp[j] - '0';
            mat[1][n - i + 1][m - j + 1] = tmp[j] - '0';
        }
    }
    preprocess();
    divide();
    return 0;
}