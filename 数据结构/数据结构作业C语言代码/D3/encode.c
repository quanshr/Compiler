#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int l=32,r=126,n,i,j,k,t,p,q;
char s[200],v[200],ss[200],exist[200],to[200],opt[1000010];

int main()
{
	FILE *in=fopen("in.txt","r");
	FILE *out=fopen("in_crpyt.txt","w");
	//printf("%d\n",in);
	gets(s);
	n=strlen(s);
	//printf("%s",s);
	for(i=0;i<n;i++)
		if(!v[s[i]])
		{
			v[s[i]]=1;
			ss[t++]=s[i];
		}
	for(i=l;i<=r;i++)
		if(!v[i]) ss[t++]=i;
	p=0;
	for(i=0;i<=r-l;i++) exist[i]=1;
	for(i=0;i<r-l;i++)
	{
		int x=ss[p];
		exist[p]=0;
		q=p;
		while(x)
		{
			q=(q+1)%(r-l+1);
			x-=exist[q];
			//printf("%d\n",x);
		}
		to[ss[p]]=ss[q];
		p=q;
	}
	to[ss[p]]=ss[0];
	//for(i=l;i<=r;i++)	printf("%c",to[i]);
	//printf("%d\n",fgets(opt,100000,in));
	while(fgets(opt,1000000,in)!=NULL)
	{
		//printf("begin");
		int m=strlen(opt);
		for(i=0;i<m;i++)
			if(opt[i]>=l&&opt[i]<=r) fprintf(out,"%c",to[opt[i]]);
			else fprintf(out,"%c",opt[i]);
	}
	return 0;
}
