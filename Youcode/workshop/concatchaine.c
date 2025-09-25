#include <stdio.h>
#include <string.h>
int main()
{
    char chaine1[100];
    char chaine2[100];
    printf("entrer la premiere chaine :");
    fgets(chaine1, sizeof(chaine1), stdin);
    printf("entrer la deuxieme chaine :");
    fgets(chaine2, sizeof(chaine2), stdin);
    strcat(chaine1, chaine2); // Concatenate chaine2 to the end of chaine1
    printf("la chaine apres concatenation est : %s", chaine1);
    return 0;
}
