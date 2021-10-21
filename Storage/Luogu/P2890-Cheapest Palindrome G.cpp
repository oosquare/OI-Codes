#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2000 + 10;

int n, m, cost[256][2];
char str1[maxn], str2[maxn];
int f[maxn][maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n;
    cin >> (str1 + 1);
    
    for (int i = 1; i <= m; ++i) {
        char c;
        cin >> c;
        cin >> cost[c][0] >> cost[c][1];
    }
        
    for (int i = 1; i <= n; ++i)
        str2[i] = str1[n - i + 1];
    
    memset(f, 0x3f, sizeof(f));
    f[1][1] = 0;
    
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 1; j <= n + 1; ++j) {
            if (str1[i] == str2[j]) {
                if (i <= n && j <= n)
                    f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j]);
                
                continue;
            }
            
            if (i <= n) {
                f[i + 1][j] = min(f[i + 1][j], f[i][j] + cost[str1[i]][1]);
                f[i + 1][j] = min(f[i + 1][j], f[i][j] + cost[str1[i]][0]);
            }
            
            if (j <= n) {
                f[i][j + 1] = min(f[i][j + 1], f[i][j] + cost[str2[j]][0]);
                f[i][j + 1] = min(f[i][j + 1], f[i][j] + cost[str2[j]][1]);
            }
        }
    }
    
    cout << f[n + 1][n + 1] / 2 << endl;
    return 0;
} 