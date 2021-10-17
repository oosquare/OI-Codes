#include <bits/stdc++.h>
using namespace std;

int xo, yo, ans;

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> xo >> yo;
    for (int a = 1; a * xo <= yo; ++a)
        if (yo % (a * xo) == 0 && gcd(a, yo / (a * xo)) == 1)
            ++ans;
    cout << ans << endl;
    return 0;
}