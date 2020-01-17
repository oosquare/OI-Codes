#include<cstdio>
using namespace std;

struct s
{
	int a,b,g,k;
};

int n;
s a[10001];
int x,y;

inline int read(){
	int x=0,f=1;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-f;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	return x*f;
}

int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].a=read();
		a[i].b=read();
		a[i].g=read();
		a[i].k=read();
	}
	x=read();
	y=read();
	for(int i=n;i>=1;i--){
		if(x>=a[i].a&&x<=a[i].a+a[i].g&&y>=a[i].b&&y<=a[i].b+a[i].k){
			printf("%d",i);
			return 0; 
		}
	}
	printf("-1");
}