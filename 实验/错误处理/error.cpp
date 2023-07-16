#include <bits/stdc++.h>
using namespace std;

int n; //读入字符串总长 
int _i; //词法分析过程循环变量 
char s[50000010]; //读入的所有字符 
map<string,string> mp; //词法的对应
string sym,str; //当前读入的符号（词法）,具体字符串 

string ftype="";
int havereturn;
int iswhile;

int error,_j,line=1;  //错误信息，上次处理到的位置 
int lstnon=1,_k;    //上个非终结符开始的位置，目前已经不需要 
map<string,int> funcnum;  //函数的参数个数 
map<string,unsigned long long> functyp;  //函数参数类型 
map<string,string> funcretyp;

int nw=0;   //当前目录
map<string,string> chtab[100010];
// "func int" "func void" "i0" "c0" "i1" "c1" "i2" "c2"
int dingyi; //是否处于定义阶段    //不再需要，直接在定义部分处理 

void getsym();
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
	freopen("error.txt","w",stdout);
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

int getlineth()
{
	while(_j<_i) line+=s[_j++]=='\n';
	error=0;
	return line;
}
int getlastline()
{
	//cout<<str<<endl;
	//cout<<_i<<"  "<<n<<"   ";
	int _j=_i,_k;
	_i=_k=0;
	while(_i<_j)
	{
		_k=_i;
		getsym();
	}
	//cout<<_k<<endl;
	int res=1;
	for(int i=0;i<_k;i++)
		if(s[i]=='\n') res++;
	_i=_j;
	//cout<<str<<endl;
	return res;
}
//每个语法成分压栈、弹栈   //不需要 
void getsym()
{
	while(_i<=n&&bian(s[_i])) _i++;
	if(_i>=n)
	{
		sym=str="END";
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
	/*
	pt(sym);
	putchar(' ');
	pt(str);
	putchar('\n');*/
	if(sym=="STRCON")
	{
		//cout<<str<<endl;
		for(int i=1,len=str.length();i<len-1;i++)
		{
			if(str[i]!=32&&str[i]!=33
			&&(str[i]<40||str[i]>126||str[i]==92&&str[i+1]!='n')&&
			!(str[i]=='%'&&str[i+1]=='d'))
				error=1;
		}
		if(error) printf("%d a\n",getlineth());
	}
	else if(str=="{") nw++;
	else if(str=="}") chtab[nw--].clear();
	getsym();
}
int getlastline();
void gptget(string t)   //grammer_print and getsym 语法分析作业的输出并读入下一个字符 
{
	/*
	pt(sym);
	putchar(' ');
	pt(str);
	putchar('\n');
	if(sym=="STRCON")
	{
		//cout<<str<<endl;
		for(int i=1,len=str.length();i<len-1;i++)
		{
			if(str[i]!=32&&str[i]!=33
			&&(str[i]<40||str[i]>126||str[i]==92&&str[i+1]!='n'))
				error=1;
		}
		if(error) printf("%d a\n",getlineth());
	}
	getsym();*/
	if(str!=t)
	{
		//cout<<str<<"         "<<t<<endl;
		if(t==";") printf("%d i\n",getlastline());
		else if(t==")") printf("%d j\n",getlastline());
		else if(t=="]") printf("%d k\n",getlastline());
		return;
	}
	gptget();
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
void FuncFParams(string name);
int FuncFParam();
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
void FuncRParams(int *a,unsigned long long *b);
void MulExp();
void AddExp();
void RelExp();
void EqExp();
void LAndExp();
void LOrExp();
void ConstExp();

int Ident();
void IntConst();

int isExp()
{
	return (str=="("||str=="+"||str=="-"||sym=="IDENFR"||sym=="INTCON");
}
void def(string name,string type)
{
	if(chtab[nw][name]!="") printf("%d b\n",getlineth());
	else chtab[nw][name]=type;
}

//CompUnit → {Decl} {FuncDef} MainFuncDef
void CompUnit()
{
	while(sym=="const"||nextsym(2)!="(") Decl();
	while(nextsym(1)!="main") FuncDef();
	MainFuncDef();
	//printf("<CompUnit>\n");
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
	gptget(";");   // ;
	//printf("<ConstDecl>\n");
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
	//Ident();
	string name=str;
	int dimen=0;
	gptget();
	while(str=="[")
	{
		dimen++;
		gptget();   // [
		ConstExp();
		gptget("]");  // ]
	}
	def(name,(dimen==0?"c0":dimen==1?"c1":"c2"));
	gptget();   // =
	ConstInitVal();
	//printf("<ConstDef>\n");
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
	//printf("<ConstInitVal>\n");
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
	gptget(";");  // ;
	//printf("<VarDecl>\n");
	return 1;
}
//VarDef → Ident { '[' ConstExp ']' } | Ident { '[' ConstExp ']' } '=' InitVal
void VarDef()
{
	//Ident();
	string name=str;
	int dimen=0;
	gptget();
	while(str=="[")
	{
		dimen++;
		gptget();  // [
		ConstExp();
		gptget("]");  // ]
	}
	def(name,dimen==0?"i0":dimen==1?"i1":"i2");
	if(str=="=")
	{
		gptget();  // =
		InitVal();
	}
	//printf("<VarDef>\n");
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
	//printf("<InitVal>\n");
}

//FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
int FuncDef()
{
	if(str!="void"&&str!="int") return 0;
	ftype=str;
	FuncType();
	string funcname=str;
	def(funcname,"func "+ftype);
	//chtab[nw][funcname]="func "+ftype;
	Ident();
	gptget();  // (
	if(str!=")"&&str!="{") FuncFParams(funcname);
	gptget(")"); // )
	Block();
	if(ftype=="int"&&havereturn==0) printf("%d g\n",getlastline());
	
	//printf("<FuncDef>\n");
	ftype="";
	return 1;
}
//MainFuncDef → 'int' 'main' '(' ')' Block
void MainFuncDef()
{
	gptget();  // int
	gptget();  // main
	def("main","func int");
	gptget();  // (
	gptget(")");  // )
	Block();
	if(havereturn==0) printf("%d g\n",getlastline());
	
	//printf("<MainFuncDef>\n");
}

//FuncType → 'void' | 'int'
void FuncType()
{
	gptget();  // void or int
	//printf("<FuncType>\n");
}
//FuncFParams → FuncFParam { ',' FuncFParam }
void FuncFParams(string name) 
{
	funcnum[name]++;
	//functyp[name]=functyp[name]*2+(str=="int");
	functyp[name]=functyp[name]*3+FuncFParam();
	while(str==",")
	{
		funcnum[name]++;
		gptget();  // ,
		functyp[name]=functyp[name]*3+FuncFParam();
	}
	//printf("<FuncFParams>\n");
}
//FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]
int FuncFParam()
{
	int res=0;
	BType();
	string name=str;
	Ident();
	if(str=="[")
	{
		res=1;
		gptget();  // [
		gptget("]");  // ]
		while(str=="[")
		{
			res=2;
			gptget(); // [
			ConstExp(); 
			gptget("]");  // ]
		}
	}
	nw++;
	def(name,res==0?"i0":res==1?"i1":"i2");
	nw--;
	return res;
	//printf("<FuncFParam>\n");
}
//Block → '{' { BlockItem } '}'
void Block()
{
	gptget();  // {
	while(str!="}") BlockItem();
	gptget();  // }
	//printf("<Block>\n");
}
//BlockItem → Decl | Stmt
void BlockItem()
{
	havereturn=0;
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
		int nwline=getlineth();
		gptget();   //printf
		gptget();   // (
		int num=0;
		for(int i=0;i<str.length()-1;i++)
			if(str[i]=='%'&&str[i+1]=='d') num++;
		gptget();   // formatstring
		while(str==",")
		{
			num--;
			gptget(); // ,
			Exp();
		}
		gptget(")");  // )
		gptget(";");  // ;
		if(num!=0) printf("%d l\n",nwline);
	}
	else if(str=="return") //Stmt →'return' [Exp] ';' 
	{
		havereturn=1;
		gptget();   //return
		/*
		if(str!=";")
		{
			if(ftype=="void")
			{
				printf("%d f\n",getlineth());
			}
			Exp();
		}
		gptget(";");  // ;
		*/
		if(isExp())
		{
			if(ftype=="void") printf("%d f\n",getlineth());
			Exp();
		}
		gptget(";");  //  ;
	}
	else if(str=="break"||str=="continue")
	{
		if(!iswhile) printf("%d m\n",getlineth());
		gptget();  // break or continue;
		gptget(";");  // ;
	}
	else if(str=="while") 	//Stmt →'while' '(' Cond ')' Stmt
	{
		iswhile++;
		gptget();  // while
		gptget();  // (
		Cond();
		gptget(")"); // )
		Stmt();
		iswhile--;
	}
	else if(str=="if") //Stmt →'if' '(' Cond ')' Stmt [ 'else' Stmt ] 
	{
		gptget();  //if
		gptget();  // (
		Cond();
		gptget(")");  // )
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
		while(nextsym(_j)!="END"&&nextsym(_j)!=";"&&nextsym(_j)!="=") _j++;
		if(nextsym(_j)=="=")
		{
			string name=str;
			LVal();
			for(int i=nw;i>=0;i--)
			{
				if(chtab[i][name]!="")
				{
					if(chtab[i][name][0]=='c')     //const
						printf("%d h\n",getlineth());
					break;
				}
			}
			gptget();  // =
			
			if(str=="getint")
			{
				gptget();  // getint
				gptget();  // (
				gptget(")");  // )
				gptget(";");  // ;
			}
			else
			{
				Exp();
				gptget(";");  // ;
			}
		}
		else
		{
			Exp();
			gptget(";");  // ;
		}
	}
	//printf("<Stmt>\n");
}

//Exp → AddExp
void Exp()
{
	AddExp();
	//printf("<Exp>\n");
}
//Cond → LOrExp
void Cond()
{
	LOrExp();
	//printf("<Cond>\n");
}
//LVal → Ident {'[' Exp ']'}
void LVal()
{
	string name=str;
	for(int i=nw;i>=0;i--)
	{
		if(chtab[i][name]!="") break;
		else if(i==0) printf("%d c\n",getlineth());
	}
	Ident();
	while(str=="[")
	{
		gptget("[");
		Exp();
		gptget("]");
	}
	//printf("<LVal>\n");
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
	//printf("<PrimaryExp>\n");
}
//Number → IntConst
void Number()
{
	IntConst();
	//printf("<Number>\n");
}
//UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
void UnaryExp()
{
	if(UnaryOp()) UnaryExp();
	else if(sym=="IDENFR"&&nextsym(1)=="(")
	{
		int nwline=getlineth(),num=0;
		unsigned long long typ=0;
		string funcname=str;
		if(chtab[0][funcname]=="") printf("%d c\n",getlineth());
		gptget(); // Ident
		gptget(); // (
		if(str!=")"&&str!=";") FuncRParams(&num,&typ);
		gptget(")"); // )
		if(funcnum[funcname]!=num) printf("%d d\n",nwline);
		else if(functyp[funcname]!=typ) printf("%d e\n",nwline);
		//if(funcnum[funcname]!=typ) cout<<typ<< "   "<<functyp[funcname]<<endl;
	}
	else PrimaryExp();
	//printf("<UnaryExp>\n");
}
//UnaryOp → '+' | '-' | '!'
int UnaryOp()
{
	if(str=="+"||str=="-"||str=="!")
	{
		gptget();  // + - !
		//printf("<UnaryOp>\n");
		return 1;
	}
	return 0;
}
void funcparam(int *num,unsigned long long *typ,int be,int en)
{
	//cout<<be<<"  "<<en<<endl;
	(*num)++;
	_i=0;
	while(_i<be) gptget();
	string name=str;
	
	if(Ident())
	{
		string ths="";
		for(int i=nw;i>=0;i--)
			if(chtab[i][name]!="")
			{
				ths=chtab[i][name];
				break;
			}
		if(ths=="func void") *typ=-1;
		else if(ths=="func int") *typ=*typ*3;
		else if(ths[1]=='0') *typ=*typ*3;
		else if(ths[1]=='1')
		{
			if(str=="[") *typ=*typ*3;
			else
			{
				if(ths[0]=='i') *typ=*typ*3+1;
				else *typ=-1521;
			}
		}
		else if(ths[1]=='2')
		{
			if(str!="[") 
			{
				if(ths[0]=='i') *typ=*typ*3+2;
				else *typ=-214;
			}
			else
			{
				int sum=0;
				do
				{
					if(str=="[") sum++;
					else if(str=="]") sum--;
					gptget();
				}while(sum&&_i<en);
				if(sum==0)
				{
					if(str!="[")
					{
						if(ths[0]=='i') *typ=*typ*3+1;
						else *typ=-22;
					}
					else *typ=*typ*3;
				}
			}
		}
	}
	else *typ=*typ*3;
	while(_i<en) gptget();
}
//FuncRParams → Exp { ',' Exp }
void FuncRParams(int *num,unsigned long long *typ)
{
	int be=_i;
	Exp();
	int en=_i;
	funcparam(num,typ,be,en);
	while(str==",")
	{
		gptget(",");
		int be=_i;
		Exp();
		int en=_i;
		funcparam(num,typ,be,en);
	}
	//cout<<"     "<<*num<<endl;
	//printf("<FuncRParams>\n");
}
//MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
void MulExp()
{
	UnaryExp();
	while(str=="*"||str=="/"||str=="%")
	{
		//printf("<MulExp>\n");		
		gptget();  // * / %
		UnaryExp();
	}
	//printf("<MulExp>\n");
}
//AddExp → MulExp | AddExp ('+' | '-') MulExp
void AddExp()
{
	MulExp();
	while(str=="+"||str=="-")
	{
		//printf("<AddExp>\n");
		gptget();  // + -
		MulExp();
	}
	//printf("<AddExp>\n");
}
//RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
void RelExp()
{
	AddExp();
	while(str=="<"||str==">"||str=="<="||str==">=")
	{
		//printf("<RelExp>\n");
		gptget();   //  <  >  <=  =>
		AddExp();
	}
	//printf("<RelExp>\n");
}
//EqExp → RelExp | EqExp ('==' | '!=') RelExp
void EqExp()
{
	RelExp();
	while(str=="=="||str=="!=")
	{
		//printf("<EqExp>\n");
		gptget();  // == !=
		RelExp();
	}
	//printf("<EqExp>\n");
}
//LAndExp → EqExp | LAndExp '&&' EqExp 
void LAndExp()
{
	EqExp();
	while(str=="&&")
	{
		//printf("<LAndExp>\n");
		gptget();  // &&
		EqExp();
	}
	//printf("<LAndExp>\n");
}
//LOrExp → LAndExp | LOrExp '||' LAndExp
void LOrExp()
{
	LAndExp();
	while(str=="||")
	{
		//printf("<LOrExp>\n");
		gptget(); // ||
		LAndExp();
	}
	//printf("<LOrExp>\n");
}
//ConstExp → AddExp
void ConstExp()
{
	AddExp();
	//printf("<ConstExp>\n");
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
