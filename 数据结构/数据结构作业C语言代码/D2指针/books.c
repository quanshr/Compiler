#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n,op,aa[10]={50,70,100,110};
char s[1010][210],c,f[210];
int i,j,k;
int cmp(char *a,char *b)
{
	while(*a!=' '&&*b!=' ')
	{
		if(*a<*b) return -1;
		if(*a>*b) return 1;
		a++; b++;
	}
	if(*a==' ')
	{
		if(*b==' ') return 0;
		return -1;
	}
	return 1;
}
int ucmp(char *a,char *b)
{
	while(*a!='\0'&&*b!='\0')
	{
		if(*a<*b) return -1;
		if(*a>*b) return 1;
		a++; b++;
	}
	if(*a=='\0') return 0;
	return 1;
}
void fswap(char *a,char *b)
{
	int q=0;
	for(q=0;q<=120;q++)
	{
		c=*a;
		*a=*b;
		*b=c;
		a++; b++;
	}
}
void fprint(char *a)
{
	while(*a!='\0')
	{
		printf("%c",*a);
		a++;
	}
	printf("\n");
}
void formprint(char *a)
{
	int x=0,u=0;
	while(1)
	{
		if(*a!=' '&&*a!='\0')
		{
			x++;
			printf("%c",*a);
		}
		else
		{
			while(x<aa[u])
			{
				printf(" ");
				x++;
			}
			u++;
			if(*a=='\0')
			{
				printf("\n");
				return;
			}
		}
		a++;
	}
}


int main()
{
	/*scanf("%d",&op);
	if(op!=0)
		printf("op!=0!!");*/
	//freopen("books.txt","r",stdin);
	FILE *in=fopen("books.txt","r"); 
	//printf("DD");
	while(fgets(s[++n],100000,in)!=NULL)
	{
		
		//gets(s[++t])
		//printf("%s\n",s[n]);
		if(s[n][0]=='\n') break;
		//printf("%s\n",s[n]);
	}
	n--;
	//fclose(stdin);
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			if(cmp(s[i],s[j])==1)
				fswap(s[i],s[j]);
	//printf("END\n");
	//freopen("CON","r",stdin);
	///dev/console:freopen("/dev/console", "r", stdin);
	//freopen("/dev/tty","r",stdin);
	while(1)
	{
		scanf("%d",&op);
		//printf("%d \n",op);
		if(op==0) break;
		getchar();
		if(op==1)
		{
			gets(s[++n]);
			//printf("12%s\n",s[n]);
			i=n;
			while(i>=2&&cmp(s[i],s[i-1])==-1)
			{
				fswap(s[i],s[i-1]);
				i--;
			}
		}
		else if(op==2)
		{
			gets(f);
			//printf("   %s\n",f);
			for(i=1;i<=n;i++)
				for(j=0;s[i][j]!=' ';j++)
				{//printf("%d ",1);
					if(ucmp(f,s[i]+j)==0)
					{
						formprint(s[i]);
						break;
					}
				}
		}
		else
		{
			gets(f);
			int m=0;
			for(i=1;i<=n;i++)
			{
				for(j=0;s[i][j]!=' ';j++)
					if(ucmp(f,s[i]+j)==0) goto aaa;
				m++;
				if(i!=m) fswap(s[i],s[m]);
				aaa:;
			}
			n=m;
		}
		//printf("ENDd\n");
		//for(i=1;i<=n;i++) formprint(s[i]);
	}
	//printf("END");
	freopen("ordered.txt","w",stdout);
	for(i=1;i<=n;i++)
		formprint(s[i]);
	return 0;
}
