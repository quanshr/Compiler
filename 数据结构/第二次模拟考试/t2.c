#include <stdio.h>
#include <stdlib.h>

int hash(char c[])
{
	int x=0,i;
	for(i=0;c[i]!='\0';i++) x=(x*233+c[i]-'a'+1)%200000;
	return x;
}
int st[1010],op,p,x,b[200010],mp[1010],i,t;
char s[20],name[1010][20];
int vec[1010][1010];

int main()
{
	while(scanf("%d",&op)!=EOF)
	{
		//printf("eee");
		if(op==8)
		{
			scanf("%s",s);
			//printf("    %s\n",s);
			x=hash(s);
			//printf("   %d\n",x);
			if(!b[x])
			{
				b[x]=++t;
				for(i=0;i==0||s[i-1]!='\0';i++)
					name[t][i]=s[i];
				mp[i]=x;
			}
			if(p) vec[st[p]][++vec[st[p]][0]]=b[x];
			st[++p]=b[x];
		}
		else p--;
	}
	for(i=1;i<=t;i++)
	{
		if(vec[i][0])
		{
			printf("%s:",name[i]);
			printf("%s",name[vec[i][1]]);
			int j,k;
			for(j=2;j<=vec[i][0];j++)
			{
				int ok=1;
				for(k=1;k<j;k++)
					if(vec[i][j]==vec[i][k]) ok=0;
				if(ok) printf(",%s",name[vec[i][j]]);
			}
			printf("\n");
		}
	}
	return 0;
}
