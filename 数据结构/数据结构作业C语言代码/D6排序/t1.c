#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NHASH 3001
#define MULT 37
unsigned int hash(char *str)
{
    unsigned int h=0;
    char *p;
    for(p=str;*p!='\0';p++)
		h=MULT*h+*p;
    return h%NHASH;
}
int n,i,j,k,m,beg[200],ed[200],op,ans,ok,res,v[200];
FILE *fp;
typedef struct Word
{
	char c[22];
}word;
word a[30010],s;
int cmp(word x,word y)
{
	int i=0;
	while(x.c[i]!='\0'&&y.c[i]!='\0')
	{
		if(x.c[i]<y.c[i]) return -1;
		if(x.c[i]>y.c[i]) return 1;
		i++;
	}
	if(x.c[i]=='\0'&&y.c[i]=='\0') return 0;
	if(x.c[i]=='\0') return -1;
	return 1;
}

int main()
{
	fp=fopen("dictionary3000.txt","r");
	while(fscanf(fp,"%s",s.c)!=EOF)
	{
		n=strlen(s.c);
		for(i=0;i<n;i++) a[m].c[i]=s.c[i];
		a[m].c[n]='\0';
		if(!beg[a[m].c[0]-'a']) beg[a[m].c[0]-'a']=m;
		ed[a[m].c[0]-'a']=m;
		v[a[m].c[0]-'a']=1;
		m++;
	}
	beg[0]=0;
	while(scanf("%s%d",s.c,&op)!=EOF)
	{
		n=strlen(s.c);
		ans=ok=0;
		if(op==1)
		{
			for(i=0;i<m;i++)
			{
				ans++;
				res=cmp(a[i],s);
				if(res==0)
				{
					ok=1;
					break;
				}
				else if(res==1) break;
			}
		}
		else if(op==2||op==3)
		{
			int l,r;
			if(op==2) l=0,r=m-1;
			else
			{
				if(!v[s.c[0]-'a']) goto aaa;
				l=beg[s.c[0]-'a'],r=ed[s.c[0]-'a'];
			}
			while(l<=r)
			{
				int mid=l+r>>1;
				res=cmp(a[mid],s);
				ans++;
				if(res==0)
				{
					ok=1;
					break;
				}
				if(res==1) r=mid-1;
				else l=mid+1;
			}
		}
		else
		{
			unsigned int k=hash(s.c);
			for(i=0;i<m;i++)
			{
				if(k==hash(a[i].c))
					ans++;
				res=cmp(a[i],s);
				if(res==0)
				{
					ok=1;
					break;
				}
				if(res==1) break; 
			}
		}
		aaa:;
		printf("%d %d\n",ok,ans);
	}
	return 0;
}
