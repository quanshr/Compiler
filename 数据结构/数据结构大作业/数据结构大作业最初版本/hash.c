#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ull unsigned long long
int n,N,i,j,m,mm,cnt,t,ts,vis[2000010];
int v[10010];
ull word[10010],x,dic[2000010],p=1007;
char s[10000010],ss[10000010];
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
	ull aa=*(ull*)a,bb=*(ull*)b;
	if(aa>bb) return 1;
	if(aa<bb) return -1;
	return 0;
}

int main(int argc,char** argv)
{
	int ii=strlen(argv[2]);
	for(i=0;i<ii;i++) N=N*10+argv[2][i]-'0';
	for(i=3;i<argc;i++)
	{
		int jj=strlen(argv[i]);
		for(j=0;j<jj;j++)
		{
			if(argv[i][j]>='A'&&argv[i][j]<='Z') word[i-2]=word[i-2]*p+argv[i][j]-'A'+1;
			else word[i-2]=word[i-2]*p+argv[i][j]-'a'+1;
		}
	}
	m=argc-3;
	
	stream=fopen("dictionary.txt","r");
	fread(s,sizeof(s),1,stream);
	n=strlen(s);
	printf("%d\n",n);
	for(i=0;i<=n;i++)
	{
		if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
		if(s[i]>='a'&&s[i]<='z') x=x*p+s[i]-'a'+1;
		else if(x)
		{
			dic[++t]=x;
			x=0;
		}
		s[i]=0;
	}
	qsort(dic+1,t,sizeof(ull),cmpull);
//	printf("%d\n",t);
//	for(i=1;i<=t;i++) printf("%d %llu\n",i,dic[i]);

	stream=fopen("stopwords.txt","r");
	fread(s,sizeof(s),1,stream);
	n=strlen(s);
	for(i=0;i<n;i++)
	{
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
			if(dic[l]==x) vis[l]=1;
			x=0;
		}
		if(s[i]=='\0')
		{
			s[i]=0;
			break;
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
	fclose(stream);
	return 0;
}
