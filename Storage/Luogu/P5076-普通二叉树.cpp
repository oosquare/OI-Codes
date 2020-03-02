#include <bits/stdc++.h>
using namespace std;

template <typename T> class FHQTreap {
  public:
    FHQTreap() { Root = nullptr; }

    void insert(T key) {
        Node *x, *y;
        split(Root, key - 1, x, y);
        Root = merge(merge(x, create(key)), y);
    }

    void remove(T key) {
        Node *x, *y, *z;
        split(Root, key, x, z);
        split(x, key - 1, x, y);
        if (y) {
            y = merge(y->Left, y->Right);
        }
        Root = merge(merge(x, y), z);
    }

    int rank(T key) {
        Node *x, *y;
        int ans;
        split(Root, key - 1, x, y);
        ans = (x ? x->Size : 0) + 1;
        Root = merge(x, y);
        return ans;
    }

    T at(int r) {
        if (Root == nullptr || r > Root->Size)
            return T();
        Node *root = Root;
        while (root) {
            int ls = root->Left ? root->Left->Size : 0;
            if (ls + 1 == r) {
                break;
            } else if (ls + 1 > r) {
                root = root->Left;
            } else {
                r -= ls + 1;
                root = root->Right;
            }
        }
        return root->Key;
    }

    T previous(T key) {
        Node *x, *y, *root;
        T ans;
        split(Root, key - 1, x, y);
        root = x;
        if (root == nullptr)
            return -0x7fffffff;
        while (root->Right)
            root = root->Right;
        ans = root->Key;
        Root = merge(x, y);
        return ans;
    }

    T next(T key) {
        Node *x, *y, *root;
        T ans;
        split(Root, key, x, y);
        root = y;
        if (root == nullptr)
            return 0x7fffffff;
        while (root->Left)
            root = root->Left;
        ans = root->Key;
        Root = merge(x, y);
        return ans;
    }

    int size() { return (Root ? Root->Size : 0); }

    bool find(T key) {
        Node *x, *y, *z;
        split(Root, key, x, z);
        split(x, key - 1, x, y);
        bool ans;
        if (y)
            ans = true;
        else
            ans = false;
        Root = merge(merge(x, y), z);
        return ans;
    }

  private:
    struct Node {
        T Key;
        Node *Left, *Right;
        int Size, Priority;
    } * Root;
    int Seed;

    int random() { return Seed = int((Seed + 3) * 482711ll % 2147483647); }

    Node *create(T key) {
        Node *root = new Node;
        root->Key = key;
        root->Size = 1;
        root->Left = root->Right = nullptr;
        root->Priority = random();
        return root;
    }

    void pushup(Node *root) {
        if (root)
            root->Size = (root->Left ? root->Left->Size : 0) +
                         (root->Right ? root->Right->Size : 0) + 1;
    }

    void split(Node *root, T key, Node *&x, Node *&y) {
        if (root == nullptr) {
            x = y = nullptr;
            return;
        }
        if (!(key < root->Key)) {
            x = root;
            split(root->Right, key, root->Right, y);
        } else {
            y = root;
            split(root->Left, key, x, root->Left);
        }
        pushup(root);
    }

    Node *merge(Node *x, Node *y) {
        if (x == nullptr)
            return y;
        if (y == nullptr)
            return x;
        if (x->Priority > y->Priority) {
            x->Right = merge(x->Right, y);
            pushup(x);
            return x;
        } else {
            y->Left = merge(x, y->Left);
            pushup(y);
            return y;
        }
    }
};

FHQTreap<int> tree;
int n, x, opt;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            printf("%d\n", tree.rank(x));
        if (opt == 2)
            printf("%d\n", tree.at(x));
        if (opt == 3)
            printf("%d\n", tree.previous(x));
        if (opt == 4)
            printf("%d\n", tree.next(x));
        if (opt == 5)
            tree.insert(x);
    }
    return 0;
}