#include <bits/stdc++.h>
using namespace std;

template <typename T,int MaxSize>
class Treap
{
public:
	void insert(T key) {
		int x, y;
		split(Root, key - 1, x, y);
		Root = merge(merge(x, create(key)), y);
	}

	void remove(T key) {
		int x, y, z;
		split(Root, key, x, z);
		split(x, key - 1, x, y);
		y = merge(Tree[y].Left, Tree[y].Right);
		Root = merge(merge(x, y), z);
	}

	T lower(T key) {
		int x, y, root;
		split(Root, key - 1, x, y);
		root = x;
		if(root == 0) return -0x7fffffff;
		while(Tree[root].Right) root = Tree[root].Right;
		Root = merge(x, y);
		return Tree[root].Key;
	}

	T upper(T key) {
		int x, y, root;
		split(Root, key, x, y);
		root = y;
		if(root == 0) return 0x7fffffff;
		while(Tree[root].Left) root = Tree[root].Left;
		Root = merge(x, y);
		return Tree[root].Key;
	}

	bool find(T key) {
		int x, y, z;
		split(Root, key, x, z);
		split(x, key - 1, x, y);
		bool ans;
		if(Tree[y].Size) ans = true;
		else ans = false;
		Root = merge(merge(x, y), z);
		return ans;

	}
private:
	struct Node
	{
		int Left, Right, Size, Priority;
		T Key;
	} Tree[MaxSize];
	int Root, Seed, Total;

	int random() {
		return Seed = (int)(Seed * 510343ll % 0x7fffffff);
	}

	int create(T key) {
		int root = ++Total;
		Tree[root].Key = key;
		Tree[root].Size = 1;
		Tree[root].Priority = random();
		Tree[root].Left = Tree[root].Right = 0;
		return root;
	}

	void pushup(int root) {
		Tree[root].Size = Tree[Tree[root].Left].Size + Tree[Tree[root].Right].Size + 1;
	}

	void split(int root, T key, int & x, int & y) {
		if(root == 0) {
			x = y =0;
			return;
		}
		if(key < Tree[root].Key) {
			y = root;
			split(Tree[root].Left, key, x, Tree[root].Left);
		} else {
			x = root;
			split(Tree[root].Right, key, Tree[root].Right, y);
		}
		pushup(root);
	}

	int merge(int x, int y) {
		if(x == 0 || y == 0) {
			return x + y;
		}
		if(Tree[x].Priority < Tree[y].Priority) {
			Tree[x].Right = merge(Tree[x].Right, y);
			pushup(x);
			return x;
		} else {
			Tree[y].Left = merge(x, Tree[y].Left);
			pushup(y);
			return y;
		}
	}
};

Treap<int, 100000> tree;
int n, m, x;
stack<int> stk;
char cmd[2];

int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		scanf("%s", cmd);
		if(cmd[0] == 'D') { scanf("%d", &x); tree.insert(x); stk.push(x); }
		if(cmd[0] == 'R') { x = stk.top(); stk.pop(); tree.remove(x); }
		if(cmd[0] == 'Q') {
			scanf("%d", &x);
			if(tree.find(x)) {
				printf("0\n");
			} else {
				int l = tree.lower(x), u = tree.upper(x), ans = 0;
				if(l == -0x7fffffff) l = 0;
				if(u == 0x7fffffff) u = n + 1;
				printf("%d\n", u - l - 1);
			}
		}
	}
	return 0;
}