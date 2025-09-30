//tri bulles 
#include<stdio.h>
#include<stdlib.h>
int main() 
{
    int i,j,n,temp;
    int *tab;
    printf("donner la taille du tableau\n");
    scanf("%d",&n);
    tab=(int*)malloc(n*sizeof(int));
    printf("donner les elements du tableau\n");
    for(i=0;i<n;i++)
        scanf("%d",&tab[i]);
        
    for(i=0;i<n-1;i++)
        for(j=0;j<n-i-1;j++)
            if(tab[j]>tab[j+1])
            {
                temp=tab[j];
                tab[j]=tab[j+1];
                tab[j+1]=temp;
            }
    printf("le tableau trie est:\n");
    for(i=0;i<n;i++)
        printf("%d ",tab[i]);
    free(tab);
}