#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n,m,i,j,st[100010],p,op[100010],pos[100010],len[100010];
char s[100010],c[1010][1010];

int main()
{
	gets(s);
	m=strlen(s);
	scanf("%d",&n);
	while(1)/**/
	{
		i++;
		scanf("%d",&op[i]);
		if(op[i]==-1) break;
		if(i<=n)
		{
			if(op[i]==3) p--;
			else
			{
				scanf("%d%s",&pos[i],c[i]);
				st[++p]=i;
				len[i]=strlen(c[i]);
			}
		}
		else
		{
			if(op[i]==3)
			{
				if(!p) continue;
				int x=st[p--];
				if(op[x]==1)
				{
					int i=x;
					for(j=pos[i];j<=pos[i]+len[i]-1;j++) c[i][j-pos[i]]=s[j];
					for(j=pos[i]+len[i];j<m;j++) s[j-len[i]]=s[j];
					m-=len[i];				
				}
				else
				{
					int i=x;
					for(j=m-1;j>=pos[i];j--) s[j+len[i]]=s[j];
					for(j=pos[i];j<=pos[i]+len[i]-1;j++) s[j]=c[i][j-pos[i]];
					m+=len[i];					
				}
			}
			else if(op[i]==1)
			{
				scanf("%d%s",&pos[i],c[i]);
				//printf("  %d %d %c\n",m,pos[i],c[i][0]);
				st[++p]=i;
				len[i]=strlen(c[i]);
				for(j=m-1;j>=pos[i];j--) s[j+len[i]]=s[j];
				for(j=pos[i];j<=pos[i]+len[i]-1;j++) s[j]=c[i][j-pos[i]];
				m+=len[i];
			}
			else
			{
				scanf("%d%d",&pos[i],&len[i]);
				if(m-pos[i]<len[i]) len[i]=m-pos[i];
				st[++p]=i;
				for(j=pos[i];j<=pos[i]+len[i]-1;j++) c[i][j-pos[i]]=s[j];
				for(j=pos[i]+len[i];j<m;j++) s[j-len[i]]=s[j];
				m-=len[i];
			}
		}
		//for(j=0;j<m;j++) printf("%c",s[j]);
		//printf("%d end\n",i);
	}
	for(j=0;j<m;j++) printf("%c",s[j]);
	return 0;
}

