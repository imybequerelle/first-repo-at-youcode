#include <stdio.h>
#include <string.h>
int main() 
{
    char chaine[100];
    char souschaine[100];
    printf("entrer la chaine :");
    fgets(chaine, sizeof(chaine), stdin);
    chaine[strcspn(chaine, "\n")] = '\0';
     printf("entrer la sous chaine  :");
    fgets(souschaine, sizeof(souschaine), stdin);
    souschaine[strcspn(souschaine, "\n")] = '\0';
    if (strstr(chaine, souschaine) != NULL)
    {
        printf("la sous chaine est presente dans la chaine");
    }
    else
    {
        printf("la sous chaine n'est pas presente dans la chaine");
    }
}