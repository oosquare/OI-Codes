#include <iostream>
using namespace std;

constexpr int maxl = 5000 + 10;
constexpr int mod = 1e8;

char str1[maxl], str2[maxl];
int len1, len2, f[2][maxl], g[2][maxl];

int length(char str[]) {
    int len = 1;

    while (str[len] != '.')
        ++len;

    return len - 1;
}

int main() {
    cin >> (str1 + 1);
    cin >> (str2 + 1);
    len1 = length(str1);
    len2 = length(str2);

    for (int i = 0; i <= len2; ++i)
        g[0][i] = 1;

    for (int i = 1; i <= len1; ++i) {
        int now = (i & 1), pre = (now ^ 1);
        g[now][0] = 1;

        for (int j = 1; j <= len2; ++j) {
            g[now][j] = 0;
            f[now][j] = max(f[now][j - 1], f[pre][j]);
            
            if (str1[i] == str2[j]) {
                f[now][j] = max(f[now][j], f[pre][j - 1] + 1);

                if (f[now][j] == f[pre][j - 1] + 1)
                    g[now][j] = g[pre][j - 1];
            }
            
            if (f[now][j] == f[pre][j])
                g[now][j] = (g[now][j] + g[pre][j]) % mod;

            if (f[now][j] == f[now][j - 1])
                g[now][j] = (g[now][j] + g[now][j - 1]) % mod;

            if (f[now][j] == f[pre][j - 1])
                g[now][j] = (g[now][j] - g[pre][j - 1] + mod) % mod;
        }
    }

    cout << f[len1 & 1][len2] << endl;
    cout << g[len1 & 1][len2] << endl;
    return 0;
}