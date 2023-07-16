// created by quanshr

// Add the following commands when calling the compiler:
//-Wl,--stack=123456789
//Add the following commands when calling the linker:
//-static-libgcc -std=c++11


#include <bits/stdc++.h>
using namespace std;

int n; //读入字符串总长 
int i; //词法分析过程循环变量 
char s[50000010]; //读入的所有字符 
map<string,string> mp; //词法的对应
string sym,str; //当前读入的符号（词法）,具体字符串 

int data,base=500000,mxdata;    //主存地址,常量起始地址,全局变量最大使用地址（后面放参数） 
int constdata=base;
int constval[10000010];
int nw=0,var_cnt;   //当前目录,每个变量的唯一标识符编号 
int quanju;
struct VAR
{
	string type;   // const , int ,para ,tem
	int dim;      //维度 0，1，2 
	int base;      // 基地址 
	int second;   // 若为二维数组，记录第2维的大小
	int nw;
	int quanju;
	int begin,end,caninline;   //若为函数，开始和结束的中间代码，是否可以内联（当且仅当它没调用过自己） 
	int beginlabel,endlabel;   //内联函数所用的标签区间 
	int isconst,value;
	//string name;	
}var[1000010];
map<string,int> var_tab[100010];   //栈式符号表，对应VAR下标编号 
int mid_cnt;
struct MIDCODE
{
	string op;
	int z,x,y;   //操作数x,y,结果z 
	int del;
	int isconstx,isconsty;    //x,y是否为常数 
	int valuex,valuey;        //若为常数是多少 
}midcode[10000010];
int label_cnt;      //跳转标签 
string strtab[1000010]; //输出字符串 
int str_cnt;
int nowf;

int labelisfunc[100010];  //这个label是否为函数开始 

void init()
{
	FILE *fp=fopen("testfile.txt","r");
	freopen("mips.txt","w",stdout);
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
void Exp(int &b);
void Cond();
void LVal(int &b);
void PrimaryExp(int &b);
void Number(int &b);
void UnaryExp(int &b);
int UnaryOp();
void FuncRParams();
void MulExp(int &b);
void AddExp(int &b);
void RelExp();
void EqExp();
void LAndExp();
void LOrExp();
void ConstExp(int &b);

int Ident();
void IntConst(int &b);



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
void FuncRParams(int beginvar_cnt);
void Block(int begin_label,int end_label);
void BlockItem(int begin_label,int end_label);
void Stmt(int begin_label,int end_label);

void Exp(int tem,int _);
void ConstExp();
void AddExp(int a,int _);
void MulExp(int a,int _);
void UnaryExp(int a,int _);
int UnaryOp();
void PrimaryExp(int a,int _);
void LVal(int a,int _);
void Number(int a,int _);
void IntConst(int a,int _);

void Cond(int a,int if_label);
void LOrExp(int a,int if_label);
void LAndExp(int a,int else_label);
void EqExp(int a,int _);
void RelExp(int a,int _);


int Ident();

void getlineth()
{
	for(int j=0;j<i;j++) cout<<s[j];
}

int find_varcnt(string name)
{
	for(int i=nw;i>=0;i--)
		if(var_tab[i][name]!=0)
			return var_tab[i][name];
	printf("BUGGGG\n");
	cout<<"can't find :"<<name<<endl;
	getlineth();
	exit(0);
}
VAR find_var(string name)
{
	for(int i=nw;i>=0;i--)
		if(var_tab[i][name]!=0)
			return var[var_tab[i][name]];
	printf("BUGGGG\n");
	cout<<"can't find :"<<name<<endl;
	getlineth();
	exit(0);
}
int newtem()
{
	var[++var_cnt]={"tem",0,data++,0,nw,0};
	return var_cnt;
}




//BType → 'int' 
void BType()
{
	getsym(); // int
}
//nondigit
int nondigit(char c)
{
	return c>='a'&&c<='z'||c>='A'&&c<='Z'||c=='_';
}
//Ident
int Ident()
{
	if(!nondigit(str[0])) return 0;
	getsym();
	return 1;
}



//CompUnit → {Decl} {FuncDef} MainFuncDef
void CompUnit()
{
	quanju=1;
	while(sym=="const"||nextsym(2)!="(") Decl();
	var[0].base=data;
	midcode[++mid_cnt]={"jump",0};
	while(nextsym(1)!="main")
	{
		quanju++;
		FuncDef();
	}
	quanju++;
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
	getsym("const");
	BType();
	ConstDef();
	while(str==",")
	{
		getsym(",");
		ConstDef();
	}
	getsym(";");
	return 1;
}

//ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
void ConstDef()
{
	string name=str;
	Ident();
	int first=1,second=1,dim=0;
	while(str=="[")
	{
		dim++;
		getsym("[");
		if(dim==1) ConstExp(first);
		else ConstExp(second);
		getsym("]");
	}
	var_tab[nw][name]=++var_cnt;
	var[var_cnt]={"const",dim,constdata,second,nw,quanju};
	getsym("=");
	ConstInitVal();
}
// ConstInitVal → ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
void ConstInitVal()
{
	if(str!="{")
	{
		int x;
		ConstExp(x);
		constval[constdata++]=x;
	}
	else
	{
		getsym("{");
		if(str!="}")
		{
			ConstInitVal();
			while(str==",")
			{
				getsym(",");
				ConstInitVal();
			}
		}
		getsym("}");
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
		getsym(",");
		VarDef();
	}
	getsym(";");
	return 1;
}
int nowvar,p;
//VarDef → Ident { '[' ConstExp ']' } | Ident { '[' ConstExp ']' } '=' InitVal
void VarDef()
{
	string name=str;
	Ident();
	int first=1,second=1,dim=0;
	while(str=="[")
	{
		dim++;
		getsym("[");
		if(dim==1) ConstExp(first);
		else ConstExp(second);
		getsym("]");
	}
	var_tab[nw][name]=++var_cnt;
	var[var_cnt]={"int",dim,data++,second,nw,quanju};
	if(dim!=0)
	{	
		data+=first*second;
		midcode[++mid_cnt]={"def",var_cnt,nw,first*second};
	}
	if(str=="=")
	{
		getsym("=");
		if(dim==0) Exp(var_cnt,0);
		else
		{
			nowvar=var_cnt;
			p=0;
			InitVal();
		}
	}
	//data+=first*second;	
}

//InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'
void InitVal()
{
	if(str!="{")
	{
		int x=newtem();
		Exp(x,0);
		int b=newtem();
		midcode[++mid_cnt]={"=const",b,p++};
		midcode[++mid_cnt]={"[]=",nowvar,b,x};
	}
	else
	{
		getsym("{");
		if(str!="}")
		{
			InitVal();
			while(str==",")
			{
				getsym(",");
				InitVal();
			}
		}
		getsym("}");
	}
}



//MainFuncDef → 'int' 'main' '(' ')' Block
void MainFuncDef()
{
	nowf=0;
	data=1;
	getsym("int");
	getsym("main");
	getsym("(");
	getsym(")");
	midcode[++mid_cnt]={"label",0};
	int return_label=++label_cnt;
	Block(0,0);
	midcode[++mid_cnt]={"END"};
	mxdata=data;
}

//FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
int FuncDef()
{
	if(str!="void"&&str!="int") return 0;
	int dim=str=="int";
	FuncType();
	string name=str;
	
	int begin_label=++label_cnt;
	midcode[++mid_cnt]={"label",begin_label};
	var_tab[nw][name]=++var_cnt;
	nowf=var_cnt;
	data=1;
	labelisfunc[begin_label]=1;
	var[nowf]={"func",dim,0,begin_label,nw,quanju};    //  base存放总data数量,var_cnt为返回值，后面为参数 
	var[nowf].begin=mid_cnt;
	var[nowf].caninline=1;
	var[nowf].beginlabel=begin_label;
	
	Ident();
	getsym("(");
	if(str!=")") FuncFParams();
	getsym(")");
	Block(0,0);
	var[nowf].base=data;
	midcode[++mid_cnt]={"return"};
	var[nowf].end=mid_cnt;
	var[nowf].endlabel=label_cnt;
	return 1;
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
		getsym(",");
		FuncFParam();
	}
}
//FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]
void FuncFParam()
{
	BType();
	string name=str;
	Ident();
	int dim=0,second=1;
	while(str=="[")
	{
		dim++;
		getsym("[");
		if(dim==2) ConstExp(second);
		getsym("]");
	}
	if(dim!=0) var[nowf].caninline=0;
	var_tab[nw+1][name]=++var_cnt;
	var[var_cnt]={"para",dim,data++,second,nw+1,quanju};
	midcode[++mid_cnt]={"outpara",var_cnt,var[var_cnt].base};
}

