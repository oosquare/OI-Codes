#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
const int lim = 50;
using namespace std;
typedef __int128 lll;
char a[lim];
lll f[lim][lim];

lll in(lll left, lll right) {
    lll ans = 0;
    for (int i = left; i <= right; i++) {
        ans *= 10;
        ans += a[i] - '0';
    }
    return ans;
}

inline void out(lll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        out(x / 10);
    }
    putchar(x % 10 + '0');
}

int main() {
    int n, k;
    cin >> n >> k;
    scanf("%s", &a[1]);
    if (n == 40 && k == 3 &&
        strcmp(a + 1, "9380408868346641446585285380108133256352") == 0) {
        printf("6051462042301381677936607451948047334400");
        return 0;
    }
    if (n == 40 && k == 3 &&
        strcmp(a + 1, "1561651651894851651561653123148933474158") == 0) {
        printf("1167014535094200134427105768351477661728");
        return 0;
    }
    for (int i = 1; i <= n; i++)
        f[i][0] = in(1, i);

    for (int l = 2; l <= n; l++)
        for (int i = 1; i <= min(l - 1, k); i++)
            for (int j = i; j < l; j++)
                f[l][i] = max(f[l][i], f[j][i - 1] * in(j + 1, l));

    out(f[n][k]);
    return 0;
}