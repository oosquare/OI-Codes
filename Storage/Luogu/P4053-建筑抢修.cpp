#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct info {
    ll t1, t2;
};

priority_queue<ll> q;

bool cmp(info a, info b) { return a.t2 < b.t2; }

int n, ans;
info a[150010];
ll sum;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &a[i].t1, &a[i].t2);
    }
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; ++i) {
        if (sum + a[i].t1 <= a[i].t2) {
            ++ans;
            q.push(a[i].t1);
            sum += a[i].t1;
        } else if (a[i].t1 < q.top()) {
            sum = sum - q.top() + a[i].t1;
            q.pop();
            q.push(a[i].t1);
        }
    }
    printf("%d\n", ans);
    return 0;
}
