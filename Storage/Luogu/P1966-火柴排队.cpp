#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int mod = 1e8 - 3;

struct BinaryIndexedTree {
    int tree[maxn], size;

    int lowbit(int x) {
        return x & (-x);
    }
    
    void add(int pos, int val) {
        for (; pos <= size; pos += lowbit(pos))
            tree[pos] = (tree[pos] + val) % mod;
    }
    
    int query(int pos) {
        int res = 0;
    
        for (; pos; pos -= lowbit(pos))
            res = (res + tree[pos]) % mod;
    
        return res;
    }
};

int n, a[maxn], b[maxn];
int pos[maxn], p[maxn];
int ans;
BinaryIndexedTree fr, bk;

void discretize(int arr[]) {
    vector<int> val;

    for (int i = 1; i <= n; ++i)
        val.push_back(arr[i]);

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    for (int i = 1; i <= n; ++i)
        arr[i] = lower_bound(val.begin(), val.end(), arr[i]) - val.begin() + 1;    
}


int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    fr.size = bk.size = n;

    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    for (int i = 1; i <= n; ++i)
        cin >> b[i];

    discretize(a);
    discretize(b);
    
    for (int i = 1; i <= n; ++i)
        pos[b[i]] = i;

    for (int i = 1; i <= n; ++i)
        p[i] = pos[a[i]];

    for (int i = 1; i <= n; ++i) {
        ans = (ans + abs(i - p[i])) % mod;

        if (p[i] < i) {
            ans = (ans - (bk.query(n) - bk.query(p[i])) + mod) % mod;
            ans = (ans + (fr.query(n) - fr.query(p[i]))) % mod;
            fr.add(p[i], 1);
        } else if (p[i] > i) {
            ans = (ans + (bk.query(n) - bk.query(p[i]))) % mod;
            bk.add(p[i], 1);
        }
    }

    cout << ans << endl;
    return 0;
}