#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int x,l,r,s;
}node;
node e[100010];
int cnt,n,x,i,j,a[10010],tot,u,b[10010],mx;
void add(int x)
{
	int p=1;
	while(1)
	{
		a[i]++; tot++;
		if(x==e[p].x) break;
		if(x<e[p].x)
		{
			if(!e[p].l)
			{
				e[p].l=++cnt;
				e[cnt].x=x;
				a[i]--; tot--;
			}
			p=e[p].l;
		}
		else
		{
			if(!e[p].r)
			{
				e[p].r=++cnt;
				e[cnt].x=x;
				a[i]--; tot--;
			}
			p=e[p].r;
		}
	}
	e[p].s++;
	//if(a[i]>a[u]||a[i]==a[u]&&x<b[u]) u=i;
}
void find(int x)
{
	int p=1;
	while(1)
	{
		printf("%d ",e[p].x);
		if(x==e[p].x) break;
		if(x<e[p].x) p=e[p].l;
		else p=e[p].r;
	}
}
void dfs(int p)
{
	if(!p||u) return;
	//printf("%d\n",e[p].x);
	dfs(e[p].l);
	dfs(e[p].r);
	if(!u&&e[p].s==mx)
	{
		u=p;
		return;
	}	
}

int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&x);
		b[i]=x;
		if(i==1)
		{
			e[++cnt].x=x;
			e[cnt].s=1;
			//u=1;
		}
		else add(x);
	}
	printf("%d\n",tot);
	for(i=1;i<=cnt;i++)
		if(e[i].s>mx) mx=e[i].s;
	//printf("%d\n",mx);
	dfs(1);
	find(e[u].x);
	return 0;
}
