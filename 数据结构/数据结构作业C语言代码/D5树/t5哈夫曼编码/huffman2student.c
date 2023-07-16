//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
FILE *Src, *Obj;
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码
void atoHZIP(); 				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();					//输出步骤1的结果
void print2(struct tnode *p);	//输出步骤2的结果 
void print3();					//输出步骤3的结果
void print4();					//输出步骤4的结果

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//输入当前实验步骤 
	
	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	(Step==1) ? print1(): 1; 			//输出实验步骤1结果	
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	(Step==2) ? print2(Root): 2; 		//输出实验步骤2结果	
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
	(Step==3) ? print3(): 3; 			//输出实验步骤3结果
	(Step>=4) ? atoHZIP(),print4(): 4; 	//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//【实验步骤1】开始 

void statCount()
{
	char s[100010];
	Ccount[0]=1;
	while(fgets(s,100000,Src)!=NULL)
	{
		int n=strlen(s),i;
		for(i=0;i<n;i++)
			if(s[i]!='\n') Ccount[s[i]]++;
	}
}

//【实验步骤1】结束

//【实验步骤2】开始
int cmp(struct tnode *a,struct tnode *b)
{
	if(a->weight<b->weight||a->weight==b->weight&&a->c<b->c) return -1;
	return 1;
}

void createHTree()
{
	//printf("Begin\n");
	int i,cnt=0;
	struct tnode *F[10010],*t;
	for(i=0;i<128;i++)
	{
		if(Ccount[i]>0)
		{	
			struct tnode *p=(struct tnode*)malloc(sizeof(struct tnode));
			p->c=i; p->weight=Ccount[i];
			p->left=p->right=NULL;
			F[++cnt]=p;    //add p into F;
		}
	}
	int j;
	for(i=1;i<=cnt;i++)
		for(j=i+1;j<=cnt;j++)
			if(cmp(F[i],F[j])==1)
			{
				t=F[i];
				F[i]=F[j];
				F[j]=t;
			}
	//printf("%d\n",cnt);
	for(;cnt>=2;cnt--)
	{
		struct tnode *T1=F[1],*T2=F[2];
		struct tnode *T=(struct tnode*)malloc(sizeof(struct tnode));
		//printf("%d %d\n",T1->weight,T2->weight);
		T->weight=T1->weight+T2->weight;
		//printf("%d\n",T->weight);
		//printf("%d\n",cnt);
		T->left=T1; T->right=T2;
		int m=0,flag=0;
		for(i=3;i<=cnt;i++)
		{
			if(!flag&&T->weight<F[i]->weight)
			{
				flag=1;
				F[++m]=T;
			}
			F[++m]=F[i];
		}
		if(!flag) F[++m]=T;
		//printf("%d\n",flag);
	}
	Root=F[1];
}

//【实验步骤2】结束

//【实验步骤3】开始

char Hc[32];
void mk(struct tnode *t,int m)
{
	if(t->left==NULL)
	{
		int i;
		for(i=0;i<m;i++) HCode[t->c][i]=Hc[i];
		HCode[t->c][m]='\0';
		return;
	}
	Hc[m]='0';
	mk(t->left,m+1);
	Hc[m]='1';
	mk(t->right,m+1);
}

void makeHCode()
{
	mk(Root,0);
} 

//【实验步骤3】结束

//【实验步骤4】开始

void atoHZIP()
{
	FILE *fp=fopen("input.txt","r");
	char s[1000010];
	int n=fread(s,1,1000000,fp);
	//printf("%s",HCode[s[n]]);
	//printf("%s",s);
	int i,j,sz=0;
	char to[1000010];
	for(i=0;i<=n;i++)
	{
		if(s[i]=='\n') continue;
		for(j=0;HCode[s[i]][j]!='\0';j++) to[sz++]=HCode[s[i]][j];
	}
	//printf("%d\n",sz);
	unsigned char hc=0;
	for(i=0;i<sz;i++)
	{
	    hc=(hc<<1)|(to[i]-'0');
	    //printf("  %c\n",to[i]);
		if((i+1)%8==0)
		{
			fputc(hc,Obj);     //输出到目标（压缩）文件中
			printf("%x",hc);   //按十六进制输出到屏幕上
			//printf("%d\n",hc);
			hc=0;
		}
	}
	if(i%8!=0)
	{
		while(i%8!=0)
		{
			hc<<=1;
			i++;
		}
		fputc(hc,Obj);
		printf("%x",hc);
	}
}

//【实验步骤4】结束

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\n原文件大小：%ldB\n",in_size);
	printf("压缩后文件大小：%ldB\n",out_size);
	printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
