#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 3e5 + 10;

struct Range {
    long long l, r;
    int id;

    bool operator<(const Range & rhs) const {
        return (r != rhs.r ? r < rhs.r : l > rhs.l);
    }
};

int n, a[MAX_N], b[MAX_N], c[MAX_N];
long long sumb[MAX_N], sumc[MAX_N];
int arr[MAX_N];
int f[MAX_N], ans = 0x3f3f3f3f;
Range range[MAX_N];

bool check() {
    for (int i = 1; i < n; ++i)
        if (b[i] > c[i])
            return false;
    
    return true;
}

void discretize() {
    vector<long long> val;
    
    for (int i = 1; i <= n; ++i)
        val.push_back(range[i].l);
    
    sort(val.begin(), val.end());
    auto it = unique(val.begin(), val.end());
    val.erase(it, val.end());

    for (int i = 1; i <= n; ++i)
        range[i].l = (long long) (lower_bound(val.begin(), val.end(), range[i].l) - val.begin() + 1);
}

int lowbit(int x) {
    return x & (-x);
}

void update(int x, int y) {
    x = n - x + 1;
    
    for (; x <= n; x += lowbit(x))
        arr[x] = max(arr[x], y);
}

int query(int x) {
    x = n - x + 1;
    int res = 0;

    for (; x; x -= lowbit(x))
        res = max(res, arr[x]);
    
    return res;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("clyz.in", "r", stdin);
    freopen("clyz.out", "w", stdout);
#else
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    
    for (int i = 1; i < n; ++i)
        cin >> b[i];
    
    for (int i = 1; i < n; ++i)
        cin >> c[i];

    if (!check()) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        sumb[i] = sumb[i - 1] + b[i - 1];
        sumc[i] = sumc[i - 1] + c[i - 1];
        // cout << i << " : ";
        range[i] = { a[i] - sumc[i], a[i] - sumb[i], i };
        // cout << "(" << range[i].l << ", " << range[i].r << ") " << endl;
    }

    sort(range + 1, range + 1 + n);
    discretize();

    // for (int i = 0; i <= n + 1; ++i)
    //     arr[i] = -1;
    
    // f[1] = 1;
    // update(range[1].l, f[1]);
    // ans = min(ans, n - f[1]);

    for (int i = 1; i <= n; ++i) {
        f[i] = query((int) range[i].l) + 1;
        update((int) range[i].l, f[i]);
        ans = min(ans, n - f[i]);
        // cout << "(" << range[i].l << ", " << range[i].r << ") " << range[i].id << " " << f[i] << endl;
    }

    cout << ans << endl;
    return 0;
}
