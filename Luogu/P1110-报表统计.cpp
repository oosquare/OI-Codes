#include <bits/stdc++.h>
using namespace std;

template <int MaxSize>
class FHQTreap
{
public:
    int insert(int key) {
        int x, y;
        valueSplit(Root, key - 1, x, y);
        Root = merge(merge(x, create(key)), y);
        return min(key - valuePrev(key), valueNext(key) - key);
    }

    int insertAt(int key, int pos) {
        int x, y;
        splitSize(Root, pos, x, y);
        Root = merge(merge(x, create(key)), y);
        return min(abs(key - sizePrev(pos + 1)), abs(sizeNext(pos + 1) - key));
    }
private:
    struct Node
    {
        int Key, Left, Right, Size, Priority;
    } Tree[MaxSize];
    int Total, Seed = 233, Root;

    int random() { 
        return Seed = (Seed * 141821ll % 0x7fffffff); 
    }

    int create(int key) {
        int root = ++Total;
        Tree[root].Key = key;
        Tree[root].Size = 1;
        Tree[root].Left = Tree[root].Right = 0;
        Tree[root].Priority = random();
        return root;
    }

    void pushup(int root) {
        if (root != 0)
            Tree[root].Size = Tree[Tree[root].Left].Size + Tree[Tree[root].Right].Size + 1;
    }

    void valueSplit(int root, int key, int &x, int &y) {
        if (root == 0) {
            x = y = 0;
            return;
        }
        if (Tree[root].Key <= key) {
            x = root;
            valueSplit(Tree[root].Right, key, Tree[root].Right, y);
            pushup(x);
        } else {
            y = root;
            valueSplit(Tree[root].Left, key, x, Tree[root].Left);
            pushup(y);
        }
    }

    void splitSize(int root, int sze, int &x, int &y) {
        if (root == 0) {
            x = y = 0;
            return;
        }
        if (Tree[Tree[root].Left].Size + 1 <= sze) {
            x = root;
            splitSize(Tree[x].Right, sze - Tree[Tree[x].Left].Size - 1, Tree[x].Right, y);
            pushup(x);
        } else {
            y = root;
            splitSize(Tree[y].Left, sze, x, Tree[y].Left);
            pushup(y);
        }
    }

    int merge(int x, int y) {
        if (x == 0 || y == 0)
            return  x + y;
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

    int valuePrev(int key) {
        int x, y, ans;
        valueSplit(Root, key - 1, x, y);
        int root = x;
        if (x == 0)
            return -0x3f3f3f3f;
        while (Tree[root].Right) 
            root = Tree[root].Right;
        ans = Tree[root].Key;
        Root = merge(x, y);
        return ans;
    }

    int valueNext(int key) {
        int x, y, ans;
        valueSplit(Root, key, x, y);
        int root = y;
        if (y == 0)
            return 0x3f3f3f3f;
        while (Tree[root].Left)
            root = Tree[root].Left;
        ans = Tree[root].Key;
        Root = merge(x, y);
        return ans;
    }

    int sizePrev(int sze) {
        int x, y, ans;
        splitSize(Root, sze - 1, x, y);
        int root = x;
        if (x == 0)
            return -0x3f3f3f3f;
        while (Tree[root].Right) 
            root = Tree[root].Right;
        ans = Tree[root].Key;
        Root = merge(x, y);
        return ans;
    }

    int sizeNext(int sze) {
        int x, y, ans;
        splitSize(Root, sze, x, y);
        int root = y;
        if (y == 0)
            return 0x3f3f3f3f;
        while (Tree[root].Left)
            root = Tree[root].Left;
        ans = Tree[root].Key;
        Root = merge(x, y);
        return ans;
    }
};

FHQTreap<500010> tree1, tree2;
int n, m, ans1 = 0x7fffffff, ans2 = 0x7fffffff, x, p, last = 0x3f3f3f3f;
char cmd[100];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        tree1.insertAt(x, i);
        ans2 = min(ans2, tree2.insert(x));
        ans1 = min(ans1, abs(x - last));
        last = x;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%s", cmd);
        if (cmd[0] == 'I') {
            scanf("%d%d", &p, &x);    
            ans1 = min(ans1, tree1.insertAt(x, p));
            ans2 = min(ans2, tree2.insert(x));
        } else if (cmd[4] == 'G') {
            printf("%d\n", ans1);
        } else {
            printf("%d\n", ans2);
        }
    }
    return 0;
}