#include <stdio.h>
#include <stdlib.h>

int n,m,a[1010][2];
int i,j,z,x,y;
int v[1010],e[1010];
void dfs(int x,int dep)
{
	v[x]=1;
	if(x==n-1)
	{
		int i;
		for(i=0;i<dep;i++) printf("%d ",e[i]);
		printf("\n");
		return;
	}
	int i;
	for(i=0;i<1000;i++)
		if(a[i][0]==x&&!v[a[i][1]])
		{
			v[a[i][1]]=1;
			e[dep]=i;
			dfs(a[i][1],dep+1);
			v[a[i][1]]=0;
		}
		else if(a[i][1]==x&&!v[a[i][0]])
		{
			v[a[i][0]]=1;
			e[dep]=i;
			dfs(a[i][0],dep+1);
			v[a[i][0]]=0;
		}
		
}

int main()
{
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d",&z);
		scanf("%d%d",&a[z][0],&a[z][1]);
	}
	dfs(0,0);
	return 0;
}
