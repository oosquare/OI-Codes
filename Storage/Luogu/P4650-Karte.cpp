#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5 + 10;

int n, k, a[maxn], selected[maxn], ans[maxn];

int selectLast() {
    int cnt = 0;
    for (int i = n; i >= 1; --i) {
        if (a[i] <= k)
            break;
        ++cnt;
        ans[k - cnt + 1] = a[i];
        selected[i] = true;
    }
    return cnt;
}

bool selectFirst(int rest) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (cnt == rest)
            break;
        if (a[i] <= cnt || selected[i])
            continue;
        ++cnt;
        ans[cnt] = a[i];
        selected[i] = true;
    }
    if (cnt < rest)
        return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    sort(a + 1, a + 1 + n);
    
    int rest = k - selectLast();
    if (rest < 0) {
        cout << -1 << endl;
        return 0;
    }

    bool vaild = selectFirst(rest);
    if (vaild == false) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = n; i >= 1; --i) {
        if (selected[i])
            continue;
        cout << a[i] << " ";
    }
    for (int i = k; i >= 1; --i)
        cout << ans[i] << " ";
    cout << endl;

    return 0;
}