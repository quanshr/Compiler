#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n,ok[110],t,sor[110],v[110];
char name[110][25],num[110][25],na[110][25],nu[110][25];
int i,j,k,u;
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

int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("\n%s %s",name[i],num[i]);
		u=0;
		for(j=1;j<i;j++)
		{
			if(!v[j]) continue;
			if(cmp(name[i],name[j])==0)
			{
				if(cmp(num[i],num[j])==0) goto aaa;
				u++;
			}
		}
		t++;
		v[i]=1;
		for(j=0;name[i][j]!='\0';j++)
			na[t][j]=name[i][j];
		if(u==0) na[t][j]='\0';
		else
		{
			na[t][j]='_';
			na[t][++j]=u+'0';
			na[t][++j]='\0';
		}
		for(j=0;num[i][j]!='\0';j++)
			nu[t][j]=num[i][j];
		nu[t][j]='\0';
		aaa:;
	}
	for(i=1;i<=t;i++) sor[i]=i;
	for(i=1;i<=t;i++)
		for(j=i+1;j<=t;j++)
			if(cmp(na[sor[i]],na[sor[j]])==1)
			{
				k=sor[i];
				sor[i]=sor[j];
				sor[j]=k;
				//printf("%d ",k);
			}
	//printf("\n");
	for(i=1;i<=t;i++)
	{
		for(j=0;na[sor[i]][j]!='\0';j++) printf("%c",na[sor[i]][j]);
		printf(" ");
		for(j=0;nu[sor[i]][j]!='\0';j++) printf("%c",nu[sor[i]][j]);
		printf("\n");
	}
	return 0;
}
