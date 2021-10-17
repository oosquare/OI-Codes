#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e4 + 10;
constexpr int oo = 0x3f3f3f3f;

int n, m;
vector<pair<int, int>> tree[maxn];
int res, mid, sum;
int selected[maxn], tmp[maxn], f[maxn];

void link(int x, int y, int l) {
    tree[x].push_back({y, l});
    tree[y].push_back({x, l});
}

void dfs(int x, int fa) {
    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;
        dfs(y, x);
    }

    int top = 0;
    for (auto [y, l] : tree[x]) {
        if (y == fa)
            continue;
        tmp[++top] = f[y] + l;
    }

    sort(tmp + 1, tmp + 1 + top);
    while (top > 0 && tmp[top] >= mid) {
        --top;
        --res;
    }

    for (int i = 1; i <= top; ++i) {
        if (selected[i] == x)
            continue;

        int ll = i + 1, rr = top, j = top + 1;
        while (ll <= rr) {
            int mmid = (ll + rr) / 2;
            if (tmp[i] + tmp[mmid] >= mid) {
                j = mmid;
                rr = mmid - 1;
            } else {
                ll = mmid + 1;
            }
        }
        
        while (j <= top && selected[j] == x)
            ++j;
        if (j <= top) {
            selected[i] = selected[j] = x;
            --res;
        }
    }

    f[x] = 0;
    for (int i = top; i >= 1; --i) {
        if (selected[i] != x) {
            f[x] = tmp[i];
            break;
        }
    }
}

bool check(int mid) {
    memset(selected, 0, sizeof(selected));
    res = m;
    dfs(1, 0);
    // cerr << d << " " << mid << " " << res << endl;
    return res <= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        link(a, b, l);
        sum += l;
    }
    int l = 1, r = sum, ans = 1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}