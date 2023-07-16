#include <stdio.h>
#include <stdlib.h>

int n,k,num[510],l[510][12],r[510][12],i,j,x,y,p;

int main()
{
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		for(j=1;j<=k;j++) scanf("%d",&l[i][j]);
		for(j=1;j<=k;j++) scanf("%d",&r[i][j]);
	}
	for(i=1;i<=n;i++)
	{
		int ok=0;
		for(j=1;j<=n;j++)
		{
			int flag=1;
			for(p=1;p<=k;p++)
				if(l[i][p]!=r[j][p]) flag=0;
			if(flag) ok=1;
		}
		if(!ok) x=i;
	}
	for(i=1;i<=n;i++)
	{
		int ok=0;
		for(j=1;j<=n;j++)
		{
			int flag=1;
			for(p=1;p<=k;p++)
				if(r[i][p]!=l[j][p]) flag=0;
			if(flag) ok=1;
		}
		if(!ok) y=i;
	}
	if(x==0) printf("H@ppy Birthd@y t0 lqq!");
	else
	{
		x=num[x]; y=num[y];
		if(x>y) printf("%d %d",y,x);
		else printf("%d %d",x,y);
	}
	return 0;
}
