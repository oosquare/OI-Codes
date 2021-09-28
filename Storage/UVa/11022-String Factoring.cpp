#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 80 + 10;

int n, pi[maxn][maxn], f[maxn][maxn];
char str[maxn];

void preprocess() {
    memset(pi, 0, sizeof(pi));
    n = strlen(str + 1);
    for (int s = 1; s <= n; ++s) {
        int j = 0;
        for (int i = 2; i + s - 1 <= n; ++i) {
            while (j && str[i + s - 1] != str[j + s])
                j = pi[s][j];
            if (str[i + s - 1] == str[j + s])
                ++j;
            pi[s][i] = j;
        }
    }
}

int get(int l, int r) {
    int len = r - l + 1;
    if (len % (len - pi[l][len]) == 0)
        return len - pi[l][len];
    else
        return len;
}

int solve() {
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            f[i][j] = get(i, j);
        }
    }
    for (int l = 1; l <= n; ++l) {
        for (int i = 1, j = l; j <= n; ++i, ++j) {
            for (int k = i; k < j; ++k) {
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
            }
            int t = get(i, j);
            if (t != (j - i + 1)) {
                f[i][j] = min(f[i][j], f[i][i + t - 1]);
            }

        }
    }
    return f[1][n];
}

int main() {
    ios::sync_with_stdio(false);
    while (true) {
        cin >> (str + 1);
        if (str[1] == '*')
            break;
        preprocess();
        cout << solve() << endl;
    }
    return 0;
}