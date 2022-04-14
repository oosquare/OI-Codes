#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

constexpr int MAXN = 2e5 + 10;

struct Node {
    int id;
    double val;

    bool operator<(const Node & rhs) const {
        return val != rhs.val ? val < rhs.val : id < rhs.id;
    }
};

int n, q, p;
set<Node> buc[MAXN];
int t[MAXN], k[MAXN], pos[MAXN][3];
double val[MAXN][3];
long long arr[MAXN], save[MAXN][3];
int lst, ans[MAXN];

void init(int id) {
    for (int i = 0; i < k[id]; ++i) {
        save[id][i] = arr[pos[id][i]];
        val[id][i] = 1.0 * arr[pos[id][i]] + 1.0 * t[id] / k[id];
        buc[pos[id][i]].insert({ id, val[id][i] });
    }

    for (int i = 0; i < k[id]; ++i)
        t[id] += arr[pos[id][i]];
}

void find(int x, int y) {
    arr[x] += y;

    while (buc[x].size() && buc[x].begin()->val <= arr[x]) {
        int id = buc[x].begin()->id;
        double sum = 0, tmp = 0;

        for (int i = 0; i < k[id]; ++i) {
            buc[pos[id][i]].erase({ id, val[id][i] });
            sum += val[id][i];
            tmp += arr[pos[id][i]];
        }

        if (tmp < t[id]) {
            for (int i = 0; i < k[id]; ++i) {
                val[id][i] = (sum - tmp) / k[id] + arr[pos[id][i]];
                buc[pos[id][i]].insert({ id, val[id][i] });
            }
        } else {
            ans[++lst] = id;
        }
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("obs.in", "r", stdin);
    freopen("obs.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> q;

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
            }

            init(p);
        } else {
            int x, y;
            cin >> x >> y;
            x ^= lst;
            y ^= lst;
            lst = 0;
            find(x, y);
            sort(ans + 1, ans + 1 + lst);
            cout << lst << " ";

            for (int j = 1; j <= lst; ++j)
                cout << ans[j] << " ";

            cout << endl;
        }
    }
    return 0;
}
