#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, k, ans = 0x3f3f3f3f3f3f3f3f;
ll prime[100000], cnt[100000], tot;

void preprocess() {
    ll tmp = k;
    for (ll i = 2; i * i <= k; ++i) {
        if (tmp % i == 0) {
            ++tot;
            prime[tot] = i;
            while (tmp % i == 0) {
                ++cnt[tot];
                tmp /= i;
            }
        }
    }
    if (tmp != 1) {
        ++tot;
        prime[tot] = tmp;
        cnt[tot] = 1;
    }
}

ll find(ll x, ll y) {
    ll res = 0;
    while (x >= y) {
        res += x / y;
        x /= y;
    }
    return res; 
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    preprocess();
    for (int i = 1; i <= tot; ++i)
        ans = min(ans, find(n, prime[i]) / cnt[i]);
    cout << ans << endl;
    return 0;
}