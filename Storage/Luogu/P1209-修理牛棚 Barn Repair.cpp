#include <bits/stdc++.h>
using namespace std;

constexpr int maxc = 200 + 10;

struct Range {
    int l, r;

    bool operator<(const Range &rhs) const {
        return r - l + 1 < rhs.r - rhs.l + 1;
    }
};

int m, s, c, a[maxc], b[maxc], t, ans;
vector<Range> v;

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> s >> c;
    for (int i = 1; i <= c; ++i) {
        cin >> a[i];
        b[a[i]] = true;
    }
    b[s + 1] = true;
    Range tmp;
    for (int i = 1; i <= s; ++i) {
        if (b[i] == false) {
            if (b[i + 1] == true) {
                v.push_back(tmp);
                continue;
            }
            ++tmp.r;
        } else {
            if (b[i] == true && b[i + 1] == false) {
                tmp.l = tmp.r = i + 1;
                ++t;
            }
            ++ans;
        }
    }
    if (b[s] == true)
        ++t;
    sort(v.begin(), v.end());
    for (auto [l, r] : v) {
        if (t <= m)
            break;
        if (l == 0 || r == s)
            continue;
        ans += r - l + 1;
        --t;
    }
    cout << ans << endl;
    return 0;
}