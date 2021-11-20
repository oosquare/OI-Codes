#include <iostream>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>
using namespace std;

constexpr int maxn = 1e6 + 10;
constexpr int maxk = 60 + 10;

int n, k;
vector<int> val, pos[maxn], gift[maxk];
int cnt[maxn], cnt2, ans = 0x3f3f3f3f;

void add(int i) {
    for (int x : pos[i]) {
        if (!cnt[x])
            ++cnt2;

        ++cnt[x];
    }
}

void sub(int i) {
    for (int x : pos[i]) {
        --cnt[x];

        if (!cnt[x])
            --cnt2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;

    for (int i = 1; i <= k; ++i) {
        int t, x;
        cin >> t;

        for (int j = 1; j <= t; ++j) {
            cin >> x;
            gift[i].push_back(x);
            val.push_back(x);
        }
    }

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= k; ++i) {
        for (int &j : gift[i]) {
            j = lower_bound(val.begin(), val.end(), j) - val.begin() + 1;
            pos[j].push_back(i);
        }
    }

    for (int i = 1, j = 1; i <= n; ++i) {
        add(i);

        while (j <= i && cnt2 == k) {
            ans = min(ans, val[i - 1] - val[j - 1]);
            sub(j++);
        }
    }

    cout << ans << endl;
    return 0;
}