#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxl = 1e5 + 10;

int l, k;
ll x[maxl], mx, s;

bool checkMin(ll mid) {
    int cnt = 0;
    ll len = 0;
    for (int i = 1; i <= l; ++i) {
        len += x[i];
        if (len < 0)
            len = 0;
        if (len >= mid) {
            ++cnt;
            len = 0;
        }
    }
    return cnt <= k;
}

bool checkMax(ll mid) {
    int cnt = 0;
    ll len = 0;
    for (int i = 1; i <= l; ++i) {
        len += x[i];
        if (len < 0)
            len = 0;
        if (len >= mid) {
            ++cnt;
            len = 0;
        }
    }
    return cnt >= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> l >> k;

    for (int i = 1; i <= l; ++i) {
        cin >> x[i];

        if (x[i] >= 0) {
            s += x[i];
            mx = max(mx, s);
        } else {
            s = 0;
        }
    }

    mx = 0x3f3f3f3f3f3f3f3f;

    ll left = 1, right = mx, minAns = -1, maxAns = -1;

    while (left <= right) {
        ll mid = (left + right) / 2;

        if (checkMin(mid)) {
            minAns = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    left = minAns;
    right = mx;

    while (left <= right) {
        ll mid = (left + right) / 2;

        if (checkMax(mid)) {
            maxAns = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (minAns == -1 || maxAns == -1)
        cout << -1 << endl;
    else
        cout << minAns << " " << maxAns << endl;

    return 0;
}