#include <bits/stdc++.h>
using namespace std;

struct node
{
    int l,r,sum,lmax[2],rmax[2],allmax[2];
    int val,rev;
};

node tree[100000];
int n,m;
int a[100000];

void pushup(node & now,const node & lc,const node & rc) {
    now.sum=lc.sum+rc.sum;
    for(int i=0;i<=1;++i) {
        now.lmax[i]=lc.lmax[i];
        if(i==1&&lc.r-lc.l+1==lc.sum) {
            now.lmax[i]+=rc.lmax[i];
        } else if(i==0&&lc.sum==0) {
            now.lmax[i]+=rc.lmax[i];
        }
        now.rmax[i]=rc.rmax[i];
        if(i==1&&rc.r-rc.l+1==rc.sum) {
            now.rmax[i]+=lc.rmax[i];
        } else if(i==0&&rc.sum==0) {
            now.rmax[i]+=lc.rmax[i];
        }
        now.allmax[i]=lc.rmax[i]+rc.lmax[i];
        now.allmax[i]=max(now.allmax[i],lc.allmax[i]);
        now.allmax[i]=max(now.allmax[i],rc.allmax[i]);
    }
}

void pushdown(node & now,node & lc,node & rc) {
    if(now.val!=-1) {
        now.rev=lc.rev=rc.rev=0;
        lc.val=rc.val=now.val;

        lc.sum=(lc.r-lc.l+1)*now.val;
        rc.sum=(rc.r-rc.l+1)*now.val;

        lc.allmax[now.val]=lc.lmax[now.val]=lc.rmax[now.val]=lc.r-lc.l+1;
        rc.allmax[now.val]=rc.lmax[now.val]=rc.rmax[now.val]=rc.r-rc.l+1;
        lc.allmax[now.val^1]=lc.lmax[now.val^1]=lc.rmax[now.val^1]=0;
        rc.allmax[now.val^1]=rc.lmax[now.val^1]=rc.rmax[now.val^1]=0;

        now.val=-1;
    }
    if(now.rev) {
        lc.sum=(lc.r-lc.l+1)-lc.sum;
        rc.sum=(rc.r-rc.l+1)-rc.sum;

        if(lc.val!=-1) lc.val^=1; else lc.rev^=1;
        if(rc.val!=-1) rc.val^=1; else rc.rev^=1;

        swap(lc.allmax[0],lc.allmax[1]);
        swap(lc.lmax[0],lc.lmax[1]);
        swap(lc.rmax[0],lc.rmax[1]);
        swap(rc.allmax[0],rc.allmax[1]);
        swap(rc.lmax[0],rc.lmax[1]);
        swap(rc.rmax[0],rc.rmax[1]);

        now.rev=0;
    }
}

void modify(int root,int type,int ml,int mr) {
    pushdown(tree[root],tree[root<<1],tree[root<<1|1]);
    if(tree[root].l==ml&&tree[root].r==mr) {
        if(type==0||type==1) {
            tree[root].sum=(tree[root].r-tree[root].l+1)*type;
            tree[root].allmax[type]=tree[root].lmax[type]=tree[root].rmax[type]=
                tree[root].r-tree[root].l+1;
            tree[root].allmax[type^1]=tree[root].lmax[type^1]=tree[root].rmax[type^1]=0;
            tree[root].val=type;
        } else {
            tree[root].sum=(tree[root].r-tree[root].l+1)-tree[root].sum;
            if(tree[root].val!=-1) tree[root].val^=1; else tree[root].rev^=1;
            swap(tree[root].allmax[0],tree[root].allmax[1]);
            swap(tree[root].lmax[0],tree[root].lmax[1]);
            swap(tree[root].rmax[0],tree[root].rmax[1]);
        }
        return;
    }
    int mid=(tree[root].l+tree[root].r)/2;
    if(mid<ml) modify(root<<1|1,type,ml,mr);
    else if(mr<=mid) modify(root<<1,type,ml,mr);
    else modify(root<<1,type,ml,mid),modify(root<<1|1,type,mid+1,mr);
    pushup(tree[root],tree[root<<1],tree[root<<1|1]);
}

int querysum(int root,int ql,int qr) {
    pushdown(tree[root],tree[root<<1],tree[root<<1|1]);
    if(ql==tree[root].l&&tree[root].r==qr) {
        return tree[root].sum;
    }
    int mid=(tree[root].l+tree[root].r)/2;
    if(mid<ql) return querysum(root<<1|1,ql,qr);
    else if(qr<=mid) return querysum(root<<1,ql,qr);
    else return querysum(root<<1,ql,mid)+querysum(root<<1|1,mid+1,qr);
}

node querymax(int root,int ql,int qr) {
    pushdown(tree[root],tree[root<<1],tree[root<<1|1]);
    if(ql==tree[root].l&&tree[root].r==qr) {
        return tree[root];
    }
    int mid=(tree[root].l+tree[root].r)/2;
    if(mid<ql) return querymax(root<<1|1,ql,qr);
    else if(qr<=mid) return querymax(root<<1,ql,qr);
    else {
        node res,lc=querymax(root<<1,ql,mid),rc=querymax(root<<1|1,mid+1,qr);
        pushup(res,lc,rc);
        return res;
    }
}

void build(int root,int l,int r) {
    tree[root].l=l; tree[root].r=r; tree[root].val=-1;
    if(l==r) {
        tree[root].sum=a[l];
        tree[root].allmax[0]=tree[root].lmax[0]=tree[root].rmax[0]=a[l]==0;
        tree[root].allmax[1]=tree[root].lmax[1]=tree[root].rmax[1]=a[l]==1;
        return;
    }
    int mid=(l+r)/2;
    build(root<<1,l,mid); build(root<<1|1,mid+1,r);
    pushup(tree[root],tree[root<<1],tree[root<<1|1]);
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
    }
    build(1,1,n);
    while(m--) {
        int opt,l,r;
        scanf("%d%d%d",&opt,&l,&r);
        l++; r++;
        if(opt==0||opt==1||opt==2) modify(1,opt,l,r);
        if(opt==3) printf("%d\n",querysum(1,l,r));
        if(opt==4) printf("%d\n",querymax(1,l,r).allmax[1]);
    }
    return 0;
}