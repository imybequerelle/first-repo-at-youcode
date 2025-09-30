#include<stdio.h>
#include<string.h>
int main()
{
    char chaine[]="abcd";
    int longueur = 0;
    while (chaine[longueur] != '\0' && chaine[longueur] != '\n')
    {
        longueur++;
    }
    printf("la longueur de la chaine est : %d", longueur);
    return 0;
}