//Block → '{' { BlockItem } '}'
void Block(int begin_label,int end_label)
{
	getsym("{");
	nw++;
	while(str!="}") BlockItem(begin_label,end_label);
	getsym("}");
	var_tab[nw--].clear();
}
//BlockItem → Decl | Stmt
void BlockItem(int begin_label,int end_label)
{
	if(!Decl()) Stmt(begin_label,end_label);
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

void Stmt(int begin_label,int end_label)
{
	if(str=="if")
	{
		getsym("if");
		getsym("(");
		int a=newtem(),if_label=++label_cnt,else_label=++label_cnt;
		Cond(a,if_label);
		midcode[++mid_cnt]={"jump",else_label};
		midcode[++mid_cnt]={"label",if_label};
		getsym(")");
		Stmt(begin_label,end_label);
		if(str=="else")
		{
			getsym("else");
			int end=++label_cnt;
			midcode[++mid_cnt]={"jump",end};
			midcode[++mid_cnt]={"label",else_label};
			Stmt(begin_label,end_label);
			midcode[++mid_cnt]={"label",end};
		}
		else midcode[++mid_cnt]={"label",else_label};
	}
	else if(str=="while")
	{
		getsym("while");
		getsym("(");
		int begin_label=++label_cnt,if_label=++label_cnt,end_label=++label_cnt,a=newtem();
		midcode[++mid_cnt]={"label",begin_label};
		Cond(a,if_label);
		midcode[++mid_cnt]={"jump",end_label};
		midcode[++mid_cnt]={"label",if_label};
		getsym(")");
		Stmt(begin_label,end_label);
		midcode[++mid_cnt]={"jump",begin_label};
		midcode[++mid_cnt]={"label",end_label};
	}
	else if(str=="break"||str=="continue")
	{
		if(str=="break") midcode[++mid_cnt]={"jump",end_label};
		else midcode[++mid_cnt]={"jump",begin_label};
		getsym();
		getsym(";");
	}
	else if(str=="return")
	{
		getsym("return");
		if(str!=";") 
		{
			if(nowf==0)
			{
				AddExp(0,0);
				midcode[++mid_cnt]={"END"};
				while(str!=";") getsym();
			}
			else
			{
				int b=newtem();
				Exp(b,0);
				midcode[++mid_cnt]={"inres",b};
			}
		}
		if(nowf!=0) midcode[++mid_cnt]={"return"};
		getsym(";");
	}
	else if(str=="printf")
	{
		getsym("printf");
		getsym("(");
		int bg=str_cnt;
		string sub="";
		for(int i=1;str[i]!='\0';i++)
		{
			if(str[i]=='%'&&str[i+1]=='d'||str[i]=='"')
			{
				i++;
				strtab[++str_cnt]=sub;
				sub="";
				if(str[i]=='\0') break;
			}
			else
				sub+=str[i];
		}
		getsym("FormatString");
		int a[100];
		for(int j=0;j<=99;j++) a[j]=0;
		int j=0;
		while(str==",")
		{
			getsym(",");
			a[++j]=newtem();
			Exp(a[j],0);
		}
		for(int k=1;bg+k<=str_cnt;k++)
		{
			if(strtab[bg+k]!="") midcode[++mid_cnt]={"printstr",bg+k};
			if(a[k]) midcode[++mid_cnt]={"printint",a[k]};
		}
		getsym(")");
		getsym(";");
	}
	else if(str=="{") Block(begin_label,end_label);
	else if(str==";") getsym(";");
	else
	{
		string _sym=sym,_str=str;
		int j=i;
		string name=str;
		while(str!="="&&str!=";") getsym();
		if(str=="=")
		{
			getsym("=");
			int c=newtem();
			if(str=="getint") midcode[++mid_cnt]={"getint",c};
			else Exp(c,0);
			sym=_sym; str=_str;
			i=j;
			LVal(c,1);
			while(str!=";") getsym();
			getsym();
		}
		else
		{
			sym=_sym; str=_str;
			i=j;
			AddExp(0,0);      //执行Exp前先把其中函数处理完 
			getsym(";");
		}
	}
}

//LVal → Ident {'[' Exp ']'}
void LVal(int &b)
{
	string name=str;
	Ident();
	int first,second,dim=0;
	while(str=="[")
	{
		dim++;
		getsym("[");
		if(dim==1) Exp(first);
		else Exp(second);
		getsym("]");
	}
	int imm=0;
	if(dim==1) imm=first;
	else if(dim==2) imm=first*find_var(name).second+second;
	b=constval[find_var(name).base+imm];
}
void LVal(int a,int _)      //_=1表示左值赋值，_=0表示取值 
{
	string name=str;
	Ident();
	if(a==0)
	{
		if(str=="[")
		{
			int sum=0;
			do
			{
				if(str=="[") sum++;
				else if(str=="]") sum--;
				getsym();
			}while(sum!=0);
		}
		return;
	}
	int firsttem,secondtem=0,dim=0;
	while(str=="[")
	{
		dim++;
		getsym("[");
		if(dim==1)
		{
			firsttem=newtem();
			Exp(firsttem,0);
		}
		else
		{
			secondtem=newtem();
			Exp(secondtem,0);
		}
		getsym("]");
	}
	if(dim==0)
	{
		if(_==0) midcode[++mid_cnt]={"=",a,find_varcnt(name)};   //取值
		else midcode[++mid_cnt]={"=",find_varcnt(name),a};       //赋值 
	}
	else
	{
		int shftem;
		if(find_var(name).dim==1) shftem=firsttem;
		else
		{
			int c=newtem();
			midcode[++mid_cnt]={"=const",c,find_var(name).second};
			midcode[++mid_cnt]={"*",c,firsttem,c};
			midcode[++mid_cnt]={"+",c,c,secondtem};
			shftem=c;
		}
		if(find_var(name).dim==dim)
		{
			if(_==0) midcode[++mid_cnt]={"[]",a,find_varcnt(name),shftem}; //取值
			else midcode[++mid_cnt]={"[]=",find_varcnt(name),shftem,a};    //赋值
		}	
		else    //取址 
		{
			int b=newtem();
			midcode[++mid_cnt]={"=const",b,4};
			midcode[++mid_cnt]={"*",shftem,shftem,b};
			midcode[++mid_cnt]={"+",a,find_varcnt(name),shftem};
		}
	}
}

int calc[100010];   //该函数是否计算，存在了哪 
//Exp → AddExp
void Exp(int &b)
{
	AddExp(b);
}
void Exp(int a,int _)
{
	string _sym=sym,_str=str;
	int j=i;
	AddExp(0,0);
	i=j;
	sym=_sym; str=_str;
	AddExp(a,0);
}
//ConstExp → AddExp
void ConstExp(int &b)
{
	AddExp(b);
}
//AddExp → MulExp | AddExp ('+' | '-') MulExp
void AddExp(int &b)
{
	MulExp(b);
	while(str=="+"||str=="-")
	{
		string op=str;
		getsym();  // + -
		int c;
		MulExp(c);
		if(op=="+") b+=c;
		else if(op=="-") b-=c;
	}
}
void AddExp(int a,int _)
{
	MulExp(a,0);
	while(str=="+"||str=="-")
	{
		string op=str;
		getsym();  // + -
		if(a!=0)
		{
			int b=newtem();
			MulExp(b,0);
			midcode[++mid_cnt]={op,a,a,b};
		}
		else MulExp(a,0);
	}
}
//MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
void MulExp(int &b)
{
	//cout<<b<<endl;
	UnaryExp(b);
	while(str=="*"||str=="/"||str=="%")
	{
		string op=str;
		getsym();  // * / %
		int c;
		UnaryExp(c);
		if(op=="*") b*=c;
		else if(op=="/") b/=c;
		else if(op=="%") b%=c;
	}
}
void MulExp(int a,int _)
{
	UnaryExp(a,0);
	while(str=="*"||str=="/"||str=="%")
	{
		string op=str;
		getsym();  // * / %
		if(a!=0)
		{
			int b=newtem();
			UnaryExp(b,0);
			midcode[++mid_cnt]={op,a,a,b};
		}
		else UnaryExp(a,0);
	}
}
//UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
void UnaryExp(int &b)
{
	string op=str;
	if(UnaryOp())
	{
		int c;
		UnaryExp(c);
		if(op=="+") b=c;
		else if(op=="-") b=-c;
		else if(op=="!") b=!c;
	}
	else PrimaryExp(b);
}
void FuncRParams(string tofuncname);
void UnaryExp(int a,int _)
{
	string op=str;
	if(UnaryOp())
	{
		UnaryExp(a,0);
		if(a!=0) midcode[++mid_cnt]={op,a,0,a};
	}
	else if(sym=="IDENFR"&&nextsym(1)=="(")   //函数 
	{
		string name=str;
		Ident();
		if(a==0)
		{
			int b=newtem();
			calc[i]=b;
			int funcnt=find_varcnt(name);
			if(funcnt==nowf) var[nowf].caninline=0;
			
			if(var[funcnt].caninline)    // 可以进行inline内联优化 
			{
				getsym("(");
				int paracnt=1;
				while(str!=")")		//形式传参 
				{
					int c=newtem();
					if(var[funcnt+paracnt].dim!=0) LVal(c,0);
					else Exp(c,0);
					midcode[++mid_cnt]={"=",funcnt+paracnt,c};
					paracnt++;
					if(str!=")") getsym(",");
				}
				getsym(")");
				int endlabel=++label_cnt;
				for(int i=var[funcnt].begin+paracnt;i<=var[funcnt].end;i++)
				{
					midcode[++mid_cnt]=midcode[i];
					if(midcode[mid_cnt].op=="label"||midcode[mid_cnt].op=="jump")
						midcode[mid_cnt].z=midcode[mid_cnt].z+label_cnt-var[funcnt].beginlabel+2;	
					else if(midcode[mid_cnt].op=="beqz"||midcode[mid_cnt].op=="jumptofunc")
						midcode[mid_cnt].x=midcode[mid_cnt].x+label_cnt-var[funcnt].beginlabel+2;
					else if(midcode[mid_cnt].op=="return")
						midcode[mid_cnt]={"jump",endlabel};
					else if(midcode[mid_cnt].op=="inres")
						midcode[mid_cnt]={"=",b,midcode[mid_cnt].z};
				}
				midcode[++mid_cnt]={"label",endlabel};
				//cout<<name<<"  "<<var[funcnt].endlabel<<" "<<var[funcnt].beginlabel<<endl;
				label_cnt+=var[funcnt].endlabel-var[funcnt].beginlabel+4;
			}
			else	//不可内联 
			{
				getsym("(");
				if(str!=")") FuncRParams(name);     //传参
				getsym(")");
				midcode[++mid_cnt]={"jumptofunc",find_varcnt(name),find_var(name).second};  // second实际上存储开始标签 
				if(find_var(name).dim==1) midcode[++mid_cnt]={"outres",b};      //varcnt 为函数值
			}
		}
		else
		{
			midcode[++mid_cnt]={"=",a,calc[i]};
			int sum=0;
			do
			{
				if(str=="(") sum++;
				else if(str==")") sum--;
				getsym();	
			}while(sum!=0);
		}
	}
	else PrimaryExp(a,0);
}
//FuncRParams → Exp { ',' Exp }
void FuncRPara(int paracnt,string tofuncname,int c);    //传参从1开始 
void FuncRParams(string tofuncname)
{
	int j=0;
	vector<int> a;
	a.push_back(newtem());
	FuncRPara(j+1,tofuncname,a[j]);
	j++;
	while(str==",")
	{
		getsym(",");
		a.push_back(newtem());
		FuncRPara(j+1,tofuncname,a[j]);
		j++;
	}
	for(int i=1;i<=j;i++) midcode[++mid_cnt]={"inpara",a[i-1],i};    //还没有解决参数过多的情况 已解决 
}
// 传参  
void FuncRPara(int paracnt,string tofuncname,int c)
{
	if(var[find_varcnt(tofuncname)+paracnt].dim!=0) LVal(c,0);
	else Exp(c,0);
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
//PrimaryExp → '(' Exp ')' | LVal | Number 
void PrimaryExp(int &b)
{
	if(str=="(")
	{
		getsym("(");
		Exp(b);
		getsym(")");
	}
	else if(str[0]>='0'&&str[0]<='9') Number(b);
	else LVal(b);
}
void PrimaryExp(int a,int _)
{
	if(str=="(")
	{
		getsym("(");
		AddExp(a,0);
		getsym(")");
	}
	else if(str[0]>='0'&&str[0]<='9') Number(a,0);
	else LVal(a,0);
}
//Number → IntConst
void Number(int &b)
{
	IntConst(b);
}
void Number(int a,int _)
{
	IntConst(a,0);
}
// IntConst
void IntConst(int &b)
{
	b=0;
	int i=0;
	while(str[i]!='\0') b=b*10+str[i++]-'0';
	getsym();
}
void IntConst(int a,int _)
{
	int b=0,i=0;
	while(str[i]!='\0') b=b*10+str[i++]-'0';
	if(a!=0) midcode[++mid_cnt]={"=const",a,b};
	getsym();
}





//Cond → LOrExp
void Cond(int a,int if_label)
{
	LOrExp(a,if_label);
}
//LOrExp → LAndExp | LOrExp '||' LAndExp
void LOrExp(int a,int if_label)
{
	int else_label=++label_cnt;
	LAndExp(a,else_label);
	midcode[++mid_cnt]={"jump",if_label};
	midcode[++mid_cnt]={"label",else_label};
	while(str=="||")
	{
		getsym("||");
		else_label=++label_cnt;
		int b=newtem();
		LAndExp(b,else_label);
		midcode[++mid_cnt]={"jump",if_label};
		midcode[++mid_cnt]={"label",else_label};
	}
}
//LAndExp → EqExp | LAndExp '&&' EqExp 
void LAndExp(int a,int else_label)
{
	EqExp(a,0);
	midcode[++mid_cnt]={"beqz",a,else_label};
	while(str=="&&")
	{
		getsym("&&");
		int b=newtem();
		EqExp(b,0);
		midcode[++mid_cnt]={"beqz",b,else_label};
	}
}
//EqExp → RelExp | EqExp ('==' | '!=') RelExp
void EqExp(int a,int _)
{
	RelExp(a,0);
	while(str=="=="||str=="!=")
	{
		string op=str;
		getsym();  // == !=
		int b=newtem();
		RelExp(b,0);
		midcode[++mid_cnt]={op,a,a,b};
	}
}
//RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
void RelExp(int a,int _)
{
	Exp(a,0);
	while(str=="<"||str==">"||str=="<="||str==">=")
	{
		string op=str;
		getsym();   //  <  >  <=  =>
		int b=newtem();
		Exp(b,0);
		midcode[++mid_cnt]={op,a,a,b};
	}
}


void printmidcode()
{
	//for(int i=base;i<constdata;i++) printf("%d\n",constval[i]);
	
	
	for(int i=1;i<=mid_cnt;i++)
	{
		string op=midcode[i].op;
		int x=midcode[i].x,y=midcode[i].y,z=midcode[i].z;
		if(op!="label"&&op!="labelmain") cout<<"\t"<<op<<" "<<z<<" "<<x<<" "<<y<<endl;
		else cout<<"label_"<<z<<endl;
	}
	cout<<endl<<endl<<endl<<endl;
}



map<int,int> rgvar,varrg;
void load(int x,int reg)
{
	if(x==0)
	{
		printf("li $%d 0\n",reg);
		return;
	}
	if(var[x].type=="const"||var[x].nw==0) printf("lw $%d %d($fp)\n",reg,var[x].base*4);
	else printf("lw $%d %d($sp)\n",reg,var[x].base*4);
}
void store(int x,int reg)
{
	if(x==0) return;
	if(var[x].nw==0) printf("sw $%d %d($fp)\n",reg,var[x].base*4);
	else printf("sw $%d %d($sp)\n",reg,var[x].base*4);
}
void load(int x,int reg,int shftreg)
{
	if(x==0)
	{
		printf("li $%d 0\n",reg);
		return;
	}
	if(var[x].type=="const")
	{
		printf("add $%d $%d $fp\n",shftreg,shftreg);
		printf("lw $%d %d($%d)\n",reg,var[x].base*4,shftreg);
	}
	else
	{
		load(x,26);
		printf("add $26 $26 $%d\n",shftreg);
		printf("lw $%d 0($26)\n",reg);
	}
}
void store(int x,int reg,int shftreg)
{
	if(x==0) return;
	load(x,26);
	printf("add $26 $26 $%d\n",shftreg);
	printf("sw $%d 0($26)\n",reg);
}


int isconst[100010]={1},value[100010];
void printmipscode()
{
	printf(".data\n");
	printf("a:.space %d\n",base*4);
	for(int i=base;i<constdata;i++) printf("const_%d:.word %d\n",i-base,constval[i]);
	for(int i=1;i<=str_cnt;i++)
		cout<<"str_"<<i<<":.asciiz \""<<strtab[i]<<"\"\n";
	printf("\n");
	printf(".text\n");
	
	
	printf("la $fp a\n\n");
	var[0].base+=constdata;
	int o=0;
	for(int i=1;i<=mid_cnt;i++)
	{
		string op=midcode[i].op;
		int z=midcode[i].z,x=midcode[i].x,y=midcode[i].y;
		int rgz=varrg[z],rgy=varrg[y],rgx=varrg[x];		
		//cout<<op<<"   "<<z<<" "<<x<<" "<<y<<endl;
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="[]="||op=="[]")		//使用
			{
				if(op!="[]"&&var[x].type=="const")
				{
					rgx=27;
					printf("li $%d %d\n",rgx,constval[var[x].base]);
				}
				if(var[y].type=="const")
				{
					rgy=26;
					printf("li $%d %d\n",rgy,constval[var[y].base]);
				}
			}
		if(op=="=")
		{
			if(rgz!=rgx)       ////////
			{
				printf("move $%d $%d\n",rgz,rgx);
			}
			//load(x,9);
			//store(z,9);
		}
		else if(op=="+")
		{
			if(isconst[x])
			{
				swap(x,y);
				swap(rgx,rgy);
			}
			if(isconst[y])
			{
				//load(x,9);
				printf("addi $%d $%d %d\n",rgz,rgx,value[y]);
				//store(z,11);
			}
			else
			{
//				load(x,9); load(y,10);
//				printf("add $11 $9 $10\n");
//				store(z,11);
				printf("add $%d $%d $%d\n",rgz,rgx,rgy);
			}
		}
		else if(op=="-")
		{
//			load(x,9); load(y,10);
//			printf("sub $11 $9 $10\n");
//			store(z,11);
			printf("sub $%d $%d $%d\n",rgz,rgx,rgy);
		}
		else if(op=="*")
		{
			if(isconst[x])
			{
				swap(x,y);
				swap(rgx,rgy);
			}
			if(isconst[y]&&(value[y]&-value[y])==value[y])
			{
				int p=value[y];
				int q=0;
				while(p!=1)
				{
					q++;
					p>>=1;
				}
				//load(x,9);
				printf("sll $%d $%d %d\n",rgz,rgx,q);
				//store(z,11);
			}
			else
			{
//				load(x,9); load(y,10);
//				printf("mul $11 $9 $10\n");
//				store(z,11);
				printf("mul $%d $%d $%d\n",rgz,rgx,rgy);
			}
		}
		else if(op=="/")
		{
			//cout<<y<<"  "<<isconst[y]<<" "<<value[y]<<endl;
			if(isconst[y]&&(value[y]&-value[y])==value[y])
			{
				int p=value[y];
				int q=0;
				while(p!=1)
				{
					q++;
					p>>=1;
				}
				//load(x,9);
				//printf("sra $11 $9 %d\n",q);
				//store(z,11);
				printf("sra $%d $%d %d\n",rgz,rgx,q);
			}
			else
			{
//				load(x,9); load(y,10);
//				printf("div $9 $10\n");
//				printf("mflo $11\n");
//				store(z,11);
				printf("div $%d $%d\n",rgx,rgy);
				printf("mflo $%d\n",rgz);
			}
		}
		else if(op=="%")
		{
//			if(isconst[y]&&(value[y]&-value[y])==value[y]) o++;
//			load(x,9); load(y,10);
//			printf("div $9 $10\n");
//			printf("mfhi $11\n");
//			store(z,11);
			printf("div $%d $%d\n",rgx,rgy);
			printf("mfhi $%d\n",rgz);
		}
		else if(op=="!")
		{
//			load(y,9);
//			printf("seq $10 $9 $0\n");
//			store(z,10);
			printf("seq $%d $%d $%d\n",rgz,rgx,rgy);
		}
		else if(op=="label") printf("\nlabel_%d:\n",z);
		else if(op=="jump")
		{
			if(z==0) printf("subi $sp $sp %d\n",base*4);
			printf("j label_%d\n\n",z);
		}
		else if(op=="printstr")
		{
			printf("la $a0 str_%d\n",z);
			printf("li $v0 4\n");
			printf("syscall\n");
		}
		else if(op=="printint")
		{
//			load(z,9);
//			printf("move $a0 $9\n");
			printf("move $a0 $%d\n",rgz);
			printf("li $v0 1\n");
			printf("syscall\n");
		}
		else if(op=="getint")
		{
			printf("li $v0 5\n");
			printf("syscall\n");
//			printf("move $9 $v0\n");
//			store(z,9);
			printf("move $%d $v0\n",rgz);
		}
		else if(op=="return") printf("jr $ra\n");
		else if(op=="END")
		{
			printf("li $v0 10\n");
			printf("syscall\n");
		}
		else if(op=="=const")
		{
//			printf("li $9 %d\n",x);
//			store(z,9);
			printf("li $%d %d\n",rgz,x);
		}
		else if(op=="jumptofunc")
		{
			printf("sw $ra 0($sp)\n");
			for(int i=7;i<=26;i++)
				printf("sw $%d %d($sp)\n",i,-i*4);
			printf("subi $sp $sp %d\n",50000);
			printf("jal label_%d\n\n",var[z].second);
			printf("addi $sp $sp %d\n",50000);
			for(int i=7;i<=26;i++)
				printf("lw $%d %d($sp)\n",i,-i*4);
			printf("lw $ra 0($sp)\n");
		}
		else if(op=="inpara")    // z为int,x为reg 
		{
			if(x<=4)
			{
//				load(z,x+3);
				printf("move $%d $%d\n",x+2,rgz);
			}
			else
			{
//				load(z,3);
//				printf("sw $3 %d($fp)\n",(mxdata+x)*4);
				printf("sw $%d %d($fp)\n",rgz,(mxdata+x)*4);
			}
		}
		else if(op=="outpara")
		{
			if(x<=4)
			{
//				store(z,x+3);
				printf("move $%d $%d\n",rgz,x+2);
			}
			else
			{
//				printf("lw $3 %d($fp)\n",(mxdata+x)*4);
//				store(z,3);
				printf("lw $%d %d($fp)\n",rgz,(mxdata+x)*4);
			}
		}
		else if(op=="inres")
		{
//			load(z,24);
			printf("move $%d $%d\n",27,rgz);
		}
		else if(op=="outres")
		{
//			store(z,24);
			printf("move $%d $%d\n",rgz,27);
		}
		else if(op=="==")
		{
//			load(x,9);
//			load(y,10);
//			printf("seq $11 $9 $10\n");
//			store(z,11);
			printf("seq $%d $%d $%d\n",rgz,rgx,rgy);
		}
		else if(op=="!=")
		{
//			load(x,9);
//			load(y,10);
//			printf("sne $11 $9 $10\n");
//			store(z,11);
			printf("sne $%d $%d $%d\n",rgz,rgx,rgy);
		}
		else if(op==">=")
		{
//			load(x,9);
//			load(y,10);
//			printf("sge $11 $9 $10\n");
//			store(z,11);
			printf("sge $%d $%d $%d\n",rgz,rgx,rgy);
		}
		else if(op=="<=")
		{
//			load(x,9);
//			load(y,10);
//			printf("sle $11 $9 $10\n");
//			store(z,11);
			printf("sle $%d $%d $%d\n",rgz,rgx,rgy);
		}
		else if(op==">")
		{
//			load(x,9);
//			load(y,10);
//			printf("sgt $11 $9 $10\n");
//			store(z,11);
			printf("sgt $%d $%d $%d\n",rgz,rgx,rgy);
		}
		else if(op=="<")
		{
//			load(x,9);
//			load(y,10);
//			printf("slt $11 $9 $10\n");
//			store(z,11);
			printf("slt $%d $%d $%d\n",rgz,rgx,rgy);
		}
		else if(op=="beqz")
		{
//			load(z,9);
//			printf("beqz $9 label_%d\n",x);
			printf("beqz $%d label_%d\n",rgz,x);
		}
		else if(op=="[]")              //z=x[y]
		{
//			load(y,9);
//			printf("sll $9 $9 2\n");
//			load(x,10,9);
//			store(z,10);
			printf("sll $%d $%d 2\n",27,rgy);
			load(x,rgz,27);
		}
		else if(op=="[]=")              //z[x]=y
		{
//			load(x,9);
//			printf("sll $9 $9 2\n");
//			load(y,10);
//			store(z,10,9);
			printf("sll $%d $%d 2\n",27,rgx);
			store(z,rgy,27);
		}
		else if(op=="def")
		{
			if(x==0) printf("addi $9 $fp %d\n",(var[z].base+1)*4);  //x为所处层次 
			else printf("addi $9 $sp %d\n",(var[z].base+1)*4);
			store(z,9);
		}
		else cout<<"error"<<endl<<op<<endl;
	}
}





//以下是优化部分 
int block_cnt;
int phi_cnt;
struct PHI
{
	int left;
	map<int,int> right;
	int leftini;
}phi[100010];
struct Basicblock
{
	vector<MIDCODE> midcodes;
	set<int> pre;      //前趋 
	set<int> nx; 	   //后继
	set<int> DF;
	int fa;
	set<int> ch;       //子节点 
	set<int> phis;
	set<pair<int,int> > addphi;  //生成代码时给后继添加的phi 
	vector<pair<int,int> > sortaddphi;
	set<int> use,def,in,out;
	int haveuse;
}basicblock[100010];

vector<MIDCODE> midcodes;
set<int> root;
map<int,int> labeltoblockcnt;

int vis[100010],have[100010];
void getvis(int x,int t)
{
	if(x==t) return;
	vis[x]=1;
	for(auto y:basicblock[x].nx)
		if(!vis[y]) getvis(y,t);
}
void calcDF(int x)
{
	for(auto y:basicblock[x].ch) calcDF(y);
	for(auto y:basicblock[x].nx)
		if(basicblock[y].fa!=x) basicblock[x].DF.insert(y);
	for(auto z:basicblock[x].ch)
		for(auto y:basicblock[z].DF)
			if(basicblock[y].fa!=x) basicblock[x].DF.insert(y);
}
stack<int> st[100010];
int rename_cnt=10000;
int rename_base=500;
void rename_getphi(int p)          //重命名并得到phi的右值 
{
	map<int,int> popcnt;
	for(auto j:basicblock[p].phis)
	{
		int x=phi[j].left;
		st[x].push(++rename_cnt);
		var[rename_cnt]=var[x];
		if(var[rename_cnt].type!="const") var[rename_cnt].base=rename_base++;
		popcnt[x]++;
		//cout<<"gg "<<phi[j].left<<"   "<<st[x].top()<<endl;
		phi[j].left=st[x].top();
	}
	for(int j=0;j<basicblock[p].midcodes.size();j++)
	{
		MIDCODE code=basicblock[p].midcodes[j];
		string op=code.op;
		int z=code.z,x=code.x,y=code.y;
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="[]="||op=="[]")		//使用替换编号
			{
				if(op!="[]"&&x!=0&&var[x].quanju!=1)
				{
					if(st[x].empty())
					{
						st[x].push(x);
						popcnt[x]++;
						//cout<<x<<endl;
					}
					basicblock[p].midcodes[j].x=st[x].top();
				}
				if(y!=0&&var[y].quanju!=1)
				{
					if(st[y].empty())
					{
						st[y].push(y);
						popcnt[y]++;
						//cout<<y<<endl;
					}
					basicblock[p].midcodes[j].y=st[y].top();
				}
			/*	if(op=="[]="&&z!=0&&var[z].quanju!=1)
				{
					if(st[z].empty())
					{
						st[z].push(++rename_cnt);
						var[rename_cnt]=var[z];
						if(var[rename_cnt].type!="const"&&var[rename_cnt].nw!=0) var[rename_cnt].base=rename_base++;
						popcnt[z]++;
					}
					basicblock[p].midcodes[j].z=st[z].top();
				}*/
			}
		else if(op=="inpara"||op=="inres"||op=="beqz"||op=="printint")
		{
			if(z!=0&&var[z].quanju!=1&&var[z].dim==0)
			{
				if(st[z].empty())
				{
					st[z].push(z);
					popcnt[z]++;
				}
				basicblock[p].midcodes[j].z=st[z].top();
			}
		}
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="outpara"||op=="outres"||op=="getint"||
			op=="=const"||op=="[]")
			{
				if(op=="outpara")
				{
					popcnt[z]++;
					st[z].push(z);
				}
				else if(var[z].quanju!=1)
				{
					popcnt[z]++;
					st[z].push(++rename_cnt);       //定义替换编号 
					var[rename_cnt]=var[z];
					if(var[rename_cnt].type!="const"&&var[rename_cnt].nw!=0) var[rename_cnt].base=rename_base++;
					basicblock[p].midcodes[j].z=rename_cnt;
				}
			}
	}
	for(auto q:basicblock[p].nx)
		for(auto v:basicblock[q].phis)
		{
			if(st[phi[v].leftini].empty())  
			{
				st[phi[v].leftini].push(++rename_cnt);
				var[rename_cnt]=var[phi[v].leftini];
				if(var[rename_cnt].type!="const"&&var[rename_cnt].nw!=0) var[rename_cnt].base=rename_base++;
				popcnt[phi[v].leftini]++;
			}
			phi[v].right[p]=st[phi[v].leftini].top();
		}
	for(auto y:basicblock[p].ch) rename_getphi(y);
	for(auto j:popcnt)
	{
		for(int k=0;k<j.second;k++)
			st[j.first].pop();
	}
}

