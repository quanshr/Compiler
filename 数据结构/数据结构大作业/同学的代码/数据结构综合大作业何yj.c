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

int TNd[artmax];//ÿ���ĵ���ĵ�������
int Dnk[wdmax];//���ֵ���k���ĵ���
int kflag[wdmax];//��¼�������ĵ����Ƿ����
int DNk[1010];//���ڼ���ؼ����ڼ����ĵ��г��ֹ�
int TNkd[wdmax][artmax];//���ڼ�¼����k���ĵ�d�г��ֵĴ���
int artnum, pagenum;//artnum��ʾ��ҳ��� pagenum��ʾ�ĵ����
double TFkd[wdmax][artmax];//���ڼ�¼����k���ĵ�d�еĴ�Ƶ
double IDFk[wdmax];//���ĵ�Ƶ��

struct pageinformation {
	int artnum;//��ʾ��ҳ���
	int pagenum;//��ʾ�ĵ���
	double Simd;//���ڼ�¼simdֵ
};
struct pageinformation page[pagemax];

struct words {
	char word[100];
};
struct words keywords[1010];//���ڴ洢�ؼ���

struct b_tree {
	int end;		//���ڱ�ʾ�ж��ٵ����Ըýڵ��β
	char ch;		//���ڱ�ʾ�ýڵ����洢����ĸ
	int flag;       //���ڼ�¼�ýڵ㲻Ϊ�� flag=1 ��Ϊ��
	struct b_tree* nextlettle[26];
};
typedef struct b_tree* trie;
struct b_tree* rootd =NULL;//���ʱ��ͷ�ڵ�
struct b_tree* roots = NULL;//ͣ�ñ��ͷ�ڵ�
struct b_tree* p=NULL, *q=NULL,* r=NULL;

trie createnode()//Ϊ�ڵ�����ռ䣬���ҳ�ʼ��
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
void insert(char s[])//�ֵ�������
{
	q = rootd;
	int index;//���������±�
	int i;
	for (i =0; i<strlen(s); i++)
	{
		index = s[i] - 'a';//�����±꣬��ʾ��ĸ����
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

void insert1(char s[])//�ֵ�������
{
	q = roots;
	int index;//���������±�
	int i;
	for (i = 0; i < strlen(s); i++)
	{
		index = s[i] - 'a';//�����±꣬��ʾ��ĸ����
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

int  search(trie p, char s[])//�ֵ�������
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

int kbinsearch(struct words key[], int n, char find[])//���ֲ��ҹؼ���
{
	int low =0, high = n-1, mid;
	int result = -1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (strcmp(find, key[mid].word) == 0)
		{
			result = mid;
			break; /*���ҳɹ�*/
		}
		if (strcmp(find, key[mid].word) > 0)
			low = mid + 1; /*׼�����Һ�벿�� */
		if (strcmp(find, key[mid].word) < 0)
			high = mid - 1; /*׼������ǰ�벿�� */
	}
	return result; /*����ʧ�� */
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
	int stopcnt = 0;       //ͣ�ô�����
	int diccnt = 0;
	int keynum = argc - 2;//�ؼ�������
	int findbresult = 0;//���ڱ�ʾ�ڵ��ʱ�����ҵĽ��
	int findsresult = 0;//���ڱ�ʾ��ͣ�ñ�����ҵĽ��
	int findkresult = 0;//���ڱ�ʾ�ڹؼ�������ҵĽ��
	int pagecnt = 0;   //���ڼ�¼�ĵ�����
	int pageptf=0;     
	rootd = createnode();
	roots = createnode();
	for (i = 0; i < keynum; i++)
	{
		strcpy(keywords[i].word, argv[i + 2]);//���ؼ��ʴ�������
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

	while (fscanf(fps, "%s", str) != EOF)//��ͣ�ô��ĵ�����
	{
		insert1(str);
		stopcnt++;
	}

	while (fscanf(fpd, "%s", str) != EOF)//���ֵ���ĵ����ҽ��ֵ���
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
			if (isalpha(c))//��ȡ���ʣ��������ĸ����������ַ���
				str[i++] = tolower(c);
			else if (!isalpha(c))//��������ַ����������ڶ��ĵ��ʣ��������Ƿ�Ϊ���ʱ���ĵ���
			{
				if (isalpha(str[0])) {
					findsresult = search(roots,str);//�ж��Ƿ�Ϊͣ�ô�
					if (findsresult == 0)
					{
						findbresult = search(rootd, str);
						if (findbresult == 1)//�ж��Ƿ�Ϊ���ʱ���
						{
							TNd[pagecnt]++;
						}
						findkresult = kbinsearch(keywords,keynum,str);
						if (findkresult != -1)
						{
							if (kflag[findkresult] == 0)
							{
								DNk[findkresult]++;
								kflag[findkresult] =1 ;//��ֹͬһ�������ڸ��ĵ����ֶ��ظ���¼
							}
							TNkd[findkresult][pagecnt]++;
						}	
					}
				}
				for (i = 0; i < 100;i++)//���ַ������
				{
					str[i] = '\0';
				}
				i = 0;
			}
			
			if (c == '\f')
			{    
				memset(kflag, 0, sizeof(kflag));//��գ��Ա���һҳ��¼
				break;
			}
		}
		if (isalpha(str[0])) {
					findsresult = search(roots,str);//�ж��Ƿ�Ϊͣ�ô�
					if (findsresult == 0)
					{
						findbresult = search(rootd, str);
						if (findbresult == 1)//�ж��Ƿ�Ϊ���ʱ���
						{
							TNd[pagecnt]++;
						}
						findkresult = kbinsearch(keywords,keynum,str);
						if (findkresult != -1)
						{
							if (kflag[findkresult] == 0)
							{
								DNk[findkresult]++;
								kflag[findkresult] =1 ;//��ֹͬһ�������ڸ��ĵ����ֶ��ظ���¼
							}
							TNkd[findkresult][pagecnt]++;
						}	
					}
				}
				for (i = 0; i < 100;i++)//���ַ������
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
