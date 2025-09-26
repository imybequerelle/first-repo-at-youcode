#include<stdio.h>
#include<string.h>
int main()
{
    char chaine[100];
    printf("entrer la chaine :");   
    fgets(chaine, sizeof(chaine), stdin);
    int i = 0, j = 0;
    while (chaine[i] != '\0')
    {
        if (chaine[i] != ' ' && chaine[i] != '\n' && chaine[i] != '\t')
        {
            chaine[j++] = chaine[i];
        }
        i++;
    }
    chaine[j] = '\0';             // Null termine la string  modifiee
    printf("la chaine apres suppression des espaces est : %s", chaine);
    return 0;
}