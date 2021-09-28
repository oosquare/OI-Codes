#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5 + 10;
constexpr int maxw = 2e5 + 10;

int n, w;
int a[maxn], b[maxw];
int pi[maxw];

void preprocess() {
    --n;
    --w;
    for (int i = n; i >= 1; --i)
        a[i] = a[i - 1] - a[i];
    for (int i = w; i >= 1; --i)
        b[i] = b[i - 1] - b[i];
    for (int i = 2, j = 0; i <= w; ++i) {
        while (j && b[i] != b[j + 1])
            j = pi[j];
        if (b[i] == b[j + 1])
            ++j;
        pi[i] = j;
    }
}

void solve() {
    int ans = 0;
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j && a[i] != b[j + 1])
            j = pi[j];
        if (a[i] == b[j + 1])
            ++j;
        if (j == w) {
            ++ans;
            j = pi[j];
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> w;
    if (w == 1) {
        cout << n << endl;
        return 0;
    }
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < w; ++i)
        cin >> b[i];
    preprocess();
    solve();
    return 0;
}