#include <stdio.h>
#include <stdlib.h>
int read()
{
	int f=1,x=0; char ch=getchar();
	while(ch>'9'||ch<'0') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return f*x;
}

int i,j,n,m,M,a[10000010],b[10000010],front,rear,q[10000010],nw,ok;

int main()
{
	n=read(); m=read(); M=read();
	for(i=1;i<=n;i++) a[i]=read();
	if(n<=M)
	{
		while(m--)
		{
			ok=1;
			for(i=1;i<=n;i++)
			{
				b[i]=read();
				if(b[i]!=a[i]) ok=0;
			}
			if(ok) printf("Y\n");
			else printf("N\n");
		}
		return 0;
	}
	while(m--)
	{
		ok=1;
		for(i=1;i<=n;i++) b[i]=read();
		front=0; rear=-1;
		for(i=1;i<=M;i++) q[++rear]=a[i];
		nw=M;
		for(i=1;i<=n;i++)
		{
			while(q[front]!=b[i])
			{
				do
				{
					rear=(rear+1)%M;
					q[rear]=a[++nw];
					if(nw>n)
					{
						ok=0;
						goto aaa;
					}
				}while(rear!=front);
			}
			front=(front+1)%M;
		}
		aaa:;
		if(ok) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
