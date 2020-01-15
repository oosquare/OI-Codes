#include <cstdio>
#include <cstring>
using namespace std;

const int lim=1000001;
bool re[lim];
int prime[lim],v[lim];
int m;

void generate(int n){
    memset(v,0,sizeof(v));
    m=0;
    for(int i=2;i<=n;i++){
        if(v[i]==0){
            v[i]=i;
            prime[++m]=i;
            re[i]=1;
        }
        for(int j=1;j<=m;j++){
            if(prime[j]>v[i]||prime[j]>n/i)break;
            v[i*prime[j]]=prime[j];
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    generate(lim);
    if(n<=2){
        printf("1\n");
    }else{
        printf("2\n");
    }
    for(int i=2;i<=n+1;i++){
        if(re[i])printf("1 ");
        else printf("2 ");
    }
}