#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2000 + 10;

char str[maxn];
int t, n, pi[maxn];

void preprocess() {
    n = strlen(str + 1);
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && str[i] != str[j + 1])
            j = pi[j];
        if (str[i] == str[j + 1])
            ++j;
        pi[i] = j;
    }
}

int get(int x) {
    return (x % (x - pi[x]) ? x : (x - pi[x]));
}

void solve() {
    int t;
    for (int i = n; i >= 1; --i) {
        t = get(i);
        if (t != i)
            break;
    }
    int idx = n % t + 1;
    for (int i = 1; i <= 8; ++i, ++idx)
        cout.put(str[(idx - 1) % t + 1]);
    cout << "..." << endl;
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