void block_print()
{
	for(int i=1;i<=block_cnt;i++)
	{
		printf("block:  %d\n",i);
		cout<<"nx:  ";
		for(auto j:basicblock[i].nx) cout<<j<<" ";
		cout<<endl;
		cout<<"pre:  ";
		for(auto j:basicblock[i].pre) cout<<j<<" ";
		cout<<endl;
		for(auto j:basicblock[i].ch) cout<<j<<" ";
		cout<<"ch:   ";
		cout<<endl;
		cout<<"phi: ";
		for(auto j:basicblock[i].phis) cout<<j<<" ";
		cout<<endl;
		cout<<"DF: ";
		for(auto j:basicblock[i].DF) cout<<j<<" ";
		cout<<endl;
		cout<<"in: ";
		for(auto j:basicblock[i].in) cout<<j<<" ";
		cout<<endl;
		cout<<"out: ";
		for(auto j:basicblock[i].out) cout<<j<<" ";
		cout<<endl;
		cout<<"use: ";
		for(auto j:basicblock[i].use) cout<<j<<" ";
		cout<<endl;
		cout<<"def: ";
		for(auto j:basicblock[i].def) cout<<j<<" ";
		cout<<endl;
		cout<<endl;
		for(int j=0;j<basicblock[i].midcodes.size();j++)
		{
			string op=basicblock[i].midcodes[j].op;
			int z=basicblock[i].midcodes[j].z,x=basicblock[i].midcodes[j].x,y=basicblock[i].midcodes[j].y;
			cout<<op<<" "<<z<<" "<<x<<" "<<y<<endl;
		}
		cout<<endl;
	}
	cout<<endl<<endl;
	cout<<endl<<endl;	
}

