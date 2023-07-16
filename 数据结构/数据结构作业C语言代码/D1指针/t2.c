#include <stdio.h>
#include <string.h>

int n,lst=1;
long long x,ans,f=1;
char s[100010];

int main()
{
	gets(s);
	n=strlen(s);
	//printf("%d\n",n);
	int i,j;
	for(i=0;i<n;i++)
	{
		//printf("%c %d %d %d %d\n",s[i],ans,lst,f,x);
		if(s[i]==' ') continue;
		if(s[i]>='0'&&s[i]<='9')
			x=x*10+s[i]-'0';
		else
		{
			if(lst==1) f*=x;
			else f/=x;
			if(s[i]=='/') lst=-1;
			else lst=1;
			if(s[i]!='*'&&s[i]!='/')
			{
				ans+=f;
				lst=1;
				if(s[i]=='+') f=1;
				else f=-1;
			}
			x=0;
		}
	}
	printf("%lld",ans);
	return 0;
}

