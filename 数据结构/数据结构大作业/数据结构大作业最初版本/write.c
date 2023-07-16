#include <stdio.h>

void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

int main()
{
	write(15);
	return 0;
}
