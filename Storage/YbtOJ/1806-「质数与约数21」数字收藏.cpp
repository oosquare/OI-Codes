#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

int n, k;
long long ans;
int num[maxn], cnt[maxn];
int miu[maxn], prime[maxn], notprime[maxn], tot;

void getmiu(int n) {
    miu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!notprime[i])
            prime[++tot] = i, miu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] <= n; ++j) {
            notprime[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                miu[i * prime[j]] = 0;
                break;
            }
            miu[i * prime[j]] = -miu[i];
        }
    }
}

void add(int x) {
    if (x % k != 0)
        return;
    x /= k;

    int d;
    for (d = 1; d * d < x; ++d) {
        if (x % d != 0)
            continue;
        ans += miu[d] * cnt[d] + miu[x / d] * cnt[x / d];
    }
    if (d * d == x)
        ans += miu[d] * cnt[d];

    for (d = 1; d * d < x; ++d) {
        if (x % d != 0)
            continue;
        ++cnt[d];
        ++cnt[x / d];
    }
    if (d * d == x)
        ++cnt[d];
}

void sub(int x) {
    if (x % k != 0)
        return;
    x /= k;

    int d = 0;
    for (d = 1; d * d < x; ++d) {
        if (x % d != 0)
            continue;
        --cnt[d];
        --cnt[x / d];
    }
    if (d * d == x)
        --cnt[d];

    for (d = 1; d * d < x; ++d) {
        if (x % d != 0)
            continue;
        ans -= miu[d] * cnt[d] + miu[x / d] * cnt[x / d];
    }
    if (d * d == x)
        ans -= miu[d] * cnt[d];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
#endif
    getmiu(100000);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == 0) {
            if (num[b] != 0) {
                --num[b];
                sub(b);
            }
        } else {
            ++num[b];
            add(b);
        }
        cout << ans << endl;
    }
    return 0;
}
