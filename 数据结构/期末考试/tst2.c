#include <stdio.h>
#include <stdlib.h>

struct point
{
	float x,y;
};
struct trangle
{
	struct point a,b,c;
}tr;

int main()
{
	(tr.b).x=1.5;
	printf("%f\n",tr.b.x);
	return 0;
}
