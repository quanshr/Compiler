//局部子表达式优化 


#include <bits/stdc++.h>
using namespace std;

int n; //读入字符串总长 
int i; //词法分析过程循环变量 
char s[50000010]; //读入的所有字符 
map<string,string> mp; //词法的对应
string sym,str; //当前读入的符号（词法）,具体字符串 

int data,base=50000;    //主存地址,常量起始地址 
int constdata=base;
int constval[1000010];
int nw=0,var_cnt;   //当前目录,每个变量的唯一标识符编号 
struct VAR
{
	string type;   // const , int ,para ,tem
	int dim;      //维度 0，1，2 
	int base;      // 基地址 
	int second;   // 若为二维数组，记录第2维的大小
	int nw;
	string name;
}var[1000010];
map<string,int> var_tab[100010];   //栈式符号表，对应VAR下标编号 
int mid_cnt;
struct MIDCODE
{
	string op;
	int z,x,y;   //操作数x,y,结果z 
}midcode[1000010];
int label;      //跳转标签 
string strtab[1000010]; //输出字符串 
int str_cnt;
int nowf;

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
	mp["bitand"]="bitand";
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

int find_varcnt(string name)
{
	for(int i=nw;i>=0;i--)
		if(var_tab[i][name]!=0)
			return var_tab[i][name];
	printf("BUGGGG\n");
	cout<<nw<<" "<<name<<endl;
	for(auto it=var_tab[0].begin();it!=var_tab[0].end();it++) cout<<it->first<<" "<<it->second<<endl;
	cout<<endl;
}
VAR find_var(string name)
{
	for(int i=nw;i>=0;i--)
		if(var_tab[i][name]!=0)
			return var[var_tab[i][name]];
	printf("BUGGGG\n");
	cout<<nw<<" "<<name<<endl;
	for(auto it=var_tab[0].begin();it!=var_tab[0].end();it++) cout<<it->first<<" "<<it->second<<endl;
	cout<<endl;
}
int newtem()
{
	var[++var_cnt]={"tem",0,data++,0,nw};
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
	while(sym=="const"||nextsym(2)!="(") Decl();
	var[0].base=data;
	midcode[++mid_cnt]={"jump",0};
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
	var[var_cnt]={"const",dim,constdata,second,nw};
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
	var[var_cnt]={"int",dim,data++,second,nw};
	if(dim!=0)
	{	
		data+=first*second;
		midcode[++mid_cnt]={"def",var_cnt,nw,first*second};
	}
	if(str=="=")
	{
		getsym("=");
		if(dim==0)
		{
			if(str=="getint")
			{
				getsym();
				getsym();
				getsym();
				//cout<<str<<endl;
				midcode[++mid_cnt]={"getint",var_cnt};
			}
			else Exp(var_cnt,0);
		}
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
	int return_label=++label;
	Block(0,0);
	midcode[++mid_cnt]={"END"};
}

//FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
int FuncDef()
{
	if(str!="void"&&str!="int") return 0;
	int dim=str=="int";
	FuncType();
	string name=str;
	
	int begin_label=++label;
	midcode[++mid_cnt]={"label",begin_label};
	var_tab[nw][name]=++var_cnt;
	nowf=var_cnt;
	data=1;
	var[var_cnt]={"func",dim,0,begin_label,nw};    //  base存放总data数量,var_cnt为返回值，后面为参数 
	Ident();
	getsym("(");
	if(str!=")") FuncFParams();
	getsym(")");
	Block(0,0);
	var[nowf].base=data;
	midcode[++mid_cnt]={"return"};
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
	var_tab[nw+1][name]=++var_cnt;
	var[var_cnt]={"para",dim,data++,second,nw+1};
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
		int a=newtem(),if_label=++label,else_label=++label;
		Cond(a,if_label);
		midcode[++mid_cnt]={"jump",else_label};
		midcode[++mid_cnt]={"label",if_label};
		getsym(")");
		Stmt(begin_label,end_label);
		if(str=="else")
		{
			getsym("else");
			int end=++label;
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
		int begin_label=++label,if_label=++label,end_label=++label,a=newtem();
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
	while(str=="*"||str=="/"||str=="%"||str=="bitand")
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
	else if(sym=="IDENFR"&&nextsym(1)=="(")
	{
		string name=str;
		Ident();
		if(a==0)
		{
			int b=newtem();
			calc[i]=b;
			getsym("(");
			if(str!=")") FuncRParams(name);     //传参
			getsym(")");
			midcode[++mid_cnt]={"jumptofunc",find_varcnt(name)};  // second实际上存储开始标签 
			if(find_var(name).dim==1) midcode[++mid_cnt]={"outres",b};      //varcnt 为函数值
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
	int j=0,a[20];
	a[++j]=newtem();
	FuncRPara(j,tofuncname,a[j]);
	while(str==",")
	{
		getsym(",");
		a[++j]=newtem();
		FuncRPara(j,tofuncname,a[j]);
	}
	for(int i=1;i<=j;i++) midcode[++mid_cnt]={"inpara",i,a[i]};
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
	int else_label=++label;
	LAndExp(a,else_label);
	midcode[++mid_cnt]={"jump",if_label};
	midcode[++mid_cnt]={"label",else_label};
	while(str=="||")
	{
		getsym("||");
		else_label=++label;
		LAndExp(a,else_label);
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
		EqExp(a,0);
		midcode[++mid_cnt]={"beqz",a,else_label};
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
		load(x,8);
		printf("add $8 $8 $%d\n",shftreg);
		printf("lw $%d 0($8)\n",reg);
	}
}
void store(int x,int reg,int shftreg)
{
	if(x==0) return;
	load(x,8);
	printf("add $8 $8 $%d\n",shftreg);
	printf("sw $%d 0($8)\n",reg);
}

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
	for(int i=1;i<=mid_cnt;i++)
	{
		string op=midcode[i].op;
		int x=midcode[i].x,y=midcode[i].y,z=midcode[i].z;
		//cout<<op<<"   "<<z<<" "<<x<<" "<<y<<endl;
		if(op=="=")
		{
			load(x,9);
			store(z,9);
		}
		else if(op=="+")
		{
			load(x,9); load(y,10);
			printf("add $11 $9 $10\n");
			store(z,11);
		}
		else if(op=="-")
		{
			load(x,9); load(y,10);
			printf("sub $11 $9 $10\n");
			store(z,11);
		}
		else if(op=="*")
		{
			load(x,9); load(y,10);
			printf("mult $9 $10\n");
			printf("mflo $11\n");
			store(z,11);
		}
		else if(op=="/")
		{
			load(x,9); load(y,10);
			printf("div $9 $10\n");
			printf("mflo $11\n");
			store(z,11);
		}
		else if(op=="%")
		{
			load(x,9); load(y,10);
			printf("div $9 $10\n");
			printf("mfhi $11\n");
			store(z,11);
		}
		else if(op=="!")
		{
			load(y,9);
			printf("seq $10 $9 $0\n");
			store(z,10);
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
			load(z,9);
			printf("move $a0 $9\n");
			printf("li $v0 1\n");
			printf("syscall\n");
		}
		else if(op=="getint")
		{
			printf("li $v0 5\n");
			printf("syscall\n");
			printf("move $9 $v0\n");
			store(z,9);
		}
		else if(op=="return") printf("jr $ra\n");
		else if(op=="END")
		{
			printf("li $v0 10\n");
			printf("syscall\n");
		}
		else if(op=="=const")
		{
			printf("li $9 %d\n",x);
			store(z,9);
		}
		else if(op=="jumptofunc")
		{
			printf("sw $ra 0($sp)\n");
			printf("subiu $sp $sp %d\n",var[z].base*4);
			printf("jal label_%d\n\n",var[z].second);
			printf("addi $sp $sp %d\n",var[z].base*4);
			printf("lw $ra 0($sp)\n");
		}
		else if(op=="inpara")
		{
			load(x,9);
			printf("move $%d $9\n",z+14);
		}
		else if(op=="outpara")
		{
			store(z,x+14);
		}
		else if(op=="inres")
		{
			load(z,20);
		}
		else if(op=="outres")
		{
			store(z,20);
		}
		else if(op=="==")
		{
			load(x,9);
			load(y,10);
			printf("seq $11 $9 $10\n");
			store(z,11);
		}
		else if(op=="!=")
		{
			load(x,9);
			load(y,10);
			printf("sne $11 $9 $10\n");
			store(z,11);
		}
		else if(op==">=")
		{
			load(x,9);
			load(y,10);
			printf("sge $11 $9 $10\n");
			store(z,11);
		}
		else if(op=="<=")
		{
			load(x,9);
			load(y,10);
			printf("sle $11 $9 $10\n");
			store(z,11);
		}
		else if(op==">")
		{
			load(x,9);
			load(y,10);
			printf("sgt $11 $9 $10\n");
			store(z,11);
		}
		else if(op=="<")
		{
			load(x,9);
			load(y,10);
			printf("slt $11 $9 $10\n");
			store(z,11);
		}
		else if(op=="beqz")
		{
			load(z,9);
			printf("beqz $9 label_%d\n",x);
		}
		else if(op=="[]")
		{
			load(y,9);
			printf("sll $9 $9 2\n");
			load(x,10,9);
			store(z,10);
		}
		else if(op=="[]=")
		{
			load(x,9);
			printf("sll $9 $9 2\n");
			load(y,10);
			store(z,10,9);
		}
		else if(op=="def")
		{
			if(x==0) printf("addi $9 $fp %d\n",(var[z].base+1)*4);  //x为所处层次 
			else printf("addi $9 $sp %d\n",(var[z].base+1)*4);
			store(z,9);
		}
		else if(op=="bitand")
		{
			load(x,9); load(y,10);
			printf("and $11 $9 $10\n");
			store(z,11);
		}
		else cout<<"error"<<endl<<op<<endl;
	}
}





//以下是优化部分 
int block_cnt;
struct Basicblock
{
	vector<MIDCODE> midcodes;
}basicblock[100010];

void fenkuai()   //分块 
{
	int bg,ed;
	for(int i=1;i<=mid_cnt;i++)
	{
		bg=ed=0;
		if(i==1) bg=1;
		if(i==mid_cnt) ed=1;
		string op=midcode[i].op;
		int z=midcode[i].z,x=midcode[i].x,y=midcode[i].y;
		if(op=="beqz"||op=="jump"||op=="jal"||op=="jr"||op=="return"||op=="jumptofunc"||op=="END")
			ed=1;
		if(op=="label") bg=1;
		if(bg==1) block_cnt++;
		basicblock[block_cnt].midcodes.push_back(midcode[i]);
		if(ed==1) block_cnt++;
	}
	for(int i=1;i<=block_cnt;i++)
	{
		for(int j=0;j<basicblock[i].midcodes.size();j++)
		{
			string op=basicblock[i].midcodes[j].op;
			int z=basicblock[i].midcodes[j].z,x=basicblock[i].midcodes[j].x,y=basicblock[i].midcodes[j].y;		
			cout<<op<<" "<<z<<" "<<x<<" "<<y<<endl;
		}
		cout<<endl;	
	}
	
}

void com_sub_exp_optimize()   //公共子表达式优化 
{
	for(int i=1;i<=block_cnt;i++)
	{
		//midcode_to_DAG();
	}
}


int main()
{
	init();
	getsym();
	CompUnit();
	//printmidcode();
	//for(int i=1;i<=var_cnt;i++) cout<<i<<"   "<<var[i].type<<"  "<<var[i].base<<" "<<var[i].nw<<endl;
	//fenkuai();
	
	//com_sub_exp_optimize();   //公共子表达式优化 
	printmipscode();
	

	return 0;
} 
