#include<stdio.h>
#include<stdlib.h>

char chaine[1];
void inverserchaine(char chaine[])
{
    int longueur = 0;
    while (chaine[longueur] != '\0' && chaine[longueur] != '\n')
    {
        longueur++;
    }

    for (int i = 0; i < longueur / 2; i++)
    {
        char temp = chaine[i];
        chaine[i] = chaine[longueur - i - 1];
        chaine[longueur - i - 1] = temp;
    }
    printf("la chaine apres inversion est : %s", chaine);
}
int main()
{
    printf("entrer la chaine a inverser :");
    fgets(chaine, sizeof(chaine), stdin);
    inverserchaine(chaine);
    return 0;
}