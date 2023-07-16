#include <stdio.h>
#include <string.h>

int n,s[10010],t[10010],top,f;
char x[10010];
int i,j;

int main()
{
	scanf("%s",x+1);
	n=strlen(x+1);
	top=100;
	for(i=n;i;i--) s[top--]=x[i]-'0';
	scanf("%s",x+1);
	n=strlen(x+1);
	top=100;
	for(i=n;i;i--) t[top--]=x[i]-'0';
	for(i=1;i<=100;i++)
		if(s[i]<t[i])
		{
			for(;i<=100;i++)
			{
				int k=s[i];
				s[i]=t[i];
				t[i]=k;
			}
			f=-1;
		}
		else if(s[i]>t[i]) break;
	for(i=100;i;i--)
	{
		s[i]-=t[i];
		if(s[i]<0)
		{
			s[i]+=10;
			s[i-1]--;
		}
	}
	if(f==-1) printf("-");
	for(i=1;i<=100;i++)
		if(s[i]!=0)
		{
			for(;i<=100;i++)
				printf("%d",s[i]);
		}
	if(i==101) printf("0");
	return 0;
}

