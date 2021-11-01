#include <bits/stdc++.h>
using namespace std;

constexpr int maxr = 500 + 10;
constexpr int maxc = 500 + 10;

int r, c, a, b;
int n[maxr][maxc], s[maxc];

bool check(int mid, int line) {
    int sum = 0, cnt = 0;

    for (int i = 1; i <= c; ++i)
        s[i] += n[line][i];

    for (int i = 1; i <= c; ++ i) {
        sum += s[i];

        if (sum >= mid) {
            ++cnt;
            sum = 0;
        }
    }

    return cnt >= b;
}

void clear() {
    for (int i = 1; i <= c; ++i)
        s[i] = 0;
}

bool check(int mid) {
    int cnt = 0;
    clear();

    for (int i = 1; i <= r; ++i) {
        if (check(mid, i)) {
            ++cnt;
            clear();
        }
    }

    return cnt >= a;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> r >> c >> a >> b;

    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
            cin >> n[i][j];

    int left = 0, right = 1000000000, ans = 0;
    
    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << ans << endl;
    return 0;
}