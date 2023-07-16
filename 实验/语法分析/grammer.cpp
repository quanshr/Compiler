#include <bits/stdc++.h>
using namespace std;

int n; //读入字符串总长 
int _i; //词法分析过程循环变量 
char s[50000010]; //读入的所有字符 
map<string,string> mp; //词法的对应
string sym,str; //当前读入的符号（词法）,具体字符串 

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
		sym=mp[t];
		str=t;
		return 1;
	}
	return 0;
}
int isletter(char c)
{
	return c>='a'&&c<='z'||c>='A'&&c<='Z'||c=='_'
		||c>='0'&&c<='9';
}
void opt()		//词法分析 
{
	string t="";
	t=t+s[_i];
	if(!bian(s[_i+1]))
	{
		string tt=t+s[_i+1];
		if(tt!="if"&&prt(tt))
		{
			_i+=2;
			return;
		}
	}
	if(prt(t))
	{
		_i++;
		return;
	}
	if(s[_i]=='"')
	{
		do
		{
			t=t+s[++_i];
		}while(s[_i]!='"');
		_i++;
		sym="STRCON";
		str=t;
		return;
	}
	if(s[_i]>='0'&&s[_i]<='9')
	{
		_i++;
		while(s[_i]>='0'&&s[_i]<='9')
		{
			t=t+s[_i];
			_i++;
		}
		sym="INTCON";
		str=t;
		return;
	}
	_i++;
	while(isletter(s[_i]))
	{
		t=t+s[_i];
		_i++;
	}
	if(prt(t)) return;
	sym="IDENFR";
	str=t;
	return;
}
void init()
{
	FILE *fp=fopen("testfile.txt","r");
	n=fread(s,1,50000000,fp);
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
}

void getsym()
{
	while(_i<n&&bian(s[_i])) _i++;
	if(_i>=n)
	{
		sym="END";
		return;
	}
	if(s[_i]=='/'&&s[_i+1]=='*')
	{
		_i+=3;
		while(s[_i-1]!='*'||s[_i]!='/') _i++;
		_i++;
		getsym();
		return;
	}
	if(s[_i]=='/'&&s[_i+1]=='/')
	{
		while(s[_i]!='\n') _i++;
		_i++;
		getsym();
		return;
	}
	opt();
}

//以上是词法分析部分 




