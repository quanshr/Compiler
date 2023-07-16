#include <stdio.h>
#include <stdlib.h>

int n,m,i,j,k;
int t,tt;
long long ans[5000010],a[5000010],xa[5000010],b[5000010],xb[5000010],c[5000010];
int cmp(const void *p1,const void *p2)
{
	const long long *a=(const long long *)p1;
	const long long *b=(const long long *)p2;
	if(*a<*b) return 1;
	if(*a==*b) return 0;
	return -1;
}
int main()
{
	do
	{
		n++;
		scanf("%lld%lld",&a[n],&xa[n]);
	}while(xa[n]!=0);
	do
	{
		m++;
		scanf("%lld%lld",&b[m],&xb[m]);
	}while(xb[m]!=0);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			c[++t]=xa[i]+xb[j];
	qsort(c+1,t,sizeof(long long),cmp);
	for(i=1;i<=t;i++)
		if(!tt||c[tt]!=c[i]) c[++tt]=c[i];
	t=tt;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			for(k=1;k<=t;k++)
				if(xa[i]+xb[j]==c[k])
					ans[k]+=a[i]*b[j];
	for(i=1;i<=t;i++)
		if(ans[i]!=0) printf("%lld %lld ",ans[i],c[i]);
	return 0;
}