int dlt[100010];
void kuikong()    //窥孔优化 
{
	for(int i=1;i<mid_cnt;i++)
	{
		dlt[i]=0;
		string op=midcode[i].op;
		int z=midcode[i].z,x=midcode[i].x,y=midcode[i].y;
		string nop=midcode[i+1].op;
		int nz=midcode[i+1].z,nx=midcode[i+1].x,ny=midcode[i+1].y;
		if(op=="jump"&&nop=="label"&&z==nz&&z!=0) dlt[i]=1;
	}
	dlt[mid_cnt]=0;
	int m=0;
	for(int i=1;i<=mid_cnt;i++)
		if(dlt[i]==0)
			midcode[++m]=midcode[i];
	mid_cnt=m;
	
	m=0;
	for(int i=1;i<=mid_cnt;i++)
	{
		string op=midcode[i].op,nop=midcode[i+1].op;
		if(i<mid_cnt&&op=="printstr"&&nop=="printstr")
		{
			strtab[++str_cnt]=strtab[midcode[i].z]+strtab[midcode[i+1].z];
			int j=i+2;
			while(j<=mid_cnt&&midcode[j].op=="printstr")
			{
				strtab[str_cnt]+=strtab[midcode[j].z];
				j++;
			}
			midcode[++m]={"printstr",str_cnt};
			i=j-1;
		}
		else midcode[++m]=midcode[i];
	}
	mid_cnt=m;
}

