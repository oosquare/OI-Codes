#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 20;

/* f[第几位][前2位][前1位][有4][有8][连续长度] */
ll f[maxn][maxn][maxn][2][2][4]; 
vector<int> digit;
ll l, r;

ll DP(int pos, int is4, int is8, int len, int front1, int front2, bool limit) {
    if (is4 && is8)
        return 0;
    if (pos == -1)
        return len == 3;
    if (!limit && f[pos][front1][front2][is4][is8][len] != -1)
        return f[pos][front1][front2][is4][is8][len];
    ll res = 0;
    int up = limit ? digit[pos] : 9;
    for (int i = 0; i <= up; ++i) {
        if (pos == digit.size() - 1 && i == 0)
            continue;
        int nlen = 1;
        if (front1 == front2 && front2 == i)
            nlen = 3;
        else if (front2 == i)
            nlen = 2;
        nlen = min(max(nlen, len), 3);
        res += DP(pos - 1, is4 | (i == 4), is8 | (i == 8), nlen, front2, i, limit && i == up);
    }
    if (!limit)
        f[pos][front1][front2][is4][is8][len] = res;
    return res;
}

ll solve(ll num) {
    if (num < 1e10)
        return 0;
    memset(f, -1, sizeof(f));
    digit.clear();
    while (num) {
        digit.push_back(num % 10);
        num /= 10;
    }
    ll res = 0;
    // for (int i = 1; i <= digit[digit.size() - 1]; ++i)
    //     res += DP(digit.size() - 2, 0, i == 4, 1, 0, i, i < digit[digit.size() - 1]);
    // return res;
    return DP(digit.size() - 1, 0, 0, 0, 11, 11, true);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
#endif
    cin >> l >> r;
    cout << solve(r) - solve(l - 1) << endl;
    return 0;
}
