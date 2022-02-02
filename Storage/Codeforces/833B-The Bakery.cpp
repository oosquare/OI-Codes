#include <iostream>
using namespace std;

constexpr int maxn = 35000 + 5;
constexpr int maxk = 50 + 5;

int n, k, a[maxn];
int cnt[maxn], sum, nl, nr;
int f[maxk][maxn];

inline void add(int x) {
    if (!(cnt[a[x]]++))
        ++sum;
}

inline void del(int x) {
    if (!(--cnt[a[x]]))
        --sum;
}

int query(int l, int r) {
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

inline int weight(int i, int j) {
    return query(j + 1, i);
}

void dp(int l, int r, int pl, int pr, int i) {
    if (l > r)
        return;

    int mid = (l + r) / 2, pos = 0;

    for (int j = pl; j <= min(pr, mid - 1); ++j) {
        if (f[i][mid] < f[i - 1][j] + weight(mid, j)) {
            f[i][mid] = f[i - 1][j] + weight(mid, j);
            pos = j;
        }
    }

    dp(l, mid - 1, pl, pos, i);
    dp(mid + 1, r, pos, pr, i);
}

int main() {
    cin >> n >> k;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    nl = nr = cnt[a[1]] = sum = 1;

    for (int i = 1; i <= k; ++i)
        dp(1, n, 0, n - 1, i);

    cout << f[k][n] << endl;
    return 0;
}