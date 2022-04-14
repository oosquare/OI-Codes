#include <iostream>
#include <cstring>

int t, v, cnt[35], mrk[35];
long long comb[5][5];
constexpr long long bin[5] = {1, 2, 4, 8, 16};
constexpr int id[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 16, 17, 25, 26, 34};
long long dp1[35][3][3][5][2], dp2[35][8], dp3[14][15];

void preprocess() {
    for (int i = 0; i < 5; ++i) {
        comb[i][0] = comb[i][i] = 1;

        for (int j = 1; j < i; ++j)
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
    }
}

void updateMax(long long &x, long long y) {
    if (x < y)
        x = y;
}

long long choose(int x, int y) { return comb[cnt[x]][y] * (mrk[x] ? bin[y] : 1); }

void solve1l1(int &i, int &j, int &k, int &a, int &b) {
    for (int c = 0;; ++c) {
        if (!(c <= 2 && j + k + c <= cnt[i + 1] && a + c <= 4))
            break;

        for (int d = 0;; ++d) {
            if (!(j + k + c + d * 3 <= cnt[i + 1] && a + c + d <= 4))
                break;

            int t = j + k + c + d * 3;

            updateMax(dp1[i + 1][k][c][a + c + d][b], dp1[i][j][k][a][b] * choose(i + 1, t));

            if (!(!b && t + 2 <= cnt[i + 1]))
                continue;

            updateMax(dp1[i + 1][k][c][a + c + d][1], dp1[i][j][k][a][b] * choose(i + 1, t + 2));
        }
    }
}

void solve2l2(int &i, int &j, int &k) {
    for (int a = j + k; a <= 4; ++a) {
        for (int b = 0; b <= 1; ++b) {
            if (!dp1[i][j][k][a][b])
                continue;

            solve1l1(i, j, k, a, b);

            if (!(cnt[i + 1] - j - k == 4 && a < 4))
                continue;

            updateMax(dp1[i + 1][k][0][a + 1][b], dp1[i][j][k][a][b] * choose(i + 1, 4));
        }
    }
}

void solve3l3(int &i, int &j) {
    for (int k = 0; k < 3; ++k) {
        if (!(!k || (i > 7 && (i - 7) % 9 != 8 && (i - 7) % 9 != 0)))
            continue;

        if (!(cnt[i + 1] >= j + k))
            continue;

        solve2l2(i, j, k);
    }
}

long long solve1() {
    memset(dp1, 0, sizeof(dp1));
    dp1[0][0][0][0][0] = 1;

    for (int i = 0; i < 34; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (!(!j || (i > 7 && (i - 7) % 9 != 0 && (i - 7) % 9 != 1)))
                continue;

            solve3l3(i, j);
        }
    }

    return dp1[34][0][0][4][1];
}

long long solve2() {
    memset(dp2, 0, sizeof(dp2));
    dp2[0][0] = 1;

    for (int i = 0; i < 34; ++i) {
        for (int j = 0; j <= 7; ++j) {
            updateMax(dp2[i + 1][j], dp2[i][j]);

            if (j < 7)
                updateMax(dp2[i + 1][j + 1], dp2[i][j] * choose(i + 1, 2));
        }
    }

    return dp2[34][7] * 7;
}

long long solve3() {
    memset(dp3, 0, sizeof(dp3));
    dp3[0][0] = 1;

    for (int i = 0; i < 13; ++i)
        for (int j = 0; j <= 14; ++j)
            for (int k = 1; k <= cnt[id[i + 1]] && k <= 2; ++k)
                updateMax(dp3[i + 1][j + k], dp3[i][j] * choose(id[i + 1], k));

    return dp3[13][14] * 13;
}

void read1(int &v, char str[]) {
    if (str[0] == 'E')
        v = 1;
    else if (str[0] == 'S')
        v = 2;
    else if (str[0] == 'W')
        v = 3;
    else if (str[0] == 'N')
        v = 4;
    else if (str[0] == 'Z')
        v = 5;
    else if (str[0] == 'B')
        v = 6;
    else
        v = 7;
}

void read2(int &v, char str[]) {
    if (str[1] == 'm')
        v = 7;
    else if (str[1] == 'p')
        v = 16;
    else
        v = 25;

    v += str[0] - '0';
}

int read() {
    int v;
    char str[5];
    std::cin >> str;

    if (str[0] == '0')
        return 0;

    if (std::strlen(str) == 1)
        read1(v, str);
    else
        read2(v, str);

    return v;
}

int main() {
#ifdef ONLINE_JUDGE
    std::freopen("b.in", "r", stdin);
    std::freopen("b.out", "w", stdout);
#else
    std::freopen("project.in", "r", stdin);
    std::freopen("project.out", "w", stdout);
#endif
    preprocess();
    std::cin >> t;

    while (t--) {
        for (int i = 1; i <= 34; ++i) {
            cnt[i] = 4;
            mrk[i] = 0;
        }

        while (v = read(), v != 0)
            --cnt[v];

        while (v = read(), v != 0)
            mrk[v] = 1;

        std::cout << std::max(std::max(solve1(), solve2()), solve3()) << std::endl;
    }

    return 0;
}