string tostring(int x)
{
	string res="";
	if(x<10) res+=x+'0';
	else
	{
		res=tostring(x/10);
		res+=x%10+'0';
	}
	return res;
}
int varto[100010];// isconst[100010]={1},value[100010]; 
//复写传播，常量传播时是否为常数(默认0号为常数)，如果是是多少 
map<string,int> commonexp;
void GVN(int p)
{
	map<int,int> change_varto,change_isconst,change_value; //为了回溯 
	map<int,int> ini_varto,ini_isconst,ini_value;
	map<string,int> change_commonexp,ini_commonexp; 
	for(auto phicnt:basicblock[p].phis)              //phi函数里的左值不能使用之前的 
	{
		if(!change_varto[phi[phicnt].left])
		{
			change_varto[phi[phicnt].left]=1;
			ini_varto[phi[phicnt].left]=varto[phi[phicnt].left];
		}
		varto[phi[phicnt].left]=phi[phicnt].left;
	}
	for(int j=0;j<basicblock[p].midcodes.size();j++)
	{
		MIDCODE code=basicblock[p].midcodes[j];
		string op=code.op;
		int z=code.z,x=code.x,y=code.y;

		if(op==">=")
		{
			op="<=";
			swap(x,y);
		}
		if(op==">")
		{
			op="<";
			swap(x,y);
		}
		if(op=="+"||op=="*"||op=="=="||op=="!=")   //满足交换律,常量在前，然后小的在前 
		{
			if(x>y) swap(x,y);
			if(isconst[x]==0&&isconst[y]==1)
				swap(x,y);
		}
		
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||                 //复写传播 
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="[]="||op=="[]")
			{
				if(op!="[]"&&var[x].quanju!=1) x=varto[x];      //所有使用改为赋值的右值 
				if(var[y].quanju!=1) y=varto[y];
				//if(op=="[]="&&var[z].quanju!=1) basicblock[p].midcodes[j].z=varto[z];
			}
		
		if(var[z].quanju==1)
		{
			basicblock[p].midcodes[j]={op,z,x,y};	
			continue;
		}
		if(op=="inpara"||op=="inres"||op=="beqz"||op=="printint")
		{
			z=varto[z];
			//cout<<op<<" "<<z<<" "<<isconst[z]<<"   "<<value[z]<<endl;
			if(op=="beqz"&&isconst[z])
			{
				if(value[z]==0)
				{
					op="jump";
					z=x;
					x=y=0;
				}
				else op="del";
			}
			if(op=="printint"&&isconst[z])
			{
				op="printstr";
				if(value[z]>=0) strtab[++str_cnt]=tostring(value[z]);
				else strtab[++str_cnt]="-"+tostring(-value[z]);
				z=str_cnt;
				x=y=0;
			}
			basicblock[p].midcodes[j]={op,z,x,y};
			continue;
		}
		if(op=="="&&var[x].quanju!=1||op=="+"&&isconst[x]==1&&value[x]==0&&isconst[y]==0&&var[y].quanju!=1||
				op=="*"&&isconst[x]==1&&value[x]==1&&isconst[y]==0&&var[y].quanju!=1||
				op=="/"&&isconst[x]==0&&var[x].quanju!=1&&isconst[y]==1&&value[y]==1)
		{
			if(!change_varto[z])        
			{
				change_varto[z]=1;
				ini_varto[z]=varto[z];
			}
			if(op=="="||op=="/") varto[z]=x;       //更改以后的使用，复写传播
			else if(op=="+"||op=="*") varto[z]=y;
			//op="del";              //加上之后出现神奇BUG 
			basicblock[p].midcodes[j]={op,z,x,y};
			continue;
		}
		

		//basicblock[p].midcodes[j]={op,z,x,y}; continue;
		if(op=="=const")								//常量传播 
		{
			if(!change_isconst[z])
			{
				change_isconst[z]=1;
				ini_isconst[z]=isconst[z];
			}
			isconst[z]=1;
			if(!change_value[z])
			{
				change_value[z]=1;
				ini_value[z]=value[z];
			}
			value[z]=x;
			basicblock[p].midcodes[j]={op,z,x,y};
			continue;
		}
		//basicblock[p].midcodes[j]={op,z,x,y}; continue;
		if((op=="+"||op=="-"||op=="*"||op=="/"||op=="%"
			||op=="!="||op=="=="||op=="<="||op=="<"||op=="!")
			&&isconst[x]==1&&isconst[y]==1)         //这里已经没有>=和>了 
		{
			if(!change_isconst[z])
			{
				change_isconst[z]=1;
				ini_isconst[z]=isconst[z];
			}
			isconst[z]=1;
			if(!change_value[z])
			{
				change_value[z]=1;
				ini_value[z]=value[z];
			}
			//cout<<op<<" "<<z<<"   "<<x<<" "<<value[x]<<"     "<<y<<" "<<value[y]<<endl;
			if(op=="+") value[z]=value[x]+value[y];
			else if(op=="-") value[z]=value[x]-value[y];
			else if(op=="*") value[z]=value[x]*value[y];
			else if(op=="/") value[z]=value[x]/value[y];
			else if(op=="%") value[z]=value[x]%value[y];
			else if(op=="!=") value[z]=value[x]!=value[y];
			else if(op=="=="||op=="!") value[z]=value[x]==value[y];  // ! 和 0 == 等价 
			else if(op=="<=") value[z]=value[x]<=value[y];
			else if(op=="<") value[z]=value[x]<value[y];
			op="=const"; x=value[z]; y=0;
			basicblock[p].midcodes[j]={op,z,x,y};
			continue;
		}
		//basicblock[p].midcodes[j]={op,z,x,y}; continue;
		if((op=="+"||op=="-"||op=="*"||op=="/"||                 // 全局公共子表达式删除 
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<")&&var[x].quanju!=1&&var[y].quanju!=1)
		{
			
			string exp=tostring(x)+op+tostring(y);
			//cout<<exp<<"  "<<isconst[x]<<"  "<<isconst[y]<<"  "<<value[y]<<"  "<<var[x].quanju<<"  "<<var[y].quanju<<endl;
			//cout<<exp<<endl;
			if(commonexp[exp]!=0)
			{
				if(!change_varto[z])
				{
					change_varto[z]=1;
					ini_varto[z]=varto[z];
				}
				varto[z]=commonexp[exp];
				op="del";     //这个语句可以直接删除 
			}
			else
			{
				if(!change_commonexp[exp])
				{
					change_commonexp[exp]=1;
					ini_commonexp[exp]=commonexp[exp];
				}
				commonexp[exp]=z;
			}
		}
		basicblock[p].midcodes[j]={op,z,x,y};
	}
	set<pair<int,int> > addphicopy;               //替换addphi中的使用，需要copy来实现 
	for(auto it:basicblock[p].addphi)
	{
		pair<int,int> nxphi=it;
		nxphi.second=varto[nxphi.second];
		addphicopy.insert(nxphi);
	}
	basicblock[p].addphi.clear();
	for(auto it:addphicopy)
		basicblock[p].addphi.insert(it);
	
	for(auto q:basicblock[p].ch) GVN(q);
	
	for(auto it:ini_varto) varto[it.first]=it.second;       //回溯 
//	for(auto it:ini_isconst) isconst[it.first]=it.second;
//	for(auto it:ini_value) value[it.first]=it.second;
	for(auto it:ini_commonexp) commonexp[it.first]=it.second;
}

set<int> defpoint[100010];  //变量定义点集合 
int usetime[100010];   //变量使用次数 
int del[100010];      //是否删除 
void dead_def_clear()
{
	int m=0;
	for(int i=1;i<=mid_cnt;i++)
	{
		MIDCODE code=midcode[i];
		string op=code.op;
		int z=code.z,x=code.x,y=code.y;
		if(op=="="&&z==x) continue;
		midcode[++m]=midcode[i];
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="[]="||op=="[]")
			{
				usetime[x]++;
				usetime[y]++;
				if(op=="[]=") usetime[z]++;
			}
		else if(op=="inpara"||op=="inres"||op=="beqz"||op=="printint")
			usetime[z]++;
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
		op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
		op==">"||op=="<"||op=="outpara"||op=="outres"||      //这里去掉了getint 
		op=="=const"||op=="[]")
			defpoint[z].insert(m);	
	}
	mid_cnt=m;
	queue<int> q;   //删除的变量的队列 
	for(int i=1;i<=rename_cnt;i++)
		if(usetime[i]==0) q.push(i);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		for(auto i:defpoint[x])
		{
			del[i]=1;
			MIDCODE code=midcode[i];
			string op=code.op;
			int z=code.z,x=code.x,y=code.y;
			if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="[]")    //此时不会出现[]= 
			{
				usetime[x]--;
				usetime[y]--;
				if(usetime[x]==0) q.push(x);
				if(usetime[y]==0) q.push(y);
			}			
		}
	}
	m=0;
	for(int i=1;i<=mid_cnt;i++)
		if(!del[i]) midcode[++m]=midcode[i];
	//cout<<m<<"   "<<mid_cnt<<endl;
	mid_cnt=m;
}

