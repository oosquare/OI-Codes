#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;

constexpr int MAX_N = 2e5 + 10;
constexpr int MAX_C = 4;

int n, m, k, mp[256];
char s[MAX_N], t[MAX_N];
bitset<MAX_N> range[MAX_C], ch[MAX_C], ans;
int d[MAX_C][MAX_N];

int main() {
    ios::sync_with_stdio(false);
    mp[(int) 'A'] = 0;
    mp[(int) 'G'] = 1;
    mp[(int) 'C'] = 2;
    mp[(int) 'T'] = 3;

    cin >> n >> m >> k;
    cin >> s;
    cin >> t;

    for (int i = 0; i < n; ++i) {
        int c = mp[(int) s[i]];
        ++d[c][max(i - k, 0)];
        --d[c][min(i + k + 1, n)];
        ans.set(i);
    }

    for (int j = 0; j < MAX_C; ++j) {
        if (d[j][0])
            range[j].set(0);

        for (int i = 1; i < n; ++i) {
            d[j][i] += d[j][i - 1];

            if (d[j][i])
                range[j].set(i);
        }
    }

    for (int i = 0; i < m; ++i)
        ch[mp[(int) t[i]]].set(i);
    
    for (int i = 0; i < m; ++i)
        ans &= (range[mp[(int) t[i]]] >> i);
    
    cout << ans.count() << endl;
    return 0;
}