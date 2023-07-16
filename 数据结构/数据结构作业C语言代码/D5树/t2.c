#include <stdio.h>
#include <stdlib.h>

int n,i,j,cnt,p;
char s[10010];
struct
{
	int l,r,x;
	char c[12];
}e[100010];
int pt;
int cmp(int a,int b)
{
	int p1=0;
	while(e[a].c[p1]==e[b].c[p1])
	{
		if(e[a].c[p1]=='\0') return 0;
		p1++;
	}
	if(e[a].c[p1]<e[b].c[p1]) return -1;
	return 1;
}
void dfs(int p)
{
	if(e[p].l) dfs(e[p].l);
	if(p!=1) printf("%s %d\n",e[p].c,e[p].x);
	if(e[p].r) dfs(e[p].r);
}

int main()
{
	freopen("article.txt","r",stdin);
	e[++cnt].c[0]='\0';
	while(scanf("%s",s)!=EOF)
	{
		n=strlen(s);
		//if(n==0||s[0]=='\n') break;
		//printf("%s\n",s);
		for(i=0;i<n;i++) if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
		i=0;
		while(i<n)
		{
			while(i<n&&s[i]<'a'||s[i]>'z') i++;
			pt=0;
			while(i<n&&s[i]>='a'&&s[i]<='z')
				e[100000].c[pt++]=s[i++];
			e[100000].c[pt]='\0';
			//printf("%s\n",e[100000]);
			p=1;
			while(cmp(100000,p)!=0)
			{
				if(cmp(100000,p)==-1)
				{
					if(!e[p].l)
					{
						e[p].l=++cnt;
						for(j=0;j<12;j++) e[cnt].c[j]=e[100000].c[j];
					}
					p=e[p].l;
				}
				else
				{
					if(!e[p].r)
					{
						e[p].r=++cnt;
						for(j=0;j<12;j++) e[cnt].c[j]=e[100000].c[j];
					}
					p=e[p].r;
				}
			}
			e[p].x++;
		}
	}
	printf("%s",e[2].c);
	if(e[2].r) printf(" %s",e[e[2].r].c);
	if(e[e[2].r].r) printf(" %s",e[e[e[2].r].r].c);
	printf("\n");
	dfs(1);
	return 0;
}
