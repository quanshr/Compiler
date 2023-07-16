#include <stdio.h>
#include <stdlib.h>

int i,st[10010],op[10010];
double rear[10010];
char s[10010];
int t;
void prt(int x)
{
	if(x>=0) printf("%d",x);
	else if(-x==3) printf("+");
	else if(-x==4) printf("-");
	else if(-x==5) printf("*");
	else if(-x==6) printf("/");
}
double calc(char *s)
{
	int cnt=0,p=0,i;
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]==' ') continue;
		if(s[i]>='0'&&s[i]<='9')
		{
			int x=0;
			while(s[i]>='0'&&s[i]<='9')
			{
				x=x*10+s[i]-'0';
				i++;
			}
			rear[++cnt]=x;
			op[cnt]=0;
			i--;
			continue;
		}
		if(s[i]=='(') st[++p]=-1;
		else if(s[i]==')')
		{
			while(p&&-st[p]!=1)
				op[++cnt]=st[p--];
			p--;
		}
		else if(s[i]=='+'||s[i]=='-')
		{
			while(p&&-st[p]>=3) op[++cnt]=st[p--];
			if(s[i]=='+') st[++p]=-3;
			else st[++p]=-4;
		}
		else if(s[i]=='*'||s[i]=='/')
		{
			while(p&&-st[p]>=5) op[++cnt]=st[p--];
			if(s[i]=='*') st[++p]=-5;
			else st[++p]=-6;
		}
	}
	while(p) op[++cnt]=st[p--];
	//for(i=1;i<=cnt;i++) printf("%d ",rear[i]);
	for(i=1;i<=cnt;i++)
	{
		if(rear[i]>=0) st[++p]=rear[i];
		else if(rear[i]==-3)
		{
			st[p-1]=st[p-1]+st[p];
			p--;
		}
		else if(rear[i]==-4)
		{
			st[p-1]=st[p-1]-st[p];
			p--;
		}
		else if(rear[i]==-5)
		{
			st[p-1]=st[p-1]*st[p];
			p--;
		}
		else if(rear[i]==-6)
		{
			st[p-1]=st[p-1]/st[p];
			p--;
		}
	}
	return st[p--];
}

int main()
{
	gets(s);
	printf("%.3lf",calc(s));
	return 0;
}