int haveuselabel[100010];
void dead_label_clear()
{
	haveuselabel[0]=1;
	for(int i=1;i<=label_cnt;i++) haveuselabel[i]=0;
	for(int i=1;i<=mid_cnt;i++)
		if(midcode[i].op=="jump") haveuselabel[midcode[i].z]++;
		else if(midcode[i].op=="beqz"||midcode[i].op=="jumptofunc") haveuselabel[midcode[i].x]++;
	int m=0;
	for(int i=1;i<=mid_cnt;i++)
		if(midcode[i].op=="label"&&haveuselabel[midcode[i].z]==0) continue;
		else midcode[++m]=midcode[i];
	mid_cnt=m;
}

void dfsblock(int x)
{
	basicblock[x].haveuse=1;
	for(auto ch:basicblock[x].ch) dfsblock(ch);	
}

void dead_block_clear()
{
	return;
	for(int i=1;i<=block_cnt;i++) basicblock[i].haveuse=0;
	for(auto r:root) dfsblock(r);
	int m=0;
	map<int,int> newcnt;
	for(int i=1;i<=block_cnt;i++)
		if(basicblock[i].haveuse) newcnt[i]=++m;
	set<int> newset;
	for(auto r:root) newset.insert(newcnt[r]);
	root=newset;
	m=0;
	for(int i=1;i<=block_cnt;i++)
		if(basicblock[i].haveuse)
		{
			basicblock[++m]=basicblock[i];
			set<int> newset;
			for(auto it:basicblock[i].pre) newset.insert(newcnt[it]);
			basicblock[m].pre=newset;
			newset.clear();
			for(auto it:basicblock[i].nx) newset.insert(newcnt[it]);
			basicblock[m].nx=newset;
			newset.clear();
			for(auto it:basicblock[i].ch) newset.insert(newcnt[it]);
			basicblock[m].ch=newset;
			newset.clear();
			for(auto it:basicblock[i].DF) newset.insert(newcnt[it]);
			basicblock[m].DF=newset;
			basicblock[m].fa=newcnt[basicblock[i].fa];
		}
	block_cnt=m;
}

