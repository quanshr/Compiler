#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define N1 16
#define N2 65536
#define N3 1130000
#define N4 40000000
#define N5 5000000
#define N6 100000
#define eps 0.000001
unsigned short TNkd[N1][N2],TNd[N2],DNk[N1];
unsigned short anum,wnum=2;
char id[N2][50];
double IDFk[N1];

/*typedef struct Node
{
	int v[26];
	unsigned char end;
}node;
node e[N3];*/
unsigned char end[N3];
int v[N3][26];

int p,cnt=1;

struct Ap
{
	double Simd;//int+0.5
	unsigned short cnt;
}ap[N2];

unsigned char buf[N4];
FILE *fp;
int i,j,k;
int flen,N;

int cmp(const void *a,const void *b)
{
	if((((struct Ap*)b)->Simd)-(((struct Ap*)a)->Simd)>eps)	return 1;
	if((((struct Ap*)a)->Simd)-(((struct Ap*)b)->Simd)>eps)	return -1;
	if((((struct Ap*)a)->cnt)>(((struct Ap*)b)->cnt))	return 1;
	if((((struct Ap*)a)->cnt)<(((struct Ap*)b)->cnt))	return -1;
	return 0;
}
void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

int f1[127];
inline void ini()
{
	for(i=0;i<26;++i)	f1[i+'a']=f1[i+'A']=i;
}
int main(int argc,char** argv)
{	
	ini();
	
	fp=fopen("dictionary.txt","r");
	flen=fread(buf,1,N5,fp);
	i=0;
	while(i<flen)
	{
		p=1;
		for(;buf[i]<123&&buf[i]>96;++i)
		{
			if(!v[p][f1[buf[i]]])	v[p][f1[buf[i]]]=++cnt;
			p=v[p][f1[buf[i]]];
		}
		end[p]=1;
		++i;
	}
	
	fp=fopen("stopwords.txt","r");
	flen=fread(buf,1,N6,fp);
	i=0;
	while(i<flen)
	{
		p=1;
		for(;buf[i]<123&&buf[i]>96;++i)	p=v[p][f1[buf[i]]];
		end[p]=0;
		++i;
	}
	
	k=strlen(argv[1]);
	for(i=0;i<k;++i) N=N*10+argv[1][i]-'0';
	for(i=2;i<argc;++i)
	{
		p=1;
		for(j=0;argv[i][j];++j)	p=v[p][f1[argv[i][j]]];
		if(end[p])	end[p]=wnum++;
	}
	
	fp=fopen("article.txt","r");
	flen=fread(buf,1,N4,fp);
	buf[flen]=12;
	
	i=0; 
	while(i<flen)
	{
		for(;buf[i]<33||buf[i]>126;++i);
		for(k=0;buf[i]!='\r'&&buf[i]!='\n';++i,++k)	id[anum][k]=buf[i];
		while(buf[i]!=12)
		{
			p=1;
			for(;(buf[i]<123&&buf[i]>96)||(buf[i]<91&&buf[i]>64);++i)	p=v[p][f1[buf[i]]];
			if(end[p])
			{
				++TNd[anum];
				if(end[p]>1)	++TNkd[end[p]][anum];
			}
			p=1;
			for(;(buf[i]<65||(buf[i]>90&&buf[i]<97)||buf[i]>122)&&buf[i]!=12;++i);
		}
		for(k=2;k<wnum;++k)	if(TNkd[k][anum])	++DNk[k];
		++anum;
	}
	
	double danum=anum,sigma;
	for(j=2;j<wnum;++j)	if(DNk[j])	IDFk[j]=log10(danum/DNk[j]);
	for(i=0;i<anum;++i)//int+0.5
	{
		sigma=0;
		for(j=2;j<wnum;++j)	sigma+=IDFk[j]*TNkd[j][i];
		ap[i].Simd=sigma*100/TNd[i];
		ap[i].cnt=i;
	}
	qsort(ap,anum,sizeof(struct Ap),cmp);
		printf("%d %d\n",anum,wnum);
		for(j=2;j<wnum;++j) printf("%d ",DNk[j]);
	freopen("results.txt","w",stdout);
	for(i=0,j;i<N&&i<anum&&ap[i].Simd>=eps;++i)
	{
		/*ap[i].Simd+=5;
		j=ap[i].Simd/10000000;
		write(j);
		putchar('.');
		ap[i].Simd-=j*10000000;
		ap[i].Simd/=10;
		write(ap[i].Simd);*/
		printf("%.6lf %d %s\n",ap[i].Simd,ap[i].cnt+1,id[ap[i].cnt]);
	}
	return 0;
}
