#include<stdio.h>
#include<string.h>
//conversion en minuscule
int main()
{
    char chaine[100];
    printf("entrer la chaine :");
    fgets(chaine, sizeof(chaine), stdin);
    for(int i=0;chaine[i]!='\0';i++)
    {
        if(chaine[i]>='A' && chaine[i]<='Z')
        {
            chaine[i]=chaine[i]+32;
        }
    }   
    printf("la chaine en minuscule est : %s",chaine);
}