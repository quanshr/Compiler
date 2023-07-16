#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ull unsigned long long
int n,N,i,j,m,mm,cnt,t,ts,vis[5000010],nw=1;
ull word[100010],x,dic[5000010],p=107;
char s[10000010],ss[100010][110];
int _s[10000010];
FILE *stream;
int tnd[100010],tnkd[100010][110],dnk[100010];
double tfkd[100010][110],idfk[110],simd[100010],lg=log(10);
int cmpull(const void *a, const void *b)
{
	ull aa=*(ull*)a,bb=*(ull*)b;
	if(aa>bb) return 1;
	if(aa<bb) return -1;
	return 0;
}
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
	gets(_s);
	printf("%d\n%s",strlen(_s),_s);
	printf("\n%d",'-');
	return 0;
}
