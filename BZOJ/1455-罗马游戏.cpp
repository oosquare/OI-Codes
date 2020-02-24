#include <bits/stdc++.h>
using namespace std;

struct node
{
    int l,r,v,d,fa;
};

const int maxn=100000+10;
node heap[maxn<<4]; int tot,root[maxn];
int n,m;

int merge(int x,int y){
    if(!x||!y) return x^y;
    if((heap[x].v>heap[y].v)||(heap[x].v==heap[y].v&&x>y)) swap(x,y);
    heap[x].r=merge(heap[x].r,y);
    if(heap[heap[x].l].d<heap[heap[x].r].d) swap(heap[x].l,heap[x].r);
    heap[x].d=heap[heap[x].r].d+1;
    heap[x].fa=heap[heap[x].l].fa=heap[heap[x].r].fa=x;
    return x;
}

void pop(int x){
    heap[x].v=-1;
    heap[heap[x].l].fa=heap[x].l;
    heap[heap[x].r].fa=heap[x].r;
    heap[x].fa=merge(heap[x].l,heap[x].r);
}

int find(int x){
    return x==heap[x].fa?x:heap[x].fa=find(heap[x].fa);
}

int main(){
    scanf("%d",&n);
    heap[0].d=-1;
    for(int i=1;i<=n;++i){
        int x; scanf("%d",&x);
        heap[i].v=x; heap[i].fa=i;
    }
    scanf("%d",&m);
    while(m--){
        int x,y; char opt[5];
        scanf("%s",&opt);
        if(opt[0]=='M'){
            scanf("%d%d",&x,&y);
            if(heap[x].v==-1||heap[y].v==-1) continue;
            int fx=find(x),fy=find(y);
            if(fx!=fy) heap[fx].fa=heap[fy].fa=merge(fx,fy);
        }else{
            scanf("%d",&x);
            if(heap[x].v==-1) printf("0\n");
            else{
                printf("%d\n",heap[find(x)].v);
                pop(find(x));
            }
        }
    }
    return 0;
}
