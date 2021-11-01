#include <bits/stdc++.h>
using namespace std;

long long s, t, n;

void solve() {
    long long ans1, ans2;

    if (s >= n) {
        ans1 = 3 * (n - 1);

        if (s - (n - 1) > t)
            ans1 += 3;
        else if (s - (n - 1) == t)
            ans1 += 1;
    } else {
        ans1 = 3 * s + n - s - 1;

        if (t == 0)
            ++ans1;
    }

    if (t < s) {
        ans2 = 3;
        
        if (t < n - 1)
            ans2 += n - 1 - t;
    } else {
        long long a = 3, b = 0;
        
        if (t < n - 1)
            a += n - 1 - t;

        if (n > t - s)
            b = n - (t - s);

        ans2 = min(a, b);
    }

    cout << ans1 << " " << ans2 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    
    while (cin >> s >> t >> n)
        solve();

    return 0;
}