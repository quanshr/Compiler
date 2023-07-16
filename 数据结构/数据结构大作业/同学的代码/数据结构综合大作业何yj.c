#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define max 26
#define wdmax 1010
#define pagemax 10010
#define artmax 100010
#define dealt 1e-6
char str[100];

int TNd[artmax];//每个文档里的单词数量
int Dnk[wdmax];//出现单词k的文档数
int kflag[wdmax];//记录单词在文档中是否出现
int DNk[1010];//用于计算关键词在几个文档中出现过
int TNkd[wdmax][artmax];//用于记录单词k在文档d中出现的次数
int artnum, pagenum;//artnum表示网页序号 pagenum表示文档序号
double TFkd[wdmax][artmax];//用于记录单词k在文档d中的词频
double IDFk[wdmax];//逆文档频率

struct pageinformation {
	int artnum;//表示网页序号
	int pagenum;//表示文档号
	double Simd;//用于记录simd值
};
struct pageinformation page[pagemax];

struct words {
	char word[100];
};
struct words keywords[1010];//用于存储关键词

struct b_tree {
	int end;		//用于表示有多少单词以该节点结尾
	char ch;		//用于表示该节点所存储的字母
	int flag;       //用于记录该节点不为空 flag=1 则不为空
	struct b_tree* nextlettle[26];
};
typedef struct b_tree* trie;
struct b_tree* rootd =NULL;//单词表的头节点
struct b_tree* roots = NULL;//停用表的头节点
struct b_tree* p=NULL, *q=NULL,* r=NULL;

trie createnode()//为节点申请空间，并且初始化
{
	p= (trie)malloc(sizeof(struct b_tree));
	int i;
	for (i = 0; i < max; i++)
		p->nextlettle[i] = NULL;
	p->end = 0;
	p->ch = '\0';
	p->flag = 0;
	return p;
}
void insert(char s[])//字典树插入
{
	q = rootd;
	int index;//用于索引下标
	int i;
	for (i =0; i<strlen(s); i++)
	{
		index = s[i] - 'a';//计算下标，表示字母存在
		if (q->nextlettle[index] == NULL)
		{
			p = createnode();
		    p->ch = s[i];
			p->flag = 1;
			q->nextlettle[index] =p;
			q = p;
		}
		else 
			q = q->nextlettle[index];
	}
}

void insert1(char s[])//字典树插入
{
	q = roots;
	int index;//用于索引下标
	int i;
	for (i = 0; i < strlen(s); i++)
	{
		index = s[i] - 'a';//计算下标，表示字母存在
		if (q->nextlettle[index] == NULL)
		{
			p = createnode();
			p->ch = s[i];
			p->flag = 1;
			q->nextlettle[index] = p;
			q = p;
		}
		else
			q = q->nextlettle[index];
	}
}

int  search(trie p, char s[])//字典树查找
{
	int find;
	int i;
	for (i = 0; i<strlen(s); i++)
	{
		find = s[i] - 'a';
		if (p->nextlettle[find] == NULL)
		{
			return 0;
		}
		else p = p->nextlettle[find];
	}
	return 1;
}

int kbinsearch(struct words key[], int n, char find[])//二分查找关键词
{
	int low =0, high = n-1, mid;
	int result = -1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (strcmp(find, key[mid].word) == 0)
		{
			result = mid;
			break; /*查找成功*/
		}
		if (strcmp(find, key[mid].word) > 0)
			low = mid + 1; /*准备查找后半部分 */
		if (strcmp(find, key[mid].word) < 0)
			high = mid - 1; /*准备查找前半部分 */
	}
	return result; /*查找失败 */
}

int cmp(const void* p1, const void* p2)
{
	struct pageinformation* a = (struct pageinformation*)p1;
	struct pageinformation* b = (struct pageinformation*)p2;
	if (fabs(a->Simd - b->Simd) < dealt)
		return a->pagenum - b->pagenum;
	else if (a->Simd > b->Simd) return -1;
	else if (a->Simd < b->Simd) return 1;
}

