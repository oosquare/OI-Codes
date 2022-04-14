#pragma GCC optimize(3)
#include <cstdio>
#include <bitset>
using namespace std;

constexpr int MAX_N = 2e5;
constexpr int MAX_C = 10;

int n, m, k;
char s[MAX_N + 2], t[MAX_N + 2];
bitset<MAX_N> range[MAX_C], ch[MAX_C], ans;
int d[MAX_C][MAX_N];

int main() {
#ifdef ONLINE_JUDGE
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
#endif
    scanf("%d%d%d%s%s", &n, &m, &k, s, t);

    for (int i = 0; i < n; ++i) {
        int c = s[i] - '0';
        ++d[c][max(i - k, 0)];

        if (i + k + 1 < n)
            --d[c][i + k + 1];

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

    for (int i = 0; i < m; ++i) ch[t[i] - '0'].set(i);

    for (int i = 0; i < m; ++i) ans &= (range[t[i] - '0'] >> i);

    printf("%llu\n", ans.count());
    return 0;
}
