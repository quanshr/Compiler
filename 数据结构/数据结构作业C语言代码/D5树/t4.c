#include <stdio.h>
#include <stdlib.h>

int n,x,y,i,j,k,cnt;
struct 
{
	int s[3];
}e[10010];
struct Node
{
	int x,p;
}node[10010];
int q[10010],l,r;
void bfs()
{
	q[l=r=1]=100;
	while(l<=r)
	{
		int x=q[l++],i=0;
		for(i=0;i<3;i++)
			if(e[x].s[i]) q[++r]=e[x].s[i];
	}
}
int cmp(const void *p1,const void *p2)
{
	struct Node a1=*((struct Node *)p1),a2=*((struct Node *)p2);
	if(a1.x>a2.x) return -1;
	if(a1.x<a2.x) return 1;
	if(a1.p<a2.p) return -1;
	return 1;
}

int main()
{
	while(scanf("%d",&x))
	{
		if(x==-1) break;
		i=0;
		while(scanf("%d",&y))
		{
			if(y==-1) break;
			e[x].s[i++]=y;
		}
	}
	cnt=0;
	while(scanf("%d%d",&x,&y)!=EOF)
	{
		node[++cnt].p=x;
		node[cnt].x=y;
	}
	bfs();
	qsort(node+1,cnt,sizeof(struct Node),cmp);
	//for(i=1;i<=cnt;i++) printf("%d %d %d\n",i,node[i].p,node[i].x);
	int j=1;
	for(i=1;i<=cnt;i++)
	{
		while(q[j]>=100) j++;
		printf("%d->%d\n",node[i].p,q[j]);
		j++;
	}
	return 0;
}
