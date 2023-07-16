#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n,u=3,i,x,l,r,in[1000010],out[1000010];

int main()
{
	scanf("%d",&n);
	l=1; r=0;
	for(i=1;l<=r||i<=n;i++)
	{
		if(i<=n)
		{
			scanf("%d",&x);
			while(x)
			{
				in[++r]=i;
				x--;
			}
			if(u<=4&&(r-l+1)/u>=7) u++;
			if(u<=4&&(r-l+1)/u>=7) u++;
		}
		int v=u;
		while(l<=r&&v)
		{
			out[l++]=i;
			v--;
		}
		if(u>=4&&(r-l+1)/u<7) u--;
		if(u>=4&&(r-l+1)/u<7) u--;
	}
	for(i=1;i<=r;i++)
		printf("%d : %d\n",i,out[i]-in[i]);
	return 0;
}

