#include <bits/stdc++.h>
using namespace std;

inline char mygetchar() {
    static char ff[100000], *A = ff, *B = ff;
    return A == B && (B = (A = ff) + fread(ff, 1, 100000, stdin), A == B)
               ? EOF
               : *A++;
}

template <typename T = int> T read() {
    T x = 0, s = 1;
    char c = mygetchar();
    while (c < '0' || '9' < c) {
        if (c == '-')
            s = -1;
        c = mygetchar();
    }
    while ('0' <= c && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = mygetchar();
    }
    return x * s;
}

constexpr int maxu = 250 + 2;
constexpr int maxm = 500;
typedef long long ll;

class Matrix {
  public:
    Matrix(int r = 0, int c = 0) : Row(r), Col(c) {
        memset(Data, 0x3f, sizeof(Data));
    }

    ll &at(int x, int y) { return Data[x][y]; }

    Matrix operator*(const Matrix &rhs) {
        Matrix res(Row, rhs.Col);
        for (int i = 1; i <= Row; ++i)
            for (int k = 1; k <= Col; ++k)
                for (int j = 1; j <= rhs.Col; ++j)
                    res.Data[i][j] =
                        min(res.Data[i][j], Data[i][k] + rhs.Data[k][j]);
        return res;
    }

    Matrix operator^(ll k) {
        if (k == 1)
            return *this;
        --k;
        Matrix res = *this;
        Matrix self = *this;
        while (k) {
            if (k % 2 == 1)
                res = res * self;
            self = self * self;
            k /= 2;
        }
        return res;
    }

  private:
    ll Data[maxu][maxu];
    int Row, Col;
};

struct {
    int x, y;
    ll w;
} edge[maxm];

int n, t, s, e;
Matrix m(250, 250);
vector<int> v;

int main() {
#ifndef ONLINE_JUDGE
    freopen("Environment/project.in", "r", stdin);
    freopen("Environment/project.out", "w", stdout);
#endif
    n = read();
    t = read();
    s = read();
    e = read();
    for (int i = 1; i <= t; ++i) {
        edge[i].w = read<ll>();
        v.push_back(edge[i].x = read());
        v.push_back(edge[i].y = read());
    }
    sort(v.begin(), v.end());
    auto endit = unique(v.begin(), v.end());
    auto getid = [&](int x) {
        return lower_bound(v.begin(), endit, x) - v.begin() + 1;
    };
    for (int i = 1; i <= t; ++i) {
        m.at(getid(edge[i].x), getid(edge[i].y)) =
            m.at(getid(edge[i].y), getid(edge[i].x)) = edge[i].w;
    }
    printf("%lld\n", (m ^ n).at(getid(s), getid(e)));
    return 0;
}