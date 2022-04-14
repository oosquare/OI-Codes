#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 100000 + 10;
constexpr int mod = 99824353;

int n, a, b, v[maxn], p[maxn], ans[maxn];
int l, r, vl, vr, cnt;

int rand(int l, int r) {
    static int x = 1;
    x = (1ll * x * x + 1ll * a * x + b) % mod;
    return x % (r - l + 1) + l;
}

int main() {
    freopen("account.in", "r", stdin);
    freopen("account.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n >> a >> b;
    iota(v + 1, v + 1 + n, 1);
    l = vl = 1;
    r = vr = n;
    cnt = 1;

    for (int i = 1; i <= n; ++i) {
        int index = rand(l, r);

        if (v[index] == cnt) {
            ans[v[index]] = vr--;
            swap(v[index], v[l]);
            swap(v[l], v[r]);
            --r;
        } else {
            ans[v[index]] = vl++;
            swap(v[index], v[l]);
            ++l;
        }

        while (ans[cnt])
            ++cnt;
    }

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";

    cout << endl;
    return 0;
}
