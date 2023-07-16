#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n,op,aa[10]={50,70,100,110};
char s[1010][210],c,f[210];
int i,j,k;
int cmp(char *a,char *b)
{
	while(*a!='\0'&&*b!='\0')
	{
		if(*a<*b) return -1;
		if(*a>*b) return 1;
		a++; b++;
	}
	if(*a=='\0')
	{
		if(*b=='\0') return 0;
		return -1;
	}
	return 1;
}
int ucmp(char *a,char *b)
{
	while(*a!='\0'&&*b!='\0')
	{
		if(*a<*b) return -1;
		if(*a>*b) return 1;
		a++; b++;
	}
	if(*a=='\0') return 0;
	return 1;
}
void fswap(char *a,char *b)
{
	int i=0;
	for(i=0;i<=120;i++)
	{
		c=*a;
		*a=*b;
		*b=c;
		a++; b++;
	}
}
void fprint(char *a)
{
	while(*a!='\0')
	{
		printf("%c",*a);
		a++;
	}
	printf("\n");
}
void formprint(char *a)
{
	int x=0,u=0;
	while(1)
	{
		if(*a!=' '&&*a!='\0')
		{
			x++;
			printf("%c",*a);
		}
		else
		{
			while(x<aa[u])
			{
				printf(" ");
				x++;
			}
			u++;
			if(*a=='\0')
			{
				printf("\n");
				return;
			}
		}
		a++;
	}
}


int main()
{
	gets(f);
	printf("%s\n",f);
	gets(f);
	printf("%s\n",f);
	return 0;
}
