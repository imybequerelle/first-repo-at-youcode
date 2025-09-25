#include<stdio.h>
#include<string.h>
int main()
{
    char chaine[100];
    char souschaine[100];
    printf("entrer la chaine :");
    fgets(chaine, sizeof(chaine), stdin);
     printf("entrer la sous chaine  :");
    fgets(souschaine, sizeof(souschaine), stdin);
    if (strstr(chaine, souschaine) != NULL)
    {
        printf("la sous chaine est presente dans la chaine");
    }
    else
    {
        printf("la sous chaine n'est pas presente dans la chaine");
    }
}