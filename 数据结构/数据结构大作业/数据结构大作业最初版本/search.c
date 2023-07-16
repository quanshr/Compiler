#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define N1 1000
#define N2 10000
#define N4 100000000
const float eps=0.000001;
int TNkd[N1][N2],TNd[N2],DNk[N1],anum,wnum=2;
char id[N2][50];
float IDFk[N1];
struct Ap
{
	float Simd;
	int cnt;
}ap[N2];

unsigned char buf[N4];
FILE *fp;
int i,j,k;
int flen,N;
typedef struct Trie
{
	unsigned char cnt,v,end,ava[26];
	struct Trie *up,*down[26];
}trie;
trie root;
trie *p,*q;

int cmp(const void *a,const void *b)
{
	struct Ap *c=(struct Ap*)a,*d=(struct Ap*)b;
	if(eps<d->Simd-c->Simd)	return 1;
	if(c->Simd-d->Simd>eps)	return -1;
	if(c->cnt>d->cnt)	return 1;
	if(c->cnt<d->cnt)	return -1;
	return 0;
}
int main(int argc,char** argv)
{	
	fp=fopen("dictionary.txt","r");
	flen=fread(buf,1,N4,fp);
	fclose(fp);
	buf[flen++]=0;
	p=&root;
	for(i=0,j=0,k;i<flen;i++)
	{
		if(buf[i]<=122&&buf[i]>=97)
		{
			if(!j)	j=1;
			k=buf[i]-97;
			if(!p->ava[k])
			{
				p->down[k]=(trie*)malloc(sizeof(trie));
				p->ava[k]=1;
				p->cnt++;
				p->down[k]->up=p;
				p=p->down[k];
				p->v=k;
				p->end=0;
				p->cnt=0;
				memset(p->ava,0,26);
			}
			else	p=p->down[k];
		}
		else if(j)
		{
			p->end=1;
			p=&root;
			j=0;
		}
	}
	
	fp=fopen("stopwords.txt","r");
	flen=fread(buf,1,N4,fp);
	fclose(fp);
	buf[flen++]=0;
	p=&root;
	for(i=0,j=0,k;i<flen;i++)
	{
		if(buf[i]<=122&&buf[i]>=97)
		{
			if(!j)	j=1;
			k=buf[i]-97;
			if(!p->ava[k])
			{
				for(;buf[i]<=122&&buf[i]>=97&&i<flen;i++);
				j=0;
				p=&root;
				i--;
			}
			else	p=p->down[k];
		}
		else if(buf[i]<=90&&buf[i]>=65)
		{
			if(!j)	j=1;
			k=buf[i]-65;
			if(!p->ava[k])
			{
				for(;buf[i]<=90&&buf[i]>=65&&i<flen;i++);
				j=0;
				p=&root;
				i--;
			}
			else	p=p->down[k];
		}
		else if(j)
		{
			if(p->end)
			{
				p->end=0;
				while(p->end==0&&p->cnt==0)
				{
					q=p;
					p=p->up;
					p->ava[q->v]=0;
					p->cnt--;
					free(q);
				}
			}
			p=&root;
			j=0;
		}
	}
	
	k=strlen(argv[1]);
	for(i=0;i<k;i++) N=N*10+argv[1][i]-'0';
	for(i=2;i<argc;i++)
	{
		p=&root;
		for(j=0,k;argv[i][j];j++)
		{
			k=argv[i][j]>96?argv[i][j]-97:argv[i][j]-65;
			if(!p->ava[k])	break;
			p=p->down[k];
		}
		if(p->end&&!argv[i][j])	p->end=wnum++;
	}
	
	fp=fopen("article.txt","r");
	flen=fread(buf,1,N4,fp);
		printf("%d\n",flen);
	fclose(fp);
	buf[flen++]=0;
	p=&root;
	
	i=0;j=0;
	while(i<flen)
	{
		for(;buf[i]<33||buf[i]>126;i++);
		for(k=0;buf[i]!='\r'&&buf[i]!='\n';i++,k++)	id[anum][k]=buf[i];
		//printf("%d:%s\n",anum,id[anum]);
		for(;buf[i]!=12&&i<flen;i++)
		{
			if(buf[i]<=122&&buf[i]>=97)
			{
				if(!j)	j=1;
				k=buf[i]-97;
				if(!p->ava[k])
				{
					for(;((buf[i]<=122&&buf[i]>=97)||(buf[i]<=90&&buf[i]>=65))&&i<flen;i++);
					j=0;
					p=&root;
					i--;
				}
				else	p=p->down[k];
			}
			else if(buf[i]<=90&&buf[i]>=65)
			{
				if(!j)	j=1;
				k=buf[i]-65;
				if(!p->ava[k])
				{
					for(;((buf[i]<=122&&buf[i]>=97)||(buf[i]<=90&&buf[i]>=65))&&i<flen;i++);
					j=0;
					p=&root;
					i--;
				}
				else	p=p->down[k];
			}
			else if(j)
			{
				if(p->end)
				{
					TNd[anum]++;
					if(p->end>1)	TNkd[p->end][anum]++;
				}
				p=&root;
				j=0;
			}
		}
		for(k=2;k<wnum;k++)	if(TNkd[k][anum])	DNk[k]++;
		anum++;
	}
//	printf("%d\n",anum);
	double danum=anum;
	for(j=2;j<wnum;j++)	IDFk[j]=DNk[j]?log10(danum/DNk[j]):0;
	//for(j=2;j<wnum;j++)	printf("%d\n",TNkd[j][23]);
	for(i=0;i<anum;i++)
	{
		for(j=2;j<wnum;j++)	ap[i].Simd+=IDFk[j]*TNkd[j][i];
		ap[i].Simd=ap[i].Simd*100/TNd[i];
		ap[i].cnt=i;
	}
	qsort(ap,anum,sizeof(struct Ap),cmp);
	for(i=0;i<5&&i<anum&&ap[i].Simd>=eps;i++)	printf("%.6f %d %s\n",ap[i].Simd,ap[i].cnt+1,id[ap[i].cnt]);
	fp=fopen("results.txt","w");
	for(i=0;i<N&&i<anum&&ap[i].Simd>=eps;i++)	fprintf(fp,"%.6f %d %s\n",ap[i].Simd,ap[i].cnt+1,id[ap[i].cnt]);
	fclose(fp);
	//for(i=0;i<anum;i++)	printf("TNd:%d\n",TNd[i]);
	//for(i=2;i<wnum;i++)	printf("DNk:%d\n",DNk[i]);
	//system("pause");
	return 0;
}
