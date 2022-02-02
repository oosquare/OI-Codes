#include <iostream>
#include <iomanip>

constexpr int maxn = 1e5 + 10;
constexpr long double eps = 1e-16;
constexpr long double oo = 1e18;

int n, s;
long double a[maxn], b[maxn], rate[maxn];
int seq[maxn], tmp[maxn];
int st[maxn], top;
long double f[maxn];

inline bool equal(long double a, long double b) {
    return std::abs(b - a) < eps;
}

inline bool less(long double a, long double b) {
    return b - a > eps;
}

inline long double getX(int i) {
    return -f[i] / (a[i] * rate[i] + b[i]);
}

inline long double getY(int i) {
    return rate[i] * f[i] / (a[i] * rate[i] + b[i]);
}

inline long double slope(int i, int j) {
    if (equal(getX(i), getX(j)))
        return (less(getY(i), getY(j)) ? oo : -oo);

    return (getY(j) - getY(i)) / (getX(j) - getX(i));
}

int find(long double k) {
    int l = 1, r = top;

    while (l < r) {
        int mid = (l + r) / 2;

        if (!less(k, slope(st[mid], st[mid + 1])))
            r = mid;
        else
            l = mid + 1;
    }

    return st[l];
}

void update(int l, int r) {
    int mid = (l + r) / 2;
    top = 0;

    for (int t = l; t <= mid; ++t) {
        int i = seq[t];

        while (top > 1 && !less(slope(st[top], i), slope(st[top - 1], st[top])))
            --top;

        st[++top] = i;
    }

    for (int t = mid + 1; t <= r; ++t) {
        int i = seq[t], j = find(b[i] / a[i]);
        f[i] = std::max(f[i], f[j] * (a[i] * rate[j] + b[i]) / (a[j] * rate[j] + b[j]), less);
    }
}

void merge(int l, int r) {
    int mid = (l + r) / 2, it1 = l, it2 = mid + 1, it = l - 1;

    while (it1 <= mid && it2 <= r) {
        if (less(getX(seq[it1]), getX(seq[it2])))
            tmp[++it] = seq[it1++];
        else
            tmp[++it] = seq[it2++];
    }

    while (it1 <= mid)
        tmp[++it] = seq[it1++];

    while (it2 <= r)
        tmp[++it] = seq[it2++];

    for (int i = l; i <= r; ++i)
        seq[i] = tmp[i];
}

void cdq(int l, int r) {
    if (l > r)
        return;

    if (l == r) {
        f[l] = std::max(f[l], f[l - 1], less);
        return;
    }

    int mid = (l + r) / 2;
    cdq(l, mid);
    update(l, r);
    cdq(mid + 1, r);
    merge(l, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> n >> s;

    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i] >> b[i] >> rate[i];
        seq[i] = i;
    }

    f[1] = s;
    cdq(1, n);
    std::cout << std::setprecision(15) << f[n] << std::endl;
    return 0;
}