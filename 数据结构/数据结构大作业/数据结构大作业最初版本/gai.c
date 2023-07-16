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
	p.x=1007; p.y=107;
	int ii=strlen(argv[2]);
	for(i=0;i<ii;i++) N=N*10+argv[2][i]-'0';
	for(i=3;i<argc;i++)
	{
		int jj=strlen(argv[i]);
		for(j=0;j<jj;j++)
		{
			char ch=argv[i][j];
			if(argv[i][j]>='A'&&argv[i][j]<='Z') ch=ch-'A'+'a';
			deal(&word[i-2],ch);
		}
	}
	m=argc-3;
	stream=fopen("dictionary.txt","r");
	while(fscanf(stream,"%s",s)!=EOF)
	{
		n=strlen(s);
		if(n==0) break;
		for(i=0;i<=n;i++)
		{
			if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
			if(s[i]>='a'&&s[i]<='z') deal(&x,s[i]);
			else if(x.x||x.y)
			{
				dic[++t]=x;
				x.x=x.y=0;
			}
		}
	}
	qsort(dic+1,t,sizeof(hash),cmpull);
	//printf("%d\n",t);
	//for(i=1;i<=t;i++) printf("%llu %llu\n",dic[i].x,dic[i].y);
	
	stream=fopen("stopwords.txt","r");
	while(fscanf(stream,"%s",s)!=EOF)
	{
		n=strlen(s);
		if(n==0) break;
		for(i=0;i<=n;i++)
		{
			if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
			if(s[i]>='a'&&s[i]<='z') deal(&x,s[i]);
			else if(x.x||x.y)
			{
				int l=1,r=t;
				while(l<r)
				{
					int mid=l+r>>1;
					if(cmp_ull(x,dic[mid])==1) l=mid+1;
					else r=mid; 
				}
				if(cmp_ull(x,dic[l])==0) vis[l]=1;
				x.x=x.y=0;
			}
		}
	}
	mm=0;
	for(i=1;i<=t;i++) if(!vis[i]) dic[++mm]=dic[i];
	t=mm;

	stream=fopen("article.txt","r");

	cnt=1;
	while(fscanf(stream,"%s",s)!=EOF)
	{
		n=strlen(s);
		if(n==0) break;
		if(nw)
		{
			for(i=0;i<=n;i++)
			{
				if(s[i]>='0'&&s[i]<='9'||s[i]=='-')
					ss[cnt][i]=s[i];
				else
				{
					ss[cnt][i]='\0';
					break;
				}
				//ss[cnt][i]=s[i];
			}
			nw=0;
		}
		for(i=0;i<=n;i++)
		{
			if(s[i]=='\f')
			{
				cnt++;
				nw=1;
				break;
			}
			if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
			if(s[i]>='a'&&s[i]<='z') deal(&x,s[i]);
			else if(x.x||x.y)
			{
				int l=1,r=t;
				while(l<r)
				{
					int mid=l+r>>1;
					if(cmp_ull(x,dic[mid])==1) l=mid+1;
					else r=mid;
				}
				if(cmp_ull(x,dic[l])==0)
				{
					tnd[cnt]++;
					for(j=1;j<=m;j++)
						if(cmp_ull(word[j],x)==0)
						{
							if(!tnkd[cnt][j]) dnk[j]++;
							tnkd[cnt][j]++;
						}
				}
				x.x=x.y=0;
			}
		}
	}
	for(i=1;i<=cnt;i++)
		for(j=1;j<=m;j++) if(tnd[i]) tfkd[i][j]=100.0*tnkd[i][j]/tnd[i];
	for(j=1;j<=m;j++) if(dnk[j]) idfk[j]=log(1.0*cnt/dnk[j]);
	for(i=1;i<=cnt;i++)
		for(j=1;j<=m;j++)
			simd[i]+=tfkd[i][j]*idfk[j];
	for(i=1;i<=cnt;i++)
	{
		ans[i].x=simd[i];
		ans[i].p=i;
	}
	//printf("%d\n",cnt);
	//for(i=1;i<=m;i++) printf("%d %d  %.6lf\n",i,dnk[i],idfk[i]/lg);
	qsort(ans+1,cnt,sizeof(node),cmp);
	for(i=1;i<=5;i++) if(ans[i].x>eps) printf("%.6lf %d %s\n",ans[i].x/lg,ans[i].p,ss[ans[i].p]);
	stream=fopen("results.txt","w");
	for(i=1;i<=cnt;i++) if(ans[i].x>eps) 
		fprintf(stream,"%.6lf %d %s\n",ans[i].x/lg,ans[i].p,ss[ans[i].p]);
	fclose(stream);
	return 0;
}
