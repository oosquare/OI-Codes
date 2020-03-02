#include <bits/stdc++.h>
using namespace std;

struct node {
    int next[4];
    int fail;
    int status;
    int &operator[](int x) { return next[x]; }
};

struct record {
    int pre,len;
};

struct record2 {
    int present,status,len;
};

constexpr int maxn=15;
constexpr int maxl=6000;
int n,t;
node ac[maxl]; int total=1,root=1;
bool vis[maxl][1<<12];
char ss[maxl];

int convert(char c){
    if(c=='A') return 0;
    if(c=='G') return 1;
    if(c=='C') return 2;
    if(c=='T') return 3;
}

char convert(int v){
    if(v==0) return 'A';
    if(v==1) return 'G';
    if(v==2) return 'C';
    if(v==3) return 'T';
}

void insert(char s[],int id){
    int len=strlen(s),x=root;
    for(int i=0;i<len;++i){
        int y=convert(s[i]);
        if(!ac[x][y]) ac[x][y]=++total;
        x=ac[x][y];
    }
    ac[x].status|=1<<(id-1);
}

void build(){
    queue<int> q;
    for(int i=0;i<4;++i) ac[0][i]=root;
    q.push(root);
    while(!q.empty()){
        int x=q.front(); q.pop();
        for(int i=0;i<4;++i){
            if(!ac[x][i]) ac[x][i]=ac[ac[x].fail][i];
            else{
                ac[ac[x][i]].fail=ac[ac[x].fail][i];
                ac[ac[x][i]].status|=ac[x].status;
                q.push(ac[x][i]);
            }
        }
    }
    for(int i=1;i<=total;++i) ac[i].status|=ac[ac[i].fail].status;
}

void DP(){
    queue<record2> q;
    q.push((record2){1,0,0});
    vis[1][0]=1;
    int ends=(1<<n)-1;
    while(!q.empty()){
        int x=q.front().present,s=q.front().status,l=q.front().len; q.pop();
        if(s==ends){
            printf("%d\n",l);
            return;
        }
        for(int i=0;i<4;++i){
            int y=ac[x][i];
            int ns=ac[y].status|s;
            if(vis[y][ns]) continue;
            vis[y][ns]=true;
            q.push((record2){y,ns,l+1});
        }
    }
}

int main(){
    scanf("%d",&t);
    while(t--){
        memset(ac,0,sizeof(ac));
        memset(vis,0,sizeof(vis));
        total=1;
        scanf("%d",&n);
        for(int i=1;i<=n;++i){
            scanf("%s",ss);
            insert(ss,i);
        }
        build();
        DP();
    }
    return 0;
}