#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include <unordered_map>
using namespace std;

constexpr int maxn = 5e6 + 10;
constexpr int mod = 1000000993;
constexpr int base = 97;

char str[maxn];
int mp[256];
int n, k, power[maxn], val[maxn];
unordered_map<int, int> s;
int ans;

inline int calc(int l, int r) {
    return (val[r] - 1ll * val[l - 1] * power[r - l + 1] % mod + mod) % mod;
}

int main() {
    freopen("dna.in", "r", stdin);
    freopen("dna.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> (str + 1);
    cin >> k;
    n = strlen(str + 1);
    power[0] = 1;
    mp['A'] = 0, mp['G'] = 1, mp['C'] = 2, mp['T'] = 3;

    for (int i = 1; i <= n; ++i) {
        power[i] = 1ll * power[i - 1] * base % mod;
        val[i] = (1ll * val[i - 1] * base + mp[(int)str[i]]) % mod;
    }

    for (int i = 1; i + k - 1 <= n; ++i)
        ++s[calc(i, i + k - 1)];

    for (auto [k, v] : s)
        ans = max(ans, v);

    cout << ans << endl;
    return 0;
}
