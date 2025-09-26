#include<stdio.h>
#include<string.h>
//comparaison de deux chaines de caracteres
int main()
{
    char str1[100], str2[100];
    printf("Entrer la premiere chaine : ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = 0; // enlever le saut de ligne
    printf("Entrer la deuxieme chaine : ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = 0; // enlever le saut de ligne

    if(comparer_chaines(str1, str2) == 0) {
        printf("Les chaines sont identiques.\n");
    } else {
        printf("Les chaines sont differentes.\n");
    }

    return 0;
}