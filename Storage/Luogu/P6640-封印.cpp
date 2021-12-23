#include <iostream>
#include <cstring>
using namespace std;

constexpr int maxn = 4e5 + 10;

struct Node {
    int next[26], link, len;

    int &operator[](int x) {
        return next[x];
    }
};

int q;
char s[maxn], t[maxn];
int ls, lt;
Node sam[maxn];
int tot = 1, last = 1;
int pre[maxn], mx[maxn][19], logg[maxn];

void insert(char c) {
    int x = ++tot, p = last, w = c - 'a';
    last = x;
    sam[x].len = sam[p].len + 1;

    for (; p && !sam[p][w]; p = sam[p].link)
        sam[p][w] = x;

    if (!p) {
        sam[x].link = 1;
    } else {
        int q = sam[p][w];

        if (sam[q].len == sam[p].len + 1) {
            sam[x].link = q;
        } else {
            int nq = ++tot;
            sam[nq] = sam[q];
            sam[nq].len = sam[p].len + 1;
            sam[q].link = sam[x].link = nq;

            for (; p && sam[p][w] == q; p = sam[p].link)
                sam[p][w] = nq;
        }
    }
}

void insert(char str[], int len) {
    for (int i = 1; i <= len; ++i)
        insert(str[i]);
}

void match(char str[], int len) {
    int x = 1, l = 0;

    for (int i = 1; i <= len; ++i) {
        int w = str[i] - 'a';

        while (x && !sam[x][w]) {
            x = sam[x].link;
            l = sam[x].len;
        }

        if (sam[x][w]) {
            x = sam[x][w];
            ++l;
        }

        pre[i] = l;
    }
}

int find(int l0, int r0) {
    int l = l0, r = r0, p = r0 + 1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (mid - pre[mid] + 1 >= l0) {
            p = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return p;
}

int query(int l, int r) {
    if (l > r)
        return 0;

    int s = logg[r - l + 1];
    return max(mx[l][s], mx[r - (1 << s) + 1][s]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> (s + 1) >> (t + 1);
    ls = strlen(s + 1);
    lt = strlen(t + 1);
    insert(t, lt);
    match(s, ls);

    logg[0] = -1;

    for (int i = 1; i <= ls; ++i) {
        logg[i] = logg[i / 2] + 1;
        mx[i][0] = pre[i];
        cerr << mx[i][0] << endl;
    }

    for (int j = 1; j <= 18; ++j)
        for (int i = 1; i + (1 << j) - 1 <= ls; ++i)
            mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
    
    cin >> q;

    while (q--) {
        int l, r;
        cin >> l >> r;
        int p = find(l, r);
        cout << max(p - l, query(p, r)) << endl;
    }

    return 0;
}