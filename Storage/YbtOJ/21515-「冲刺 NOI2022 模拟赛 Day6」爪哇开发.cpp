#include <iostream>
using namespace std;

constexpr int MAX_N = 3e5 + 10;
constexpr int INFINITY = 0x3f3f3f3f;

struct Range {
    int l, r;

    Range(int l = INFINITY, int r = -INFINITY) {
        this->l = l;
        this->r = r;
    }

    bool empty() const { return l > r; }

    Range operator&(const Range & rhs) const {
        if (empty() || rhs.empty() || r < rhs.l || rhs.r < l) return Range();
        return Range(max(l, rhs.l), min(r, rhs.r));
    }
};

int n;
Range range[MAX_N];

Range st[MAX_N][20];
int log2Val[MAX_N];

long long f[MAX_N];
int stk[MAX_N], top;

void preprocess() {
    log2Val[0] = -1;
    for (int i = 1; i <= n; ++i) {
        log2Val[i] = log2Val[i / 2] + 1;
        st[i][0] = range[i];
    }
    for (int j = 1; j <= 19; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            st[i][j] = (st[i][j - 1] & st[i + (1 << (j - 1))][j - 1]);
}

Range intersection(int l, int r) {
    if (l > r) return Range();
    int s = log2Val[r - l + 1];
    return (st[l][s] & st[r - (1 << s) + 1][s]);
}

long long comb(int x) { return 1ll * x * (x - 1) / 2; }

int getX(int i) { return i; }

double getY(int i) { return f[i] + (1.0 * i * i + i) / 2; }

double slope(int i, int j) { return (getY(j) - getY(i)) / (getX(j) - getX(i)); }

void push(int j) {
    while (top > 1 && slope(j, stk[top]) <= slope(stk[top], stk[top - 1])) --top;
    stk[++top] = j;
}

void divide(int l, int r) {
    if (l == r) {
        f[l] = max(f[l], f[l - 1]);
        return;
    }
    int mid = (l + r) / 2;
    divide(l, mid);
    top = 0;
    for (int i = r, j = mid + 1; i > mid; --i) {
        while (j - 1 >= l - 1 && !intersection(j, i).empty()) push(--j);
        while (top > 1 && slope(stk[top], stk[top - 1]) >= i) --top;
        if (top) f[i] = max(f[i], f[stk[top]] + comb(i - stk[top]));
    }
    divide(mid + 1, r);
}

int main() {
    freopen("development.in", "r", stdin);
    freopen("development.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int l, r;
        cin >> l >> r;
        --r;
        range[i] = Range(l, r);
    }
    preprocess();
    divide(1, n);
    cout << f[n] << endl;
    return 0;
}
