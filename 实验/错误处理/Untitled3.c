#include <stdio.h>

int x,i;

int main()
{
	scanf("%d",&x);
	while(x%2==0)
	{
		x/=2;
		i++;
	}
	x=x*x;
	int y=x/2,z=y+1;
	if(y==1)
	{
		printf("-1\n");
		return;
	}
	while(i>0)
	{
		y*=2;
		z*=2;
		i--;
	}
	printf("%d %d",y,z);
	return 0;
}
