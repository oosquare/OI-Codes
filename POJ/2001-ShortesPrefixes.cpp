#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=1e7;

int n,trie[maxn][27],cnt[maxn],last[maxn],tot=1;
char s[maxn][30],a[maxn];

void insert(char str[]){
    int len=strlen(str+1),u=1;
    for(int i=1;i<=len;++i){
        int c=str[i]-'a';
        if(!trie[u][c]) trie[u][c]=++tot;
        u=trie[u][c];
        ++cnt[u];
    }
    //last[u]=1;
}

void query(char str[],char ans[]){
    int len=strlen(str+1),u=1;
    for(int i=1;i<=len;++i){
        int c=str[i]-'a';
        u=trie[u][c];
        putchar(str[i]);
        if(cnt[u]==1) break;
    }
    putchar('\n');
}

int main(){
    n=1;
    while(scanf("%s",s[n]+1)!=EOF){
        insert(s[n]);
        ++n;
    }
    --n;
    for(int i=1;i<=n;++i){
        printf("%s ",s[i]+1);
        query(s[i],a);
    }
}