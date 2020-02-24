#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000;

int minn, n, ans;

class FHQTreap {
public:
    void insert(int key) {
        if (key < minn)
            return;
        int x, y;
        split(Root, key - 1, x, y);
        Root = merge(merge(x, create(key)), y);
    }

    void plus(int key) { plus(Root, key); }

    void minus(int key) {
        minus(Root, key);
        int x, y;
        split(Root, minn - 1, x, y);
        ans += Tree[x].Size;
        Root = y;
    }

    int at(int r) {
        if (r > Tree[Root].Size)
            return -1;
        int root = Root;
        while (true) {
            if (Tree[Tree[root].Right].Size + 1 == r) {
                break;
            } else if (Tree[Tree[root].Right].Size + 1 > r) {
                root = Tree[root].Right;
            } else {
                r -= Tree[Tree[root].Right].Size + 1;
                root = Tree[root].Left;
            }
        }
        return Tree[root].Key;
    }

private:
    struct Node {
        int Key, Left, Right, Size, Priority;
    } Tree[maxn];
    int Root, Seed = 233, Total;

    int random() { return Seed = (int)(Seed * 104143ll % 0x7fffffff); }

    int create(int key) {
        int root = ++Total;
        Tree[root].Key = key;
        Tree[root].Size = 1;
        Tree[root].Priority = random();
        Tree[root].Left = Tree[root].Right = 0;
        return root;
    }

    void pushup(int root) { Tree[root].Size = Tree[Tree[root].Left].Size + Tree[Tree[root].Right].Size + 1; }

    void split(int root, int key, int &x, int &y) {
        if (root == 0) {
            x = y = 0;
            return;
        }
        if (Tree[root].Key <= key) {
            x = root;
            split(Tree[root].Right, key, Tree[root].Right, y);
        } else {
            y = root;
            split(Tree[root].Left, key, x, Tree[root].Left);
        }
        pushup(root);
    }

    int merge(int x, int y) {
        if (x == 0 || y == 0) {
            return x + y;
        }
        if (Tree[x].Priority < Tree[y].Priority) {
            Tree[x].Right = merge(Tree[x].Right, y);
            pushup(x);
            return x;
        } else {
            Tree[y].Left = merge(x, Tree[y].Left);
            pushup(y);
            return y;
        }
    }

    void plus(int root, int key) {
        if (root == 0)
            return;
        Tree[root].Key += key;
        plus(Tree[root].Left, key);
        plus(Tree[root].Right, key);
    }

    void minus(int root, int key) {
        if (root == 0)
            return;
        Tree[root].Key -= key;
        minus(Tree[root].Left, key);
        minus(Tree[root].Right, key);
    }
};

FHQTreap tree;
char cmd[10];
int x;

int main() {
    scanf("%d%d", &n, &minn);
    while (n--) {
        scanf("%s%d", cmd, &x);
        if (cmd[0] == 'I')
            tree.insert(x);
        if (cmd[0] == 'A')
            tree.plus(x);
        if (cmd[0] == 'S')
            tree.minus(x);
        if (cmd[0] == 'F')
            printf("%d\n", tree.at(x));
    }
    printf("%d\n", ans);
    return 0;
}