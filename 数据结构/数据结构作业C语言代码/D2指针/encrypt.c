#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n,m,v[200],f[200];
char s[20010],t[2000010];
int i,j;

int main()
{
	scanf("%s\n",s+1);
	n=strlen(s+1);
	m=0;
	for(i=1;i<=n;i++)
	{
		if(v[s[i]-'a']) continue;
		v[s[i]-'a']=1;
		f[m++]=s[i]-'a';
	}
	int k=25;
	while(m<26)
	{
		while(v[k]) k--;
		v[k]=1;
		f[m++]=k;
	}
	//for(i=0;i<26;i++) printf("%c",f[i]+'a');
	freopen("encrypt.txt","r",stdin);
	freopen("output.txt","w",stdout);
	gets(t+1);
	n=strlen(t+1);
	for(i=1;i<=n;i++)
	{
		if(t[i]>='a'&&t[i]<='z')
			printf("%c",f[t[i]-'a']+'a');
		else printf("%c",t[i]);
	}
	return 0;
}
