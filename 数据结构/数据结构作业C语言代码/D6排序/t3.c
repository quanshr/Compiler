#include <stdio.h>
#include <stdlib.h>

int n,op,a[110],ans,i,j;
void adjust(int k[],int i,int n)
{
	int j,temp;
	temp=k[i];
	j=2*i+1;
	while(j<n)
	{
		if(j<n-1&&k[j]<k[j+1])
			j++;
		if(ans++,temp>=k[j])
			break;
		k[(j-1)/2]=k[j];
		j=2*j+1;
	}
	k[(j-1)/2]=temp;
}
void heapSort(int k[],int n)
{
	int i,temp;
	for(i=n/2-1;i>=0;i--)
		adjust(k,i,n);
	for(i=n-1;i>=1;i--)
	{
		temp=k[i];
		k[i]=k[0];
		k[0]=temp;
		adjust(k,0,i);
	}
}
int b[110];
void merge(int x[],int tmp[],int left,int rightend)
{
	if(left==rightend) return;
	int leftend=(left+rightend)/2;
	merge(a,b,left,leftend);
	merge(a,b,leftend+1,rightend);
	int i=left,j=leftend+1,q=left;
	while(i<=leftend&&j<=rightend)
	{
		if(ans++,x[i]<=x[j]) 
			tmp[q++]=x[i++];
		else
			tmp[q++]=x[j++];
	}
    while(i<=leftend)
		tmp[q++]=x[i++];
    while(j<=rightend)
		tmp[q++]=x[j++];
    for(i=left;i<=rightend;i++)
		x[i]=tmp[i];
}
void swap(int *a,int *b)
{
	int x=*a;
	*a=*b;
	*b=x;
}
void quickSort(int k[],int left,int right)
{
    int i,last;
    if(left<right)
	{
		last=left;
		for(i=left+1;i<=right;i++)
			if(ans++,k[i]<k[left])
				swap(&k[++last],&k[i]); 
		swap(&k[left],&k[last]);
		quickSort(k,left,last-1); 
		quickSort(k,last+1,right);
	}
}

int main()
{
	scanf("%d%d",&n,&op);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	if(op==1)
	{
		for(i=1;i<=n;i++)
		{
			int p=i;
			for(j=i+1;j<=n;j++)
				if(ans++,a[j]<a[p])
					p=j;
			int x=a[i];
			a[i]=a[p];
			a[p]=x;
		}
	}
	else if(op==2)
	{
		for(i=1;i<=n;i++)
		{
			int ok=1;
			for(j=1;j<=n-i;j++)
				if(ans++,a[j]>a[j+1])
				{
					int x=a[j];
					a[j]=a[j+1];
					a[j+1]=x;
					ok=0;
				}
			if(ok) break;
		}
	}
	else if(op==3)
	{
		heapSort(a+1,n);
	}
	else if(op==4)
	{
		merge(a,b,1,n);
	}
	else
	{
		quickSort(a,1,n);
	}
	for(i=1;i<=n;i++) printf("%d ",a[i]);
	printf("\n%d",ans);
	return 0;
}
