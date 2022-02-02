#include <iostream>
using namespace std;

constexpr int maxn = 5e4 + 10;

struct Frame {
    int from, left;
};

int n, l, c[maxn];
long long sum[maxn];
Frame q[maxn];
int fr, bk;
long long f[maxn];

inline long long power(long long x) {
    return x * x;
}

inline long long weight(int i, int j) {
    return f[j] + power(sum[i] - sum[j] + i - j - 1 - l);
}

int find(int i) {
    int l = q[bk].left, r = n, pos = n + 1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (weight(mid, q[bk].from) > weight(mid, i)) {
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
    q[1] = {0, 1};

    for (int i = 1; i <= n; ++i) {
        if (q[fr + 1].left == i)
            ++fr;

        int j = q[fr].from;
        f[i] = weight(i, j);

        while (weight(q[bk].left, q[bk].from) > weight(q[bk].left, i))
            --bk;

        int pi = find(i);

        if (pi <= n)
            q[++bk] = {i, pi};
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> l;

    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        sum[i] = sum[i - 1] + c[i];
    }

    dp();
    cout << f[n] << endl;
    return 0;
}