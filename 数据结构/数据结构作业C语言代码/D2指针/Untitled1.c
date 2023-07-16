#include <stdio.h>

int a[10]={1,5,10,15};
int *p;

int main()
{
	p=a;
	printf("%d",*((char*)1));
	printf("\n%d",*p);
	return 0; 
}
