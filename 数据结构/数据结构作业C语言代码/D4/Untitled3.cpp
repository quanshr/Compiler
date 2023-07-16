#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n,i,j,k,now,st1[210],p,st2[210],q,flag,m;
int op[210],line[210],t;
char s[210],c[4]={'(',')','{','}'};

int main(){
	freopen("example.c","r",stdin);
	while(gets(s)){
		k++;
		n=strlen(s);
		//printf("%d\n",n);
		for(i=0;i<n;i++){
			if(i>=1&&s[i-1]=='/'&&s[i]=='*') m=1;
			if(i>=1&&s[i-1]=='*'&&s[i]=='/') m=0;
			if(m) continue;
			if(i>=1&&s[i-1]=='/'&&s[i]=='/') break;
			if(s[i]=='\''){
				for(i=i+1;i<n;i++)
					if(s[i]=='\'') break;
				continue;
			}
			if(s[i]=='"'){
				for(i=i+1;i<n;i++)
					if(s[i]=='"') break;
				continue;
			}
			for(j=0;j<=3;j++)
				if(s[i]==c[j]){
					op[++t]=j;
					line[t]=k;
				}
		}
	}
	for(i=1;i<=t;i++){
		if(op[i]==2){
			if(p&&op[st1[p]]==0&&(!q||st1[p]>st2[q])){
				flag=st1[p];
				break;
			}
			st2[++q]=i;
		}
		else if(op[i]==1){
			if(p&&op[st1[p]]!=0){
				flag=i;
				break;
			}
			p--;
		}
		else if(op[i]==3){
			if(p&&op[st[p]]!=2){
				flag=i;
				break;
			}
			p--;
		}
		else{
			st[++p]=i;
		}
	}
	if(p) flag=st[p];
	if(flag) printf("without maching '%c' at line %d",c[op[flag]],line[flag]);
	else
		for(i=1;i<=t;i++)
			printf("%c",c[op[i]]);
	return 0;
}
