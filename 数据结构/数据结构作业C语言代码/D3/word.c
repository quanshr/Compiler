#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int n,i,j,k,t,p[100010],to[100010],sz[100010];
char s[100010];
struct Word
{
	int l;
	char c[100];
}word[100010];
int min(int a,int b) { return a<b?a:b; }
int cmp(struct Word a,struct Word b)
{
	int i=0;
	for(i=0;i<min(a.l,b.l);i++)
	{
		if(a.c[i]<b.c[i]) return -1;
		if(a.c[i]>b.c[i]) return 1;
	}
	if(a.l<b.l) return -1;
	if(a.l==b.l) return 0;
	return 1;
}

int main()
{
	FILE *in=fopen("article.txt","r");
	while(fgets(s,100000,in)!=NULL)
	{
		n=strlen(s);
		for(i=0;i<n;i++)
			if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
		for(i=0;i<n;i++)
		{
			if(s[i]>='a'&&s[i]<='z')
			{
				j=i;
				while(j+1<n&&s[j+1]>='a'&&s[j+1]<='z') j++;
				word[++t].l=j-i+1;
				for(k=i;k<=j;k++) word[t].c[k-i]=s[k];
				i=j;
			}
		}
	}
	/*for(i=1;i<=t;i++)
		if(1)
		{
			for(j=0;j<word[i].l;j++) printf("%c",word[i].c[j]);
			printf(" %d\n",sz[i]);
		}
	printf("\n\n");*/
	for(i=1;i<=t;i++) p[i]=i;
	for(i=1;i<=t;i++)
		for(j=i;j<=t;j++)
			if(cmp(word[p[i]],word[p[j]])==1)
			{
				k=p[i];
				p[i]=p[j];
				p[j]=k;
			}
	for(i=1;i<=t;i++)
		if(i!=1&&cmp(word[p[i]],word[p[i-1]])==0)
		{
			to[i]=to[i-1];
			sz[to[i]]++;
		}
		else
		{
			to[i]=i;
			sz[i]=1;
		}
	for(i=1;i<=t;i++)
		if(to[i]==i)
		{
			for(j=0;j<word[p[i]].l;j++) printf("%c",word[p[i]].c[j]);
			printf(" %d\n",sz[i]);
		}
	return 0;
}
