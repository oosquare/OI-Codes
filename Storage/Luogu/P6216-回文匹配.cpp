#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e6 + 10;
constexpr int maxm = 3e6 + 10;

int n, m;
unsigned ans, sum[maxn], sum2[maxn];
int pi[maxm], r[maxn];
char s1[maxn], s2[maxm];

void preprocess() {
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j != 0 && s2[i] != s2[j + 1])
            j = pi[j];
        if (s2[i] == s2[j + 1])
            ++j;
        pi[i] = j;
    }
}

void match() {
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j != 0 && s1[i] != s2[j + 1])
            j = pi[j];
        if (s1[i] == s2[j + 1])
            ++j;
        if (j == m) {
            ++sum[i];
            j = pi[j];
        }
    }

    for (int i = 1; i <= n; ++i)
        sum[i] += sum[i - 1];
    for (int i = 1; i <= n; ++i)
        sum2[i] = sum2[i - 1] + sum[i];
}

void find() {
    int mx = 0, mid = 0;
    for (int i = 1; i <= n; ++i) {
        if (i < mx) {
            r[i] = min(mx - i + 1, r[mid * 2 - i]);
        } else {
            r[i] = 1;
        }
        while (s1[i - r[i]] == s1[i + r[i]] && i - r[i] >= 1 && i + r[i] <= n)
            ++r[i];
        if (i + r[i] - 1 >= mx) {
            mx = i + r[i] - 1;
            mid = i;
        }
    }
}

unsigned calc(int i) {
    int t = (m + 2) / 2;
    if (r[i] < t)
        return 0;
    return sum2[i + r[i] - 1] - sum2[i + t - 2] - sum2[i - t + m - 1] + sum2[i - r[i] + m - 2];
}

void solve() {
    for (int i = 1; i <= n; ++i)
        ans += calc(i);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> (s1 + 1) >> (s2 + 1);
    preprocess();
    match();
    find();
    solve();
    return 0;
}