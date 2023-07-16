#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *s;
	int a[]={1,3,5,7,9},*pt=a+2;
	printf("%d\n",(*pt)++);
	printf("%d",*pt);
	scanf("%s",s);
	printf("%s",s);
	return 0;
}
