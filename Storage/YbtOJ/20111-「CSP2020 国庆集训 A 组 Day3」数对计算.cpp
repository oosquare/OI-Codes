#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct p {
    ll a, b;
};

p ps[100001];
int n;

bool cmp(p a, p b) { return a.b < b.b; }

int main() {
    freopen("expedition.in", "r", stdin);
    freopen("expedition.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &ps[i].a, &ps[i].b);
    }
    stable_sort(ps + 1, ps + 1 + n, cmp);
    ll cnt = ps[1].a, ans = 0;
    for (int i = 2; i <= n; i++) { // åå¹¶ææ bi ç¸åçæ°å¯¹
        if (ps[i].b == ps[i - 1].b) {
            cnt += ps[i].a;
        } else {
            ans += cnt * cnt;
            cnt = ps[i].a;
        }
    }
    ans += cnt * cnt;
    printf("%lld", ans);
}
