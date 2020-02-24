#include <bits/stdc++.h>
using namespace std;

struct node
{
    char key;
    int l,r,sze,pri;
};

constexpr int maxn=3e7+10;

node tree[maxn]; int total,root,seed;
int n,cur;
char str[maxn],cmd[10];

inline int myrand() { return seed=(int)((seed+3)*129813LL%0x7fffffff); }

inline int &ls(int root) { return tree[root].l; }

inline int &rs(int root) { return tree[root].r; };

inline void pushup(int root) { if(root) tree[root].sze=tree[ls(root)].sze+tree[rs(root)].sze+1; }

inline int create(char key) { tree[++total]=(node){ key,0,0,1,myrand() }; return total; }

void split(int root,int sze,int &x,int &y){
    if(root==0){
        x=y=0;
        return;
    }
    if(tree[ls(root)].sze<sze){
        x=root;
        split(rs(x),sze-tree[ls(root)].sze-1,rs(x),y);
        pushup(x);
    }else{
        y=root;
        split(ls(y),sze,x,ls(y));
        pushup(y);
    }
}

int merge(int x,int y){
    if(x==0||y==0)
        return x^y;
    if(tree[x].pri>tree[y].pri){
        rs(x)=merge(rs(x),y);
        pushup(x);
        return x;
    }else{
        ls(y)=merge(x,ls(y));
        pushup(y);
        return y;
    }
}

void insert(int len){
    char c; int x,y;
    split(root,cur,x,y);
    for(int i=1;i<=len;++i){
        c=getchar();
        if(c=='\r'||c=='\n'){
            --i;
            continue;
        }
        x=merge(x,create(c));
    }
    root=merge(x,y);
}

void remove(int len){
    int x,y,z;
    split(root,cur,x,y);
    split(y,len,y,z);
    root=merge(x,z);
}

void dfs(int root){
    if(root==0)
        return;
    dfs(ls(root));
    putchar(tree[root].key);
    dfs(rs(root));
}

void get(int len){
    int x,y,z;
    split(root,cur,x,y);
    split(y,len,y,z);
    dfs(y);
    putchar('\n');
    root=merge(merge(x,y),z);
}

int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%s",cmd);
        int x;
        switch(cmd[0]){
        case 'M':
            scanf("%d",&cur);
            break;
        case 'I':
            scanf("%d",&x);
            insert(x);
            break;
        case 'D':
            scanf("%d",&x);
            remove(x);
            break;
        case 'G':
            scanf("%d",&x);
            get(x);
            break;
        case 'P':
            --cur;
            break;
        case 'N':
            ++cur;
            break;
        }
    }
}