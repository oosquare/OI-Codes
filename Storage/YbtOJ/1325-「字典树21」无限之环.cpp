#include <bits/stdc++.h>
using namespace std;

struct Node {
    int next[2];
    int cnt;
    bool end;
};

Node trie[20000 * 1000 + 100];
constexpr int root = 1;
int uuid = root, n, mlen;
string str[20001];

void insert(string s, int r) {
    int x = root;
    for (int i = 1; i <= r; ++i) {
        for (int j = 0; j < (int)s.size(); ++j) {
            if (trie[x].next[s[j] - '0'] == 0)
                trie[x].next[s[j] - '0'] = ++uuid;
            x = trie[x].next[s[j] - '0'];
            ++trie[x].cnt;
        }
    }
    trie[x].end = true;
}

int DFS(int x) {
    if (x == 0)
        return 0;
    if (trie[x].cnt == 1)
        return 0;
    int res = max(DFS(trie[x].next[0]), DFS(trie[x].next[1]));
    return res + 1;

}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> str[i];
        mlen = max(mlen, (int)str[i].size());
    }
    mlen *= 2;
    for (int i = 1; i <= n; ++i)
        insert(str[i], ceil(mlen / str[i].size()));
    cout << DFS(root) - 1 << endl;
}
