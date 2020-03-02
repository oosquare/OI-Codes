#include <bits/stdc++.h>
using namespace std;

struct node {
    int next[10];
    int fail;
    bool end;
    int &operator[](int x) { return next[x]; }
};

constexpr int maxl=1200+2;
constexpr int maxm=100+2;
constexpr int maxL=1500+2;
constexpr int mod=1e9+7;

node trie[maxL<<2]; int total=1,root=1;
int f[maxl][maxL];
int digit[maxl];
char ss[maxl];
int m,n;

void insert(char s[]){
    int len=strlen(s+1);
    int x=root;
    for(int i=1;i<=len;++i){
        if(!trie[x][s[i]-'0']) trie[x][s[i]-'0']=++total;
        x=trie[x][s[i]-'0'];
    }
    trie[x].end=true;
}

void build(){
    queue<int> q;
    for(int i=0;i<=9;++i){
        trie[0][i]=root;
    }
    q.push(root);
    while(!q.empty()){
        int x=q.front(); q.pop();
        for(int i=0;i<=9;++i){
            if(!trie[x][i]){
                trie[x][i]=trie[trie[x].fail][i];
                continue;
            }
            trie[trie[x][i]].fail=trie[trie[x].fail][i];
			trie[trie[x][i]].end|=trie[trie[trie[x][i]].fail].end;
            q.push(trie[x][i]);
        }
    }
}

void preprocess(){
	for(int i=1;i<=total;++i) f[n][i]=1;
	for(int i=n-1;i;--i){
		for(int j=1;j<=total;++j){
			for(int k=0;k<=9;++k){
				if(!trie[trie[j][k]].end){
					(f[i][j]+=f[i+1][trie[j][k]])%=mod;
				}
			}
		}
	}
}

int calc(){
	int ans=0;
	for(int i=1;i<digit[1];++i){
		if(!trie[trie[root][i]].end) (ans+=f[1][trie[root][i]])%=mod;
	}
	for(int i=2;i<=n;++i){
		for(int j=1;j<=9;++j){
			if(!trie[trie[root][j]].end) (ans+=f[i][trie[root][j]])%=mod;
		}
	}
	int x=root;
	for(int i=1;i<=n;++i){
		x=trie[x][digit[i]];
		if(trie[x].end) break;
		if(i<n){
			for(int j=0;j<digit[i+1];++j){
				if(!trie[trie[x][j]].end){
					(ans+=f[i+1][trie[x][j]])%=mod;
				}
			}
		}else{
			(ans+=1)%=mod;
		}
	}
	return ans;
}

int main(){
    scanf("%s",ss+1);
    n=strlen(ss+1);
    for(int i=1;i<=n;++i){
        digit[i]=ss[i]-'0';
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i){
        scanf("%s",ss+1);
        insert(ss);
    }
    build();
    preprocess();
    printf("%d\n",calc());
    return 0;
}