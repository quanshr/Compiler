#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ull unsigned long long
int n,N,i,j,m,mm,cnt,t,ts,vis[5000010],nw=1;
ull word[100010],x,dic[5000010],p=107;
char s[10000010],ss[100010][110];
int _s;
FILE *stream;
int tnd[100010],tnkd[100010][110],dnk[100010];
double tfkd[100010][110],idfk[110],simd[100010],lg=log(10);
int cmpull(const void *a, const void *b)
{
	ull aa=*(ull*)a,bb=*(ull*)b;
	if(aa>bb) return 1;
	if(aa<bb) return -1;
	return 0;
}
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
	while(fscanf(stream,"%s",s)!=EOF)
	{
		n=strlen(s);
		if(n==0) break;
		for(i=0;i<=n;i++)
		{
			if(s[i]>='A'&&s[i]<='Z') s[i]=s[i]-'A'+'a';
			if(s[i]>='a'&&s[i]<='z') x=x*p+s[i]-'a'+1;
			else if(x)
			{
				dic[++t]=x;
				x=0;
			}
		}
	}
	qsort(dic+1,t,sizeof(ull),cmpull);
	
	
	stream=fopen("stopwords.txt","r");
	while(fscanf(stream,"%s",s)!=EOF)
	{
		n=strlen(s);
		if(n==0) break;
		for(i=0;i<=n;i++)
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
		}
	}
	mm=0;
	for(i=1;i<=t;i++) if(!vis[i]) dic[++mm]=dic[i];
	t=mm;

	stream=fopen("article.txt","r");

	cnt=1;
	n=0;
	while((_s=fgetc(stream))!=EOF)
	{
		if(_s<128) s[n++]=(char)_s;
		else s[n++]=0;
		//if(n<=100) printf("%d\n",_s);
	}
	//printf("%d\n",n);
	for(i=0;i<=n;)
	{
		//printf("888  %d\n",i);
		//if(i<=100) printf("%c",s[i]);
		if(nw)
		{
			while(!(s[i]>='0'&&s[i]<='9'||s[i]=='-')) i++;
			j=0;
			while(s[i]>='0'&&s[i]<='9'||s[i]=='-')
				ss[cnt][j++]=s[i++];
			ss[cnt][j]='\0';
			nw=0;
			//printf("%d   uu\n",i);
			continue;
		}
		{
			if(s[i]=='\f')
			{
				cnt++;
				nw=1;
				i++;
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
		}
		i++;
	}
	//for(i=1;i<=cnt;i++) printf("%d %s\n",i,ss[i]);
	for(i=1;i<=cnt;i++)
		for(j=1;j<=m;j++) tfkd[i][j]=100.0*tnkd[i][j]/tnd[i];
	for(j=1;j<=m;j++) if(dnk[j]) idfk[j]=log(1.0*cnt/dnk[j]);
	for(i=1;i<=cnt;i++)
		for(j=1;j<=m;j++)
			simd[i]+=tfkd[i][j]*idfk[j];
	for(i=1;i<=cnt;i++)
	{
		ans[i].x=simd[i];
		ans[i].p=i;
	}
	qsort(ans+1,cnt,sizeof(node),cmp);
	for(i=1;i<=5;i++) if(ans[i].x>eps) printf("%.6lf %d %s\n",ans[i].x/lg,ans[i].p,ss[ans[i].p]);
	stream=fopen("results.txt","w");
	for(i=1;i<=N;i++) if(ans[i].x>eps) fprintf(stream,"%.6lf %d %s\n",ans[i].x/lg,ans[i].p,ss[ans[i].p]);
	fclose(stream);
	return 0;
}
