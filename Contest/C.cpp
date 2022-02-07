#include <iostream>
using namespace std;

constexpr int MAXN = 1e5 + 10;

int n, q;
char str[MAXN];
int lst;

namespace Subtask1 {

bool similar(int l1, int r1, int l2, int r2) {
    int len = r1 - l1 + 1;

    for (int i = 1; i < len; ++i)
        for (int j = i + 1; j <= len; ++j)
            if ((str[l1 + i - 1] == str[l1 + j - 1]) != (str[l2 + i - 1] == str[l2 + j - 1]))
                return false;

    return true;
}

int query(int l, int r) {
    int res = 0;

    for (int i = 1, j = r - l + 1; j <= n; ++i, ++j)
        if (similar(i, j, l, r))
            ++res;

    return res;
}

void main() {
    for (int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        l ^= lst;
        r ^= lst;
        lst = query(l, r);
        cout << lst << endl;
    }
}

} // namespace Subtask1

namespace Subtask2 {

constexpr int MAXN2 = 4000 + 10;
constexpr int base1 = 281;
constexpr int base2 = 379;
constexpr int mod = 998244353;

int pos[10];
int val[MAXN2][MAXN2], buc[10];

int calc(int p) {
    return (1ll * buc[str[p] - '0'] * base1 + (pos[str[p] - '0'] - p + 1)) % mod;
}

void preprocess() {
    for (int r = n; r >= 1; --r) {
        for (int i = 0; i < 10; ++i) {
            pos[i] = r + 1;
            buc[i] = 0;
        }

        for (int l = r; l >= 1; --l) {
            int v = calc(l);
            val[l][r] = (1ll * val[l + 1][r] * base2 + v) % mod;
            buc[str[l] - '0'] = v;
            pos[str[l] - '0'] = l;
        }
    }
}

int query(int l, int r) {
    int res = 0;

    for (int i = 1, j = r - l + 1; j <= n; ++i, ++j)
        if (val[i][j] == val[l][r])
            ++res;

    return res;
}

void main() {
    preprocess();
    
    for (int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        l ^= lst;
        r ^= lst;
        lst = query(l, r);
        cout << lst << endl;
    }
}

} // namespace Subtask2


int main() {
#ifdef ONLINE_JUDGE
    freopen("similar.in", "r", stdin);
    freopen("similar.out", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> q;
    cin >> (str + 1);

    if (n <= 400 && q <= 400)
        Subtask1::main();
    else
        Subtask2::main();

#ifdef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
#endif

    return 0;
}