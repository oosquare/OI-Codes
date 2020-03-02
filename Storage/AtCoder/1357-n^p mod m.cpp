#include <iostream>
using namespace std;

typedef long long ll;

ll quickPower(ll a, ll b, ll m) {
    ll ans = 1;
    while (b) {
        if (b % 2 == 1)
            ans = ans * a % m;
        a = a * a % m;
        b /= 2;
    }
    return ans;
}

int main() {
    ll a, b, m;
    cin >> a >> m >> b;
    cout << quickPower(a, b, m) << endl;
}