#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int none = 0;
constexpr int red = 1;
constexpr int blue = 2;

struct Edge {
    int to, next;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int color[maxn], cnt[3][maxn], leaf[maxn];
int t, n;
vector<int> ans;

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void DFS(int x) {
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        DFS(y);
        cnt[red][x] += (color[y] == red);
        cnt[blue][x] += (color[y] == blue);
        leaf[x] = false;
    }
    if (leaf[x] == false) {
        if (cnt[red][x] > cnt[blue][x])
            color[x] = red;
        else if (cnt[red][x] == cnt[blue][x])
            color[x] = none;
        else
            color[x] = blue;
    }
}

void getans(int x) {
    if (leaf[x])
        ans.push_back(x);
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next)
        if (color[y] == none || cnt[blue][y] - 1 == cnt[red][y])
            getans(y);
}

void solve() {
    uuid = 0;
    memset(head, 0, sizeof(head));
    memset(cnt, 0, sizeof(cnt));
    memset(leaf, 1, sizeof(leaf));
    ans.clear();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int fa;
        cin >> fa;
        if (fa == 0)
            continue;
        link(fa, i);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
        ++color[i];
    }
    DFS(1);
    if (color[1] == blue) {
        cout << -1 << endl;
        return;
    }
    if (color[1] == red) {
        for (int i = 1; i <= n; ++i)
            if (leaf[i] && color[i] == none)
                ans.push_back(i);
        cout << ans.size() << " ";
        for (int i : ans)
            cout << i << " ";
        cout << endl;
    } else {
        getans(1);
        sort(ans.begin(), ans.end());
        cout << ans.size() << " ";
        for (int i : ans)
            cout << i << " ";
        cout << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("rab.in", "r", stdin);
    freopen("rab.out", "w", stdout);
#endif
    cin >> t;
    while (t--)
        solve();
    return 0;
}
/*
#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int none = 0;
constexpr int red = 1;
constexpr int blue = 2;

struct Edge {
    int to, next;
};

Edge tree[maxn * 2];
int uuid, head[maxn];
int color[maxn], cnt[maxn], leaf[maxn];
int t, n;
vector<int> ans;

void link(int x, int y) {
    tree[++uuid] = {y, head[x]};
    head[x] = uuid;
}

void DFS(int x) {
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        DFS(y);
        cnt[x] += (color[y] == 0);
        cnt[x] -= (color[y] == 1);
        leaf[x] = false;
    }
    if (leaf[x] == false)
        color[x] = cnt[x] == 0 ? -1 : (cnt[x] < 0);
}

void getans(int x) {
    if (leaf[x])
        ans.push_back(x);
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next)
        if (color[y] == -1 || cnt[y] == -1)
            getans(y);
}

void solve() {
    uuid = 0;
    memset(head, 0, sizeof(head));
    memset(cnt, 0, sizeof(cnt));
    memset(leaf, 1, sizeof(leaf));
    ans.clear();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int fa;
        cin >> fa;
        if (fa == 0)
            continue;
        link(fa, i);
    }
    for (int i = 1; i <= n; ++i)
        cin >> color[i];
    DFS(1);
    if (color[1] == 1) {
        cout << -1 << endl;
        return;
    }
    if (color[1] == -1) {
        for (int i = 1; i <= n; ++i)
            if (leaf[i] && color[i] != none)
                ans.push_back(i);
        cout << ans.size() << " ";
        for (int i : ans)
            cout << i << " ";
        cout << endl;
    } else {
        getans(1);
        sort(ans.begin(), ans.end());
        cout << ans.size() << " ";
        for (int i : ans)
            cout << i << " ";
        cout << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("rab.in", "r", stdin);
    freopen("rab.out", "w", stdout);
#endif
    cin >> t;
    while (t--)
        solve();
    return 0;
}
*/
