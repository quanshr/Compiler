#include <stdio.h>
#include <stdlib.h>

FILE *fp;
int n,i,j,k,M,m;
typedef struct Node
{
	int num,p;
	char name[21];
}stu;
stu a[110],b[110][2],d[110];
int v[110],c[110];
int cmp(const void *_x,const void *_y)
{
	stu *x=(stu*)_x,*y=(stu*)_y;
	if(x->num>y->num) return 1;
	return -1;
}

int main()
{
	fp=fopen("in.txt","r");
	while(fscanf(fp,"%d%s%d",&a[n+1].num,a[n+1].name,&a[n+1].p)!=EOF)
	{
		n++;
		d[n]=a[n];
		//printf("%d",n);
	}
	for(i=1;i<=n;i++)
	{
		b[a[i].p][v[a[i].p]++]=a[i];
		if(a[i].p>M) M=a[i].p;
	}
	for(i=1;i<=100;i++)
		if(v[i]==2&&b[i][0].num>b[i][1].num)
		{
			stu x=b[i][0];
			b[i][0]=b[i][1];
			b[i][1]=x;
		}
	//if(M>n) M=n;
	j=100; k=v[j]-1;
	while(k<0)
	{
		j--;
		k=v[j]-1;
	}
	for(i=1;i<=j&&i<=n;i++)
	{
		if(!v[i])
		{
			b[i][v[i]++]=b[j][k--];
			b[i][v[i]].p=i;
			v[j]--;
			while(k<0)
			{
				j--;
				k=v[j]-1;
			}
		}
	}
	//for(i=1;i<=100;i++) v[i]+=c[i];
	for(i=1;i<=100;i++)
	{
		for(j=0;j<v[i];j++)
			printf("  %d %s %d\n",b[i][j].num,b[i][j].name,i);
	}
	m=100;
	while(!v[m]) m--;
	j=m+1;
	for(i=1;i<=m;i++)
		if(v[i]>1)
			b[j++][0]=b[i][1];
	for(i=1;i<=n;i++)
	{
		a[i]=b[i][0];
		a[i].p=i;
		printf(" %d %s %d\n",a[i].num,a[i].name,a[i].p);
	}
	qsort(a+1,n,sizeof(a[1]),cmp);
	fp=fopen("out.txt","w");
	for(i=1;i<=n;i++)
		fprintf(fp,"%d %s %d\n",a[i].num,a[i].name,a[i].p);
	return 0;
}
