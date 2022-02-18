#include <iostream>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 1e6 + 10;

int n, k;
long long ans;
int prime[MAX_N], phi[MAX_N], tot;
bool notPrime[MAX_N];

void preprocess(int n) {
    notPrime[1] = true;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            phi[i] = i - 1;
        }

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;

            if (i % prime[j]) {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            } else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    
    if (k == 1) {
        cout << 3 << endl;
        return 0;
    }

    preprocess(n);

    sort(phi + 3, phi + n + 1);
    
    for (int i = 3; i <= k + 2; ++i)
        ans += phi[i];
    
    cout << ans + 2 << endl;
    return 0;
}