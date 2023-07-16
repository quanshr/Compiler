#include <stdio.h>
#include <stdlib.h>

int i,j,ans;

int main()
{
	for(i=0;i<(1<<8);i++)
	{
		int x=0,ok=1;
		for(j=0;j<8;j++)
		{
			int y=(i>>j)&1;
			if(y) x++;
			else x--;
			if(x<0) ok=0; 
		}
		if(x==0) ans+=ok;
	}
	printf("%d",ans);
	return 0;
}
