#include<stdio.h>
#include<string.h>
//conversion en majuscule
int main()
{
    char chaine[100];
    printf("entrer la chaine :");
    fgets(chaine, sizeof(chaine), stdin);
    for(int i=0;chaine[i]!='\0';i++)
    {
        if(chaine[i]>='a' && chaine[i]<='z')
        {
            chaine[i]=chaine[i]-32;
        }
    }   
    printf("la chaine en majuscule est : %s",chaine);
}
