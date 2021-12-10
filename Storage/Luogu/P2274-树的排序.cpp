#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxm = 30;

struct Node {
    int ls, rs;
};

long long n, cnt[maxm];
Node tree[maxm];
int uuid;

void preprocess() {
    cnt[0] = cnt[1] = 1;

    for (int i = 2; i < maxm; ++i)
        for (int j = 0; j < i; ++j)
            cnt[i] += cnt[j] * cnt[i - 1 - j];
}

int build(int tot, long long rk) {
    if (!tot)
        return 0;

    int id = ++uuid;
    int totL = 0, totR = 0;
    long long rkL = 0, rkR = 0;
    long long tmp = rk;

    for (int i = 0; i <= tot - 1; ++i) {
        if (tmp <= cnt[i] * cnt[tot - 1 - i]) {
            totL = i;
            totR = tot - 1 - i;
            break;
        }

        tmp -= cnt[i] * cnt[tot - 1 - i];
    }

    rkL = (tmp - 1) / cnt[totR] + 1;
    rkR = (tmp - 1) % cnt[totR] + 1;

    tree[id].ls = build(totL, rkL);
    tree[id].rs = build(totR, rkR);
    return id;
}

void output(int x) {
    if (tree[x].ls) {
        cout << "(";
        output(tree[x].ls);
        cout << ")";
    }

    cout << "X";

    if (tree[x].rs) {
        cout << "(";
        output(tree[x].rs);
        cout << ")";
    }
}

int main() {
    ios::sync_with_stdio(false);
    preprocess();
    cin >> n;

    for (int i = 1; i < maxm; ++i) {
        if (n <= cnt[i]) {
            build(i, n);
            break;
        }

        n -= cnt[i];
    }

    output(1);
    return 0;
}