#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n,m,g;
char s[2000010],t[2000010],ch,p[2000010];
int i,j;

int main()
{
	scanf("%s\n%s",s,t);
	n=strlen(s); m=strlen(t);
	//printf("%d %d \n",n,m);
	for(i=0;i<n;i++)
		if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
	freopen("filein.txt","r",stdin);
	freopen("fileout.txt","w",stdout);
	while(1)
	{
		ch=getchar();
		if(ch==EOF) break;
		p[++g]=ch;
		//printf("%c",ch);
	}
	for(i=1;i<=g;i++)
	{
		if(i+n>g)
		{
			printf("%c",p[i]);
			continue;
		}
		for(j=0;j<n;j++)
			if(p[i+j]>='A'&&p[i+j]<='Z'&&p[i+j]-'A'+'a'!=s[j]
			 ||p[i+j]>='a'&&p[i+j]<='z'&&p[i+j]!=s[j]
			 ||(p[i+j]<'A'||p[i+j]>'Z')&&(p[i+j]<'a'||p[i+j]>'z'))
			{
				printf("%c",p[i]);
				goto aaa;
			}
		i=i+n-1;
		//printf("%d\n\n",i);
		for(j=0;j<m;j++) printf("%c",t[j]);
		aaa:;
	}
	return 0;
}
