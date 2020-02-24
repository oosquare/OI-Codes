#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template <int MaxN>
class SuffixArray
{
public:
	inline void init(char str[]) {
		Len=strlen(str+1);
		for(int i=1;i<=Len;++i) Data[i]=str[i];
	}

	inline void preprocess(bool sa,bool height) {
		if(sa) DAPreprocess(Len);
		if(height) heightPreprocess(Len);
	}

	inline int atRank(int x) { return Rank[Cur][x]; }

	inline int atSA(int x) { return SA[x]; }

	inline int atHeight(int x) { return Height[x]; }

public:
	int SA[MaxN],Rank[2][MaxN],Height[MaxN],TmpSort[MaxN],Data[MaxN],Cur,Len;

	void sort(int n,int m) {
		for(int i=0;i<=m;++i) TmpSort[i]=0;
		for(int i=1;i<=n;++i) ++TmpSort[Rank[Cur][Rank[Cur^1][i]]];
		for(int i=1;i<=m;++i) TmpSort[i]+=TmpSort[i-1];
		for(int i=n;i>=1;i--) SA[TmpSort[Rank[Cur][Rank[Cur^1][i]]]--]=Rank[Cur^1][i];
	}

	inline bool equal(int f[],int x,int y,int l) { return f[x]==f[y]&&f[x+l]==f[y+l]; }

	void DAPreprocess(int n) {
		int m;
		for(int i=1;i<=n;++i) { Rank[Cur][i]=Data[i]; Rank[Cur^1][i]=i; }
		m=200; sort(n,m);
		for(int w=1,p=1,i;p<n;w*=2,m=p) {
			for(p=0,i=n-w+1;i<=n;++i) Rank[Cur^1][++p]=i;
			for(i=1;i<=n;++i) if(SA[i]>w) Rank[Cur^1][++p]=SA[i]-w;
			sort(n,m); Cur^=1; Rank[Cur][SA[1]]=p=1;
			for(i=2;i<=n;++i) Rank[Cur][SA[i]]=equal(Rank[Cur^1],SA[i],SA[i-1],w)?p:++p;
		}
	}

	void heightPreprocess(int n) {
		int j,k=0;
		for(int i=1;i<=n;Height[Rank[Cur][i++]]=k)
			for(k=k?k-1:k,j=SA[Rank[Cur][i]-1];Data[i+k]==Data[j+k];++k)
				;
	}
};

SuffixArray<20010> sa;
int val[20010],n;

inline int SA(int x) { return sa.atSA(x); }

inline int rank(int x) { return sa.atRank(x); }

inline int height(int x) { return sa.atHeight(x); }

bool check(int k) {
	int minn,maxx;
	minn=maxx=sa.atSA(1);
	for(int i=2;i<=n;++i) {
		if(height(i)<k) {
			minn=maxx=SA(i);
		} else {
			minn=min(minn,SA(i));
			maxx=max(maxx,SA(i));
		}
		if(maxx-minn>k) return true;
	}
	return false;
}

void solve() {
	for(int i=1,j=0;i<=n;++i) {
		scanf("%d",&val[i]);
		sa.Data[i]=val[i]-j+100;
		j=val[i];
	}
	sa.Data[n+1]=0;
	sa.Len=n+1;
	sa.preprocess(true,true);
	int left=2,right=n/2;
	while(left<=right) {
		int mid=(left+right)/2;
		if(check(mid)) {
			left=mid+1;
		} else {
			right=mid-1;
		}
	}
	if(right>=4) printf("%d\n",right+1);
	else printf("0\n");
}

int main() {
	while(true) {
		scanf("%d",&n);
		if(!n) break;
		solve();
	}
	return 0;
}
