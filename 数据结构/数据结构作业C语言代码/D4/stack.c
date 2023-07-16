#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n,i,j,k,now,st[410],p,flag,m;
int op[410],line[410],t;
char s[410],c[4]={'(',')','{','}'};

int main(){
    freopen("example.c","r",stdin);
    while(gets(s)){
        k++;
        n=strlen(s);
        //printf("%d\n",n);
        for(i=0;i<n;i++){
            if(i>=1&&s[i-1]=='/'&&s[i]=='*'){
                m=1;
                i++;
                continue;
            }
            if(i>=1&&s[i-1]=='*'&&s[i]=='/') m=0;
            if(m) continue;
            if(i>=1&&s[i-1]=='/'&&s[i]=='/') break;
            if(s[i]=='\''){
                for(i=i+1;i<n;i++)
                    if(s[i]=='\'') break;
                continue;
            }
            if(s[i]=='\"'){
                for(i=i+1;i<n;i++)
                    if(s[i]=='\"') break;
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
            if(p&&op[st[p]]==0){
                flag=st[p];
                break;
            }
            st[++p]=i;
        }
        else if(op[i]==1){
            if(!p||op[st[p]]!=0){
                flag=i;
                break;
            }
            p--;
        }
        else if(op[i]==3){
            if(!p||op[st[p]]!=2){
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
    if(flag) printf("without maching \'%c\' at line %d",c[op[flag]],line[flag]);
    else
        for(i=1;i<=t;i++)
            printf("%c",c[op[i]]);
    return 0;
}
