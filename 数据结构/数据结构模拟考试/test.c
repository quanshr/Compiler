#include <stdio.h>
#include <stdlib.h>

struct {
	int x;
	char *y;
}tab[2]={{1,"ab"},{2,"cd"}},*p=tab;

int main()
{
	printf("%c",*(++p)->y);
	return 0;
}
