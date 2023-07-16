#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n,a[20],i,j,v[20],p,l;
char s[20],t[20][20];

int main()
{
	scanf("%d%s",&n,s);
	l=strlen(s);
	for(i=1;i<n;i++) scanf("%s",t[i]);
	for(i=1;i<n;i++)
	{
		for(j=0;j<l;j++)
			if(s[j]!=t[i][j]) a[i]++;
	}
	for(i=1;i<n;i++)
	{
		for(p=1;p<n;p++)
			if(!v[p]) break;
		for(j=p+1;j<n;j++)
			if(!v[j])
			{
				if(a[j]>a[p]) p=j;
				else if(a[j]==a[p])
				{
					int ok=0,k;
					for(k=0;k<l;k++)
					{
						if(t[j][k]==t[p][k]) continue;
						if(t[j][k]<t[p][k]) ok=1;
						break;
					}
					if(ok) p=j;
				}
			}
		printf("%s %s %d\n",s,t[p],a[p]);
		v[p]=1;
	}
	return 0;
}
