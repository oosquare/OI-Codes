#include <bits/stdc++.h> 
using namespace std;

struct node {
    int cnt[26],assign;
    int &operator[](int x){
        return cnt[x];
    }
};

constexpr int maxn=50000+10;
constexpr int null=27;
node tree[maxn<<4];
int n,m;
char a[maxn];

inline void pushup(int x){
    for(int i=0;i<26;++i){
        tree[x][i]=tree[x<<1][i]+tree[x<<1|1][i];
    }
}

inline void pushdown(int x,int l,int r){
    if(tree[x].assign!=null){
        tree[x<<1].assign=tree[x<<1|1].assign=tree[x].assign;
        memset(tree[x<<1].cnt,0,sizeof(tree[x<<1].cnt));
        memset(tree[x<<1|1].cnt,0,sizeof(tree[x<<1|1].cnt));
        int mid=(l+r)>>1;
        tree[x<<1][tree[x].assign]=mid-l+1;
        tree[x<<1|1][tree[x].assign]=r-mid;
        tree[x].assign=null;
    }
}

void assign(int x,int l,int r,int ml,int mr,int v){
    if(ml<=l&&r<=mr){
        tree[x].assign=v;
        memset(tree[x].cnt,0,sizeof(tree[x].cnt));
        tree[x][v]=r-l+1;
        return;
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    if(ml<=mid) assign(x<<1,l,mid,ml,mr,v);
    if(mid<mr) assign(x<<1|1,mid+1,r,ml,mr,v);
    pushup(x);
}

int query(int x,int l,int r,int ql,int qr,int v){
    if(ql<=l&&r<=qr){
        return tree[x][v];
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    int res=0;
    if(ql<=mid) res+=query(x<<1,l,mid,ql,qr,v);
    if(mid<qr) res+=query(x<<1|1,mid+1,r,ql,qr,v);
    return res;
}

node queryall(int x,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        return tree[x];
    }
    pushdown(x,l,r);
    int mid=(l+r)>>1;
    if(qr<=mid) return queryall(x<<1,l,mid,ql,qr);
    else if(mid<ql) return queryall(x<<1|1,mid+1,r,ql,qr);
    else{
        node res1=queryall(x<<1,l,mid,ql,qr),res2=queryall(x<<1|1,mid+1,r,ql,qr);
        for(int i=0;i<26;++i){
            res1.cnt[i]+=res2.cnt[i];
        }
        return res1;
    }
}

void sort(int l,int r){
    node res=queryall(1,1,n,l,r);
    int now=l;
    for(int i=0;i<26;++i){
        if(!res[i]) continue;
        assign(1,1,n,now,now+res[i]-1,i);
        now+=res[i];
    }
}

void build(int x,int l,int r){
    tree[x].assign=null;
    if(l==r){
        tree[x][toupper(a[l])-'A']=1;
        return;
    }
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}

int main(){
    scanf("%d%d",&n,&m);
    scanf("%s",a+1);
    build(1,1,n);
    while(m--){
        int opt,x,y;
        scanf("%d%d%d",&opt,&x,&y);
        if(opt==1){
            scanf("%s",a);
            printf("%d\n",query(1,1,n,x,y,toupper(a[0])-'A'));
        }else if(opt==2){
            scanf("%s",a);
            assign(1,1,n,x,y,toupper(a[0])-'A');
        }else{
            sort(x,y);
        }
    }
    return 0;
}