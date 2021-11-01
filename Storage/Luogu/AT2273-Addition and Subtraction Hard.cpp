#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;

using ll = long long;

constexpr int maxn = 1e5 + 10;
constexpr ll oo = 0x3f3f;//0x3f3f3f3f3f3f3f3f;

int n;
ll a[maxn], sym[maxn], f[maxn][3];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    sym[1] = 1;
    cin >> a[1];

    for (int i = 2; i <= n; ++i) {
        char c;
        cin >> c >> a[i];
        sym[i] = (c == '+' ? 1 : -1);
    }

    memset(f, ~0x3f, sizeof(f));
    f[1][0] = a[1];

    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= 2; ++j)
            f[i][0] = max(f[i][0], f[i - 1][j] + sym[i] * a[i]);

        if (sym[i] == 1) {
            for (int j = 1; j <= 2; ++j)
                f[i][1] = max(f[i][1], f[i - 1][j] - a[i]);
        } else {
            for (int j = 0; j <= 2; ++j)
                f[i][1] = max(f[i][1], f[i - 1][j] + (j == 0 ? -1 : 1) * a[i]);
        }

        if (sym[i] == 1) {
            f[i][2] = max(f[i][2], f[i - 1][2] + a[i]);
        } else {
            for (int j = 1; j <= 2; ++j)
                f[i][2] = max(f[i][2], f[i - 1][j] + (j == -1 ? -1 : 1) * a[i]);
        }
    }

    cout << max(max(f[n][0], f[n][1]), f[n][2]) << endl;
    return 0;
}