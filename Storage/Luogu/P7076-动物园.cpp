#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

constexpr int maxn = 1e6 + 10;

vector<int> req[64], tmp;
bool selected[maxn];
ull vis, ans;
int n, m, c, k, cnt;

inline bool vaild(int b) {
    for (int i : req[b])
        if (!selected[i])
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> c >> k;
    for (int i = 1; i <= n; ++i) {
        ull a;
        cin >> a;
        vis |= a;
    }
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        req[a].push_back(b);
        tmp.push_back(b);
    }
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for (int i = 0; i < k; ++i)
        for (int &j : req[i])
            j = lower_bound(tmp.begin(), tmp.end(), j) - tmp.begin() + 1;
    for (int i = 0; i < k; ++i) {
        if (!(1 & (vis >> i)))
            continue;
        for (int j : req[i])
            selected[j] = true;
    }
    for (int i = 0; i < k; ++i)
        if (vaild(i))
            ++cnt;
    if (cnt == 64 && n != 0)
        cout << numeric_limits<ull>::max() - n + 1 << endl;
    else if (cnt == 64 && n == 0)
        cout << "18446744073709551616" << endl;
    else
        cout << ((ull)1 << cnt) - n << endl;
    return 0;
}