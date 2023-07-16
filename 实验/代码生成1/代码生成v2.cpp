//参数寄存器不够，改完应该是对的
//之后开始寄存器分配优化 


#include <bits/stdc++.h>
using namespace std;

int n; //读入字符串总长 
int i; //词法分析过程循环变量 
char s[50000010]; //读入的所有字符 
map<string,string> mp; //词法的对应
string sym,str; //当前读入的符号（词法）,具体字符串 

int data;    //主存地址
int constdata[1000010];
int nw=0,var_cnt;   //当前目录,每个变量的唯一标识符编号 
struct VAR
{
	string type;   // const or int
	int dim;      //维度 0，1，2 
	int base;      // 基地址 
	int second;   // 若为二维数组，记录第2维的大小 
}var[1000010];
map<string,int> var_tab[100010];   //栈式符号表，对应VAR下标编号 
int mid_cnt;
struct MIDCODE
{
	string op;
	int x,y,z;   //操作数x,y,结果z 
}midcode[1000010],midcode2[10010];
int tem_cnt;     //临时变量 
int label;      //跳转标签 
string strtab[1000010]; //输出字符串 
int str_cnt;

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
	if(str=="{") nw++;
	else if(str=="}") var_tab[nw--].clear();
	
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
void Block(int begin_label,int end_label,int return_label);
void BlockItem(int begin_label,int end_label,int return_label);
void Stmt(int begin_label,int end_label,int return_label);

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
void LVal_getaddr(int &tem,int &base);


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
	midcode[++mid_cnt]={"jmain"};
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

//ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
void ConstDef()
{
	string name=str;
	Ident();
	int first=1,second=1,dim=0;
	while(str=="[")
	{
		dim++;
		getsym();   // [
		if(dim==1) ConstExp(first);
		else ConstExp(second);
		//ConstExp();
		//cout<<first<<" "<<second<<endl;
		getsym();  // ]
	}
	var_tab[nw][name]=++var_cnt;
	var[var_cnt]={"const",dim,data,second};
	//data+=first*second;
	getsym();   // =
	ConstInitVal();
}
// ConstInitVal → ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
void ConstInitVal()
{
	if(str!="{")
	{
		int x;
		ConstExp(x);
		constdata[data]=x;
		midcode[++mid_cnt]={"data=const",data++,x,0};
	}
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
	string name=str;
	Ident();
	int first=1,second=1,dim=0;
	while(str=="[")
	{
		dim++;
		getsym();  // [
		if(dim==1) ConstExp(first);
		else ConstExp(second);
		getsym();  // ]
	}
	var_tab[nw][name]=++var_cnt;
	var[var_cnt]={"int",dim,data,second};
	if(str=="=")
	{
		getsym();  // =
		InitVal();
	}
	data+=first*second;	
}
//InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'
void InitVal()
{
	if(str!="{")
	{
		int x=++tem_cnt;
		Exp(x,0);
		midcode[++mid_cnt]={"storeword",x,data++,0};
	}
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



//MainFuncDef → 'int' 'main' '(' ')' Block
void MainFuncDef()
{
	getsym();  // int
	getsym();  // main
	getsym();  // (
	getsym();  // )
	midcode[++mid_cnt]={"labelmain"};
	int return_label=++label;
	Block(0,0,return_label);
	midcode[++mid_cnt]={"label",return_label};
	midcode[++mid_cnt]={"END"};
}

//FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
int FuncDef(int _)    //useless
{
	if(str!="void"&&str!="int") return 0;
	FuncType();
	string name=str;
	var_tab[nw][name]=++var_cnt;
	var[var_cnt]={"func"};
	Ident();
	getsym();  // (
	if(str!=")") FuncFParams();
	getsym(); // )
	Block();
	return 1;
}
int FuncDef()
{
	if(str!="void"&&str!="int") return 0;
	int dim=str=="int";
	FuncType();
	string name=str;
	
	int begin_label=++label;
	midcode[++mid_cnt]={"label",begin_label};
	var_tab[nw][name]=++var_cnt;
	var[var_cnt]={"func",dim,var_cnt,begin_label};    //  base存放var_cnt 
	Ident();
	getsym();  // (
	int begindata=data,beginmidcode=mid_cnt,return_label=++label,begintem=tem_cnt;
	if(str!=")") FuncFParams();
	int paradata=data;      //参数在[begindata,paradata) 
	getsym(); // )
	Block(0,0,return_label);
	int t=0;
	for(int i=beginmidcode+1;i<=mid_cnt;i++) midcode2[++t]=midcode[i];
	
	mid_cnt=beginmidcode;
	midcode[++mid_cnt]={"push$ra"};
	for(int i=begindata;i<data;i++) midcode[++mid_cnt]={"pushdata",i};
	for(int i=begintem+1;i<=tem_cnt;i++) midcode[++mid_cnt]={"pushtem",i};  //copy 
	
	int a0=4;
	for(int i=begindata;i<paradata;i++) midcode[++mid_cnt]={"outpara",a0++,i};  //传参
	
	for(int i=1;i<=t;i++) midcode[++mid_cnt]=midcode2[i];   //函数体部分
	
	midcode[++mid_cnt]={"label",return_label};
	for(int i=tem_cnt;i>begintem;i--) midcode[++mid_cnt]={"poptem",i};
	for(int i=data-1;i>=begindata;i--) midcode[++mid_cnt]={"popdata",i};
	midcode[++mid_cnt]={"pop$ra"};
	midcode[++mid_cnt]={"jump_$ra"};
	
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
		getsym();  // ,
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
	if(str=="[")
	{
		dim++;
		getsym();  // [
		getsym();  // ]
		if(str=="[")
		{
			dim++;
			getsym(); // [
			ConstExp(second);
			getsym();  // ]
		}
	}
	var_tab[nw+1][name]=++var_cnt;
	var[var_cnt]={"para",dim,data++,second};
}

//Block → '{' { BlockItem } '}'
void Block()
{
	getsym();  // {
	while(str!="}") BlockItem();
	getsym();  // }
}
void Block(int begin_label,int end_label,int return_label)
{
	getsym();  // {
	while(str!="}") BlockItem(begin_label,end_label,return_label);
	getsym();  // }
}
//BlockItem → Decl | Stmt
void BlockItem()
{
	if(!Decl()) Stmt();
	//printf("<BlockItem>\n");
}
void BlockItem(int begin_label,int end_label,int return_label)
{
	if(!Decl()) Stmt(begin_label,end_label,return_label);
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

void Stmt(int begin_label,int end_label,int return_label)
{
	if(str=="if")
	{
		getsym("if");
		getsym("(");
		int a=++tem_cnt,if_label=++label,else_label=++label;
		Cond(a,if_label);
		midcode[++mid_cnt]={"jump",else_label};
		midcode[++mid_cnt]={"label",if_label};
		getsym(")");
		Stmt(begin_label,end_label,return_label);
		if(str=="else")
		{
			getsym("else");
			int end=++label;
			midcode[++mid_cnt]={"jump",end};
			midcode[++mid_cnt]={"label",else_label};
			Stmt(begin_label,end_label,return_label);
			midcode[++mid_cnt]={"label",end};
		}
		else midcode[++mid_cnt]={"label",else_label};
	}
	else if(str=="while")
	{
		getsym("while");
		getsym("(");
		int begin_label=++label,if_label=++label,end_label=++label,a=++tem_cnt;
		midcode[++mid_cnt]={"label",begin_label};
		Cond(a,if_label);
		midcode[++mid_cnt]={"jump",end_label};
		midcode[++mid_cnt]={"label",if_label};
		getsym(")");
		Stmt(begin_label,end_label,return_label);
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
			int x=++tem_cnt;
			Exp(x,0);
			midcode[++mid_cnt]={"inttoreg",x,25};
		}
		midcode[++mid_cnt]={"jump",return_label};
		getsym(";");
	}
	else if(str=="printf")
	{
		getsym("printf");
		getsym("(");
		int bg=str_cnt,j=0;
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
		while(str==",")
		{
			j++;
			//midcode[++mid_cnt]={"printstr",bg+j};
			getsym(",");
			a[j]=++tem_cnt;
			Exp(a[j],0);
			//midcode[++mid_cnt]={"printint",a};
		}
		for(int k=1;bg+k<=str_cnt;k++)
		{
			midcode[++mid_cnt]={"printstr",bg+k};
			if(a[k]) midcode[++mid_cnt]={"printint",a[k]};
		}
		//if(bg+j<str_cnt) midcode[++mid_cnt]={"printstr",str_cnt};
		getsym(")");
		getsym(";");
	}
	else if(str=="{") Block(begin_label,end_label,return_label);
	else if(str==";") getsym(";");
	else
	{
		int j=0;
		while(nextsym(j)!="="&&nextsym(j)!=";") j++;
		if(nextsym(j)=="=")
		{
			int a,b;
			LVal_getaddr(a,b);       //左值表达式，xb为基地址的tem（不乘4），xa为偏移量的tem（乘4） 
			getsym("=");
			if(str=="getint")
			{
				getsym("getint");
				getsym("(");
				getsym(")");
				getsym(";");
				midcode[++mid_cnt]={"read_in_data",b,a,0};
			}
			else
			{
				int c=++tem_cnt;
				Exp(c,0);
				getsym(";");
				midcode[++mid_cnt]={"storeword_zalridy*4",c,b,a};
			}
		}
		else
		{
			int a=++tem_cnt;
			Exp(a,0);
			getsym(";");
		}
	}
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
	b=constdata[find_var(name).base+imm];
}
void LVal(int a,int _)
{
	string name=str;
	Ident();
	int firsttem=++tem_cnt,secondtem=++tem_cnt,dim=0;
	while(str=="[")
	{
		dim++;
		getsym("[");
		if(dim==1) Exp(firsttem,0);
		else Exp(secondtem,0);
		getsym("]");
	}
	//cout<<dim<<endl;
	if(dim==0) midcode[++mid_cnt]={"loadword",a,find_var(name).base,0};
	else if(dim==1)
	{
		if(find_var(name).type!="para") midcode[++mid_cnt]={"loadword",a,find_var(name).base,firsttem};
		else
		{
			//cout<<"WAAAAAAAAAAAAAAAAA"<<endl;			
			//cout<<name<<endl;
			int b=++tem_cnt;
			midcode[++mid_cnt]={"loadword",b,find_var(name).base,0};
			
        	//midcode[++mid_cnt]={"printint",b};
        	//midcode[++mid_cnt]={"printstr",4};
			
			midcode[++mid_cnt]={"*const",firsttem,firsttem,4};
			midcode[++mid_cnt]={"+",b,b,firsttem};
			midcode[++mid_cnt]={"straightloadword",a,b};
		}
	}
	else
	{
		if(find_var(name).type!="para")
		{
			midcode[++mid_cnt]={"*const",firsttem,firsttem,find_var(name).second};
			midcode[++mid_cnt]={"+",firsttem,firsttem,secondtem};
			midcode[++mid_cnt]={"loadword",a,find_var(name).base,firsttem};
		}
		else
		{
			//cout<<name<<endl;
			int b=++tem_cnt;
			midcode[++mid_cnt]={"loadword",b,find_var(name).base,0};
			
			//midcode[++mid_cnt]={"printint",b};
			//midcode[++mid_cnt]={"printstr",4};
			
			midcode[++mid_cnt]={"*const",firsttem,firsttem,find_var(name).second};
			midcode[++mid_cnt]={"+",firsttem,firsttem,secondtem};
			midcode[++mid_cnt]={"*const",firsttem,firsttem,4};
			midcode[++mid_cnt]={"+",b,b,firsttem};
			midcode[++mid_cnt]={"straightloadword",a,b};
		}
	}
}
void LVal_getaddr(int &tem,int &base)   //base为基地址（不乘4）为常数，tem为偏移量的int 
                                        //若为参数，base=0,结果全部存于tem 
{
	string name=str;
	Ident();
	int dim=0;
	tem=0;
	while(str=="[")
	{
		dim++;
		getsym("[");
		if(dim==1)
		{
			tem=++tem_cnt;
			Exp(tem,0);
		}
		else
		{
			midcode[++mid_cnt]={"*const",tem,tem,find_var(name).second};
			int secondtem=++tem_cnt;
			Exp(secondtem,0);
			midcode[++mid_cnt]={"+",tem,tem,secondtem};
		}
		getsym("]");
	}
	if(dim!=0) midcode[++mid_cnt]={"*const",tem,tem,4};
	//cout<<dim<<endl;
	if(dim==0||find_var(name).type!="para") base=find_var(name).base;
	else
	{
		base=0;
		midcode[++mid_cnt]={"lw",13,find_var(name).base*4,30};
		midcode[++mid_cnt]={"inttoreg",tem,14};
		midcode[++mid_cnt]={"add",13,13,14};
		midcode[++mid_cnt]={"sub",13,13,30};
		midcode[++mid_cnt]={"regtoint",13,tem};
	}
}



//Exp → AddExp
void Exp()
{
	AddExp();
}
void Exp(int &b)
{
	AddExp(b);
}
void Exp(int a,int _)
{
	AddExp(a,0);
}
//ConstExp → AddExp
void ConstExp()
{
	AddExp();
}
void ConstExp(int &b)
{
	AddExp(b);
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
		int b=++tem_cnt;
		MulExp(b,0);
		midcode[++mid_cnt]={op,a,a,b};
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
		int b=++tem_cnt;
		UnaryExp(b,0);
		midcode[++mid_cnt]={op,a,a,b};
	}
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
	else if(sym=="IDENFR"&&nextsym(1)=="(")
	{
		getsym(); // Ident
		getsym(); // (
		if(str!=")") FuncRParams();
		getsym(); // )
	}
	else PrimaryExp(b);
}
void UnaryExp(int a,int _)
{
	string op=str;
	if(UnaryOp())
	{
		UnaryExp(a,0);
		midcode[++mid_cnt]={op,a,0,a};
	}
	else if(sym=="IDENFR"&&nextsym(1)=="(")
	{
		string name=str;
		getsym(); // Ident
		getsym(); // (
		if(str!=")") FuncRParams(find_var(name).base+1);     //函数的base实际上存储的是var_cnt 
		getsym(); // )
		midcode[++mid_cnt]={"jal",find_var(name).second};     // second实际上存储开始标签 
		midcode[++mid_cnt]={"regtoint",25,a};
	}
	else PrimaryExp(a,0);
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
void FuncRPara(int nowvar_cnt,int a);
void FuncRParams(int beginvar_cnt)
{
	int j=0,a[5];
	a[j]=++tem_cnt;
	FuncRPara(beginvar_cnt,a[j]);
	j++;
	while(str==",")
	{
		getsym(",");
		a[j]=++tem_cnt;
		FuncRPara(beginvar_cnt+j,a[j]);
		j++;
	}
	for(int i=0;i<j;i++) midcode[++mid_cnt]={"inttoreg",a[i],i+4};
}
// 传参 
void FuncRPara(int nowvar_cnt,int a)
{
	if(var[nowvar_cnt].dim!=0)
	{
		string name=str;
		Ident();
		int firsttem,dim=0;
		if(str=="[")
		{
			dim=1;
			getsym("[");
			firsttem=++tem_cnt;
			Exp(firsttem,0);
			getsym("]");
		}
		if(find_var(name).type=="para")  //若为从参数1传参数2，参数1维度一定大于等于2,因此参数1一定为地址 
		{
			if(dim==0)
			{
				midcode[++mid_cnt]={"lw",9,find_var(name).base*4,30};
				midcode[++mid_cnt]={"regtoint",9,a};
			}
			else
			{
				midcode[++mid_cnt]={"*const",firsttem,firsttem,find_var(name).second*4};
				midcode[++mid_cnt]={"inttoreg",firsttem,10};
				midcode[++mid_cnt]={"lw",9,find_var(name).base*4,30};
				midcode[++mid_cnt]={"add",9,9,10};
				midcode[++mid_cnt]={"regtoint",9,a};
			}
		}
		else
		{
			if(dim==0)
			{
				midcode[++mid_cnt]={"li",9,find_var(name).base};
				midcode[++mid_cnt]={"sll",9,9,2};
				midcode[++mid_cnt]={"add",9,9,30};
				midcode[++mid_cnt]={"regtoint",9,a};
			}
			else
			{
				midcode[++mid_cnt]={"*const",firsttem,firsttem,find_var(name).second*4};   //有多余步数但先不考虑
				midcode[++mid_cnt]={"inttoreg",firsttem,9};
				midcode[++mid_cnt]={"addi",9,9,find_var(name).base*4};
				midcode[++mid_cnt]={"add",9,9,30};
				midcode[++mid_cnt]={"regtoint",9,a};
			}
		}
	}
	else Exp(a,0);
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
		Exp(a,0);
		getsym(")");
	}
	else if(str[0]>='0'&&str[0]<='9') Number(a,0);
	else LVal(a,0);
}
//Number → IntConst
void Number()
{
	IntConst();
}
void Number(int &b)
{
	IntConst(b);
}
void Number(int a,int _)
{
	IntConst(a,0);
}
// IntConst
void IntConst()
{
	getsym();
}
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
	midcode[++mid_cnt]={"int=const",a,b,0};
	getsym();
}





