#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

constexpr int maxn = 1000 + 10;

int n, m, k, l, d;
int cntr[maxn], cntc[maxn];
int seqr[maxn], seqc[maxn];
int ansr[maxn], ansc[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k >> l >> d;

    for (int i = 1; i <= d; ++i) {
        int x, y, p, q;
        cin >> x >> y >> p >> q;

        if (x == p)
            ++cntc[min(y, q)];
        else
            ++cntr[min(x, p)];
    }

    iota(seqr + 1, seqr + n, 1);
    iota(seqc + 1, seqc + m, 1);

    sort(seqr + 1, seqr + n, [](int l, int r) {
        return cntr[l] > cntr[r];
    });

    sort(seqc + 1, seqc + m, [](int l, int r) {
        return cntc[l] > cntc[r];
    });

    for (int i = 1; i <= k; ++i)
        ansr[i] = seqr[i];

    for (int i = 1; i <= l; ++i)
        ansc[i] = seqc[i];

    sort(ansr + 1, ansr + 1 + k);
    sort(ansc + 1, ansc + 1 + l);

    for (int i = 1; i <= k; ++i)
        cout << ansr[i] << " ";

    cout << endl;

    for (int i = 1; i <= l; ++i)
        cout << ansc[i] << " ";

    cout << endl;
    return 0;
}