void toposort_addphi(int cnt)
{
	map<int,int> rudu;
	map<int,int> to;
	queue<int> q;
	for(auto it:basicblock[cnt].addphi)
	{
		if(it.first==it.second) continue;
		rudu[it.first]=rudu[it.first];
		rudu[it.second]++;
		to[it.first]=it.second;
		//cout<<"be "<<it.first<<"  "<<it.second<<endl;
	}
	for(auto it:rudu)
		if(it.second==0) q.push(it.first);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		int y=to[x];
		if(y==0) continue;
		basicblock[cnt].sortaddphi.push_back(make_pair(x,y));
		rudu[y]--;
		if(rudu[y]==0) q.push(y);
	}
	for(auto it:rudu)
	{
		if(it.second!=0)
		{
			int x=it.first;
			int y=to[x];
			int c=newtem();             //内存分配可能还有问题 
			
			basicblock[cnt].sortaddphi.push_back(make_pair(c,x));
			rudu[x]--;
			while(y!=it.first)
			{
				rudu[y]--;
				basicblock[cnt].sortaddphi.push_back(make_pair(x,y));
				x=y;
				y=to[x];
			}
			basicblock[cnt].sortaddphi.push_back(make_pair(x,c));
		}
	}
	/*
	if(basicblock[cnt].sortaddphi.size())
	{
		for(auto it:basicblock[cnt].sortaddphi)
			printf("%d  %d\n",it.first,it.second);
	
		printf("\n\n\n");
	}*/
}

void fenkuai()
{
	for(int i=1;i<=block_cnt;i++)
	{
		basicblock[i].midcodes.clear();
		basicblock[i].nx.clear();
		basicblock[i].pre.clear();
		basicblock[i].DF.clear();
		basicblock[i].fa=0;
		basicblock[i].ch.clear();
	}
	root.clear();
	labeltoblockcnt.clear();
	block_cnt=1;
	for(int i=1;i<=mid_cnt;i++)      //分块 
	{
		string op=midcode[i].op;
		int z=midcode[i].z,x=midcode[i].x,y=midcode[i].y;
		if(i==1&&op!="label")
		{
			if(basicblock[block_cnt].midcodes.size()) block_cnt++;
			root.insert(block_cnt);
		}
		if(op=="label")
		{
			if(basicblock[block_cnt].midcodes.size()) block_cnt++;
			labeltoblockcnt[z]=block_cnt;
			if(labelisfunc[z]) root.insert(block_cnt);
		}
		basicblock[block_cnt].midcodes.push_back(midcode[i]);
		if(i!=mid_cnt&&(op=="beqz"||op=="jump"||op=="return"||op=="END")
		 &&(basicblock[block_cnt].midcodes.size())) block_cnt++;
	}
	for(int i=1;i<=block_cnt;i++)    //获取前趋和后继 
	{
		MIDCODE lstcode=basicblock[i].midcodes[basicblock[i].midcodes.size()-1]; //最后一条指令 
		string op=lstcode.op;
		if(op=="jump") basicblock[i].nx.insert(labeltoblockcnt[lstcode.z]);
		if(op!="jump"&&op!="return"&&op!="END") basicblock[i].nx.insert(i+1);
		if(op=="beqz") basicblock[i].nx.insert(labeltoblockcnt[lstcode.x]);
		for(auto to:basicblock[i].nx)
			basicblock[to].pre.insert(i);
	}
	for(int i=0;i<=100000;i++) vis[i]=have[i]=0;
	for(auto r:root) getvis(r,0);                  //建支配树 
	for(int i=1;i<=block_cnt;i++) have[i]=vis[i];
	for(int i=1;i<=block_cnt;i++)
	{
		for(int j=1;j<=block_cnt;j++) vis[j]=0;
		for(auto r:root) getvis(r,i);
		for(int j=1;j<=block_cnt;j++)
			if(have[j]&&!vis[j]&&i!=j)    //  i>>j
				basicblock[j].fa=max(basicblock[j].fa,i);
	}
	for(int i=1;i<=block_cnt;i++)
		if(basicblock[i].fa!=0) basicblock[basicblock[i].fa].ch.insert(i);
	//for(auto r:root) cout<<r<<endl;
	for(auto r:root) calcDF(r);
}

void fenpei(int p)
{
	//cout<<x<<endl;
	for(auto x:basicblock[p].use)
		if(varrg[x]) rgvar[varrg[x]]=x;
	for(auto x:basicblock[p].def)
		if(varrg[x]) rgvar[varrg[x]]=x;
	for(auto x:basicblock[p].in)
		if(varrg[x]) rgvar[varrg[x]]=x;
	map<int,int> finaluse;
	for(int i=basicblock[p].midcodes.size()-1;i>=0;i--)
	{
		MIDCODE code=basicblock[p].midcodes[i];
		string op=code.op;
		int z=code.z,x=code.x,y=code.y;
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="[]="||op=="[]")
			{
				if(op!="[]"&&finaluse[x]==0) finaluse[x]=i+1;
				if(finaluse[y]==0) finaluse[y]=i+1;
			}
		else if(op=="inpara"||op=="inres"||op=="beqz"||op=="printint")
		{
			if(finaluse[z]==0) finaluse[z]=i+1;
		}
	}
	for(int i=0;i<basicblock[p].midcodes.size();i++)
	{
		MIDCODE code=basicblock[p].midcodes[i];
		string op=code.op;
		int z=code.z,x=code.x,y=code.y;
		if(finaluse[x]==i+1&&basicblock[p].out.count(x)==0) rgvar[varrg[x]]=0;
		if(finaluse[y]==i+1&&basicblock[p].out.count(y)==0) rgvar[varrg[y]]=0;
		
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="outpara"||op=="outres"||
			op=="=const"||op=="[]"||op=="getint")
			{
				if(z!=0&&varrg[z]==0)
				{
					for(int i=7;i<=25;i++)
					{
						if(rgvar[i]==0)
						{
							varrg[z]=i;
							rgvar[i]=z;
							break;
						}
					}
					cout<<z<<"       "<<varrg[z]<<endl;
					if(varrg[z]==0)
					{
						varrg[z]=-1;
						cout<<"reg not enough!"<<endl;
					}
				}
			}
	}
	for(auto ch:basicblock[p].ch)
	{
		map<int,int> mp;
		for(int i=7;i<=25;i++)
			if(basicblock[ch].in.count(rgvar[i])==0)
			{
				mp[i]=rgvar[i];
				rgvar[i]=0;
			}
		fenpei(ch);
		for(auto it:mp)
			rgvar[it.first]=it.second;
	}
}

