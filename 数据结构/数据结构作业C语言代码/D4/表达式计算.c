#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char c[100010];
double done[100010];
int n;
double calc(int l,int r)
{
	int lst=1,i;
	double f=1,x=0,ans=0;
	for(i=l;i<=r;i++)
	{
		if(c[i]==' ') continue;
		if(c[i]>='0'&&c[i]<='9')
			x=x*10+c[i]-'0';
		else if(c[i]=='[')
			x=done[i];
		else
		{
			if(lst==1) f*=x;
			else f/=x;
			if(c[i]=='/') lst=-1;
			else lst=1;
			if(c[i]!='*'&&c[i]!='/')
			{
				ans+=f;
				lst=1;
				if(c[i]=='+') f=1;
				else f=-1;
			}
			x=0;
		}
	}
	//for(i=l;i<=r;i++) printf("%c",c[i]);
	//printf("  ::     %d %d %.2lf\n",l,r,ans);
	return ans;
}
int st[100010],p;

int main()
{
	gets(c);
	n=strlen(c);
	int i;
	for(i=0;i<n;i++)
		if(c[i]=='(') st[++p]=i;
		else if(c[i]==')')
		{
			done[i]=calc(st[p]+1,i);
			int j=0;
			for(j=st[p];j<i;j++) c[j]=' ';
			c[i]='[';
			p--;
		}
	printf("%.2lf",calc(0,n));
	return 0;
}

