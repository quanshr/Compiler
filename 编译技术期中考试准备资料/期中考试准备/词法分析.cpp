#include <bits/stdc++.h>
using namespace std;

FILE *fp;
char s[10000010];
int n,i;
string sym,str;
map<string,string> mp;

void init()
{
	fp=fopen("testfile.txt","r");
	freopen("output.txt","w",stdout);
	n=fread(s,1,10000000,fp);
	mp["main"]="MAINTK";
	mp["const"]="CONSTTK";
	mp["int"]="INTTK";
	mp["break"]="BREAKTK";
	mp["continue"]="CONTINUETK";
	mp["if"]="IFTK";
	mp["else"]="ELSETK";
	mp["while"]="WHILETK";
	mp["getint"]="GETINTTK";
	mp["printf"]="PRINTFTK";
	mp["return"]="RETURNTK";
	mp["void"]="VOIDTK";
	
	mp["!"]="NOT";
	mp["&&"]="AND";
	mp["||"]="OR";
	mp["+"]="PLUS";
	mp["-"]="MINU";
	mp["*"]="MULT";
	mp["/"]="DIV";
	mp["%"]="MOD";
	mp["<"]="LSS";
	mp["<="]="LEQ";
	mp[">"]="GRE";
	mp[">="]="GEQ";
	mp["=="]="EQL";
	mp["!="]="NEQ";
	mp["="]="ASSIGN";
	mp[";"]="SEMICN";
	mp[","]="COMMA";
	mp["("]="LPARENT";
	mp[")"]="RPARENT";
	mp["["]="LBRACK";
	mp["]"]="RBRACK";
	mp["{"]="LBRACE";
	mp["}"]="RBRACE";

}

int bian(char c)
{
	return c==' '||c=='\n'||c=='\t'||c=='\r'||c=='\0';
}
int isnum(char c)
{
	return c>='0'&&c<='9';
}
int isletter(char c)
{
	return c>='a'&&c<='z'||c>='A'&&c<='Z';
}

void getsym()
{
	while(i<=n&&bian(s[i])) i++;
	if(i>n)
	{
		sym=str="END";
		return;	
	}
	if(s[i]=='/'&&s[i+1]=='/')
	{
		while(s[i]!='\n') i++;
		getsym();
		return;
	}
	if(s[i]=='/'&&s[i+1]=='*')
	{
		i+=4;
		while(s[i-2]!='*'||s[i-1]!='/') i++;
		getsym();
		return;
	}
	sym=str="";	
	if(isnum(s[i]))
	{
		while(isnum(s[i])) str+=s[i++];
		sym="INTCON";
		return;
	}
	if(isletter(s[i])||s[i]=='_')
	{
		while(isletter(s[i])||s[i]=='_'||isnum(s[i])) str+=s[i++];
		if(mp[str]!="") sym=mp[str];
		else sym="IDENFR";
		return;
	}
	if(s[i]=='"')
	{
		str+=s[i++];
		do
		{
			str+=s[i++];
		}while(s[i-1]!='"');
		sym="STRCON";
		return;
	}
	str+=s[i++];
	if(mp[str+s[i]]!="")
	{
		str+=s[i++];
		sym=mp[str];
	}
	else sym=mp[str];
}

void solve()
{
	i=0;
	while(1)
	{
		getsym();
		if(sym=="END") break;
		cout<<sym<<' '<<str<<endl;
	}
}

int main()
{
	init();
	solve();
	return 0;
}