int cmp1(const void* p1, const void* p2)
{
	struct words* a = (struct words*)p1;
	struct words* b= (struct words*)p2;
	return strcmp(a->word, b->word);
}
int main(int argc,char *argv[]) {
	FILE* fps, * fpd,*fpa ,* fpr;
	int i=0, j=0, k=0;
	int stopcnt = 0;       //停用词数量
	int diccnt = 0;
	int keynum = argc - 2;//关键词数量
	int findbresult = 0;//用于表示在单词表里查找的结果
	int findsresult = 0;//用于表示在停用表里查找的结果
	int findkresult = 0;//用于表示在关键词里查找的结果
	int pagecnt = 0;   //用于记录文档数量
	int pageptf=0;     
	rootd = createnode();
	roots = createnode();
	for (i = 0; i < keynum; i++)
	{
		strcpy(keywords[i].word, argv[i + 2]);//将关键词储存下来
	}
	qsort(keywords, keynum, sizeof(keywords[0]), cmp1);
	for (i = 0; i < strlen(argv[1]); i++)
	{
		pageptf = pageptf * 10 + argv[1][i] - '0';
	}

	fps = fopen("k.txt", "r");
	fpd = fopen("dictionary.txt", "r");
	fpa = fopen("article.txt", "r");
	fpr = fopen("result.txt", "w");

	if (fps == NULL || fpd == NULL || fpa == NULL || fpr == NULL)
	{
		perror("files can't be opened\n");
	}

	while (fscanf(fps, "%s", str) != EOF)//读停用词文档建树
	{
		insert1(str);
		stopcnt++;
	}

	while (fscanf(fpd, "%s", str) != EOF)//读字典词文档并且建字典树
	{
		insert(str);
		diccnt++;
	}
	memset(str, 0, sizeof(str));
	int c;
	i = 0;
	int jm = 0;
	int st = 0;
	while (fscanf(fpa,"%d-%d", &page[pagecnt].artnum, &page[pagecnt].pagenum)!=EOF)
	{
		while((c = fgetc(fpa)) != EOF)
		{
			if (isalpha(c))//读取单词，如果是字母，将其放入字符串
				str[i++] = tolower(c);
			else if (!isalpha(c))//如果不是字符，结束正在读的单词，并查找是否为单词表里的单词
			{
				if (isalpha(str[0])) {
					findsresult = search(roots,str);//判断是否为停用词
					if (findsresult == 0)
					{
						findbresult = search(rootd, str);
						if (findbresult == 1)//判断是否为单词表单词
						{
							TNd[pagecnt]++;
						}
						findkresult = kbinsearch(keywords,keynum,str);
						if (findkresult != -1)
						{
							if (kflag[findkresult] == 0)
							{
								DNk[findkresult]++;
								kflag[findkresult] =1 ;//防止同一个单词在该文档出现而重复记录
							}
							TNkd[findkresult][pagecnt]++;
						}	
					}
				}
				for (i = 0; i < 100;i++)//将字符串清空
				{
					str[i] = '\0';
				}
				i = 0;
			}
			
			if (c == '\f')
			{    
				memset(kflag, 0, sizeof(kflag));//清空，以便下一页记录
				break;
			}
		}
		if (isalpha(str[0])) {
					findsresult = search(roots,str);//判断是否为停用词
					if (findsresult == 0)
					{
						findbresult = search(rootd, str);
						if (findbresult == 1)//判断是否为单词表单词
						{
							TNd[pagecnt]++;
						}
						findkresult = kbinsearch(keywords,keynum,str);
						if (findkresult != -1)
						{
							if (kflag[findkresult] == 0)
							{
								DNk[findkresult]++;
								kflag[findkresult] =1 ;//防止同一个单词在该文档出现而重复记录
							}
							TNkd[findkresult][pagecnt]++;
						}	
					}
				}
				for (i = 0; i < 100;i++)//将字符串清空
				{
					str[i] = '\0';
				}
				i = 0;
		pagecnt++;
	}
	printf("%d\n\n",pagecnt);
	for (i = 0; i < keynum; i++)
	{
		if (DNk[i] != 0)
			IDFk[i] = log10(pagecnt*1.0/DNk[i]);
	}

	for (i = 0; i <pagecnt; i++)
	{
		page[i].Simd = 0.0;
		for (j = 0; j < keynum; j++)
		{
			if(TNd[i]!=0)
			{ 
				TFkd[j][i] = 1.0 * TNkd[j][i] *100/ TNd[i];
				page[i].Simd += IDFk[j] * TFkd[j][i];
			}
			
		}
	}
	for(i=0;i<pagecnt;i++)
		printf("%d %d\n",i,TNd[i]);
	qsort(page,pagecnt,sizeof(page[0]), cmp);
	for (i = 0; i < 5; i++)
	{
		printf("%.6lf %d %d-%d\n",page[i].Simd,page[i].pagenum,page[i].artnum,page[i].pagenum);
	}
	//printf("%d %d %d",jm ,st ,TNd[0]);
	fclose(fpa);
	fclose(fpd);
	fclose(fps);
	pageptf = pageptf < pagecnt ? pageptf : pagecnt;
	for (i = 0; i < pageptf; i++)
	{
		if (page[i].Simd < dealt) break;
		fprintf(fpr,"%.6lf %d %d-%d\n", page[i].Simd, page[i].pagenum, page[i].artnum, page[i].pagenum);
	}
	fclose(fpr);
	return 0;
}