void gptget()   //grammer_print and getsym 语法分析作业的输出并读入下一个字符 
{
	pt(sym);
	putchar(' ');
	pt(str);
	putchar('\n');
	getsym();
}
void gptget(string t)   //grammer_print and getsym 语法分析作业的输出并读入下一个字符 
{
	pt(sym);
	putchar(' ');
	pt(str);
	putchar('\n');
	getsym();
}
string nextsym(int k)
{
	int _j=_i;
	string _sym=sym,_str=str;
	while(k--) getsym();
	_i=_j;
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
	printf("<CompUnit>\n");
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
	gptget();  //const
	BType();
	ConstDef();
	while(str==",")
	{
		gptget();  // ,
		ConstDef();
	}
	gptget();   // ;
	printf("<ConstDecl>\n");
	return 1;
}
//BType → 'int' 
void BType()
{
	gptget(); // int
	//printf("<BType>\n");
}
//ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
void ConstDef()
{
	Ident();
	while(str=="[")
	{
		gptget();   // [
		ConstExp();
		gptget();  // ]
	}
	gptget();   // =
	ConstInitVal();
	printf("<ConstDef>\n");
}
// ConstInitVal → ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
void ConstInitVal()
{
	if(str!="{") ConstExp();
	else
	{
		gptget(); // {
		if(str!="}")
		{
			ConstInitVal();
			while(str==",")
			{
				gptget();  // ,
				ConstInitVal();
			}
		}
		gptget();  // }
	}
	printf("<ConstInitVal>\n");
}
//VarDecl → BType VarDef { ',' VarDef } ';' 
int VarDecl()
{
	if(str!="int") return 0;
	BType();
	VarDef();
	while(str==",")
	{
		gptget(); // ,
		VarDef();
	}
	gptget();  // ;
	printf("<VarDecl>\n");
	return 1;
}
//VarDef → Ident { '[' ConstExp ']' } | Ident { '[' ConstExp ']' } '=' InitVal
void VarDef()
{
	Ident();
	while(str=="[")
	{
		gptget();  // [
		ConstExp();
		gptget();  // ]
	}
	if(str=="=")
	{
		gptget();  // =
		InitVal();
	}
	printf("<VarDef>\n");
}
//InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'
void InitVal()
{
	if(str!="{") Exp();
	else
	{
		gptget(); // {
		if(str!="}")
		{
			InitVal();
			while(str==",")
			{
				gptget();  // ,
				InitVal();
			}
		}
		gptget();  // }
	}
	printf("<InitVal>\n");
}
//FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
int FuncDef()
{
	if(str!="void"&&str!="int") return 0;
	FuncType();
	Ident();
	gptget();  // (
	if(str!=")") FuncFParams();
	gptget(); // )
	Block();
	printf("<FuncDef>\n");
	return 1;
}
//MainFuncDef → 'int' 'main' '(' ')' Block
void MainFuncDef()
{
	gptget();  // int
	gptget();  // main
	gptget();  // (
	gptget();  // )
	Block();
	printf("<MainFuncDef>\n");
}
//FuncType → 'void' | 'int'
void FuncType()
{
	gptget();  // void or int
	printf("<FuncType>\n");
}
//FuncFParams → FuncFParam { ',' FuncFParam }
void FuncFParams()
{
	FuncFParam();
	while(str==",")
	{
		gptget();  // ,
		FuncFParam();
	}
	printf("<FuncFParams>\n");
}
//FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]
void FuncFParam()
{
	BType();
	Ident();
	if(str=="[")
	{
		gptget();  // [
		gptget();  // ]
		while(str=="[")
		{
			gptget(); // [
			ConstExp(); 
			gptget();  // ]
		}
	}
	printf("<FuncFParam>\n");
}
//Block → '{' { BlockItem } '}'
void Block()
{
	gptget();  // {
	while(str!="}") BlockItem();
	gptget();  // }
	printf("<Block>\n");
}
//BlockItem → Decl | Stmt
void BlockItem()
{
	if(!Decl()) Stmt();
	//printf("<BlockItem>\n");
}
//Stmt → LVal '=' Exp ';' // 每种类型的语句都要覆盖
//| [Exp] ';' //有无Exp两种情况
//| Block
//| 'if' '(' Cond ')' Stmt [ 'else' Stmt ] // 1.有else 2.无else
//| 'while' '(' Cond ')' Stmt
//| 'break' ';' | 'continue' ';'
//| 'return' [Exp] ';' // 1.有Exp 2.无Exp
//| LVal '=' 'getint''('')'';'
//| 'printf''('FormatString{','Exp}')'';'
void Stmt()
{
	if(str=="printf")  //Stmt →'printf''('FormatString{','Exp}')'';' 
	{
		gptget();   //printf
		gptget();   // (
		gptget();   // formatstring
		while(str==",")
		{
			gptget(); // ,
			Exp();
		}
		gptget();  // )
		gptget();  // ;
	}
	else if(str=="return") //Stmt →'return' [Exp] ';' 
	{
		gptget();   //return
		if(str!=";") Exp();
		gptget();  // ;
	}
	else if(str=="break"||str=="continue")
	{
		gptget();  // break or continue;
		gptget();  // ;
	}
	else if(str=="while") 	//Stmt →'while' '(' Cond ')' Stmt
	{
		gptget();  // while
		gptget();  // (
		Cond();
		gptget(); // )
		Stmt();
	}
	else if(str=="if") //Stmt →'if' '(' Cond ')' Stmt [ 'else' Stmt ] 
	{
		gptget();  //if
		gptget();  // (
		Cond();
		gptget();  // )
		Stmt();
		if(str=="else")
		{
			gptget();  //else
			Stmt();
		}
	}
	else if(str=="{") Block();
	else if(str==";") gptget();
	else
	{
		int _j=1;
		while(nextsym(_j)!=";"&&nextsym(_j)!="=") _j++;
		if(nextsym(_j)=="=")
		{
			LVal();
			gptget();  // =
			
			if(str=="getint")
			{
				gptget();  // getint
				gptget();  // (
				gptget();  // )
				gptget();  // ;
			}
			else
			{
				Exp();
				gptget();  // ;
			}
		}
		else
		{
			Exp();
			gptget();  // ;
		}
	}
	printf("<Stmt>\n");
}

