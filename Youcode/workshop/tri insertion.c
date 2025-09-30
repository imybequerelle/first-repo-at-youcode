//tri insertion 
#include<stdio.h>
#include<stdlib.h>  
int main() 
{
    int i,j,n,temp;
    int *tab;
    printf("donner la taille du tableau \n");
    scanf("%d",&n);
    tab=(int*)malloc(n*sizeof(int));
    printf("donner les elements du tableau \n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&tab[i]);
    }
    
    for(i=1;i<n;i++)
    {
        temp=tab[i];
        j=i-1;
        while((temp<tab[j])&&(j>=0))
        {
            tab[j+1]=tab[j];
            j--;
        }
        tab[j+1]=temp;
    }
    printf("le tableau trie est : \n");
    for(i=0;i<n;i++)
    {
        printf("%d \t",tab[i]);
    }
}   