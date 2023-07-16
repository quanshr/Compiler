#include <stdio.h>
#include <stdlib.h>

int n,m,a[110][110];
int i,j,x,y;
int v[110],k=-1;
void dfs(int x)
{
	printf("%d ",x);
	v[x]=1;
	int i;
	for(i=0;i<n;i++)
		if(i!=k&&a[x][i]&&!v[i])
			dfs(i);
}
void bfs()
{
	int q[110],l=1,r=0;
	q[++r]=0;
	v[0]=1;
	while(l<=r)
	{
		int x=q[l++];
		printf("%d ",x);
		int i;
		for(i=0;i<n;i++)
			if(i!=k&&a[x][i]&&!v[i])
			{
				v[i]=1;
				q[++r]=i;
			}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		a[x][y]=a[y][x]=1;
	}
	dfs(0);
	printf("\n");
	for(i=0;i<n;i++) v[i]=0;
	bfs();
	printf("\n");
	scanf("%d",&k);
	for(i=0;i<n;i++) v[i]=0;
	dfs(0);
	printf("\n");
	for(i=0;i<n;i++) v[i]=0;
	bfs();
	return 0;
}
