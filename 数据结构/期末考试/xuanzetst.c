#include <stdio.h>
#include <stdlib.h>

struct student
{
	int age;
	int no;
};
struct student std,*p;

int main()
{
	p=&std;
	std.no=10;
	printf("%d\n",*p.no);
	return 0;
}
