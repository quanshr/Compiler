#include <stdio.h>
#include <stdlib.h>

int n,i,j;
struct NODE
{
	int x1,y1,x2,y2,p;
}node[110];
int cmp(const void *p1,const void *p2)
{
	const struct NODE *a=(const struct NODE *)p1;
	const struct NODE *b=(const struct NODE *)p2;
	if(a->x1<b->x1) return -1;
	if(a->x1==b->x1) return 0;
	return 1; 
}
int belong[110],sz[110],mx;

int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&node[i].x1,&node[i].y1,&node[i].x2,&node[i].y2);
		node[i].p=i;
	}
	qsort(node+1,n,sizeof(struct NODE),cmp);
	for(i=1;i<=n;i++) belong[i]=i;
	for(i=1;i<=n;i++)
	{
		//printf("%d %d %d %d %d\n",node[i].x1,node[i].y1,node[i].x2,node[i].y2,node[i].p);
		for(j=1;j<i;j++)
			if(node[j].x2==node[i].x1&&node[j].y2==node[i].y1)
			{
				belong[i]=belong[j];
				sz[belong[j]]++;
				if(sz[belong[j]]>sz[mx])
					mx=belong[j];
			}
	}
	printf("%d %d %d",sz[mx]+1,node[mx].x1,node[mx].y1);
	return 0;
}
