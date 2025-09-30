#include<stdio.h>
#include<string.h>
//programme qui lit deux chaines de caracteres et compare leur egalite

int main()
{
    char chaine1[100];
    char chaine2[100];
    printf("entrer la premiere chaine :");
    fgets(chaine1, sizeof(chaine1), stdin);
    printf("entrer la deuxieme chaine :");
    fgets(chaine2, sizeof(chaine2), stdin);
    if (strcmp(chaine1, chaine2) == 0)
    {
        printf("les deux chaines sont egales");
    }
    else
    {
        printf("les deux chaines ne sont pas egales");
    }
    return 0;
}