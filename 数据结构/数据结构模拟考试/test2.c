#include <stdio.h>
#include <stdlib.h>

char s[1000010],t[1000010];
int len,n,m,i,j,k,left,tlen;

int main()
{
	gets(s);
	len=strlen(s);
	left=1;
	i=0;
	while(i<len)
	{
		if(s[i]=='-') left=0;
		i++;
	}
	i=0;
	while(i<len&&s[i]!='[') i++;
	while(i<len&&s[i]!=']')
	{
		if(s[i]=='-') left=1;
		i++;
	}
	i=0;
	while(s[i]>'9'||s[i]<'0') i++;
	while(s[i]>='0'&&s[i]<='9')
	{
		m=m*10+s[i]-'0';
		i++;
	}
	while(s[i]>'9'||s[i]<'0') i++;
	while(s[i]>='0'&&s[i]<='9')
	{
		n=n*10+s[i]-'0';
		i++;
	}
	gets(t);
	tlen=strlen(t);
	//printf("%d %d\n",m,n);
	if(m<tlen)
	{
		tlen=m;
		t[tlen]='\0';
	}
	if(left)
	{
		printf("%s",t);
		for(i=tlen+1;i<=n;i++) printf("#");
	}
	else
	{
		for(i=tlen+1;i<=n;i++) printf("#");
		printf("%s",t);
	}
	return 0;
}
