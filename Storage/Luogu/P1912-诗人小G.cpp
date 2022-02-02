#include <iostream>
#include <cstring>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Frame {
    int from, left;
};

int t, n, l, p;
string str[maxn];
long long sum[maxn];
int q[maxn], fr, bk;
int pre[maxn];
long double f[maxn];

long double power(long double x, long long y) {
    long double res = 1;

    for (; y; y >>= 1) {
        if (y & 1)
            res = res * x;

        x = x * x;
    }

    return res;
}

inline long double calc(int i, int j) {
    return f[j] + power(abs(sum[i] - sum[j] + i - j - 1 - l), p);
}

int find(int x, int y) {
    if (calc(n, x) < calc(n, y))
        return n + 1;

    int l = y, r = n, pos = -1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (calc(mid, y) <= calc(mid, x)) {
            pos = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return pos;
}

void dp() {
    fr = bk = 1;
    q[1] = 0;

    for (int i = 1; i <= n; ++i) {
        if (fr < bk && find(q[fr], q[fr + 1]) <= i)
            ++fr;

        f[i] = calc(i, q[fr]);
        pre[i] = q[fr];

        while (fr < bk && find(q[bk - 1], q[bk]) >= find(q[bk], i))
            --bk;

        q[++bk] = i;
    }
}

void output(int x) {
    if (!x)
        return;

    output(pre[x]);

    for (int i = pre[x] + 1; i < x; ++i)
        cout << str[i] << " ";

    cout << str[x] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;

    for (int i = 1; i <= t; ++i) {
        cin >> n >> l >> p;

        for (int j = 1; j <= n; ++j) {
            cin >> str[j];
            sum[j] = sum[j - 1] + str[j].size();
            f[j] = 1e18;
            pre[j] = 0;
        }

        dp();

        if (f[n] > 1e18) {
            cout << "Too hard to arrange" << endl;
        } else {
            cout << (long long)f[n] << endl;
            output(n);
        }

        cout << "--------------------" << endl;
    }

    return 0;
}