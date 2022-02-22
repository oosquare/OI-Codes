#include <iostream>
#include <unordered_map>
#include <limits>
using namespace std;

constexpr int LIMIT = 3e6 + 10;
constexpr int MAX_SIZE = LIMIT + 10;

int t, n;

int prime[MAX_SIZE], tot;
long long phiSum[MAX_SIZE];
int muSum[MAX_SIZE];
bool notPrime[MAX_SIZE];

unordered_map<int, long long> phiSumCache;
unordered_map<int, int> muSumCache;

void preprocess(int n) {
    notPrime[1] = true;
    phiSum[1] = 1;
    muSum[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            phiSum[i] = i - 1;
            muSum[i] = -1;
        }

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;

            if (i % prime[j]) {
                phiSum[i * prime[j]] = phiSum[i] * (prime[j] - 1);
                muSum[i * prime[j]] = -muSum[i];
            } else {
                phiSum[i * prime[j]] = phiSum[i] * prime[j];
                muSum[i * prime[j]] = 0;
                break;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        phiSum[i] += phiSum[i - 1];
        muSum[i] += muSum[i - 1];
    }
}

long long calcPhiSum(int n) {
    if (n <= LIMIT)
        return phiSum[n];
    
    if (phiSumCache.count(n))
        return phiSumCache[n];
    
    long long ans = (n == numeric_limits<int>::max() ? 2305843008139952128 : 1ll * n * (n + 1) / 2);

    for (int l = 2, r; l <= n && r < numeric_limits<int>::max(); l = r + 1) {
        r = n / (n / l);
        ans -= (r - l + 1) * calcPhiSum(n / l);
    }

    phiSumCache[n] = ans;
    return ans;
}

int calcMuSum(int n) {
    if (n <= LIMIT)
        return muSum[n];
    
    if (muSumCache.count(n))
        return muSumCache[n];
    
    int ans = 1;

    for (int l = 2, r; l <= n && r < numeric_limits<int>::max(); l = r + 1) {
        r = n / (n / l);
        ans -= (r - l + 1) * calcMuSum(n / l);
    }

    muSumCache[n] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    preprocess(LIMIT);
    
    cin >> t;

    while (t--) {
        cin >> n;
        cout << calcPhiSum(n) << " " << calcMuSum(n) << endl;
    }
    
    return 0;
}