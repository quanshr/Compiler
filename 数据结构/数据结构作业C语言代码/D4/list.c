#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *link;
}Node,*Nodeptr;
int n,m,q,i;
void josephu(int n,int m,int k)
{
	Nodeptr list,p,r,q;
	int i;
	list=NULL;
	for(i=1;i<=n;i++)
	{
		r=(Nodeptr)malloc(sizeof(Node));
		r->data=i;
		if(list==NULL) list=p=r;
		else
		{
			p->link=r;
			p=p->link;
		}
	}
	p->link=list;
	for(p=list,i=0;i<n+k-2;i++,r=p,p=p->link);
	//printf("%d\n",p->data);
	int count=0;
	while(p!=p->link)
	{
		if(count==m)
		{
			q->link=p->link;
			//printf("%d\n",p->data);
			//p->link;
			r=p->link;
			free(p);
			p=r;
			count=1;
		}
		else
		{
			count++;
			q=p;
			p=p->link;
		}
	}
	printf("%d",p->data);
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	josephu(n,m,q);
	
	return 0;
}
