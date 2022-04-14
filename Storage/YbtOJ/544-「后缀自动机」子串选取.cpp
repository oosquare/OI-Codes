#pragma GCC optimize(3, "inline")
#include <iostream>
using namespace std;

constexpr int MAXN = 5e5 + 10;
constexpr int BASE = 27;

template <typename T, int size, T mod>
class HashSet {
public:
    void insert(T x) {
        int h = x % mod;
        ++total;
        nodes[total].next = head[h];
        head[h] = total;
        nodes[total].weight = x;
    }

    bool query(T x) {
        int h = x % mod;

        for (int i = head[h]; i; i = nodes[i].next)
            if (nodes[i].weight == x)
                return true;

        return false;
    }
private:
    struct Node {
        T weight;
        int next;
    };

    Node nodes[size];
    int head[size];
    int total;
};

int n;
char s[MAXN];
unsigned h[MAXN], p[MAXN], tmp;
HashSet<unsigned, MAXN * 40, 19260817> t;
int f[MAXN], ans;

void preprocess() {
    p[0] = 1;

    for (int i = 1; i <= n; ++i)
        p[i] = p[i - 1] * BASE;

    for (int i = 1; i <= n; ++i)
        h[i] = h[i - 1] * BASE + s[i] - 'a' + 1;
}

inline unsigned calc(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

inline bool contain(int l, int r) {
    return t.query(calc(l, r));
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("substr.in", "r", stdin);
    freopen("substr.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n >> (s + 1);
    preprocess();
    t.insert(0);

    for (int i = n, l = 0, j; i >= 1; --i) {
        ++l;

        while (!contain(i, i + l - 2) && !contain(i + 1, i + l - 1)) {
            --l;
            j = i + l;

            for (int k = f[j]; k >= 1; --k) {
                tmp = h[j + k - 1] - h[j - 1] * p[k];

                if (t.query(tmp))
                    break;
                
                t.insert(tmp);
            }
        }

        f[i] = l;
        
        if (ans < f[i])
            ans = f[i];
    }

    cout << ans << endl;
    return 0;
}
