#include <stdio.h>
#include <stdlib.h>
#define int long long

int n,m,i,j,k,v[1010];
char jb[9][15]={"","caster","medic","supporter","specialist","vanguard","guard","defender","sniper"};
char s[15];
typedef struct
{
	int i,job,rk;
	char name[200];
}nd;
nd a[1010];
int cmp2(const void *_a,const void *_b)
{
	nd *a=(nd*)_a,*b=(nd*)_b;
	if(a->rk!=b->rk) return a->rk-b->rk;
	return a->i-b->i;
}
int cmp1(const void *_a,const void *_b)
{
	nd *a=(nd*)_a,*b=(nd*)_b;
	if(a->job!=b->job) return b->job-a->job;
	return a->i-b->i;
}
int ans[1010];

signed main()
{
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%s%s%lld",&a[i].i,a[i].name,s,&a[i].rk);
		for(j=1;j<=8;j++)
		{
			for(k=0;s[k]!='\0'&&jb[j][k]!='\0';k++)
				if(s[k]!=jb[j][k]) break;
			if(jb[j][k]=='\0')
			{
				a[i].job=j;
				break;
			}
		}
	}
	qsort(a+1,n,sizeof(a[1]),cmp2);
	for(i=1;i<=n;i++)
		printf("%lld %s %s %lld\n",a[i].i,a[i].name,jb[a[i].job],a[i].rk);
	qsort(a+1,n,sizeof(a[1]),cmp1);
	for(i=1;i<=n;i++)
		printf("%lld %s %s %lld\n",a[i].i,a[i].name,jb[a[i].job],a[i].rk);
	for(i=1;i<=m;i++)
	{
		int x,l,r,job;
		scanf("%lld%s%lld%lld",&x,s,&l,&r);
		for(j=1;j<=8;j++)
		{
			for(k=0;s[k]!='\0'&&jb[j][k]!='\0';k++)
				if(s[k]!=jb[j][k]) break;
			if(jb[j][k]=='\0')
			{
				job=j;
				break;
			}
		}
		ans[0]=0;
		for(j=0;j<=1000;j++)
			if(!v[j])
				for(k=1;k<=n;k++)
					if(a[k].i==j)
					{
						if(a[k].job==job&&a[k].rk>=l&&a[k].rk<=r)
							ans[++ans[0]]=j;
						break;
					}
		if(ans[0]>=x)
		{
			for(j=1;j<=x;j++)
			{
				v[ans[j]]=1;
				printf("%lld ",ans[j]);
			}
			printf("\n");
		}
		else printf("DAMEDANE\n");
	}
	return 0;
}
