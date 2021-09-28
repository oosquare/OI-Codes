#include <iostream>
using namespace std;

typedef long long ll;

ll a[4] = {0, 23, 28, 33}, b[4];
ll dd, ans, m, cas = 1;

void extendedGcd(ll a, ll b, ll& d, ll& x, ll& y) {
    if (!b) {
        d = a; x = 1; y = 0;
    } else {
        extendedGcd(b, a % b, d, x, y);
        int t = x; x = y; y = t - a / b * y;
    }
}

void intChina() {
    ll mi, x, y, i, d;
    for (i = 1; i <= 3; i++) {
        mi = m / a[i];
        extendedGcd(mi, a[i], d, x, y);
        ans = ((ans + mi * x * b[i]) % m + m) % m;
    }
}

int main() {
    m = 23 * 28 * 33;
    while (1) {
        ans = 0;
        int t1, t2, t3;
        cin >> t1 >> t2 >> t3 >> dd;
        if (t1 == -1 && t2 == -1 && t3 == -1 && dd == -1)break;
        b[1] = t1; b[2] = t2; b[3] = t3;
        intChina();
        int k = (ans - dd + m) % m;
        if (k == 0)k = m;
        cout << "Case " << cas++ << ": the next triple peak occurs in " << k << " days." << endl;
    }
}