#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 4 * 1e6 + 10;
int n, m, q;
struct arr {
    int f[4 * maxn];
    int* operator[](int x) { return f + x * m; }
} mp;  


arr v, lf, rt;
int len[4 * maxn], ql[maxn], qr[maxn], hd1, tl1, hd2, tl2;
char str[maxn];

void merge(int p, int p1, int p2) {
    hd1 = hd2 = 1;
    tl1 = tl2 = 0;
    for (int i = 1, j = 1; i <= m; i++) {
        while (hd1 <= tl1 && lf[p2][ql[tl1]] > lf[p2][i]) tl1--;
        ql[++tl1] = i;  
        while (hd2 <= tl2 && rt[p1][qr[tl2]] > rt[p1][i]) tl2--;
        qr[++tl2] = i;
        while (hd1 <= tl1 && hd2 <= tl2 &&
               lf[p2][ql[hd1]] + rt[p1][qr[hd2]] < (i - j + 1)) {
            if (ql[hd1] <= j) 
                hd1++;
            if (qr[hd2] <= j)
                hd2++;
            j++;
        }
        v[p][i] = max(v[p1][i], v[p2][i]);
        v[p][i] = max(v[p][i], (i - j + 1));  
    }
    for (int i = 1; i <= m; i++)
        lf[p][i] = (lf[p1][i] == len[p1]) ? lf[p1][i] + lf[p2][i]
                                          : lf[p1][i];  
    for (int i = 1; i <= m; i++)
        rt[p][i] = (rt[p2][i] == len[p2]) ? rt[p2][i] + rt[p1][i]
                                          : rt[p2][i];  
}

int merge(int p1, int p2, int l, int r) {
    hd1 = hd2 = 1;
    tl1 = tl2 = 0;
    int ret = 0;
    for (int i = l, j = l; i <= r; i++) {
        while (hd1 <= tl1 && lf[p2][ql[tl1]] > lf[p2][i]) tl1--;
        ql[++tl1] = i;
        while (hd2 <= tl2 && rt[p1][qr[tl2]] > rt[p1][i]) tl2--;
        qr[++tl2] = i;
        while (hd1 <= tl1 && hd2 <= tl2 &&
               lf[p2][ql[hd1]] + rt[p1][qr[hd2]] < (i - j + 1)) {
            if (ql[hd1] == j)
                hd1++;
            if (qr[hd2] == j)
                hd2++;
            j++;
        }
        ret = max(ret, (i - j + 1));
    }
    for (int i = l; i <= r; i++)
        lf[p1][i] =
            (lf[p1][i] == len[p1]) ? lf[p1][i] + lf[p2][i] : lf[p1][i];
    for (int i = l; i <= r; i++)
        rt[p1][i] =
            (rt[p2][i] == len[p2]) ? rt[p2][i] + rt[p1][i] : rt[p2][i];
    len[p1] += len[p2];
    return ret;
}

void modify(int p, int l, int r, int pos, int px) {
    if (r - l == 1) {
        v[p][px] = lf[p][px] = rt[p][px] = mp[r][px];
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        modify(p << 1, l, mid, pos, px);
    else
        modify(p << 1 | 1, mid, r, pos, px);
    merge(p, p << 1, p << 1 | 1);
}

int query(int p, int l, int r, int dl, int dr, int xl, int xr) {
    if (dl == l && dr == r) {
        int ret = merge(0, p, xl, xr);  
        for (int i = xl; i <= xr; i++)
            ret = max(ret, min(v[p][i], i - xl + 1));
        return ret;  
    }
    int ret = 0;
    int mid = (l + r) / 2;
    if (dl < mid)
        ret = max(ret, query(p << 1, l, mid, dl, min(dr, mid), xl, xr));
    if (mid < dr)
        ret = max(ret, query(p << 1 | 1, mid, r, max(dl, mid), dr, xl, xr));
    return ret;
}

int cquery(int dl, int dr, int xl, int xr) {
    for (int i = 1; i <= m; i++) v[0][i] = lf[0][i] = rt[0][i] = 0;
    len[0] = 0;
    return query(1, 0, n, dl, dr, xl, xr);
}

void build(int p, int l, int r) {
    if (r - l == 1) {
        for (int i = 1; i <= m; i++)
            lf[p][i] = rt[p][i] = v[p][i] = mp[r][i];
        len[p] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid, r);
    len[p] = len[p << 1] + len[p << 1 | 1];
    merge(p, p << 1, p << 1 | 1);

}
int main() {
#ifndef ONLINE_JUDGE
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#else
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> (str + 1);
        for (int j = 1; j <= m; j++) mp[i][j] = str[j] == '.' ? 1 : 0;
    }
    build(1, 0, n);
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        mp[x][y] ^= 1;
        modify(1, 0, n, x, y);
        cout << cquery(0, n, 1, m) << endl;
    }
    return 0;  
}
