#include <stdio.h>
#include <stdlib.h>
#define int long long
#define mod 19260817

int n,mp[100010],st[100010],p,sum[100010],pw[100010];
char s[100010];
int f[100010][2],add[100010],cnt;
int calc0(int l,int r)
{
	//return 0;
	int i,res=1;
	for(i=l;i<=r;i++)
	{
		if(mp[i])
		{
			res=res*f[i][1]%mod;
			i=mp[i]+1;
		}
	}
	return pw[sum[r]-sum[l-1]+1]-res;
}
void calc(int l,int r)
{
	int i,lst=l+1;
	cnt=0;
	//f[l][0]=f[l][1]=1;
	for(i=l+1;i<=r;i++)
	{
		//printf("    %d\n",i);
		if(mp[i]&&i!=r)
		{
			//printf("%d %d\n",i,mp[i]);
			i=mp[i];
			continue;
		}
		if(s[i]=='+'||i==r)
		{
			add[++cnt]=calc0(lst,i-1);
			lst=i+1;
		}
	}
	int res=1;
	for(i=1;i<=cnt;i++)
		res=res*add[i]%mod;
	f[l][0]=res;
	f[l][1]=pw[sum[r]-sum[l]+1]-f[l][0];
}

signed main()
{
	//freopen("evolve.in","r",stdin);
	//freopen("evolve.out","w",stdout);
	scanf("%lld%s",&n,s+1);
	int i;
	pw[0]=1;
	n=strlen(s+1);
	s[0]='('; s[++n]=')';
	for(i=1;i<=n+2;i++) pw[i]=pw[i-1]*2%mod;	
	for(i=0;i<=n;i++)
	{
		if(i>=1) sum[i]=sum[i-1];
		if(s[i]=='(') st[++p]=i;
		else if(s[i]==')')
		{
			int x=st[p--];
			mp[i]=x;
			mp[x]=i;
			calc(x,i);
		}
		else sum[i]++;
		//printf("%d\n",i);
	}
	int ans=(f[0][0]%mod+mod)%mod;
	printf("%lld",ans);
	return 0;
}
