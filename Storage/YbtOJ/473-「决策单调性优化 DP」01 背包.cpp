#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 1e6 + 10;
constexpr int maxm = 1e5 + 10;
constexpr int oo = 0x3f3f3f3f;

struct item {
    int s, v;

    bool operator<(item rhs) {
        if (s == rhs.s)
            return v > rhs.v;
        return s < rhs.s;
    }
};

int n, m, len, front, back, que[maxm];
item arr[maxn];
ll f[310][maxm], sum[maxn];

ll calculate(int s, int i, int t) {
    return f[s][i] + sum[t];
}

int find(int s1, int s2, int i, int j) {
    int tmp = (j - i) / s2, l = 0, r = min(len, (m - j) / s2), ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (calculate(s1, i, mid + tmp) <= calculate(s1, j, mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (ans == -1)
        return oo;
    else
        return j + ans * s2;
}

void solve(int i) {
    len = 0;
    for (int j = i; j <= n && arr[i].s == arr[j].s; ++j) {
        ++len;
        sum[len] = sum[len - 1] + arr[j].v;
    }
    for (int j = 1; j <= m; ++j)
        f[arr[i].s][j] = f[arr[i - 1].s][j];
    for (int j = 0; j < arr[i].s; ++j) {
        que[front = back = 1] = j;
        for (int k = j + arr[i].s; k <= m; k += arr[i].s) {
            while (
                front < back && 
                find(arr[i - 1].s, arr[i].s, que[front], que[front + 1]) <= k
            )
                ++front;
            f[arr[i].s][k] = max(
                f[arr[i].s][k], 
                calculate(arr[i - 1].s, que[front], min(len, (k - que[front]) / arr[i].s))
            );
            while (
                front < back && 
                find(arr[i - 1].s, arr[i].s, que[back - 1], que[back]) >= 
                find(arr[i - 1].s, arr[i].s, que[back], k)
            )
                --back;
            que[++back] = k;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("jewelry.in", "r", stdin);
    freopen("jewelry.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i].s >> arr[i].v;
    sort(arr + 1, arr + 1 + n);
    for (int i = 1; i <= n; ++i)
        if (arr[i].s != arr[i - 1].s)
            solve(i);
    copy(f[arr[n].s] + 1, f[arr[n].s] + 1 + m, ostream_iterator<ll>(cout, " "));
    return 0;
}
