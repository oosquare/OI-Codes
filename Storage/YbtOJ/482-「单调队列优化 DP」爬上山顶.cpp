#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5 + 10;

// #define int long long

typedef long long ll;

struct point {
    int x, y;

    bool operator>(point rhs) {
        if (y == rhs.y)
            return x >= rhs.x;
        return y > rhs.y;
    }
};

struct edge {
    int to, next;
    ll weight;
};

point ps[maxn];
int lh[maxn], rh[maxn], h[maxn], pre[maxn], nxt[maxn];
edge tree[maxn];
int uuid, root, head[maxn], in[maxn];
ll dis[maxn];
int n, st[maxn], top;

void link(int x, int y, int w) {
    tree[++uuid] = {y, head[x], w};
    head[x] = uuid;
    ++in[y];
}

bool sless(point i, point j, point k) {
    return 1LL * (j.y - i.y) * (k.x - j.x) < 1LL * (k.y - j.y) * (j.x - i.x);
}

void DFS(int x) {
    for (int i = head[x], y; y = tree[i].to, i; i = tree[i].next) {
        dis[y] = dis[x] + tree[i].weight;
        DFS(y);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("mountain.in", "r", stdin);
    freopen("mountain.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> ps[i].x >> ps[i].y;

    lh[1] = 0;
    st[top = 1] = 1;
    for (int i = 2; i <= n; ++i) {
        while (top >= 2 && sless(ps[st[top - 1]], ps[st[top]], ps[i]))
            --top;
        if (ps[st[top]] > ps[i])
            lh[i] = st[top];
        st[++top] = i;
    }
    rh[n] = 0;
    st[top = 1] = n;
    for (int i = n - 1; i >= 1; --i) {
        while (top >= 2 && sless(ps[i], ps[st[top]], ps[st[top - 1]]))
            --top;
        if (ps[st[top]] > ps[i])
            rh[i] = st[top];
        st[++top] = i;
    }
    for (int i = 1; i <= n; ++i)
        h[i] = ps[rh[i]].y >= ps[lh[i]].y ? rh[i] : lh[i];

    st[top = 1] = 1;
    for (int i = 2; i <= n; ++i) {
        while (top >= 1 && ps[h[i]] > ps[h[st[top]]])
            --top;
        if (h[i] && h[i] < i) {
            int j = top ? st[top] : h[i];
            link(j, i, abs(j - i));
        }
        st[++top] = i;
    }
    st[top = 1] = n;
    for (int i = n - 1; i >= 1; --i) {
        while (top >= 1 && ps[h[i]] > ps[h[st[top]]])
            --top;
        if (h[i] && h[i] > i) {
            int j = top ? st[top] : h[i];
            link(j, i, abs(j - i));
        }
        st[++top] = i;
    }

    for (int i = 1; i <= n; ++i)
        if (!in[i]) {
            root = i;
            break;
        }
    DFS(root);
    
    for (int i = 1; i <= n; ++i)
        cout << dis[i] << endl;
    return 0;
}
