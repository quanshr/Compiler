#include <stdio.h>
#include <stdlib.h>

int n,m,i;
typedef struct
{
	int p,x,y,l;
}edge;
edge e[1010];
int cmp1(const void *_a,const void *_b)
{
	if(((edge*)_a)->l<((edge*)_b)->l) return -1;
	return 1;
}
int f[1010],ans[1010],t,sum;
int find(int x)
{
	if(x==f[x]) return x;
	f[x]=find(f[x]);
	return f[x];
	//return x==f[x]?x:f[x]=find(f[x]);
}
int cmp2(const void *_a,const void *_b)
{
	return *(int*)_a<*(int*)_b?-1:1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%d%d%d",&e[i].p,&e[i].x,&e[i].y,&e[i].l);
	qsort(e+1,m,sizeof(e[1]),cmp1);	
	//for(i=1;i<=m;i++) printf("%d %d %d %d\n",e[i].p,e[i].x,e[i].y,e[i].l);
	for(i=0;i<n;i++) f[i]=i;
	for(i=1;i<=m;i++)
	{
		int fx=find(e[i].x),fy=find(e[i].y);
		if(fx==fy) continue;
		f[fx]=fy;
		ans[++t]=e[i].p;
		sum+=e[i].l;
	}
	qsort(ans+1,t,sizeof(ans[1]),cmp2);
	printf("%d\n",sum);
	for(i=1;i<=t;i++) printf("%d ",ans[i]);
	return 0;
}
