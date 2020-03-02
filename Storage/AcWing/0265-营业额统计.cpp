#include <bits/stdc++.h>
using namespace std;
set<int> s;
set<int>::iterator k, a;
int n, x, ans = 0;

int main() {
    s.insert(0x3f3f3f3f);
    s.insert(-0x3f3f3f3);
    scanf("%d", &n);
    for (register int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        if (s.size() == 2) {
            ans += x;
            s.insert(x);
        } else {
            k = s.lower_bound(x);
            if (*k != x) {
                a = k;
                a--;
                ans += min(abs(*a - x), abs(*k - x));
                s.insert(x);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}