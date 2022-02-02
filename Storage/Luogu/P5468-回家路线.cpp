#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int maxm = 2e5 + 10;
constexpr long long oo = 0x3f3f3f3f3f3f3f3f;

int n, m, a, b, c;
int from[maxm], to[maxm], st[maxm], ed[maxm];
int seq[maxm], tmp[maxm];
vector<int> lseq[maxn], rseq[maxn];
int q[maxm], fr, bk;
int timer, vis[maxn], ext[maxn], top;
long long f[maxm], ans = oo;

inline long long square(long long x) {
    return x * x;
}

inline long long getX(int i) {
    return ed[i];
}

inline long long getY(int i) {
    return f[i] + 1ll * a * square(ed[i]) - 1ll * b * ed[i];
}

inline double slope(int i, int j) {
    if (getX(i) == getX(j))
        return (getY(i) <= getY(j) ? oo : -oo);

    return 1.0 * (getY(j) - getY(i)) / (getX(j) - getX(i));
}

void update(int id) {
    fr = 1;
    bk = 0;

    for (int i : lseq[id]) {
        while (fr < bk && slope(q[bk - 1], q[bk]) >= slope(q[bk], i))
            --bk;

        q[++bk] = i;
    }

    for (int i : rseq[id]) {
        while (fr < bk && 2 * a * st[i] >= slope(q[fr], q[fr + 1]) && ed[q[fr + 1]] <= st[i])
            ++fr;

        if (fr <= bk && ed[q[fr]] <= st[i]) {
            int j = q[fr];
            f[i] = min(f[i], f[j] + a * square(st[i] - ed[j]) + b * (st[i] - ed[j]) + c);
        }
    }
}

void cdq(int l, int r) {
    if (l >= r)
        return;

    int mid = (l + r) / 2;
    cdq(l, mid);
    top = 0;
    ++timer;

    for (int i = l; i <= mid; ++i)
        lseq[to[seq[i]]].push_back(seq[i]);

    for (int i = mid + 1; i <= r; ++i) {
        rseq[from[seq[i]]].push_back(seq[i]);

        if (vis[from[seq[i]]] != timer) {
            vis[from[seq[i]]] = timer;
            ext[++top] = from[seq[i]];
        }
    }

    for (int i = 1; i <= top; ++i)
        update(ext[i]);

    for (int i = l; i <= mid; ++i)
        lseq[to[seq[i]]].clear();

    for (int i = mid + 1; i <= r; ++i)
        rseq[from[seq[i]]].clear();

    cdq(mid + 1, r);

    int it1 = l, it2 = mid + 1, it = l - 1;

    while (it1 <= mid && it2 <= r) {
        if (ed[seq[it1]] < ed[seq[it2]])
            tmp[++it] = seq[it1++];
        else
            tmp[++it] = seq[it2++];
    }

    while (it1 <= mid)
        tmp[++it] = seq[it1++];

    while (it2 <= r)
        tmp[++it] = seq[it2++];

    for (int i = l; i <= r; ++i)
        seq[i] = tmp[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> a >> b >> c;

    to[0] = 1;

    for (int i = 1; i <= m; ++i)
        cin >> from[i] >> to[i] >> st[i] >> ed[i];

    for (int i = 0; i <= m; ++i)
        seq[i] = i;

    sort(seq + 1, seq + 1 + m, [](int l, int r) {
        return st[l] < st[r];
    });

    for (int i = 1; i <= m; ++i)
        f[i] = oo;

    cdq(0, m);

    for (int i = 1; i <= m; ++i)
        if (to[i] == n)
            ans = min(ans, f[i] + ed[i]);

    cout << ans << endl;
    return 0;
}