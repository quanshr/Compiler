#include <stdio.h>
#include <string.h>

int n,p;
char s[100010];

int main()
{
	gets(s);
	n=strlen(s);
	//printf("%d\n",n);
	int i,j;
	for(i=0;i<n;i++)
		if(s[i]=='.')
			p=i;		
	for(i=0;i<n;i++)
	{
		if(s[i]>='1'&&s[i]<='9')
		{
			if(i<p) p=p-1-i;
			else p=p-i;
			printf("%c",s[i]);
			if(i!=n-1)
			{
				printf(".");
				for(i=i+1;i<n;i++)
					if(s[i]!='.')
						printf("%c",s[i]);	
			}
			printf("e%d",p);
		}
	}
	return 0;
}

