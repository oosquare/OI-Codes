#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;

struct Edge {
    int x, y, r;

    bool operator<(const Edge &rhs) {
        return r > rhs.r;
    }
};

struct Query {
    int k, v, id;

    bool operator<(const Query &rhs) {
        return k > rhs.k;
    }
};

Edge edge[maxn];
Query query[maxn];
int fa[maxn], sze[maxn], ans[maxn], n, q;

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy)
        return;
    fa[fy] = fx;
    sze[fx] += sze[fy];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    iota(fa + 1, fa + 1 + n, 1);
    fill(sze + 1, sze + 1 + n, 1);
    for (int i = 1; i < n; ++i)
        cin >> edge[i].x >> edge[i].y >> edge[i].r;
    for (int i = 1; i <= q; ++i) {
        cin >> query[i].k >> query[i].v;
        query[i].id = i;
    }
    sort(edge + 1, edge + 1 + n);
    sort(query + 1, query + 1 + q);
    int j = 1;
    for (int i = 1; i <= q; ++i) {
        while (j < n && edge[j].r >= query[i].k) {
            merge(edge[j].x, edge[j].y);
            ++j;
        }
        ans[query[i].id] = sze[find(query[i].v)] - 1;
    }
    copy(ans + 1, ans + 1 + q, ostream_iterator<int>(cout, "\n"));
    return 0;
}