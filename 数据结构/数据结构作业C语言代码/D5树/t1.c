#include <stdio.h>
#include <stdlib.h>

int n,cnt=1,p,i,j,a;
struct
{
	int x,dep,l,r;
}e[1000010];
void dfs(int p)
{
	if(!e[p].l&&!e[p].r)
	{
		printf("%d %d\n",e[p].x,e[p].dep);
		return;
	}
	if(e[p].l) dfs(e[p].l);
	if(e[p].r) dfs(e[p].r);
}

int main()
{
	scanf("%d",&n);
	e[1].x=-2e9;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a);
		p=1;
		int ok=1;
		while(ok)
		{
			if(e[p].x>a)
			{
				if(!e[p].l)
				{
					e[p].l=++cnt;
					e[cnt].x=a;
					e[cnt].dep=e[p].dep+1;
					ok=0;
				}
				p=e[p].l;
			}
			else
			{
				if(!e[p].r)
				{
					e[p].r=++cnt;
					e[cnt].x=a;
					e[cnt].dep=e[p].dep+1;
					ok=0;
				}
				p=e[p].r;
			}
		}
	}
	dfs(1);
	return 0;
}
