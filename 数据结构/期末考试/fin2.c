#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double done[100010];
double va[200];
double calc(char *c,int l,int r)
{
	int lst=1,i;
	double f=1,x=0,ans=0;
	for(i=l;i<=r;i++)
	{
		if(c[i]==' ') continue;
		if(c[i]>='0'&&c[i]<='9')
			x=x*10+c[i]-'0';
		else if(c[i]>='a'&&c[i]<='z') x=va[c[i]];
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
	return ans;
}
int st[100010],p;
double get(char *c)
{
	int n=strlen(c);
	int i;
	for(i=0;i<n;i++)
		if(c[i]=='(') st[++p]=i;
		else if(c[i]==')')
		{
			done[i]=calc(c,st[p]+1,i);
			int j=0;
			for(j=st[p];j<i;j++) c[j]=' ';
			c[i]='[';
			p--;
		}
	return calc(c,0,n);
}
int n;
char s[100010];

int main()
{
	int i;
	while(1)
	{
		gets(s);
		n=strlen(s);
		//printf("  %s\n",s);
		if(n==4&&s[0]=='e'&&s[1]=='x'&&s[2]=='i'&&s[3]=='t') break;
		int op=1;
		for(i=0;i<n;i++) if(s[i]=='=') op=0;
		if(op==0)
		{
			if(s[1]!='=') while(1);
			va[s[0]]=get(s+2);
		}
		else
		{
			//printf("   %d,%c",n,s[6]);
			//printf("%d\n",n);
			for(i=6;i<n;i+=2)
				printf("%.3lf ",va[s[i]]);
			printf("\n");
		}
	}
	return 0;
}

