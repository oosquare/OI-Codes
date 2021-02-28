#include <cstdio>
using namespace std;

int phi(int x) {
    int res = x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0)
                x /= i;
        }
    }
    if (x > 1)
        res = res / x * (x - 1);
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    int n;
    while (true) {
        scanf("%d", &n);
        if (n == 0)
            break;
        printf("%d\n", phi(n));
    }
    return 0;
}