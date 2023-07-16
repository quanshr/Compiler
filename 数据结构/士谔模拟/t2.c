#include <stdio.h>
#include <stdlib.h>

void shuffle(int* mylist, int len)
{
    static unsigned lucky_number = 520;
    while(len > 1)
    {
        int temp = *mylist;
        *mylist = *(mylist + lucky_number % len);
        *(mylist + lucky_number % len) = temp;
        mylist++; len--;
        lucky_number *= 113344;
        lucky_number += 993311;
    }
}
int cmp(const void *_a,const void *_b)
{
	int *a=(int*)_a,*b=(int*)_b;
	return *a-*b;
}
void sort(int* mylist, int len)
{
	qsort(mylist,len,sizeof(int),cmp);
}
int n;
char s[2010];
int a[2010],cnt,cnt2,i,j,k,f,st[2010],p,b[2010];
int l[2010];

int main()
{
	scanf("%s",s);
	n=strlen(s);
	f=1;
	cnt=0;
	p=0;
	for(i=0;i<n;i++)
	{
		if(s[i]=='-')
		{
			f=-1;
			continue;
		}
		if(s[i]>='0'&&s[i]<='9')
		{
			long long x=0;
			while(s[i]>='0'&&s[i]<='9')
			{
				x=x*10+s[i]-'0';
				i++;
			}
			a[++cnt]=1LL*f*x;
			f=1;
			i--; continue;
		}
		if(s[i]=='(')
		{
			st[++p]=i;
			l[i]=cnt;
		}
		else if(s[i]==')')
		{
			int x=st[p--];
			if(s[x-2]=='r') sort(a+l[x]+1,cnt-l[x]);
			else if(s[x-2]=='l') shuffle(a+l[x]+1,cnt-l[x]);
		}
	}
	
	scanf("%s",s);
	n=strlen(s);
	f=1;
	cnt2=0;
	p=0;
	for(i=0;i<n;i++)
	{
		if(s[i]=='-')
		{
			f=-1;
			continue;
		}
		if(s[i]>='0'&&s[i]<='9')
		{
			long long x=0;
			while(s[i]>='0'&&s[i]<='9')
			{
				x=x*10+s[i]-'0';
				i++;
			}
			b[++cnt2]=1LL*f*x;
			f=1;
			i--; continue;
		}
		if(s[i]=='(')
		{
			st[++p]=i;
			l[i]=cnt2;
		}
		else if(s[i]==')')
		{
			int x=st[p--];
			if(s[x-2]=='r') sort(b+l[x]+1,cnt2-l[x]);
			else if(s[x-2]=='l') shuffle(b+l[x]+1,cnt2-l[x]);
		}
	}
	if(cnt!=cnt2) printf("Failed");
	else
	{
		int ok=1;
		for(i=1;i<=cnt;i++)
			if(a[i]!=b[i]) ok=0;
		if(!ok) printf("Failed");
		else printf("TobyWendy");
	}
	return 0;
}
