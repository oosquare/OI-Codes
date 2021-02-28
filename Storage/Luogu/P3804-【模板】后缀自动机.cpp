#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e6 + 10;

int cnt[maxn];

struct SuffixAutomaton {
    struct Node {
        int next[26], len, link;

        int &operator[](int x) {
            return next[x];
        }
    };

    Node tree[maxn];
    int uuid, last;
    
    SuffixAutomaton() : uuid(1), last(1) {
        memset(tree, 0, sizeof(tree));
    }

    void clear() {
        uuid = last = 1;
        memset(tree, 0, sizeof(tree));
    }

    void insert(char c) {
        int x = last, nx = last = ++uuid, w = c - 'a';
        cnt[nx] = 1;
        tree[nx].len = tree[x].len + 1;
        for (; x && !tree[x][w]; x = tree[x].link)
            tree[x][w] = nx;
        if (x == 0) {
            tree[nx].link = 1;
        } else {
            int y = tree[x][w];
            if (tree[x].len + 1 == tree[y].len) {
                tree[nx].link = y;
            } else {
                int ny = ++uuid;
                tree[ny] = tree[y];
                tree[ny].len = tree[x].len + 1;
                tree[y].link = tree[nx].link = ny;
                for (; x && tree[x][w] == y; x = tree[x].link)
                    tree[x][w] = ny;
            }
        }
    }
};

struct Edge {
    int to, next;
};

int n;
long long ans;
char str[maxn];
SuffixAutomaton sam;
Edge tree[maxn];
int uuid, head[maxn];

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void DFS(int x) {
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        DFS(y);
        cnt[x] += cnt[y];
    }
    if (cnt[x] > 1)
        ans = max(ans, 1LL * cnt[x] * sam.tree[x].len);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> (str + 1);
    n = strlen(str + 1);
    for (int i = 1; i <= n; ++i)
        sam.insert(str[i]);
    for (int i = 2; i <= sam.uuid; ++i)
        link(sam.tree[i].link, i);
    DFS(1);
    cout << ans << endl;
    return 0;
}

