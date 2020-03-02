#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int n, k, now;
int a[100000];

inline ll C(int n, int m) {
    ll sum = 1;
    for (register int i = n - m + 1; i <= n; ++i) sum *= i;
    for (register int i = 1; i <= m; ++i) sum /= i;
    return sum;
}

inline void work(int n, int rnk) {
    for (register int i = n - k + 1; i <= n; ++i) a[i] = 1;
    rnk--;
    while (rnk--) {
        int tot = 0, fst;
        for (fst = n; fst >= 1; --fst)
            if (a[fst])
                break;
        for (; fst >= 1; --fst) {
            if (!a[fst])
                break;
            tot++;
        }
        for (register int i = n; i >= fst; --i) a[i] = 0;
        for (register int i = n; i >= n - tot + 2; --i) a[i] = 1;
        a[fst] = 1;
    }
    for (register int i = 1; i <= n; ++i) printf("%d", a[i]);
}

int main() {
    scanf("%d%d", &n, &k);
    if (k == 1) {
        printf("1");
        for (register int i = 1; i < n; ++i) printf("0");
        return 0;
    }
    --k;
    now = k;
    while (1) {
    	int cc = C(now, k);
        if (n <= cc) {
            printf("1");
            work(now, n);
            return 0;
        }
        n -= cc;
        ++now;
    }
}