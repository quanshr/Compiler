#include <stdio.h>
#include <stdlib.h>

int i,rear[10010],cnt,st[10010],p;
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

int main()
{
	gets(s);
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
			i--;
			continue;
		}
		if(s[i]=='(') st[++p]=-1;
		else if(s[i]==')')
		{
			while(p&&-st[p]!=1)
				rear[++cnt]=st[p--];
			p--;
		}
		else if(s[i]=='+'||s[i]=='-')
		{
			while(p&&-st[p]>=3) rear[++cnt]=st[p--];
			if(s[i]=='+') st[++p]=-3;
			else st[++p]=-4;
		}
		else if(s[i]=='*'||s[i]=='/')
		{
			while(p&&-st[p]>=5) rear[++cnt]=st[p--];
			if(s[i]=='*') st[++p]=-5;
			else st[++p]=-6;
		}
	}
	while(p) rear[++cnt]=st[p--];
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
	int ans=st[p--];

	printf("%d",ans);
	return 0;
}
