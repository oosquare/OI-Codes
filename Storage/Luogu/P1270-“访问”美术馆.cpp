#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 200 + 10;
constexpr int maxt = 600 + 10;

struct Node {
    int time, cnt, ls, rs;
};

Node tree[maxn];
int t, n, limit[maxn], f[maxn][maxt];

inline int &ls(int x) { return tree[x].ls; }

inline int &rs(int x) { return tree[x].rs; }

inline int leaf(int x) { return tree[x].ls == 0 && tree[x].rs == 0; }

int build() {
    int x = ++n;
    cin >> tree[x].time >> tree[x].cnt;
    tree[x].time *= 2;
    limit[x] = tree[x].time;
    if (tree[x].cnt == 0) {
        ls(x) = build();
        rs(x) = build();
        limit[x] += limit[ls(x)] + limit[rs(x)];
    } else {
        limit[x] += 5 * tree[x].cnt;
    }
    return x;
}

void DP(int x) {
    if (leaf(x)) {
        for (int i = tree[x].time + 1; i <= limit[x]; ++i) {
            f[x][i] = (i - tree[x].time) / 5;
        }
        return;
    } else {
        DP(ls(x));
        DP(rs(x));
        for (int i = tree[x].time + 1; i <= limit[x]; ++i) {
            for (int j = 0, e = i - tree[x].time; j <= e; ++j) {
                int j1 = min(j, limit[ls(x)]), j2 = min(e - j, limit[rs(x)]);
                if (f[x][i] < f[ls(x)][j1] + f[rs(x)][j2]) {
                    f[x][i] = f[ls(x)][j1] + f[rs(x)][j2];
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    build();
    DP(1);
    cout << f[1][min(t - 1, limit[1])] << endl;
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << " : ";
    //     for (int j = 1; j <= limit[i]; ++j) {
    //         cout << f[i][j];
    //         if (j % 5 == 0) cout << ", ";
    //         else cout << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}