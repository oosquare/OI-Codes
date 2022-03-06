#include <iostream>
#include <tuple>
using namespace std;

constexpr int MAX_N = 17;
constexpr int MOD = 998244353;

int n;
int a[1 << MAX_N], b[1 << MAX_N], c[1 << MAX_N];

inline int add(int x, int y) {
    x += y;
    return (x >= MOD ? x - MOD : x);
}

inline int sub(int x, int y) {
    x -= y;
    return (x < 0 ? x + MOD : x);
}

inline int mul(int x, int y) {
    return (int) (1ll * x * y % MOD);
}

inline void assign(int & x, int & y, int a, int b) {
    x = a;
    y = b;
}

constexpr int power(int x, int y) {
    int res = 1;
    for (; y; y /= 2) {
        if (y % 2) res = (int) (1ll * res * x % MOD);
        x = (int) (1ll * x * x % MOD);
    }
    return res;
}

void fwtOr(int arr[], int n, bool inv) {
    const int len = (1 << n);
    if (!inv) {
        for (int i = 1, m = 2; i < len; i *= 2, m *= 2)
            for (int j = 0; j < len; j += m)
                for (int x = j, y = j + i; y < j + m; ++x, ++y)
                    assign(arr[x], arr[y], arr[x], add(arr[x], arr[y]));
    } else {
        for (int i = 1, m = 2; i < len; i *= 2, m *= 2)
            for (int j = 0; j < len; j += m)
                for (int x = j, y = j + i; y < j + m; ++x, ++y)
                    assign(arr[x], arr[y], arr[x], sub(arr[y], arr[x]));
    }
}

void fwtAnd(int arr[], int n, bool inv) {
    const int len = (1 << n);
    if (!inv) {
        for (int i = 1, m = 2; i < len; i *= 2, m *= 2)
            for (int j = 0; j < len; j += m)
                for (int x = j, y = j + i; y < j + m; ++x, ++y)
                    assign(arr[x], arr[y], add(arr[x], arr[y]), arr[y]);
    } else {
        for (int i = 1, m = 2; i < len; i *= 2, m *= 2)
            for (int j = 0; j < len; j += m)
                for (int x = j, y = j + i; y < j + m; ++x, ++y)
                    assign(arr[x], arr[y], sub(arr[x], arr[y]), arr[y]);
    }
}

void fwtXor(int arr[], int n, bool inv) {
    const int len = (1 << n);
    static constexpr int inv2 = power(2, MOD - 2);
    if (!inv) {
        for (int i = 1, m = 2; i < len; i *= 2, m *= 2)
            for (int j = 0; j < len; j += m)
                for (int x = j, y = j + i; y < j + m; ++x, ++y)
                    assign(arr[x], arr[y], add(arr[x], arr[y]), sub(arr[x], arr[y]));
    } else {
        for (int i = 1, m = 2; i < len; i *= 2, m *= 2)
            for (int j = 0; j < len; j += m)
                for (int x = j, y = j + i; y < j + m; ++x, ++y)
                    assign(arr[x], arr[y], mul(add(arr[x], arr[y]), inv2), mul(sub(arr[x], arr[y]), inv2));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;

    for (int i = 0; i < (1 << n); ++i)
        cin >> a[i];

    for (int i = 0; i < (1 << n); ++i)
        cin >> b[i];

    fwtOr(a, n, false);
    fwtOr(b, n, false);

    for (int i = 0; i < (1 << n); ++i)
        c[i] = mul(a[i], b[i]);
    
    fwtOr(a, n, true);
    fwtOr(b, n, true);
    fwtOr(c, n, true);

    for (int i = 0; i < (1 << n); ++i)
        cout << c[i] << " ";
    
    cout << endl;

    fwtAnd(a, n, false);
    fwtAnd(b, n, false);

    for (int i = 0; i < (1 << n); ++i)
        c[i] = mul(a[i], b[i]);
    
    fwtAnd(a, n, true);
    fwtAnd(b, n, true);
    fwtAnd(c, n, true);

    for (int i = 0; i < (1 << n); ++i)
        cout << c[i] << " ";
    
    cout << endl;

    fwtXor(a, n, false);
    fwtXor(b, n, false);

    for (int i = 0; i < (1 << n); ++i)
        c[i] = mul(a[i], b[i]);
    
    fwtXor(a, n, true);
    fwtXor(b, n, true);
    fwtXor(c, n, true);

    for (int i = 0; i < (1 << n); ++i)
        cout << c[i] << " ";
    
    cout << endl;
    return 0;
}