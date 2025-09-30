#include<stdio.h>
#include<stdlib.h>
void tri_selection(int tab[],int n){
    int i,j,min,temp;
    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++){
            if(tab[j]<tab[min]){
                min=j;
            }
        }
        if(min!=i){
            temp=tab[i];
            tab[i]=tab[min];
            tab[min]=temp;
        }
    }
}   
int main(){
    int n,i;
    printf("donner la taille du tableau:");
    scanf("%d",&n);
    int *tab=(int*)malloc(n*sizeof(int));
    printf("donner les elements du tableau:\n");
    for(i=0;i<n;i++){
        scanf("%d",&tab[i]);
    }
    tri_selection(tab,n);
    printf("le tableau trie est:\n");
    for(i=0;i<n;i++){
        printf("%d ",tab[i]);
    }
    free(tab);
    return 0;
}