#include <stdio.h>

int a[30][30],x[10]={0,1,1,1},y[10]={1,1,0,-1},m,xx,yy,b;
int i,j,k,l;

int main()
{
	for(i=0;i<=20;i++)
		for(j=0;j<=20;j++)
			a[i][j]=3;
	for(i=1;i<=19;i++)
		for(j=1;j<=19;j++)
			scanf("%d",&a[i][j]);
	for(i=1;i<=19;i++)
		for(j=1;j<=19;j++)
		{
			m=a[i][j];
			if(!m) continue;
			for(k=0;k<=3;k++)
			{
				xx=i; yy=j;
				for(l=1;l<=3;l++)
				{
					xx+=x[k]; yy+=y[k];
					if(a[xx][yy]!=m) goto aaa;
				}
				if(a[i-x[k]][j-y[k]]==0||a[xx+x[k]][yy+y[k]]==0)
				{
					printf("%d:%d,%d\n",m,i,j);
					return 0;
				}
				aaa:;
			}
		}
	printf("No\n");
	return 0;
}
