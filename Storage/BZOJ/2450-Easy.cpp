#include <bits/stdc++.h>
using namespace std;

int n;
char s[300030];
double f[300030], l[300030];

int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] == 'o') {
            f[i] = f[i - 1] + 2 * l[i - 1] + 1;
            l[i] = l[i - 1] + 1;
        } else if (s[i] == 'x') {
            f[i] = f[i - 1];
            l[i] = 0;
        } else {
            f[i] = f[i - 1] + (2 * l[i - 1] + 1) / 2;
            l[i] = (l[i - 1] + 1) / 2;
        }
    }
    printf("%.4lf\n", f[n]);
    return 0;
}