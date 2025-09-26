#include <stdio.h>
#include<string.h>
int main() {

    char chaine [50];


printf("entrer la chaine  :");
    fgets(chaine,sizeof(chaine),stdin);

strrev(chaine);

printf("la chaine inverse est  : %s",chaine);
    return 0;
}