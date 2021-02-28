#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr int maxn = 1e6 + 10;

ll f[maxn];

struct SuffixAutomaton {
    struct Node {
        int next[26], len, link;

        Node() : len(0), link(0) {
            for (int i = 0; i < 26; ++i)
                next[i] = 0;
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    Node tree[maxn];
    int uuid, last;

    SuffixAutomaton() : uuid(1), last(1) {}

    void clear() {
        for (int i = 1; i <= uuid; ++i)
            tree[i] = Node();
        uuid = last = 1;
    }

    void insert(char c) {
        int x = last, nx = last = ++uuid, w = c - 'a';
        f[nx] = 1;
        tree[nx].len = tree[x].len + 1;
        for (; x && !tree[x][w]; x = tree[x].link)
            tree[x][w] = nx;
        if (x == 0) {
            tree[nx].link = 1;
        } else {
            int y = tree[x][w];
            if (tree[y].len == tree[x].len + 1) {
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

SuffixAutomaton sam;
int n, type, len;
ll k, cnt[maxn];
Edge tree[maxn];
int uuid, head[maxn];
char str[maxn], ans[maxn];

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void DFS(int x) {
    if (type == 0)
        f[x] = 1;
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        DFS(y);
        if (type == 1)
            f[x] += f[y];
    }
}

int DFS2(int x) {
    if (cnt[x] != -1)
        return cnt[x];
    cnt[x] = f[x];
    for (int i = 0; i < 26; ++i) {
        if (!sam.tree[x][i])
            continue;
        int y = sam.tree[x][i];
        cnt[x] += DFS2(y);
    }
    return cnt[x];
}

void search(int x, ll k) {
    if (k <= f[x])
        return;
    k -= f[x];
    for (int i = 0; i < 26; ++i) {
        if (!sam.tree[x][i])
            continue;
        int y = sam.tree[x][i];
        if (k > cnt[y]) {
            k -= cnt[y];
        } else {
            putchar(i + 'a');
            search(y, k);
            break;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> (str + 1) >> type >> k;
    n = strlen(str + 1);
    for (int i = 1; i <= n; ++i)
        sam.insert(str[i]);
    for (int i = 2; i <= sam.uuid; ++i)
        link(sam.tree[i].link, i);
    memset(cnt, -1, sizeof(cnt));
    DFS(1);
    f[1] = 0;
    DFS2(1);
    if (cnt[1] < k)
        cout << -1 << endl;
    else
        search(1, k);
    return 0;
}