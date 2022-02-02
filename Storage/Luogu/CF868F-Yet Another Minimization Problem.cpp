#include <iostream>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxk = 20 + 2;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

int n, k;
int a[maxn], cnt[maxn];
long long nl, nr, sum, f[maxk][maxn];

inline long long calc(int x) {
    return (x >= 2 ? 1ll * x * (x - 1) / 2 : 0);
}

inline void add(int x) {
    sum = sum - calc(cnt[a[x]]) + calc(cnt[a[x]] + 1);
    ++cnt[a[x]];
}

inline void del(int x) {
    sum = sum - calc(cnt[a[x]]) + calc(cnt[a[x]] - 1);
    --cnt[a[x]];
}

long long weight(int l, int r) {
    while (l < nl)
        add(--nl);

    while (r > nr)
        add(++nr);

    while (l > nl)
        del(nl++);

    while (r < nr)
        del(nr--);

    return sum;
}

void dp(int l, int r, int pl, int pr, int i) {
    if (l > r || pl > pr)
        return;

    int mid = (l + r) / 2, pos = 0;

    for (int j = pl; j <= min(pr, mid - 1); ++j) {
        if (f[i - 1][j] + weight(j + 1, mid) < f[i][mid]) {
            f[i][mid] = f[i - 1][j] + weight(j + 1, mid);
            pos = j;
        }
    }

    dp(l, mid - 1, pl, pos, i);
    dp(mid + 1, r, pos, pr, i);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    nl = nr = 1;
    cnt[a[1]] = 1;

    for (int i = 0; i <= k; ++i)
        for (int j = 0; j <= n; ++j)
            f[i][j] = oo;

    f[0][0] = 0;

    for (int i = 1; i <= k; ++i)
        dp(1, n, 0, n - 1, i);

    cout << f[k][n] << endl;
    return 0;
}