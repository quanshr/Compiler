#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ull unsigned long long

FILE *fp;
int n,m[110],i,j,x,y,z[110],t,w;
char to[110][40][30],SS[30],TT[30],cc[10010][30];
int top[110][40],S,T;
ull b[10010];
ull hash(char c[])
{
	int i;
	ull x=1;
	for(i=0;c[i]!='\0';i++)
		x=x*233+c[i]-'a'+1;
	return x;
}
int getp(char c[])
{
	ull x=hash(c);
	int i;
	for(i=1;i<=t;i++)
		if(b[i]==x) return i;
}
int a[510][510];
int route[1010],cnt;

int main()
{
	fp=fopen("bgstations.txt","r");
	fscanf(fp,"%d",&n);
	for(i=1;i<=n;i++)
	{
		fscanf(fp,"%d%d",&z[i],&m[i]);
		for(j=1;j<=m[i];j++)
		{
			fscanf(fp,"%s%d",to[i][j],&x);
			//printf("%s %d\n",to[i][j],strlen(to[i][j]));
			b[++t]=hash(to[i][j]);
			for(w=0;w<=25;w++) cc[t][w]=to[i][j][w];
		}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m[i];j++) top[i][j]=getp(to[i][j]);
		for(j=1;j<m[i];j++)
			a[top[i][j]][top[i][j+1]]=a[top[i][j+1]][top[i][j]]=z[i];
	}
	scanf("%s%s",SS,TT);
	//printf("%s\n%s\n",SS,TT);
	S=getp(SS); T=getp(TT);
	int q[1010],l,r,v[1010];
	q[l=r=1]=T;
	for(i=1;i<=t;i++) v[i]=0;
	v[T]=T;
	while(l<=r)
	{
		x=q[l++];
		for(i=1;i<=t;i++)
			if(a[x][i]&&!v[i])
			{
				v[i]=x;
				q[++r]=i;		
			}
	}
	int u=0,from=S;
	printf("%s",cc[S]);
	for(i=v[S];;i=v[i])
	{
		u++;
		if(i==T||a[from][i]!=a[i][v[i]])
		{
			printf("-%d(%d)-%s",a[from][i],u,cc[i]);
			u=0;
		}
		from=i;
		//printf("%s\n",cc[i]);
		if(i==T) break;
	}
	return 0;
}
