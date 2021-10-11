#include <bits/stdc++.h>
using namespace std;

int m, s, t;
int mint, maxd, f[300010][25];

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> s >> t;
    if (min(m / 10, t) * 60 >= s) {
        cout << "Yes" << endl;
        cout << (int)ceil(1.0 * s / 60) << endl;
        return 0;
    } else if (t < m / 10 && t * 60 < s) {
        cout << "No" << endl;
        cout << t * 60 << endl;
        return 0;
    } else {
        mint += m / 10;
        maxd += (m / 10) * 60;
        t -= m / 10;
        s -= (m / 10) * 60;
        m %= 10;
    }

    memset(f, ~0x3f, sizeof(f));
    f[0][m] = 0;
    for (int i = 1; i <= t; ++i) {
        for (int j = 0; j <= 20; ++j) {
            f[i][j] = f[i - 1][j] + 17;
            if (j >= 4)
                f[i][j] = max(f[i][j], f[i - 1][j - 4]);
            if (j + 10 <= 20)
                f[i][j] = max(f[i][j], f[i - 1][j + 10] + 60);
            if (f[i][j] >= s) {
                cout << "Yes" << endl;
                cout << mint + i << endl;
                return 0;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= 20; ++i)
        ans = max(ans, f[t][i]);
    cout << "No" << endl;
    cout << maxd + ans << endl;
    return 0;
}