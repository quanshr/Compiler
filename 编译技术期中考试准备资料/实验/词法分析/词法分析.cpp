#include <bits/stdc++.h>
using namespace std;

char s[1000010];
map<string,string> mp;
int bian(char c)
{
	return c==' '||c=='\n'||c=='\t'||c=='\0'||c=='\r';
}
void pt(string t)
{
	for(int i=0;t[i]!='\0';i++)
		putchar(t[i]);
}
int prt(string t)
{
	if(mp[t]!="")
	{
		pt(mp[t]);
		putchar(' ');
		pt(t);
		putchar('\n');
		return 1;
	}
	return 0;
}
int i;
int isletter(char c)
{
	return c>='a'&&c<='z'||c>='A'&&c<='Z'||c=='_'
		||c>='0'&&c<='9';
}
void opt()
{
	while(bian(s[i]))
	{
		if(s[i]=='\0') return;
		i++;
	}
	string t="";
	t=t+s[i];
	if(!bian(s[i+1]))
	{
		string tt=t+s[i+1];
		if(tt!="if"&&prt(tt))
		{
			i+=2;
			return;
		}
	}
	if(prt(t))
	{
		i+=1;
		return;
	}
	if(s[i]=='"')
	{
		do
		{
			t=t+s[++i];
		}while(s[i]!='"');
		printf("STRCON ");
		pt(t);
		printf("\n");
		i+=1;
		return;
	}
	if(s[i]>='0'&&s[i]<='9')
	{
		i+=1;
		while(s[i]>='0'&&s[i]<='9')
		{
			t=t+s[i];
			i++;
		}
		printf("INTCON ");
		pt(t);
		printf("\n");
		return;
	}
	i+=1;
	while(isletter(s[i]))
	{
		t=t+s[i];
		i++;
	}
	if(prt(t)) return;
	printf("IDENFR ");
	pt(t);
	printf("\n");
	return;
}

int main()
{
	freopen("testfile.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	//mp["Ident"]="IDENFR";
	mp["!"]="NOT";
	mp["*"]="MULT";
	mp["="]="ASSIGN";
	//mp["IntConst"]="INTCON";
	mp["&&"]="AND";
	mp["/"]="DIV";
	mp[";"]="SEMICN";
	//mp["FormatString"]="STRCON";
	mp["||"]="OR";
	mp["%"]="MOD";
	mp[","]="COMMA";
	mp["main"]="MAINTK";
	mp["while"]="WHILETK";
	mp["<"]="LSS";
	mp["("]="LPARENT";
	mp["const"]="CONSTTK";
	mp["getint"]="GETINTTK";
	mp["<="]="LEQ";
	mp[")"]="RPARENT";
	mp["int"]="INTTK";
	mp["printf"]="PRINTFTK";
	mp[">"]="GRE";
	mp["["]="LBRACK";
	mp["break"]="BREAKTK";
	mp["return"]="RETURNTK";
	mp[">="]="GEQ";
	mp["]"]="RBRACK";
	mp["continue"]="CONTINUETK";
	mp["+"]="PLUS";
	mp["=="]="EQL";
	mp["{"]="LBRACE";
	mp["if"]="IFTK";
	mp["-"]="MINU";
	mp["!="]="NEQ";
	mp["}"]="RBRACE";
	mp["else"]="ELSETK";
	mp["void"]="VOIDTK";
	
	int m=0;
	while(gets(s))
	{
		int n=strlen(s);
		for(i=0;i<n;)
		{
			while(i<n&&bian(s[i])) i++;
			if(i>=n) break;
			if(m==1)
			{
				if(s[i]=='*'&&s[i+1]=='/')
				{
					i+=2;
					m=0;
					continue;
				}
				i+=1;
				continue;
			}
			if(s[i]=='/'&&s[i+1]=='/') break;
			if(s[i]=='/'&&s[i+1]=='*')
			{
				i+=2;
				m=1;
				continue;
			}
			opt();
		}
	}
	return 0;
} 
