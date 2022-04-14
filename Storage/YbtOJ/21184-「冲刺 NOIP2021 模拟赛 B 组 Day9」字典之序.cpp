#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
#include <cstring>
using namespace std;

constexpr int maxn = 5e4 + 10;

int n, pre;
char str[maxn];
int selected[maxn], cnt[maxn];
string ans;

int main() {
    freopen("aorder.in", "r", stdin);
    freopen("aorder.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> (str + 1);
    n = strlen(str + 1);

    for (int i = 1; i <= n; ++i)
        ++cnt[str[i]];

    for (int i = 1; i <= n; ++i) {
        if (selected[str[i]])
            continue;

        --cnt[str[i]];

        if (str[pre] > str[i])
            pre = i;

        if (!cnt[str[i]]) {
            if (pre != 0)
                ans.push_back(str[pre]);
            selected[str[pre]] = true;

            for (int j = pre + 1; j <= i; ++j)
                ++cnt[str[j]];

            while (pre < n && selected[str[pre]])
                ++pre;

            i = pre - 1;
        }
    }

    cout << ans << endl;

    return 0;
}