//Exp → AddExp
void Exp()
{
	AddExp();
	printf("<Exp>\n");
}
//Cond → LOrExp
void Cond()
{
	LOrExp();
	printf("<Cond>\n");
}
//LVal → Ident {'[' Exp ']'}
void LVal()
{
	Ident();
	while(str=="[")
	{
		gptget("[");
		Exp();
		gptget("]");
	}
	printf("<LVal>\n");
}
//PrimaryExp → '(' Exp ')' | LVal | Number 
void PrimaryExp()
{
	if(str=="(")
	{
		gptget("(");
		Exp();
		gptget(")");
	}
	else if(str[0]>='0'&&str[0]<='9') Number();
	else LVal();
	printf("<PrimaryExp>\n");
}
//Number → IntConst
void Number()
{
	IntConst();
	printf("<Number>\n");
}
//UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
void UnaryExp()
{
	if(UnaryOp()) UnaryExp();
	else if(sym=="IDENFR"&&nextsym(1)=="(")
	{
		gptget(); // Ident
		gptget(); // (
		if(str!=")") FuncRParams();
		gptget(); // )
	}
	else PrimaryExp();
	printf("<UnaryExp>\n");
}
//UnaryOp → '+' | '-' | '!'
int UnaryOp()
{
	if(str=="+"||str=="-"||str=="!")
	{
		gptget();  // + - !
		printf("<UnaryOp>\n");
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
		gptget(",");
		Exp();
	}
	printf("<FuncRParams>\n");
}
//MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
void MulExp()
{
	UnaryExp();
	while(str=="*"||str=="/"||str=="%")
	{
		printf("<MulExp>\n");		
		gptget();  // * / %
		UnaryExp();
	}
	printf("<MulExp>\n");
}
//AddExp → MulExp | AddExp ('+' | '-') MulExp
void AddExp()
{
	MulExp();
	while(str=="+"||str=="-")
	{
		printf("<AddExp>\n");
		gptget();  // + -
		MulExp();
	}
	printf("<AddExp>\n");
}
//RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
void RelExp()
{
	AddExp();
	while(str=="<"||str==">"||str=="<="||str==">=")
	{
		printf("<RelExp>\n");
		gptget();   //  <  >  <=  =>
		AddExp();
	}
	printf("<RelExp>\n");
}
//EqExp → RelExp | EqExp ('==' | '!=') RelExp
void EqExp()
{
	RelExp();
	while(str=="=="||str=="!=")
	{
		printf("<EqExp>\n");
		gptget();  // == !=
		RelExp();
	}
	printf("<EqExp>\n");
}
//LAndExp → EqExp | LAndExp '&&' EqExp 
void LAndExp()
{
	EqExp();
	while(str=="&&")
	{
		printf("<LAndExp>\n");
		gptget();  // &&
		EqExp();
	}
	printf("<LAndExp>\n");
}
//LOrExp → LAndExp | LOrExp '||' LAndExp
void LOrExp()
{
	LAndExp();
	while(str=="||")
	{
		printf("<LOrExp>\n");
		gptget(); // ||
		LAndExp();
	}
	printf("<LOrExp>\n");
}
//ConstExp → AddExp
void ConstExp()
{
	AddExp();
	printf("<ConstExp>\n");
}
int nondigit(char c)
{
	return c>='a'&&c<='z'||c>='A'&&c<='Z'||c=='_';
}
int Ident()
{
	if(!nondigit(str[0])) return 0;
	//printf("Ident\n");
	gptget();
	return 1;
}
void IntConst()
{
	gptget();
	//printf("IntConst\n");
}

int main()
{
	init();
	getsym();
	CompUnit();
	return 0;
} 
