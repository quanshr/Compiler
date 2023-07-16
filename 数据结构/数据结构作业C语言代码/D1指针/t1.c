#include <stdio.h>
#include <string.h>

int n;
char s[100010];

int main()
{
	s[0]='-';
	scanf("%s",s+1);
	n=strlen(s+1);
	int i,j;
	for(i=1;i<=n;i++)
	{
		if(s[i]!='-') printf("%c",s[i]);
		else
		{
			if(s[i-1]+1<s[i+1])
			{
				if(s[i-1]>='a'&&s[i-1]<='z'&&s[i+1]>='a'&&s[i+1]<='z'
				 ||s[i-1]>='A'&&s[i-1]<='Z'&&s[i+1]>='A'&&s[i+1]<='Z'
			     ||s[i-1]>='0'&&s[i-1]<='9'&&s[i+1]>='0'&&s[i+1]<='9')
					for(j=s[i-1]+1;j!=s[i+1];j++) printf("%c",j);
				else printf("%c",s[i]);
			}
			else printf("%c",s[i]);
		}
	}
	return 0;
}



