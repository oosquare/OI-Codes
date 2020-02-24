#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

const int maxn=50000+10;
int wa[maxn],wb[maxn],wv[maxn],wss[maxn];

int cmp(int *r,int a,int b,int l) {
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void da(int *r,int *sa,int n,int m) {
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;++i) wss[i]=0;
	for(i=0;i<n;++i) wss[x[i]=r[i]]++;
	for(int i=1;i<m;++i) wss[i]+=wss[i-1];
	for(int i=n-1;i>=0;--i) sa[--wss[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p) {
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;++i) wv[i]=x[y[i]];
		for(i=0;i<m;++i) wss[i]=0;
		for(i=0;i<n;++i) wss[wv[i]]++;
		for(i=1;i<m;++i) wss[i]+=wss[i-1];
		for(i=n-1;i>=0;--i) sa[--wss[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i)
			x[sa[i]]=(cmp(y,sa[i-1],sa[i],j)?p-1:p++);
	}
}

int rankk[maxn],height[maxn],sa[maxn];

void calc(int *r,int *sa,int n) {
	int i,j,k=0;
	for(i=1;i<=n;++i) rankk[sa[i]]=i;
	for(i=0;i<n;height[rankk[i++]]=k) 
		for(k?k--:0,j=sa[rankk[i]-1];r[i+k]==r[j+k];k++);
}

int r[maxn],len,n,t,idx[maxn];
char str[maxn];

bool check(int x) {
	set<int> s;
	for(int i=1;i<len;++i) {
		if(height[i]>=x) {
			s.insert(idx[sa[i]]);
			s.insert(idx[sa[i-1]]);
		}else{
			if(s.size()==n) return true;
			s.clear();
		}
	}
	if(s.size()==n) return true;
	return false;
}

void solve() {
	if(n==1) {
		printf("%d\n",strlen(str));
		return;
	}
	int left=1,right=100,ans=0;
	while(left<=right) {
		int mid=(left+right)/2;
		if(check(mid)) {
			ans=mid;
			left=mid+1;
		}else{
			right=mid-1;
		}
	}
	printf("%d\n",ans);
}

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n); len=0;
		for(int i=1,v=0;i<=n;++i) {
			scanf("%s",str);
			int tmp=strlen(str);
			for(int j=0;j<tmp;++j) {
				idx[len]=i;
				r[len++]=(str[j]-'A'+2*n+1);
			}
			idx[len]=i;
			r[len++]=v++;
			for(int j=tmp-1;j>=0;--j) {
				idx[len]=i;
				r[len++]=(str[j]-'A'+2*n+1);
			}
			idx[len]=i;
			r[len++]=v++;
		}
		da(r,sa,len,300);
		calc(r,sa,len-1);
		solve();
	}
	return 0;
}