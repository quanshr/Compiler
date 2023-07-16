//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

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
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	(Step==1) ? print1(): 1; 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	(Step==2) ? print2(Root): 2; 		//���ʵ�鲽��2���	
	makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	(Step==3) ? print3(): 3; 			//���ʵ�鲽��3���
	(Step>=4) ? atoHZIP(),print4(): 4; 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 

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

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ
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

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

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

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ

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
			fputc(hc,Obj);     //�����Ŀ�꣨ѹ�����ļ���
			printf("%x",hc);   //��ʮ�������������Ļ��
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

//��ʵ�鲽��4������

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
	
	printf("\nԭ�ļ���С��%ldB\n",in_size);
	printf("ѹ�����ļ���С��%ldB\n",out_size);
	printf("ѹ���ʣ�%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
