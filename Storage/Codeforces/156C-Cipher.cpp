#include <iostream>
#include <cstring>
using namespace std;

constexpr int maxn = 100 + 10;
constexpr int mod = 1e9 + 7;

int t, n;
int f[maxn][maxn * 26];
char str[maxn];

int main() {
    ios::sync_with_stdio(false);

    f[0][0] = 1;

    for (int i = 1; i <= 100; ++i)
        for (int j = i; j <= 26 * i; ++j)
            for (int k = 1; k <= 26; ++k)
                if (j - k >= 0)
                    f[i][j] = (f[i][j] + f[i - 1][j - k]) % mod;

    cin >> t;

    while (t--) {
        cin >> (str + 1);
        n = strlen(str + 1);

        int sum = 0;

        for (int i = 1; i <= n; ++i)
            sum += str[i] - 'a' + 1;

        cout << f[n][sum] - 1 << endl;
    }

    return 0;
}