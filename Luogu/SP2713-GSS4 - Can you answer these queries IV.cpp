#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int n,m,p,t;

const int lim=1000105;

class SegmentTree
{
public:
    typedef long long type;
    type a[lim];

    void build(int k,int l,int r){
        if(l==r){
            st[k].v=st[k].ma=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(k<<1,l,mid);
        build(k<<1|1,mid+1,r);
        pushup(k);
    }

    void modify(int k,int l,int r,int x,int y){
        if(l==r){
            st[k].v=sqrt((double)st[k].v);
            st[k].ma=st[k].v;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid&&st[k<<1].ma>1)modify(k<<1,l,mid,x,y);
        if(mid<y&&st[k<<1|1].ma>1)modify(k<<1|1,mid+1,r,x,y);
        pushup(k);
    }

    type query(int k,int l,int r,int x,int y){
        if(x<=l&&r<=y)return st[k].v;
        int mid=(l+r)>>1;
        type res=0;
        if(x<=mid)res=res+query(k<<1,l,mid,x,y);
        if(mid<y)res=res+query(k<<1|1,mid+1,r,x,y);
        return res;
    }
private:
    struct node
    {
        type v;
        type ma;
        bool tag;
    };
    node st[lim*4];
    
    void pushup(int k){
        st[k].v=st[k<<1].v+st[k<<1|1].v;
        st[k].ma=max(st[k<<1].ma,st[k<<1|1].ma);
    }
};

SegmentTree tree;

void solve(){
    for(int i=1;i<=n;i++){
        scanf("%lld",&tree.a[i]);
    }
    tree.build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(x>y) swap(x,y);
        if(op==0){
            tree.modify(1,1,n,x,y);
        }else{
            printf("%lld\n",tree.query(1,1,n,x,y));
        }
    }
}

int main(){
    while(scanf("%d",&n)!=EOF){
        ++t;
        printf("Case #%d:\n",t);
        solve();
        printf("\n");
    }
}