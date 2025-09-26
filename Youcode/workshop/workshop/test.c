#include<studio.h>
#include<string.h>      
#include<stdlib.h>
//parcourir un tableau par nombre d iteration n 
void parcourir(int tab[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}
//fonction pour inverser un tableau
void inverser(int tab[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = tab[i];
        tab[i] = tab[n - i - 1];
        tab[n - i - 1] = temp;
    }
}       
