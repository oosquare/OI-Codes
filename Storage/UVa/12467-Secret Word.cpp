#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6 + 10;

int t, n, pi[maxn];
char str[maxn], rev[maxn];

void preprocess() {
    n = strlen(str + 1);
    for (int i = 1; i <= n; ++i)
        rev[i] = str[n - i + 1];
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && str[i] != str[j + 1])
            j = pi[j];
        if (str[i] == str[j + 1])
            ++j;
        pi[i] = j;
    }
}

void solve() {
    int ans = 1;
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j && rev[i] != str[j + 1])
            j = pi[j];
        if (rev[i] == str[j + 1])
            ++j;
        ans = max(ans, j);
        if (j == n) {
            break;
        }
    }
    for (int i = ans; i >= 1; --i)
        cout.put(str[i]);
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> (str + 1);
        preprocess();
        solve();
    }
    return 0;
}