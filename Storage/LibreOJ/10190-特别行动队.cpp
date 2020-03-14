#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 1e6 + 10;
int n, a, b, c;
ll x[maxn], f[maxn];
deque<int> q;

ll getX(int i) { return 1ll * x[i]; }

ll getY(int i) {
    return f[i] + 1ll * a * x[i] * x[i] - 1ll * b * x[i] + 1ll * c;
}

double slope(int i, int j) {
    return 1.0 * (getY(j) - getY(i)) / (getX(j) - getX(i));
}

int main() {
    scanf("%d%d%d%d", &n, &a, &b, &c);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &x[i]);
        x[i] += x[i - 1];
    }
    q.push_back(0);
    for (int i = 1; i <= n; ++i) {
        while (q.size() > 1 && slope(q[0], q[1]) > 2ll * a * x[i])
            q.pop_front();
        int j = q[0];
        f[i] = f[j] + 1ll * a * (x[i] - x[j]) * (x[i] - x[j]) +
               1ll * b * (x[i] - x[j]) + 1ll * c;
        int l = q.size() - 1;
        while (q.size() > 1 && slope(q[l - 1], q[l]) < slope(q[l], i)) {
            q.pop_back();
            --l;
        }
        q.push_back(i);
    }
    printf("%lld\n", f[n]);
    return 0;
}
