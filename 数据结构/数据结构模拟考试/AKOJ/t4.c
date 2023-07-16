#include <stdio.h>
#include <stdlib.h>
int read()
{
	int f=1,x=0; char ch=getchar();
	while(ch>'9'||ch<'0') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return f*x;
}

int i,j,n,m,cnt,op,x,y;
typedef struct
{
	int x,y,b;
}edxy;
edxy ed[10010];
int h[5010],t;
typedef struct
{
	int to,next;
}edxx;
edxx edge[10010];
void addedge1(int x,int y)
{
	edge[++t].to=y;
	edge[t].next=h[x];
	h[x]=t;
}
void addedge(int p)
{
	addedge1(ed[p].x,ed[p].y);
	addedge1(ed[p].y,ed[p].x);
}
int v[5010];
void dfs(int x)
{
	int i;
	for(i=h[x];i;i=edge[i].next)
	{
		int y=edge[i].to;
		if(!v[y])
		{
			v[y]=1;
			dfs(y);
		}
	}
}
int ans[5010],tot;
int s,mi;
void dfs2(int x)
{
	s++;
	int i;
	for(i=h[x];i;i=edge[i].next)
	{
		int y=edge[i].to;
		if(!v[y])
		{
			v[y]=1;
			dfs2(y);
		}
	}
}
int max(int a,int b)
{
	return a>b?a:b;
}
int min(int a,int b)
{
	return a<b?a:b;
}
int sz[5010],u[5010];
void dfs3(int x,int fa)
{
	int i;
	u[x]=0;
	sz[x]=1;
	for(i=h[x];i;i=edge[i].next)
	{
		int y=edge[i].to;
		if(y==fa) continue;
		dfs3(y,x);
		sz[x]+=sz[y];
		u[x]=max(u[x],sz[y]);
	}
	u[x]=max(u[x],s-sz[x]);
	mi=min(u[x],mi);
}
void dfs4(int x,int fa)
{
	int i;
	for(i=h[x];i;i=edge[i].next)
	{
		int y=edge[i].to;
		if(y==fa) continue;
		dfs4(y,x);
	}
	if(u[x]==mi) ans[++tot]=x;
}

int main()
{
	n=read(); m=read();
	for(i=1;i<n;i++)
	{
		ed[++cnt].x=read();
		ed[cnt].y=read();
		if(ed[cnt].x>ed[cnt].y)
		{
			int z=ed[cnt].x;
			ed[cnt].x=ed[cnt].y;
			ed[cnt].y=z;
		}
		addedge(cnt);
	}
	while(m--)
	{
		op=read(); x=read(); y=read();
		if(x>y)
		{
			int z=x;
			x=y;
			y=z;
		}
		if(op==1)
		{
			for(i=1;i<=n;i++) v[i]=0;
			v[x]=1;
			dfs(x);
			if(v[y]) printf("error\n");
			else
			{
				ed[++cnt].x=x; ed[cnt].y=y;
				addedge(cnt);
				printf("success\n");
			}
		}
		else
		{
			int ok=0;
			for(i=1;i<=cnt;i++)
				if(!ed[i].b&&ed[i].x==x&&ed[i].y==y)
				{
					ok=i;
					ed[i].b=1;
					break;
				}
			if(ok)
			{
				t=0;
				for(i=1;i<=n;i++) h[i]=0;
				for(i=1;i<=cnt;i++)
					if(!ed[i].b) addedge(i);
				printf("success\n");
			}
			else printf("error\n");
		}
		for(i=1;i<=n;i++) v[i]=0;
		tot=0;
		for(i=1;i<=n;i++)
		{
			if(!v[i])
			{
				s=0;
				v[i]=1;
				dfs2(i);
				mi=1e6;
				dfs3(i,i);
				dfs4(i,i);
				//printf("%d   %d   %d\n",i,s,mi);
			}
		}
		//printf("  ");
		for(i=1;i<=n;i++) v[i]=0;
		for(i=1;i<=tot;i++) v[ans[i]]=1;
		for(i=1;i<=n;i++) if(v[i]) printf("%d ",i);
		printf("\n");
	}
	return 0;
}
