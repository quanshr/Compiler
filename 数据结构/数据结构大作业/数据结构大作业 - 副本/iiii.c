#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define mod 1000000007
#define ull unsigned long long
int n,N,i,j,m,mm,cnt,t,ts,vis[2000010];
int v[10010];
typedef struct Hash
{
	ull x,y;
}hash;
hash word[10010],x,dic[2000010],p;
char s[10000010];
FILE *stream;
int tnd[10010],tnkd[10010][110],dnk[10010];
double tfkd[10010][110],idfk[110],simd[10010];
int cmp(const void *a, const void *b)
{
	double aa=*(double*)a,bb=*(double*)b;
	if(aa>bb) return 1;
	if(aa<bb) return -1;
	return 0;
}
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
void deal(hash *x,char y)
{
	(*x).x=(*x).x*p.x+y-'a'+1;
	(*x).y=((*x).y*p.y+y-'a'+2)%mod;
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
	
	
	freopen("out.txt","w",stdout);
	stream=fopen("dictionary111.txt","r");
	fread(s,sizeof(s),1,stream);
	n=strlen(s);
	printf("%d\n",n);
	for(i=0;i<=n;i++)
	{
		printf("%c",s[i]);
	
		if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
		if(s[i]>='a'&&s[i]<='z') deal(&x,s[i]);
		else if(x.x||x.y)
		{
			//dic[++t]=x;
			x.x=x.y=0;
		}
		s[i]=0;
	}
	qsort(dic+1,t,sizeof(hash),cmpull);
	//for(i=1;i<=t;i++) printf("%d %llu %llu\n",i,dic[i].x,dic[i].y);
	/*stream=fopen("stopwords.txt","r");
	fread(s,sizeof(s),1,stream);
	n=strlen(s);
	for(i=0;i<n;i++)
	{
		if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
		if(s[i]>='a'&&s[i]<='z') deal(&x,s[i]);
		else if(x.x||x.y)
		{
			int l=1,r=t;
			while(l<r)
			{
				int mid=l+r>>1;
				if(x>dic[mid]) l=mid+1;
				else r=mid; 
			}
			if(dic[l]==x) vis[l]=1;
			x=0;
		}
		s[i]=0;
	}
	s[n]=0;
	if(x)
	{
		int l=1,r=t;
		while(l<r)
		{
			int mid=l+r>>1;
			if(x>dic[mid]) l=mid+1;
			else r=mid; 
		}
		if(dic[l]==x) vis[l]=1;
		x=0;
	}
	mm=0;
	for(i=1;i<=t;i++) if(!vis[i]) dic[++mm]=dic[i];
	t=mm;
//	printf("%d\n",t);
//	for(i=1;i<=t;i++) printf("%d %llu\n",i,dic[i]);
	mm=0;
	for(i=2;i<=t;i++) if(dic[i]==dic[i-1])
	{
		printf(" Wa   %d %llu\n",i,dic[i]);
		mm++;
	}
	printf("ccc  %d\n",mm);
	stream=fopen("article.txt","r");
	fread(s,sizeof(s),1,stream);
	n=strlen(s);
	printf("  %d\n",n);
	cnt=1;
	for(i=0;i<n;i++)
	{
		if(s[i]=='\f')
		{
			cnt++;
			continue;
		}
		if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
		if(s[i]>='a'&&s[i]<='z') x=x*p+s[i]-'a'+1;
		else if(x)
		{
			int l=1,r=t;
			while(l<r)
			{
				int mid=l+r>>1;
				if(x>dic[mid]) l=mid+1;
				else r=mid; 
			}
			if(dic[l]==x)
			{
				tnd[cnt]++;
				for(j=1;j<=m;j++)
					if(word[j]==x)
					{
						if(!tnkd[cnt][j]) dnk[j]++;
						tnkd[cnt][j]++;
					}
			}
			x=0;
		}
		s[i]=0;
	}
	s[n]=0;
	if(x)
	{
		int l=1,r=t;
		while(l<r)
		{
			int mid=l+r>>1;
			if(x>dic[mid]) l=mid+1;
			else r=mid;
		}
		if(dic[l]==x)
		{
			tnd[cnt]++;
			for(j=1;j<=m;j++)
				if(word[j]==x)
				{
					if(!tnkd[cnt][j]) dnk[cnt]++;
					tnkd[cnt][j]++;
				}
		}
		x=0;
	}
	for(i=1;i<=cnt;i++)
		for(j=1;j<=m;j++) tfkd[i][j]=100.0*tnkd[i][j]/tnd[i];
	for(j=1;j<=m;j++) if(dnk[j]) idfk[j]=log(1.0*cnt/dnk[j]);
	for(i=1;i<=cnt;i++)
		for(j=1;j<=m;j++)
			simd[i]+=tfkd[i][j]*idfk[j];
	qsort(simd+1,cnt,sizeof(double),cmp);
	//for(i=1;i<=cnt;i++) printf("%d %d %.5lf\n",i,tnd[i],simd[i]/log(10));
	fclose(stream);*/
	return 0;
}
