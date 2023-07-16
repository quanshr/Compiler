#include <bits/stdc++.h>
using namespace std;

int n; //读入字符串总长 
int i; //词法分析过程循环变量 
char s[50000010]; //读入的所有字符 
map<string,string> mp; //词法的对应
string sym,str; //当前读入的符号（词法）,具体字符串 
void init()
{
	FILE *fp=fopen("testfile.txt","r");
	freopen("output.txt","w",stdout);
	n=fread(s,1,50000000,fp);
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

//以上是词法分析部分 




void getsym(string t)   //grammer_print and getsym 语法分析作业的输出并读入下一个字符 
{
	getsym();
}
string nextsym(int k)
{
	int _j=i;
	string _sym=sym,_str=str;
	while(k--) getsym();
	i=_j;
	string res=str;
	sym=_sym; str=_str;
	return res;
}
void CompUnit();
int Decl();
int ConstDecl();
void BType();
void ConstDef();
void ConstInitVal();
int VarDecl();
void VarDef();
void InitVal();
int FuncDef();
void MainFuncDef();
void FuncType();
void FuncFParams();
void FuncFParam();
void Block();
void BlockItem();
void Stmt();
void Exp();
void Cond();
void LVal();
void PrimaryExp();
void Number();
void UnaryExp();
int UnaryOp();
void FuncRParams();
void MulExp();
void AddExp();
void RelExp();
void EqExp();
void LAndExp();
void LOrExp();
void ConstExp();

int Ident();
void IntConst();


//CompUnit → {Decl} {FuncDef} MainFuncDef
void CompUnit()
{
	while(sym=="const"||nextsym(2)!="(") Decl();
	while(nextsym(1)!="main") FuncDef();
	MainFuncDef();
} 
//Decl → ConstDecl | VarDecl
int Decl()
{
	if(!ConstDecl()&&!VarDecl())
		return 0;
	return 1;
}
//ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';'
int ConstDecl()
{
	if(str!="const") return 0;
	getsym();  //const
	BType();
	ConstDef();
	while(str==",")
	{
		getsym();  // ,
		ConstDef();
	}
	getsym();   // ;
	return 1;
}
//BType → 'int' 
void BType()
{
	getsym(); // int
}
//ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
void ConstDef()
{
	Ident();
	while(str=="[")
	{
		getsym();   // [
		ConstExp();
		getsym();  // ]
	}
	getsym();   // =
	ConstInitVal();
	printf("<ConstDef>\n");
}
// ConstInitVal → ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
void ConstInitVal()
{
	if(str!="{") ConstExp();
	else
	{
		getsym(); // {
		if(str!="}")
		{
			ConstInitVal();
			while(str==",")
			{
				getsym();  // ,
				ConstInitVal();
			}
		}
		getsym();  // }
	}
}
//VarDecl → BType VarDef { ',' VarDef } ';' 
int VarDecl()
{
	if(str!="int") return 0;
	BType();
	VarDef();
	while(str==",")
	{
		getsym(); // ,
		VarDef();
	}
	getsym();  // ;
	return 1;
}
//VarDef → Ident { '[' ConstExp ']' } | Ident { '[' ConstExp ']' } '=' InitVal
void VarDef()
{
	Ident();
	while(str=="[")
	{
		getsym();  // [
		ConstExp();
		getsym();  // ]
	}
	if(str=="=")
	{
		getsym();  // =
		InitVal();
	}
}
//InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'
void InitVal()
{
	if(str!="{") Exp();
	else
	{
		getsym(); // {
		if(str!="}")
		{
			InitVal();
			while(str==",")
			{
				getsym();  // ,
				InitVal();
			}
		}
		getsym();  // }
	}
}
//FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
int FuncDef()
{
	if(str!="void"&&str!="int") return 0;
	FuncType();
	Ident();
	getsym();  // (
	if(str!=")") FuncFParams();
	getsym(); // )
	Block();
	return 1;
}
//MainFuncDef → 'int' 'main' '(' ')' Block
void MainFuncDef()
{
	getsym();  // int
	getsym();  // main
	getsym();  // (
	getsym();  // )
	Block();
}
//FuncType → 'void' | 'int'
void FuncType()
{
	getsym();  // void or int
}
//FuncFParams → FuncFParam { ',' FuncFParam }
void FuncFParams()
{
	FuncFParam();
	while(str==",")
	{
		getsym();  // ,
		FuncFParam();
	}
}
//FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]
void FuncFParam()
{
	BType();
	Ident();
	if(str=="[")
	{
		getsym();  // [
		getsym();  // ]
		while(str=="[")
		{
			getsym(); // [
			ConstExp(); 
			getsym();  // ]
		}
	}
}
//Block → '{' { BlockItem } '}'
void Block()
{
	getsym();  // {
	while(str!="}") BlockItem();
	getsym();  // }
}
//BlockItem → Decl | Stmt
void BlockItem()
{
	if(!Decl()) Stmt();
	//printf("<BlockItem>\n");
}
//	Stmt → LVal '=' Exp ';' // 每种类型的语句都要覆盖
//	| [Exp] ';' //有无Exp两种情况
//	| Block
//	| 'if' '(' Cond ')' Stmt [ 'else' Stmt ] // 1.有else 2.无else
//	| 'while' '(' Cond ')' Stmt
//	| 'break' ';' | 'continue' ';'
//	| 'return' [Exp] ';' // 1.有Exp 2.无Exp
//	| LVal '=' 'getint''('')'';'
//	| 'printf''('FormatString{','Exp}')'';'
void Stmt()
{
	if(str=="if")
	{
		getsym("if");
		getsym("(");
		Cond();
		getsym(")");
		Stmt();
		if(str=="else")
		{
			getsym("else");
			Stmt();
		}
	}
	else if(str=="while")
	{
		getsym("while");
		getsym("(");
		Cond();
		getsym(")");
		Stmt();
	}
	else if(str=="break"||str=="continue")
	{
		getsym();
		getsym(";");
	}
	else if(str=="return")
	{
		getsym("return");
		if(str!=";") Exp();
		getsym(";");
	}
	else if(str=="printf")
	{
		getsym("printf");
		getsym("(");
		getsym("FormatiString");
		while(str==",")
		{
			getsym(",");
			Exp();	
		}
		getsym(")");
		getsym(";");
	}
	else if(str=="{") Block();
	else if(str==";") getsym(";");
	else
	{
		int j=0;
		while(nextsym(j)!="="&&nextsym(j)!=";") j++;
		if(nextsym(j)=="=")
		{
			LVal();
			getsym("=");
			if(str=="getint")
			{
				getsym("getint");
				getsym("(");
				getsym(")");
				getsym(";");
			}
			else
			{
				Exp();
				getsym(";");
			}
		}
		else
		{
			Exp();
			getsym(";");
		}
	}
}

//Exp → AddExp
void Exp()
{
	AddExp();
}
//Cond → LOrExp
void Cond()
{
	LOrExp();
}
//LVal → Ident {'[' Exp ']'}
void LVal()
{
	Ident();
	while(str=="[")
	{
		getsym("[");
		Exp();
		getsym("]");
	}
}
//PrimaryExp → '(' Exp ')' | LVal | Number 
void PrimaryExp()
{
	if(str=="(")
	{
		getsym("(");
		Exp();
		getsym(")");
	}
	else if(str[0]>='0'&&str[0]<='9') Number();
	else LVal();
}
//Number → IntConst
void Number()
{
	IntConst();
}
//UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
void UnaryExp()
{
	if(UnaryOp()) UnaryExp();
	else if(sym=="IDENFR"&&nextsym(1)=="(")
	{
		getsym(); // Ident
		getsym(); // (
		if(str!=")") FuncRParams();
		getsym(); // )
	}
	else PrimaryExp();
}
//UnaryOp → '+' | '-' | '!'
int UnaryOp()
{
	if(str=="+"||str=="-"||str=="!")
	{
		getsym();  // + - !
		return 1;
	}
	return 0;
}
//FuncRParams → Exp { ',' Exp }
void FuncRParams()
{
	Exp();
	while(str==",")
	{
		getsym(",");
		Exp();
	}
}
//MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
void MulExp()
{
	UnaryExp();
	while(str=="*"||str=="/"||str=="%")
	{		
		getsym();  // * / %
		UnaryExp();
	}
}
//AddExp → MulExp | AddExp ('+' | '-') MulExp
void AddExp()
{
	MulExp();
	while(str=="+"||str=="-")
	{
		getsym();  // + -
		MulExp();
	}
}
//RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
void RelExp()
{
	AddExp();
	while(str=="<"||str==">"||str=="<="||str==">=")
	{ 
		getsym();   //  <  >  <=  =>
		AddExp();
	}
}
//EqExp → RelExp | EqExp ('==' | '!=') RelExp
void EqExp()
{
	RelExp();
	while(str=="=="||str=="!=")
	{
		getsym();  // == !=
		RelExp();
	}
}
//LAndExp → EqExp | LAndExp '&&' EqExp 
void LAndExp()
{
	EqExp();
	while(str=="&&")
	{
		getsym();  // &&
		EqExp();
	}
}
//LOrExp → LAndExp | LOrExp '||' LAndExp
void LOrExp()
{
	LAndExp();
	while(str=="||")
	{
		getsym(); // ||
		LAndExp();
	}
}
//ConstExp → AddExp
void ConstExp()
{
	AddExp();
}
int nondigit(char c)
{
	return c>='a'&&c<='z'||c>='A'&&c<='Z'||c=='_';
}
int Ident()
{
	if(!nondigit(str[0])) return 0;
	getsym();
	return 1;
}
void IntConst()
{
	getsym();
}

int main()
{
	init();
	getsym();
	CompUnit();
	return 0;
} 
