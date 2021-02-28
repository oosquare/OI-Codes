#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct SuffixAutomaton {
    struct Node {
        map<int, int> next;
        int link, len, cnt;

        Node() : link(0), len(0), cnt(1) {
            next.clear();
        }

        int &operator[](int x) {
            return next[x];
        }
    };

    Node tree[maxn * 5];
    int uuid, last;

    SuffixAutomaton() : uuid(1), last(1) {}

    void clear() {
        for (int i = 1; i <= uuid; ++i)
            tree[i] = Node();
        uuid = last = 1;
    }

    int calc() {
        return tree[last].len - tree[tree[last].link].len;
    }

    void insert(int w) {
        int x = last, nx = last = ++uuid;
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

SuffixAutomaton sam;
int n;
long long ans;

int main(int argc, char * argv[]) {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        sam.insert(x);
        ans += sam.calc();
        cout << ans << endl;
    }
    return 0;
}