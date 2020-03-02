#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5;
int n, trie[maxn][2], trtot, setot;
long long a[maxn], b[maxn], seq[maxn];

int create() {
    ++trtot;
    trie[trtot][0] = trie[trtot][1] = 0;
    return trtot;
}

void insert(int idx) {
    int x = 1;
    for (int i = 30; i >= 0; --i) {
        int y = (b[idx] & (1 << i)) ? 1 : 0;
        if (!trie[x][y]) {
            trie[x][y] = create();
        }
        x = trie[x][y];
    }
}

long long query(int id) {
    int x = 1;
    long long ans = 0;
    for (int i = 30; i >= 0; --i) {
        int y = (b[id] & (1 << i)) ? 1 : 0;
        if (trie[x][y]) {
            x = trie[x][y];
        } else {
            x = trie[x][y ^ 1];
            ans |= (1 << i);
        }
    }
    return ans;
}

long long ans = 0;

void solve(vector<int> tree, int d) {
    if (d == -1)
        return;
    if (tree.size() <= 1)
        return;
    vector<int> sons[2];
    for (int i = 0; i < tree.size(); ++i) {
        sons[(bool)(b[tree[i]] & (1 << d))].push_back(tree[i]);
    }
    if (sons[0].size() && sons[1].size()) {
        trtot = 0;
        create();
        long long nowans = 0x3f3f3f3f3f3f3f3f;
        for (int i = 0; i < sons[0].size(); ++i)
            insert(sons[0][i]);
        for (int i = 0; i < sons[1].size(); ++i)
            nowans = min(nowans, query(sons[1][i]));
        ans += nowans;
    }

    if (sons[0].size()) {
        solve(sons[0], d - 1);
    }
    if (sons[1].size()) {
        solve(sons[1], d - 1);
    }
}

int main() {
    scanf("%d", &n);
    vector<int> tree;
    tree.push_back(0);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        b[i] = b[i - 1] ^ a[i];
        tree.push_back(i);
    }
    solve(tree, 30);
    printf("%lld\n", ans);
}