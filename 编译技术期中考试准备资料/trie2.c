#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char map[127],s[50000010],end[1200010],id[70000][50];
int v[1200010][26],TNkd[20][70000],TNd[70000];
int i,j,k,p,n,cnt=1,N,sw,sa,DNk[200];
double IDFk[20],sum,eps=1e-8;
FILE *fp;
struct Node
{
	double Simd;
	unsigned short cnt;
}node[70000];
int cmp(const void *a,const void *b)
{	
	if((((struct Node*)a)->Simd)-(((struct Node*)b)->Simd)>eps)	return -1;
	if((((struct Node*)b)->Simd)-(((struct Node*)a)->Simd)>eps)	return 1;
	if((((struct Node*)a)->cnt)<(((struct Node*)b)->cnt))	return -1;
	return 1;
}

int main(int argc,char **argv)
{
	for(i=0;i<26;++i) map[i+'a']=map[i+'A']=i;
	fp=fopen("dictionary.txt","r");
	n=fread(s,1,50000000,fp);
	for(i=0;i<n;++i)
	{
		p=1;
		while(s[i]>96&&s[i]<123)
		{
			if(!v[p][map[s[i]]]) p=v[p][map[s[i++]]]=++cnt;
			else p=v[p][map[s[i++]]];
		}
		end[p]=19;
	}
	
	
	fp=fopen("stopwords.txt","r");
	n=fread(s,1,50000000,fp);
	for(i=0;i<n;++i)
	{
		p=1;
		while(s[i]>96&&s[i]<123) p=v[p][map[s[i++]]];
		end[p]=0;
	}
	
	for(i=0,k=strlen(argv[1]);i<k;++i) N=N*10+argv[1][i]-'0';
	for(i=2;i<argc;++i)
	{
		p=1;
		for(j=0;argv[i][j];++j) p=v[p][map[argv[i][j]]];
		if(end[p]) end[p]=++sw;
	}

	
	fp=fopen("article.txt","r");
	n=fread(s,1,50000000,fp);
	s[n]=12;
	i=0;
	while(i<n)
	{
		while(s[i]<33||s[i]>126) ++i;
		for(k=0;s[i]!='\r'&&s[i]!='\n';++i,++k)	id[sa][k]=s[i];
		while(s[i]!=12)
		{
			p=1;
			while((s[i]<123&&s[i]>96)||(s[i]<91&&s[i]>64)) p=v[p][map[s[i++]]];
			if(end[p])
			{
				++TNd[sa];
				++TNkd[end[p]][sa];
			}
			p=1;
			while((s[i]<65||(s[i]>90&&s[i]<97)||s[i]>122)&&s[i]!=12) ++i;
		}
		for(k=1;k<=sw;++k) if(TNkd[k][sa]) ++DNk[k];
		++sa;
	}

	double tot=sa;
	for(j=1;j<=sw;++j) if(DNk[j]) IDFk[j]=log10(tot/DNk[j]);
	for(i=0;i<sa;++i)
	{
		sum=0;
		for(j=1;j<=sw;++j) sum+=IDFk[j]*TNkd[j][i];
		node[i].Simd=sum*100/TNd[i];
		node[i].cnt=i;
	}
	qsort(node,sa,sizeof(struct Node),cmp);
	for(i=0;i<5&&i<sa&&node[i].Simd>eps;++i) printf("%.6lf %d %s\n",node[i].Simd,node[i].cnt+1,id[node[i].cnt]);	
	freopen("results.txt","w",stdout);
	for(i=0;i<N&&i<sa&&node[i].Simd>eps;++i) printf("%.6lf %d %s\n",node[i].Simd,node[i].cnt+1,id[node[i].cnt]);
		
	return 0;
}

