#include <iostream>
#include <unordered_map>
using namespace std;

constexpr int LIMIT = 2e7;
constexpr int MAX_SIZE = LIMIT + 10;

long long n, p;

int prime[MAX_SIZE], tot;
bool notPrime[MAX_SIZE];
long long phiSum[MAX_SIZE];

unordered_map<long long, long long> phiSumCache;

long long ans;

long long multiply(long long x, long long y) {
    return (x * y - (long long) ((long double) x / p * y) * p + p) % p;
}

long long power(long long x, long long y) {
    long long res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = multiply(res, x);

        x = multiply(x, x);
    }

    return res;
}

inline long long square(long long x) {
    return multiply(x, x);
}

long long linearSum(long long x) {
    return (x % 2 == 0 ? multiply(x / 2, x + 1) : multiply(x, (x + 1) / 2));
}

long long squareSum(long long x) {
    static int inv6 = power(6, p - 2);
    return multiply(multiply(multiply(x, x + 1), 2 * x + 1), inv6);
}

long long cubicSum(long long x) {
    return square(linearSum(x));
}

void preprocess(int n) {
    notPrime[1] = true;
    phiSum[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!notPrime[i]) {
            prime[++tot] = i;
            phiSum[i] = i - 1;
        }

        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notPrime[i * prime[j]] = true;

            if (i % prime[j]) {
                phiSum[i * prime[j]] = phiSum[i] * (prime[j] - 1);
            } else {
                phiSum[i * prime[j]] = phiSum[i] * prime[j];
                break;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        phiSum[i] = multiply(phiSum[i], square(i));
        phiSum[i] += phiSum[i - 1];

        if (phiSum[i] >= p)
            phiSum[i] -= p;
    }
}

long long calcPhiSum(long long n) {
    if (n <= LIMIT)
        return phiSum[n];
        
    if (phiSumCache.count(n))
        return phiSumCache[n];

    long long ans = cubicSum(n);

    for (long long l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        long long sum = (squareSum(r) - squareSum(l - 1) + p) % p;
        ans = (ans - multiply(sum, calcPhiSum(n / l)) + p) % p;
    }
    
    phiSumCache[n] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> p >> n;
    preprocess(LIMIT);

    for (long long l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        long long sum = (calcPhiSum(r) - calcPhiSum(l - 1) + p) % p;
        long long cnt = linearSum(n / l);
        ans = (ans + multiply(sum, square(cnt))) % p;
    }

    cout << ans << endl;
    return 0;
}