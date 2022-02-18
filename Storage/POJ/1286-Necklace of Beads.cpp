#include <iostream>
using namespace std;

int n;

long long power(long long x, int y) {
    long long res = 1;

    for (; y; y /= 2) {
        if (y % 2)
            res = res * x;
        
        x = x * x;
    }

    return res;
}

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

int phi(int x) {
    int res = x;

    for (int i = 2; i * i <= x; ++i) {
        if (x % i)
            continue;
        
        res = res / i * (i - 1);

        while (x % i == 0)
            x /= i;
    }

    if (x > 1)
        res = res / x * (x - 1);
    
    return res;
}

int main() {
    ios::sync_with_stdio(false);

    while (true) {
        cin >> n;
        long long ans = 0;
        
        if (n == -1)
            break;

        if (n == 0) {
            cout << 0 << endl;
            continue;
        }

        for (int i = 1; i * i <= n; ++i) {
            if (n % i)
                continue;
            
            if (i * i == n)
                ans += power(3, i) * phi(i);
            else
                ans += power(3, i) * phi(n / i) + power(3, n / i) * phi(i);
        }   

        if (n % 2)
            ans += n * power(3, (n + 1) / 2);
        else
            ans += n / 2 * power(3, n / 2) + n / 2 * power(3, n / 2 + 1);
        
        ans /= 2 * n;
        cout << ans << endl;
    }
    
    return 0;
}