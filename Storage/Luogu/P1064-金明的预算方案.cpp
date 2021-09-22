#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3.2e3 + 10;
constexpr int maxm = 60 + 10;

struct Item {
    int v, p, q;
};

struct Group {
    Item main;
    vector<Item> sub;
    int sum, p[maxn];

    void calc() {
        sum = main.v;
        for (auto i : sub) sum += i.v;
        p[main.v] = main.p;
        for (int i = 1, e = (int)sub.size(); i <= e; ++i) {
            for (int j = sum; j >= sub[i - 1].v + main.v; --j) {
                p[j] = max(p[j], p[j - sub[i - 1].v] + sub[i - 1].p);
            }
        }
    }
};

Item it[maxm];
Group g[maxm];
int n, m, idx[maxm], cnt, f[maxn];

void Dp() {
    for (int i = 1; i <= cnt; ++i) {
        for (int j = n; j >= 0; --j) {
            for (int k = g[i].main.v; k <= g[i].sum; ++k) {
                if (j < k) continue;
                f[j] = max(f[j], f[j - k] + g[i].p[k]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    n /= 10;
    for (int i = 1; i <= m; ++i) {
        cin >> it[i].v >> it[i].p >> it[i].q;
        it[i].p *= it[i].v;
        it[i].v /= 10;
        if (it[i].q == 0) idx[i] = ++cnt;
    }
    for (int i = 1; i <= m; ++i) {
        if (it[i].q == 0) g[idx[i]].main = it[i];
        else g[idx[it[i].q]].sub.push_back(it[i]);
    }
    for (int i = 1; i <= cnt; ++i) g[i].calc();
    Dp();
    cout << f[n] << endl; 
    return 0;
}