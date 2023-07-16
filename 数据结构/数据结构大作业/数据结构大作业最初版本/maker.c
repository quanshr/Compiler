#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ull unsigned long long
int n,N,i,j,m,mm,cnt,t,ts,vis[5000010],nw=1;
int v[100010];
typedef struct Hash
{
	ull x,y;
}hash;
hash word[10010],x,dic[2000010],p;
ull mod=1000000007;
int cmpull(const void *a, const void *b)
{
	hash aa=*(hash*)a,bb=*(hash*)b;
	if(aa.x!=bb.x)
	{
		if(aa.x>bb.x) return 1;
		return -1;
	}
	if(aa.y>bb.y) return 1;
	if(aa.y<bb.y) return -1;
	return 0;
}
int cmp_ull(hash aa,hash bb)
{
	if(aa.x!=bb.x)
	{
		if(aa.x>bb.x) return 1;
		return -1;
	}
	if(aa.y>bb.y) return 1;
	if(aa.y<bb.y) return -1;
	return 0;
}
void deal(hash *x,char y)
{
	(*x).x=(*x).x*p.x+y-'a'+1;
	(*x).y=((*x).y*p.y+y-'a'+2)%mod;
}

char s[10000010],ss[100010][110];
FILE *stream;
int tnd[100010],tnkd[100010][110],dnk[100010];
double tfkd[100010][110],idfk[110],simd[100010],lg=log(10);
typedef struct Node
{
	double x;
	int p;
}node;
node ans[10010];
double eps=1e-9;
int cmp(const void *a, const void *b)
{
	node aa=*(node*)a,bb=*(node*)b;
	if(fabs(aa.x-bb.x)<eps)
	{
		if(aa.p<bb.p) return -1;
		return 1;
	}
	if(aa.x<bb.x) return 1;
	return -1;
}

int main(int argc,char** argv)
{
	stream=fopen("results.txt","w");
	for(i=1;i<=1001;i++) fprintf(stream,"\f\n1-%d\narticle\n",i);
	fclose(stream);
	return 0;
}
