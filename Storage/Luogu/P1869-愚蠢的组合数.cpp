#include <bits/stdc++.h>
using namespace std;

int t, n, m;
int c[1010][1010];

void preprocess() {
    for (int i = 0; i <= 1000; ++i)
        c[i][0] = c[i][i] = 1;
    for (int i = 1; i <= 1000; ++i)
        for (int j = 1; j < i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % 2;
}

int comb(int n, int m) {
    if (n < m)
        return 0;
    if (n <= 1000 && m <= 1000)
        return c[n][m];
    return comb(n / 2, m / 2) * comb(n % 2, m % 2) % 2;
}

int main() {
    ios::sync_with_stdio(false);
    preprocess();
    cin >> t;
    while (t--) {
        cin >> n >> m;
        cout << comb(n, m) << endl;
    }
    return 0;
}