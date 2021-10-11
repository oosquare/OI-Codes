#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 10;
constexpr int maxm = 100 + 10;
constexpr int oo = 0x3f3f3f3f;

struct Switch {
    int on = 0, off = (1 << 10) - 1;

    void set(int p, int type) {
        if (type == 1)
            off &= ~(1 << (p - 1));
        else if (type == -1)
            on |= 1 << (p - 1);
    }

    int turn(int status) {
        status |= on;
        status &= off;
        return status;
    }
};

int n, m;
Switch s[maxm];
int f[1 << maxn], vis[1 << maxn];

void bfs() {
    memset(f, 0x3f, sizeof(f));
    queue<int> q;
    vis[(1 << n) - 1] = true;
    f[(1 << n) - 1] = 0;
    q.push((1 << n) - 1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 1; i <= m; ++i) {
            int y = s[i].turn(x);
            if (vis[y])
                continue;
            f[y] = f[x] + 1;
            vis[y] = true;
            q.push(y);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x;
            cin >> x;
            s[i].set(j, x);
        }
    }
    bfs();
    cout << (f[0] != oo ? f[0] : -1) << endl;
    return 0;
}