#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int n, s, a[maxn];
long long sum[maxn];

int check1(int i, int mid) { return sum[mid] - sum[i - 1] <= s; }

int check2(int i, int mid) { return sum[(mid << 1) - i + 1] - sum[mid] <= s; }

int main() {
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; ++i)
        in(a[i]), sum[i] = sum[i - 1] + a[i];
    int p = 0;
    sum[n + 1] = sum[n + 2] = 1e18;
    while ((p + 1 << 1) <= n && check1(1, p + 1))
        ++p;
    while (p && !check2(1, p))
        --p;
    printf("%d\n", (p << 1));
    for (int i = 2; i <= n; ++i) {

        while ((p + 1 << 1) - i + 1 <= n && check1(i, p + 1))
            ++p;
        while (p >= i && !check2(i, p))
            --p;
        printf("%d\n", (p - i + 1) << 1);
    }
    return 0;
}