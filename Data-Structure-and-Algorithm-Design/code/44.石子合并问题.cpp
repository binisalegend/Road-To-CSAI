#include<iostream>
#include<algorithm>
#define sum(j,k) tt[k]-tt[j-1]
using namespace std;
int n;
int se[205],tt[205],dpx[205][205],dpn[205][205];
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>se[i];
		se[i+n]=se[i];
	}
	for(int i=1;i<=2*n;i++) tt[i]=tt[i-1]+se[i];
	for(int i=1;i<n;i++) 
	{
		for(int j=1,k=j+i; j<2*n && k<2*n ; j++,k=j+i)
		{
			 dpn[j][k]=0x7fffffff;
			 for(int w=j;w<k;w++)
			 {
			 	dpx[j][k] = max(dpx[j][k],dpx[j][w]+dpx[w+1][k]+sum(j,k));
			 	dpn[j][k] = min(dpn[j][k],dpn[j][w]+dpn[w+1][k]+sum(j,k));
			 }
		} 
	}
	int maxx=0,minn=0x7fffffff;
	for(int i=1;i<=n;i++)
	{
		maxx=max(maxx,dpx[i][i+n-1]);
		minn=min(minn,dpn[i][i+n-1]);
	}
	cout<<minn<<endl<<maxx<<endl;
	return 0;
} 