//Cond → LOrExp
void Cond()
{
	LOrExp();
}
void Cond(int a,int if_label)
{
	LOrExp(a,if_label);
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
void LOrExp(int a,int if_label)
{
	int else_label=++label;
	LAndExp(a,else_label);
	midcode[++mid_cnt]={"jump",if_label};
	midcode[++mid_cnt]={"label",else_label};
	while(str=="||")
	{
		getsym(); // ||
		else_label=++label;
		LAndExp(a,else_label);
		midcode[++mid_cnt]={"jump",if_label};
		midcode[++mid_cnt]={"label",else_label};
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
void LAndExp(int a,int else_label)
{
	EqExp(a,0);
	midcode[++mid_cnt]={"beqz",a,else_label};
	while(str=="&&")
	{
		getsym();  // &&
		EqExp(a,0);
		midcode[++mid_cnt]={"beqz",a,else_label};
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
void EqExp(int a,int _)
{
	RelExp(a,0);
	while(str=="=="||str=="!=")
	{
		string op=str;
		getsym();  // == !=
		int b=++tem_cnt;
		RelExp(b,0);
		midcode[++mid_cnt]={op,a,a,b};
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
void RelExp(int a,int _)
{
	AddExp(a,0);
	while(str=="<"||str==">"||str=="<="||str==">=")
	{
		string op=str;
		getsym();   //  <  >  <=  =>
		int b=++tem_cnt;
		AddExp(b,0);
		midcode[++mid_cnt]={op,a,a,b};
	}
}
/*void RelExp(int a,int _)
{
	AddExp(a,0);
	while(str=="<"||str==">"||str=="<="||str==">=")
	{ 
		getsym();   //  <  >  <=  =>
		AddExp();
	}
}*/

int tem_data[1000010],strdata=50000;
int data_base=0,data_reg=30;
void load(int tem,int reg)
{
	printf("lw $%d %d($30)\n",reg,((tem+data+strdata)<<2)+data_base);
}
void store(int tem,int reg)
{
	printf("sw $%d %d($30)\n",reg,((tem+data+strdata)<<2)+data_base);
}
void printmipscode()
{
	printf(".data\n");
	printf("a:.space 2000000\n");
	for(int i=1;i<=str_cnt;i++)
		cout<<"str_"<<i<<":.asciiz \""<<strtab[i]<<"\"\n";
	printf("\n");
	printf(".text\n");
	printf("la $30 a\n\n");
	for(int i=1;i<=mid_cnt;i++)
	{
		//cout<<midcode[i].op<<" "<<midcode[i].x<<" "<<midcode[i].y<<" "<<midcode[i].z<<endl;
		
		string op=midcode[i].op;
		int x=midcode[i].x,y=midcode[i].y,z=midcode[i].z;
		
		if(op=="data=const") //printf("data%d = %d",x,y);
		{
			printf("li $9 %d\n",y);
			printf("sw $9 %d($30)\n",(x<<2)+data_base);
		}
		else if(op=="storeword") //printf("storeword x%d %d(x%d)",x,y,z);
		{
			load(x,9);
			load(z,10);
			printf("sll $10 $10 2\n");
			printf("add $10 $10 $30\n");
			printf("sw $9 %d($10)\n",(y<<2)+data_base);
		}
		else if(op=="storeword_zalridy*4") //printf("storeword x%d %d(x%d)",x,y,z);
		{
			load(x,9);
			load(z,10);
			printf("add $10 $10 $30\n");
			printf("sw $9 %d($10)\n",(y<<2)+data_base);
		}
		else if(op=="loadword") //printf("loadword x%d %d(x%d)",x,y,z);		
		{
			load(z,10);
			printf("sll $10 $10 2\n");
			printf("add $10 $10 $30\n");
			printf("lw $9 %d($10)\n",(y<<2)+data_base);
			store(x,9);		
		}
		else if(op=="straightloadword")
		{
			load(y,9);
			printf("lw $10 0($9)\n");
			store(x,10);
		}
		else if(op=="return_int") printf("return x%d",x);
		else if(op=="return") printf("return");
		else if(op=="read_in_data") //printf("read in %d(x%d)",x,y);   Xy已经乘4 
		{
			printf("li $v0 5\n");
			printf("syscall\n");
			load(y,9);
			//printf("sll $9 $9 2\n");
			printf("add $9 $9 $30\n");
			printf("sw $v0 %d($9)\n",(x<<2)+data_base);
		}
		else if(op=="*const") //printf("x%d = x%d * %d",x,y,z);
		{
			printf("li $v0 %d\n",z);
			//load(x,9);
			load(y,9);
			printf("mult $9 $v0\n");
			printf("mflo $10\n");
			store(x,10);
		}
		else if(op=="int=const") //printf("x%d = %d",x,y);
		{
			printf("li $9 %d\n",y);
			store(x,9);
		}
		else if(op=="label") printf("label_%d:\n",x);
		else if(op=="jump") printf("j label_%d\n",x);
		else if(op=="beqz") //printf("beqz x%d label%d",x,y);
		{
			load(x,9);
			printf("beqz $9 label_%d\n",y);
		}
		else if(op=="printint")
		{
			printf("li $v0 1\n");
			load(x,4);
			printf("syscall\n");
		}
		else if(op=="printstr")
		{
			printf("li $v0 4\n");
			printf("la $4 str_%d\n",x);
			printf("syscall\n");
		}
		else if(op=="push$ra")
		{
			printf("sw $ra 0($sp)\n");
			printf("subi $sp $sp 4\n");
		}
		else if(op=="pop$ra")
		{
			printf("addi $sp $sp 4\n");
			printf("lw $ra 0($sp)\n");
		}
		else if(op=="pushtem")
		{
			load(x,9);
			printf("sw $9 0($sp)\n");
			printf("subi $sp $sp 4\n");
		}
		else if(op=="poptem")
		{
			printf("addi $sp $sp 4\n");		
			printf("lw $9 0($sp)\n");				
			store(x,9);
		}	
		else if(op=="pushdata")
		{
			printf("lw $9 %d($30)\n",(x<<2)+data_base);
			printf("sw $9 0($sp)\n");
			printf("subi $sp $sp 4\n");
		}
		else if(op=="popdata")
		{
			printf("addi $sp $sp 4\n");
			printf("lw $9 0($sp)\n");
			printf("sw $9 %d($30)\n",(x<<2)+data_base);
		}	
		else if(op=="outpara")
		{
			printf("sw $%d %d($30)\n",x,(y<<2)+data_base);
		}
		else if(op=="jump_$ra")
		{
			printf("jr $ra\n");
		}
		else if(op=="inttoreg")
		{
			load(x,y);
		}
		else if(op=="regtoint")
		{
			store(y,x);
		}
		else if(op=="inparaaddr")
		{
			if(z!=0)
			{
				load(z,9);
				printf("li $%d %d\n",x,y);
				printf("add $%d $%d $9\n",x,x);
				printf("sll $%d $%d 2\n",x,x);
				printf("add $%d $%d $30\n",x,x);
			}
			else
			{
				printf("li $%d %d\n",x,y);
				printf("sll $%d $%d 2\n",x,x);
				printf("add $%d $%d $30\n",x,x);
			}
			//printf("END\n\n\n\n");
		}
		else if(op=="inpara")
		{
			load(y,9);
			printf("move $%d $9\n",x);
		}
		else if(op=="labelmain") printf("\nmain:\n");
		else if(op=="jmain") printf("j main\n");
		else if(op=="jal") printf("jal label_%d\n",x);
		else if(op=="load") load(x,y);    // = inttoreg
		else if(op=="lw") printf("lw $%d %d($%d)\n",x,y,z);
		else if(op=="add") printf("add $%d $%d $%d\n",x,y,z);
		else if(op=="sub") printf("sub $%d $%d $%d\n",x,y,z);	
		else if(op=="addi") printf("addi $%d $%d %d\n",x,y,z);
		else if(op=="sll") printf("sll $%d $%d %d\n",x,y,z);
		else if(op=="li") printf("li $%d %d\n",x,y);
		else if(op=="END")
		{
			printf("li $v0 10\n");
			printf("syscall\n");
		}
		else //cout<<"x"<<x<<" = x"<<y<<" "<<op<<" x"<<z;
		{
			load(y,10);
			load(z,11);
			if(op=="+") printf("add $9 $10 $11\n");
			else if(op=="-") printf("sub $9 $10 $11\n");
			else if(op=="*")
			{
				printf("mult $10 $11\n");
				printf("mflo $9\n");
			}
			else if(op=="/")
			{
				printf("div $10 $11\n");
				printf("mflo $9\n");
			}
			else if(op=="%")
			{
				printf("div $10 $11\n");
				printf("mfhi $9\n");
			}
			else if(op==">")
			{
				printf("slt $9 $11 $10\n");
			}
			else if(op=="<")
			{
				printf("slt $9 $10 $11\n");
			}
			else if(op=="<=")
			{
				printf("slt $9 $11 $10\n");
				printf("xori $9 $9 1\n");	
			}
			else if(op==">=")
			{
				printf("slt $9 $10 $11\n");
				printf("xori $9 $9 1\n");	
			}
			else if(op=="=="||op=="!")
			{
				printf("slt $9 $10 $11\n");
				printf("slt $12 $11 $10\n");
				printf("or $9 $9 $12\n");
				printf("xori $9 $9 1\n");	
			}
			else if(op=="!=")
			{
				printf("slt $9 $10 $11\n");
				printf("slt $12 $11 $10\n");
				printf("or $9 $9 $12\n");
			}
			else cout<<"BUG!"<<" "<<op<<endl;
			store(x,9);
		}
		//printf("\n");
		//printf("\n");
	}
}

void printmidcode()
{
	for(int i=1;i<=mid_cnt;i++)
	{
		string op=midcode[i].op;
		int x=midcode[i].x,y=midcode[i].y,z=midcode[i].z;
		
		if(op=="data=const") printf("data%d = %d",x,y);
		else if(op=="storeword") printf("storeword x%d %d(x%d)",x,y,z);
		else if(op=="loadword") printf("loadword x%d %d(x%d)",x,y,z);		
		else if(op=="return_int") printf("return x%d",x);
		else if(op=="return") printf("return");
		else if(op=="read_in_data") printf("read in %d(x%d)",x,y);
		else if(op=="*const") printf("x%d = x%d * %d",x,y,z);
		else if(op=="int=const") printf("x%d = %d",x,y);
		else if(op=="label") printf("label_%d:",x);
		else if(op=="jump") printf("j label_%d",x);
		else if(op=="beqz") printf("beqz x%d label_%d",x,y);
		else cout<<"x"<<x<<" = x"<<y<<" "<<op<<" x"<<z;
		printf("\n");
	}
}

int main()
{
	init();
	getsym();
	CompUnit();
//	printmidcode();
	printmipscode();
	return 0;
} 
