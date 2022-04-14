#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5 + 10;

struct opmodify {
    int time, pos, prev, val;

    bool operator<(opmodify rhs) {
        return prev < rhs.prev;
    }
};

struct opquery {
    int time, l, r, ans;

    bool operator<(opquery rhs) {
        return l < rhs.l;
    }
};

struct block {
    int l, r, x;
    
    bool operator<(block rhs) const {
        return r < rhs.r;
    }
};

struct range {
    int l, r;

    bool operator<(range rhs) const {
        return r < rhs.r;
    }
};

opmodify md[maxn * 10];
opquery qr[maxn * 10];
int n, m, a[maxn], pre[maxn], las[maxn * 2], pre2[maxn];
int type[maxn], mleft[maxn], mright[maxn], val[maxn];
int top1, top2, cnt;
vector<int> vec;
int bitree[maxn], srt[maxn];
set<block> num;
set<range> rgs[maxn];
set<int> bd;

bool cmp(opquery lhs, opquery rhs) {
    return lhs.time < rhs.time;
}

void addop(int pos, int c) {
    if (pre2[pos] == c)
        return;
    md[++top1] = {++cnt, pos, pre2[pos], -1};
    md[++top1] = {++cnt, pos, pre2[pos] = c, 1};
}

int getid(int x) {
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1;
}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], vec.push_back(a[i]);
    for (int i = 1; i <= m; ++i) {
        cin >> type[i] >> mleft[i] >> mright[i];
        if (type[i] == 1)
            cin >> val[i], vec.push_back(val[i]);
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (int i = 1; i <= n; ++i)
        a[i] = getid(a[i]);
    for (int i = 1; i <= m; ++i)
        if (type[i] == 1)
            val[i] = getid(val[i]);
    for (int i = 1; i <= n; ++i)
        pre[i] = las[a[i]], las[a[i]] = i, pre2[i] = pre[i];
}

void split(int mid) {
    auto it = num.lower_bound({0, mid, 0});
    block p = *it;
    if (mid == p.r)
        return;
    num.erase(it);
    num.insert({p.l, mid, p.x});
    num.insert({mid + 1, p.r, p.x});
    rgs[p.x].erase({p.l, p.r});
    rgs[p.x].insert({p.l, mid});
    rgs[p.x].insert({mid + 1, p.r});
}

void remove(set<block>::iterator it) {
    bd.insert(it->l);
    set<range>::iterator it1, it2;
    it1 = it2 = rgs[it->x].find({it->l, it->r});
    ++it2;
    if (it2 != rgs[it->x].end())
        bd.insert(it2->l);
    rgs[it->x].erase(it1);
    num.erase(it);
}

void insert(block p) {
    num.insert(p);
    auto it = rgs[p.x].insert({p.l, p.r}).first;
    ++it;
    if (it != rgs[p.x].end())
        bd.insert(it->l);
}

void assign(int l, int r, int v) {
    if (l != 1)
        split(l - 1);
    split(r);
    int p = l;
    while (p != r + 1) {
        auto it = num.lower_bound({0, p, 0});
        p = it->r + 1;
        remove(it);
    }
    insert({l, r, v});
    for (auto it = bd.begin(); it != bd.end(); ++it) {
        auto it1 = num.lower_bound({0, *it, 0});
        if (*it != it1->l) {
            addop(*it, *it - 1);
        } else {
            auto it2 = rgs[it1->x].lower_bound({0, *it});
            if (it2 != rgs[it1->x].begin())
                --it2, addop(*it, it2->r);
            else
                addop(*it, 0);
        }
    }
    bd.clear();
}

void insert() {
    int nc = a[1];
    int ccnt = 1;
    for (int i = 2; i <= n; ++i) {
        if (nc != a[i]) {
            num.insert({i - ccnt, i - 1, nc});
            rgs[nc].insert({i - ccnt, i - 1});
            nc = a[i];
            ccnt = 1;
        } else {
            ++ccnt;
        }
    }
    num.insert({n - ccnt + 1, n, a[n]});
    rgs[a[n]].insert({n - ccnt + 1, n});
}

int lowbit(int x) {
    return x & (-x);
}

void add(int p, int v) {
    for (; p <= n; p += lowbit(p))
        bitree[p] += v;
}

int query(int p) {
    int res = 0;
    for (; p; p -= lowbit(p))
        res += bitree[p];
    return res;
}

void clear(int p) {
    for (; p <= n; p += lowbit(p))
        if (bitree[p])
            bitree[p] = 0;
        else
            return;
}

bool cmp1(int a, int b) {
    return pre[a] < pre[b];
}

void divide(int l1, int r1, int l2, int r2, int l, int r) {
    if (l1 == r1 || l2 == r2)
        return;
    int mid = (l + r) / 2;
    int mid1 = l1;
    while (mid1 != r1 && md[mid1 + 1].time <= mid)
        ++mid1;
    int mid2 = l2;
    while (mid2 != r2 && qr[mid2 + 1].time <= mid)
        ++mid2;
    divide(l1, mid1, l2, mid2, l, mid);
    divide(mid1, r1, mid2, r2, mid, r);
    if (l1 != mid1 && mid2 != r2) {
        sort(md + l1 + 1, md + mid1 + 1);
        sort(qr + mid2 + 1, qr + r2 + 1);
        for (int i = mid2 + 1, j = l1 + 1; i <= r2; ++i) {
            while (j <= mid1 && md[j].prev < qr[i].l)
                add(md[j].pos, md[j].val), ++j;
            qr[i].ans += query(qr[i].r) - query(qr[i].l - 1);
        }
        for (int i = l1 + 1; i <= mid1; ++i)
            clear(md[i].pos);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#else
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    input();
    insert();
    for (int i = 1; i <= m; ++i) {
        if (type[i] == 1)
            assign(mleft[i], mright[i], val[i]);
        else
            qr[++top2] = {++cnt, mleft[i], mright[i], 0};
    }
    sort(qr + 1, qr + top2 + 1);
    for (int i = 1; i <= n; ++i)
        srt[i] = i;
    sort(srt + 1, srt + 1 + n, cmp1);
    for (int i = 1, j = 1; i <= top2; ++i) {
        while (j <= n && pre[srt[j]] < qr[i].l)
            add(srt[j], 1), ++j;
        qr[i].ans += query(qr[i].r) - query(qr[i].l - 1);
    }
    for (int i = 1; i <= n; ++i)
        bitree[i] = 0;
    sort(qr + 1, qr + top2 + 1, cmp);
    divide(0, top1, 0, top2, 0, cnt);
    sort(qr + 1, qr + top2 + 1, cmp);
    for (int i = 1; i <= top2; ++i)
        cout << qr[i].ans << endl;
    return 0;
}
