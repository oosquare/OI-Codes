#include <iostream>
#include <cstring>

using namespace std;

constexpr int maxn = 250 + 10;

char str[maxn], ans[maxn];
int n, k, now, pos;

int main() {
    ios::sync_with_stdio(false);
    cin >> (str + 1) >> k;
    n = strlen(str + 1);
    now = 1;

    for (int i = 1; i <= n - k; ++i) {
        pos = now;

        for (int j = now + 1; j <= k + i; ++j)
            if (str[pos] > str[j])
                pos = j;

        ans[i] = str[pos];
        now = pos + 1;
    }

    int start = 1;

    while (start <= n - k && ans[start] == '0')
        ++start;

    if (start == n - k + 1) {
        cout << 0 << endl;
    } else {
        for (int i = start; i <= n - k; ++i)
            cout << ans[i];

        cout << endl;
    }

    return 0;
}