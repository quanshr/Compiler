#include <stdio.h>
#include <string.h>

int n,v[20],a[20],i;
void dfs(int dep)
{
	if(dep==n)
	{
		int i;
		for(i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
		return;
	}
	dep++;
	int i;
	for(i=1;i<=n;i++)
		if(!v[i])
		{
			v[i]=1;
			a[dep]=i;
			dfs(dep);
			v[i]=0;
		}
}

int main()
{
	scanf("%d",&n);
	dfs(0);
	return 0;
}



