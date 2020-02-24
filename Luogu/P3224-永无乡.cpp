#include <bits/stdc++.h>
#define FILE_IO true
#define TIME_LIMIT 1000
using namespace std;

template <typename T>
void read(T &number) {
    number = 0; int symbol = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') symbol *= -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        number = (number << 3) + (number << 1) + c ^ '0';
        c = getchar();
    }
    number *= symbol;
}

struct node
{
    int key,val,lc,rc,sze,pri;
};

const int maxn=100000+100;

node tree[maxn<<4];
int root[maxn],total,seed=233;
int n,m,q;
int fa[maxn];

int rad() {
    return seed=(seed*140127ll%0x7fffffff);
}

int create(int key,int val) {
    tree[++total]=(node){key,val,0,0,1,rad()}; return total;
}

void pushup(int x) {
    if(root!=0)
        tree[x].sze=tree[tree[x].lc].sze+tree[tree[x].rc].sze+1;
}

void split(int root,int key,int &x,int &y) {
    if(root==0) {
        x=y=0;
        return;
    }
    if(tree[root].key<=key) {
        x=root;
        split(tree[root].rc,key,tree[root].rc,y);
    } else {
        y=root;
        split(tree[root].lc,key,x,tree[root].lc);
    }
    pushup(root);
}

int merge(int x,int y) { 
    if(x==0||y==0) {
        return x+y;
    }
    if(tree[x].pri>=tree[y].pri) swap(x,y);
    int a,b;
    split(y,tree[x].key,a,b);
    tree[x].lc=merge(tree[x].lc,a);
    tree[x].rc=merge(tree[x].rc,b);
    pushup(x);
    return x;
}

int at(int root,int r) {
    if(r>tree[root].sze) return -1;
    int rt=root;
    while(1) {
        int lcsze=tree[tree[rt].lc].sze+1;
        if(lcsze==r) break;
        if(lcsze>r) rt=tree[rt].lc;
        if(lcsze<r) { rt=tree[rt].rc; r-=lcsze; }
    }
    return tree[rt].val;
}

int findset(int x) {
    if(x==fa[x]) return x;
    return fa[x]=findset(fa[x]);
}

int main(int argc, char *argv[]) {
#if !defined(ONLINE_JUDGE) && FILE_IO
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
    clock_t stime = clock();
#endif
    // [ Codes ] ////////////////////////
    
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) {
        int im;
        scanf("%d",&im);
        root[i]=create(im,i);
        fa[i]=i;
    }
    for(int i=1;i<=m;++i) {
        int x,y;
        scanf("%d%d",&x,&y);
        int fx=findset(x),fy=findset(y);
        if(fx!=fy) {
            fa[fy]=fx;
            root[fx]=merge(root[fx],root[fy]);
        }
        
    }
    scanf("%d",&q);
    while(q--) {
        char s[2]; int a,b;
        scanf("%s%d%d",s,&a,&b);
        if(s[0]=='Q') {
            printf("%d\n",at(root[findset(a)],b));
        } else {
            int fx=findset(a),fy=findset(b);
            if(fx!=fy) fa[fy]=fx;
            root[fx]=merge(root[fx],root[fy]);
        }
    }

    // [ Codes ] ////////////////////////
#if !defined(ONLINE_JUDGE) && FILE_IO
    clock_t etime = clock();
    printf("\n----------------------------\n");
    printf("Time : %dms\n", etime - stime);
    if (etime - stime >= TIME_LIMIT) {
        printf("<<< Warning >>> Time Limited Exceeded\n");
    }
#endif
    return 0;
}

//
//        ^ y
//       1|                            y = sin x (0 < x < 2π)
//  - - - | - - - + - - - - - - - - - - - - - -
//        |  +         +
// -------+---------------+---------------+----------> x
//       O|               π  +         +  2π
//  - - - | - - - - - - - - - - - + - - - - - -
//      -1|
//        |
//
