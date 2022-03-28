#include <iostream>

constexpr int MAX_N = 1000 + 10;

int n;
char mat[MAX_N][MAX_N];
int cntx[MAX_N], cnty[MAX_N], full;
int pos[MAX_N];
int ans = 0x3f3f3f3f;

int main() {
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        std::scanf("%s", mat[i] + 1);

        for (int j = 1; j <= n; ++j) {
            cntx[i] += (mat[i][j] == '#');
            cnty[j] += (mat[i][j] == '#');

            if (mat[i][j] == '#')
                pos[j] = i;
        }
    }

    for (int i = 1; i <= n; ++i)
        full += (cnty[i] == n);

    for (int j = 1; j <= n; ++j) {
        bool found = false;

        for (int i = 1; i <= n; ++i) {
            if (mat[i][j] == '.')
                continue;

            found = true;
            ans = std::min(ans, n - cntx[j] + n - full);
        }

        if (found)
            continue;

        for (int i = 1; i <= n; ++i) {
            if (!pos[i])
                continue;

            ans = std::min(ans, 1 + n - cntx[j] + n - full);
        }
    }

    std::cout << (ans != 0x3f3f3f3f ? ans : -1) << std::endl;
    return 0;
}