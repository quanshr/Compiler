#include <stdio.h>
#include <stdlib.h>

int i,j,rear[10010],cnt,st[10010],p,op[10010];
double ans,re[10010];
char s[10010];
int t;
void prt(int x)
{
	if(x>=0) printf("%d",x);
	else if(x==3) printf("+");
	else if(x==4) printf("-");
	else if(x==5) printf("*");
	else if(x==6) printf("/");
}

int main()
{
	gets(s);
	for(i=0;s[i]!='=';i++)
	{
		//printf("%d ",i);
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
	/*for(i=1;i<=cnt;i++) prt(rear[i]);
	printf("\n");*/
	for(i=1;i<=cnt;i++)
	{
		if(rear[i]>=0) re[i]=rear[i];
		else op[i]=-rear[i];
	}
	for(i=0;;i++)
	{
		/*printf("%d:",i);
		for(j=1;j<=cnt;j++) //printf("%d",op[j]); 
		{
			printf("%lf %d\n",re[j],op[j]);
		}
		printf("\n");*/
		if(i)
		{
			int m=0;
			for(j=1;j<=cnt;j++)
			{
				if(j+2<=cnt&&op[j]==0&&op[j+1]==0&&op[j+2]!=0)
				{
					op[++m]=0;
					if(op[j+2]==3) re[m]=re[j]+re[j+1];
					else if(op[j+2]==4) re[m]=re[j]-re[j+1];
					else if(op[j+2]==5) re[m]=re[j]*re[j+1];
					else if(op[j+2]==6) re[m]=re[j]/re[j+1];
					j+=2;
				}
				else
				{
					re[++m]=re[j];
					op[m]=op[j];
				}
			}
			cnt=m;
		}
		if(cnt==1)
		{
			printf("%.0lf\n%d",re[1],i);
			return 0;
		}
	}
	//printf("%d",ans);
	return 0;
}