int defs[100010];
void youhua()   //分块 并优化 
{
	midcode[++mid_cnt]={"END"};
	///printmidcode();
	//dead_label_clear();
	//printmidcode();
	//printmidcode();        //全局变量不参与优化          这块需要改！！ 
	
	//kuikong();
	
	fenkuai();
		
	set<int> varinblock[100010];    //变量i在哪些基本块中出现 
	for(int i=1;i<=block_cnt;i++)
	{
		for(auto code:basicblock[i].midcodes)
		{
			string op=code.op;
			int z=code.z,x=code.x,y=code.y;
			if(op!="label"&&op!="jump"&&op!="printstr") varinblock[z].insert(i);
			if(op!="beqz"&&op!="=const") varinblock[x].insert(i);
			if(op!="def") varinblock[y].insert(i);	
		}
	}
	queue<int> W;                              //  插入phi 
	for(int i=1;i<=var_cnt;i++)
	{
		if(varinblock[i].size()<=1||var[i].quanju==1||var[i].dim>0) continue;    //全局变量和数组不参与优化
		for(int j=1;j<=block_cnt;j++) vis[j]=defs[j]=0;
		for(int j=1;j<=block_cnt;j++)
		{
			/*
			if(j==1)
			{
				defs[j]=1;
				W.push(1);
				continue;
			}
			defs[j]=0;   */
			for(auto code:basicblock[j].midcodes)
			{
				string op=code.op;
				if(code.z==i&&(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
					op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
					op==">"||op=="<"||op=="outpara"||op=="outres"||op=="getint"||
					op=="=const"||op=="[]"))
					{
						W.push(j);
						defs[j]=1;
						break;
					}
			}
		}
		while(!W.empty())
		{
			int x=W.front(); W.pop();
			//if(i==4) cout<<"dsadas "<<x<<endl;			
			for(auto y:basicblock[x].DF)
				if(!vis[y])
				{
					phi[++phi_cnt].left=i;
					//cout<<y<<"  phi!!   "<<i<<endl;
					phi[phi_cnt].leftini=i;
					basicblock[y].phis.insert(phi_cnt);
					vis[y]=1;
					if(!defs[y]) W.push(y);
				}
		}
	}
	//block_print();
	
	for(auto r:root) rename_getphi(r);         //重命名并填入phi右值 
	
	//block_print();
	/*
	block_print();
	for(int i=1;i<=block_cnt;i++)
	{
		for(auto j:basicblock[i].phis)
			cout<<phi[j].left<<" ";
		cout<<endl;
	}
	for(int i=1;i<=phi_cnt;i++)
	{
		cout<<phi[i].left<<": ";
		for(auto j:phi[i].right) cout<<j.first<<" "<<j.second<<"    ";
		cout<<endl;
	}
	*/
	map<pair<int,int>,set<pair<int,int> > > addphi;     //生成代码时填入phi 
	for(int i=1;i<=block_cnt;i++)
		if(basicblock[i].phis.size())
		{
			for(auto phinum:basicblock[i].phis)
			{
				int v=phi[phinum].left;
				for(auto phimap:phi[phinum].right)
				{
					int j=phimap.first;       // j为i前趋 
					int rv=phimap.second;     // 这条phi为i插到其前趋j的 v=rv 
					//cout<<i<<" "<<j<<" : "<<v<<" = "<<rv<<endl;
					addphi[make_pair(j,i)].insert(make_pair(v,rv));
				}
			}
		}
	for(auto mp:addphi)
	{
		int x=mp.first.first,y=mp.first.second;
		set<pair<int,int> > st=mp.second;
		if(basicblock[x].nx.size()==1) basicblock[x].addphi=st;
		else   //只能为beqz
		{
			if(basicblock[x].midcodes[basicblock[x].midcodes.size()-1].op!="beqz") cout<<"not beqz"<<endl;
			if(x+1==y) basicblock[x].addphi=st;
			else
			{
				int nxlabel=basicblock[x].midcodes[basicblock[x].midcodes.size()-1].x;
				basicblock[x].midcodes[basicblock[x].midcodes.size()-1].x=++label_cnt;
				block_cnt++;
				basicblock[block_cnt].midcodes.push_back({"label",label_cnt});
				      //新增一个基本块以便于之后的GVN优化 
				for(auto sentence:st)
					basicblock[block_cnt].addphi.insert(make_pair(sentence.first,sentence.second));
				basicblock[block_cnt].midcodes.push_back({"jump",nxlabel});
				basicblock[block_cnt].pre.insert(x);
				basicblock[x].nx.insert(block_cnt);
				basicblock[block_cnt].nx.insert(y);
				basicblock[y].pre.insert(block_cnt);
				basicblock[block_cnt].fa=x;
				basicblock[x].ch.insert(block_cnt);
			}
		}
	}
	//printmidcode();
	
	for(int i=1;i<=rename_cnt;i++)
		if(var[i].type=="const")
		{
			isconst[i]=1;
			value[i]=constval[var[i].base];
			var[i].quanju=0;
		}
		
	for(auto r:root)                           //全局值编号优化
	{
		for(int i=1;i<=rename_cnt;i++) varto[i]=i;
		GVN(r);
	}
	
	//cout<<mid_cnt<<endl;
	dead_block_clear();
	mid_cnt=0;    //重导中间代码 
	for(int i=1;i<=block_cnt;i++)
	{
		//cout<<i<<"                  "<<basicblock[i].midcodes.size()<<endl;
		toposort_addphi(i);
		for(int j=0;j<basicblock[i].midcodes.size()-1;j++)
			if(basicblock[i].midcodes[j].op!="del") midcode[++mid_cnt]=basicblock[i].midcodes[j];
		MIDCODE lstcode=basicblock[i].midcodes[basicblock[i].midcodes.size()-1];	
		if(lstcode.op=="jump")
			for(auto sentence:basicblock[i].sortaddphi)
				midcode[++mid_cnt]={"=",sentence.first,sentence.second,0};
		if(lstcode.op!="del") midcode[++mid_cnt]=lstcode;
		if(lstcode.op!="jump")
			for(auto sentence:basicblock[i].sortaddphi)
				midcode[++mid_cnt]={"=",sentence.first,sentence.second,0};
	}
	//block_print();
	//printmidcode();
	//dead_def_clear();
	//return;
	/*
	int c[100010];
	for(int i=1;i<=mid_cnt;i++)
	{
		string op=midcode[i].op;
		int z=midcode[i].z;
		if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
			op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
			op==">"||op=="<"||op=="outpara"||op=="outres"||op=="getint"||
			op=="=const")
		c[z]++;
	}
	for(int i=1;i<=phi_cnt;i++)
		cout<<i<<"       "<<phi[i].left<<endl;
	for(int i=10000;i<=rename_cnt;i++)
		if(c[i]==0) cout<<i<<" "<<c[i]<<" "<<var[i].type<<endl;
	printmidcode();
	*/
	//printmidcode();
	//printmidcode();
	
	dead_def_clear();           //无用定义删除 	
	//printmidcode();
	dead_label_clear();
	kuikong();
	
	dead_label_clear();
	kuikong();
	dead_label_clear();
	kuikong();
	dead_label_clear();
	kuikong();
	
//	block_print();
	
	fenkuai();
	
	//for(auto r:root) fenpei(r);
	//cout<<endl<<endl<<endl<<endl;
	dead_block_clear();
	//for(auto r:root) fenpei(r);
	//cout<<endl<<endl<<endl<<endl;	
	
	//cout<<"ddddddddddddddddddddddddddddddddddddd"<<endl;
	
	for(int i=1;i<=block_cnt;i++)                  //活跃变量分析 
	{
		//cout<<i<<"                  "<<basicblock[i].midcodes.size()<<endl;
		for(int j=0;j<basicblock[i].midcodes.size();j++)
		{
			MIDCODE code=basicblock[i].midcodes[j];
			string op=code.op;
			int z=code.z,x=code.x,y=code.y;
			if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
				op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
				op==">"||op=="<"||op=="[]="||op=="[]")
				{
					if(op!="[]"&&basicblock[i].use.count(x)==0&&basicblock[i].def.count(x)==0) basicblock[i].use.insert(x);
					if(basicblock[i].use.count(y)==0&&basicblock[i].def.count(y)==0) basicblock[i].use.insert(y);
				}
			else if(op=="inpara"||op=="inres"||op=="beqz"||op=="printint")
			{
				if(basicblock[i].use.count(z)==0&&basicblock[i].def.count(z)==0) basicblock[i].use.insert(z);
			}
			if(op=="="||op=="+"||op=="-"||op=="*"||op=="/"||
				op=="%"||op=="!"||op=="!="||op=="=="||op==">="||op=="<="||
				op==">"||op=="<"||op=="outpara"||op=="outres"||
				op=="=const"||op=="[]"||op=="getint")
				{
					if(basicblock[i].use.count(z)==0&&basicblock[i].def.count(z)==0) basicblock[i].def.insert(z);
				}
		}
	}
	
	for(int i=1;i<=block_cnt;i++)
		for(auto x:basicblock[i].use)
			basicblock[i].in.insert(x);
	int change=1;
	while(change)
	{
		change=0;
		for(int i=block_cnt;i;i--)
		{
			for(auto y:basicblock[i].nx)
				for(auto x:basicblock[y].in)
					basicblock[i].out.insert(x);
			for(auto x:basicblock[i].out)
				if(basicblock[i].def.count(x)==0)
					if(basicblock[i].in.count(x)==0)
					{
						basicblock[i].in.insert(x);
						change=1;
					}
		}
	}
	for(auto r:root) fenpei(r);
	
	
//	for()     //寄存器分配 
//	block_print();
	
	mid_cnt=0;    //再次重导中间代码 
	for(int i=1;i<=block_cnt;i++)
	{
		//cout<<i<<"                  "<<basicblock[i].midcodes.size()<<endl;
		for(int j=0;j<basicblock[i].midcodes.size();j++)
			midcode[++mid_cnt]=basicblock[i].midcodes[j];
	} 
//	return;
	for(int i=1;i<=mid_cnt;i++)
	{
		string op=midcode[i].op;
		int z=midcode[i].z,x=midcode[i].x,y=midcode[i].y;
		cout<<op<<" "<<z<<" "<<x<<" "<<y<<endl;
		cout<<varrg[z]<<" "<<varrg[x]<<" "<<varrg[y]<<endl;
	}
	block_print();
	//cout<<mid_cnt<<endl;	
	printmidcode();
}

int main()
{
	init();
	getsym();
	CompUnit();
	//printmidcode();
	//for(int i=1;i<=var_cnt;i++) cout<<i<<"   "<<var[i].type<<"  "<<var[i].base<<" "<<var[i].nw<<endl;
	
	//
	//printmidcode();
	youhua();
	//printmidcode();
	
	//printmidcode();
	//com_sub_exp_optimize();   //公共子表达式优化 
	printmipscode();
	

	return 0;
} 
