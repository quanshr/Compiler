#include <bits/stdc++.h>
using namespace std;

char s[10010];
int i=0;
string op()
{
	string t="";
	while(s[i]==' '||s[i]=='\t') i++;
	while(s[i]!=' '&&s[i]!='\t'&&s[i]!='\n') t=t+s[i],i++;
	t=t+'\0';
	return t;
}
void prt(string c)
{
	for(int i=0;c[i]!='\0';i++)
		putchar(c[i]);	
}

int main()
{
	freopen("re.txt","r",stdin);
	freopen("use.txt","w",stdout);
	//printf("begin");
	while(gets(s))
	{
		int n=strlen(s);
		//printf("%d",n);
		//if(n<=1) break;
		for(i=0;i<n;)
		{
			string a=op();
			string b=op();
			//prt(a);
			printf("mp[\"");
			prt(a);
			printf("\"]=\"");
			prt(b);
			printf("\";\n");
			//printf("mp[\" %s \"]=%s;\n",a,b);
		}
	}
	return 0;
}
