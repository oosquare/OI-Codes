#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6 + 10;

int n, ans, a[maxn], b[maxn];
int fa[maxn], sze[maxn], sze2[maxn];
vector<int> tmp;

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy)
        return;
    fa[fy] = fx;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("brick.in", "r", stdin);
    freopen("brick.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        tmp.push_back(a[i]);
    }
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    for (int i = 1; i <= tmp.size(); ++i) fa[i] = i;
    for (int i = 1; i <= n; ++i)
        if (a[i] != b[i])
            merge(a[i], b[i]);
    for (int i = 1; i <= n; ++i)
        if (a[i] != b[i])
            ++sze[find(a[i])];
    for (int i = 1; i <= tmp.size(); ++i) ++sze2[find(i)];
    for (int i = 1; i <= n; ++i) {
        if (sze2[i] > 2)
            ans += max(sze[i] - 1, 0);
        else
            ans += sze[i] / 2;
    }
    cout << ans << endl;
    // for (int i = 1; i <= n; ++i)
    //     cout << sze[find(i)] << " ";
    // cout << endl;
    return 0;
}
