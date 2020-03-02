#include <bits/stdc++.h>
using namespace std;

const int maxn = 50001 * 30;

struct trie {
    int total, totalReserve;
    int tree[maxn][27], treeReserve[maxn][27];
    int end[maxn], endReserve[maxn];

    trie() { total = totalReserve = 1; }

    void insert(char str[]) {
        int len = strlen(str + 1), it = 1;
        for (int i = 1; i <= len; ++i) {
            int c = str[i] - 'a';
            if (!tree[it][c])
                tree[it][c] = ++total;
            it = tree[it][c];
        }
        end[it] = true;
        it = 1;
        for (int i = len; i >= 1; --i) {
            int c = str[i] - 'a';
            if (!treeReserve[it][c])
                treeReserve[it][c] = ++totalReserve;
            it = treeReserve[it][c];
        }
        endReserve[it] = true;
    }

    bool findReserve(char str[]) {
        int len = strlen(str + 1), it = 1;
        for (int i = len; i >= 1; --i) {
            int c = str[i] - 'a';
            if (!treeReserve[it][c])
                return false;
            it = treeReserve[it][c];
            if (endReserve[it])
                return true;
        }
        return false;
    }

    bool find(char str[]) {
        int len = strlen(str + 1), it = 1;
        for (int i = 1; i <= len; ++i) {
            int c = str[i] - 'a';
            if (!tree[it][c])
                return false;
            it = tree[it][c];
            if (end[it]) {
                bool res = findReserve(str + i);
                if (res)
                    return true;
            }
        }
        return false;
    }
};

char strs[50001][30];
int n;
trie t;

int main() {
    n = 1;
    while (scanf("%s", strs[n] + 1) != EOF) {
        t.insert(strs[n]);
        ++n;
    }
    --n;
    for (int i = 1; i <= n; ++i) {
        if (t.find(strs[i])) {
            printf("%s\n", strs[i] + 1);
        }
    }
}