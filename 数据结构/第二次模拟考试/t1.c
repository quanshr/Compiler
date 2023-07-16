#include <stdio.h>
#include <stdlib.h>

int n,i,j;
int num[210],x,p[30000010],b[30000010];
char name[210][20],t[20];

int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d%s%d%s",&num[i],name[i],&x,t);
		if(!p[num[i]]) p[num[i]]=x;
		else if(p[num[i]]!=x) b[num[i]]=i;
	}
	for(i=1;i<=30000000;i++)
		if(b[i]) printf("%d %s\n",num[b[i]],name[b[i]]);
	return 0;
}
