#include <iostream>
using namespace std;

constexpr int MAXN = 2e5 + 10;

int n, q, p, t[MAXN], k[MAXN], pos[MAXN][3];
bool del[MAXN];
int lst, ans[MAXN];

namespace Subtask1 {

int sav[MAXN][3], val[MAXN];

void find() {
    lst = 0;

    for (int i = 1; i <= p; ++i) {
        if (del[i])
            continue;

        int sum = 0;

        for (int j = 0; j < k[i]; ++j)
            sum += val[pos[i][j]] - sav[i][j];

        if (sum >= t[i]) {
            del[i] = true;
            ++lst;
            ans[lst] = i;
        }
    }
}

void main() {
    for (int i = 1; i <= q; ++i) {
        int op;
        cin >> op;

        if (op == 1) {
            ++p;
            cin >> t[p] >> k[p];
            t[p] ^= lst;

            for (int j = 0; j < k[p]; ++j) {
                cin >> pos[p][j];
                pos[p][j] ^= lst;
                sav[p][j] = val[pos[p][j]];
            }
        } else {
            int x, y;
            cin >> x >> y;
            x ^= lst;
            y ^= lst;
            val[x] += y;
            find();
            cout << lst << " ";

            for (int j = 1; j <= lst; ++j)
                cout << ans[j] << " ";

            cout << endl;
        }
    }
}

} // namespace Subtask1

int main() {
#ifdef ONLINE_JUDGE
    freopen("obs.in", "r", stdin);
    freopen("obs.out", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> q;

    if (n <= 1000 && q <= 1000)
        Subtask1::main();

#ifdef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}