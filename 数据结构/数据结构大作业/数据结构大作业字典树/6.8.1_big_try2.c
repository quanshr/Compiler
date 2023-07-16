#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
struct tree
{
	int flag;
	int num;
	struct tree *next[26];
}word;//flag确定是不是字典词，num为词频，指针为单词的下一个字母
struct passage
{
	int n3;//文章在所有文章中的次序
	double TNDK[500];//文章特定词频（设成double）后面计算方便
	double TND;//文章的总字数
	double TFDK[500];
	double sim;//相关度
	char n1[20];
}pass[16000];//网页文章篇数
struct tree* creat0(FILE *fp,struct tree *root);
struct tree* creat1(FILE *fp,struct tree *root);
int cmp(const void *a,const void *b);
struct tree *root=NULL,*p=NULL;
double eps=1e-6;
int main(int argc,char **argv)
{
	FILE *dic,*stop,*art,*res;
	int num=0,i,N=0,j2=0;
	int flag1=0,DNk[500]={0};
	char l[100000];
	double IDNk[500]={0.0};
	dic=fopen("dictionary.txt","r");
	stop=fopen("stopwords.txt","r");
	art=fopen("article.txt","r");
	res=fopen("results.txt","w");
	root=(struct tree *)malloc(sizeof(struct tree));
	for(i=0;i<26;i++)
		root->next[i]=NULL;
	root->num=0;
	root->flag=0;
	root=creat0(dic,root);
	root=creat1(stop,root);
	p=root;
	for(i=0;i<strlen(argv[1]);i++)
	num=num*10+argv[1][i]-'0';
	fgets(pass[N].n1,20,art);	
	pass[N].TND=0.0;
	pass[N].sim=0.0;
	for(i=2;i<argc;i++) pass[N].TNDK[i]=0.0;
	p=root;
	while(fgets(l,100000,art)!=NULL)
	{
		p=root;
		for(i=0;i<strlen(l);i++) l[i]=tolower(l[i]); 
		int len=strlen(l);
/*		for(i=0;i<=len;)
		{
			//l[i]=tolower(l[i]);
			if(l[i]>='a'&&l[i]<='z')
			{
				if(p->next[l[i]-'a']==NULL)
				{
					while(i<len&&(l[i]>='a'&&l[i]<='z')) i++;
					//while(i<len&&(l[i]<'a'||l[i]>'z')) i++;
					//i--;		
					p=root;
					continue;
				}
				else p=p->next[l[i]-'a'];
			}
			else
			{
				while(i<strlen(l)&&(l[i]<'a'||l[i]>'z')) i++;
				//i--;
				if(p->flag==2)
				{
					p->num++;
					pass[N].TND++;					
				}
				p=root;
			}
			i++;
		}*/
		for(i=0;i<=len;i++)
		{
			if(l[i]>='a'&&l[i]<='z')
			{
				if(p!=NULL)
					p=p->next[l[i]-'a'];
			}
			else
			{
				if(p!=NULL&&p->flag==2)
				{
					p->num++;
					pass[N].TND++;
				}
				p=root;
			}
		}
		if(l[0]=='\f')
		{
			pass[N].n3=N+1;
			for(j2=2;j2<argc;j2++)
			{
				p=root;
				for(i=0;i<strlen(argv[j2]);i++)
				{
					if(argv[j2][i]>='a'&&argv[j2][i]<='z')
					p=p->next[argv[j2][i]-'a'];
					if(p==NULL)
					{
						pass[N].TNDK[j2]=0;
						DNk[j2]=0;
						continue;
					}
				}					
				if(p->flag==2) 
				{
					//printf("%s\n",argv[j2]);
					pass[N].TNDK[j2]=p->num;
					if(p->num!=0) DNk[j2]=DNk[j2]+1;;
					p->num=0;
				}
				if(pass[N].TND>eps||pass[N].TND<-eps)
				pass[N].TFDK[j2]=pass[N].TNDK[j2]*100/(pass[N].TND);
			}
			N++;
			fgets(pass[N].n1,20,art);
			pass[N].TND=0.0;
			pass[N].sim=0.0;
			for(i=2;i<argc;i++) pass[N].TNDK[i]=0.0;
		}		
	}
	pass[N].n3=N+1;
	for(j2=2;j2<argc;j2++)
	{
		p=root;
		for(i=0;i<strlen(argv[j2]);i++)
		{
			if(argv[j2][i]>='a'&&argv[j2][i]<='z')
			p=p->next[argv[j2][i]-'a'];
			if(p==NULL)
			{
				pass[N].TNDK[j2]=0;
				DNk[j2]=0;
				continue;
			}
		}		
		if(p->flag==2) 
		{
			pass[N].TNDK[j2]=p->num;
			if(p->num!=0)DNk[j2]++;
			p->num=0;
		}
		//printf("%s %d\n",argv[j2],DNk[j2]);
		if(pass[N].TND!=0)
		pass[N].TFDK[j2]=pass[N].TNDK[j2]*100/pass[N].TND;
	}
	for(i=2;i<argc;i++)//计算 
	{
		if(DNk[i]==0) IDNk[i]=0;
		else IDNk[i]=log10((double)(N+1)/(double)(DNk[i]));
	}
	if(N==0) return 0;
	for(i=0;i<N+1;i++)
		for(j2=2;j2<argc;j2++)		
			pass[i].sim=pass[i].sim+(IDNk[j2])*(pass[i].TFDK[j2]);
	qsort(pass,N+1,sizeof(pass[0]),cmp);
	if(N+1>5)
		for(i=0;i<5;i++)
			printf("%.6lf %d %s",pass[i].sim,pass[i].n3,pass[i].n1);
	else
		for(i=0;i<N+1;i++)
			printf("%.6lf %d %s",pass[i].sim,pass[i].n3,pass[i].n1);
	if(N+1>num)
		for(i=0;i<num;i++)
			fprintf(res,"%.6lf %d %s",pass[i].sim,pass[i].n3,pass[i].n1);
	else
		for(i=0;i<=N;i++)
			fprintf(res,"%.6lf %d %s",pass[i].sim,pass[i].n3,pass[i].n1);
	fclose(dic);
	fclose(stop);
	fclose(art);
	fclose(res);
	return 0;
}
struct tree* creat0(FILE *fp,struct tree *root)
{
	int len,i,j;
	char w[100],l;
	struct tree *p;
	p=root;
	while(fscanf(fp,"%s",w)!=EOF)
	{
		len=strlen(w);
		for(i=0;i<len;i++)
		{
			if(p->next[w[i]-'a']==NULL)
			{
				p->next[w[i]-'a']=(struct tree *)malloc(sizeof(struct tree));
				for(j=0;j<26;j++)
				p->next[w[i]-'a']->next[j]=NULL;
				p->next[w[i]-'a']->num=0;
			}
			
			p=p->next[w[i]-'a']; 
		}
		p->flag=2;
		p->num=0;
		p=root;
	}
	return root;
}
struct tree* creat1(FILE *fp,struct tree *root)
{
	int len,i,j;
	char w[100],l;
	struct tree *p;
	p=root;
	while(fscanf(fp,"%s",w)!=EOF)
	{
		len=strlen(w);
		for(i=0;i<len;i++)
		{
			if(p->next[w[i]-'a']==NULL)
			{
				p->next[w[i]-'a']=(struct tree *)malloc(sizeof(struct tree));
				for(j=0;j<26;j++)
				p->next[w[i]-'a']->next[j]=NULL;
				p->next[w[i]-'a']->num=0;
			}
			p=p->next[w[i]-'a'];
		}
		p->flag=1;
		p->num=0;
		p=root;
	}
	return root;
}
int cmp(const void *a,const void *b)
{
	struct passage c=*(struct passage*)a;
	struct passage d=*(struct passage*)b;
	if(d.sim!=c.sim)
	return (d.sim>c.sim)?1:-1;
	else return c.n3-d.n3;
}
