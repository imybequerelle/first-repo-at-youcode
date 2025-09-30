#include<stdio.h>
#include<stdlib.h>
int a;
int b;

int fonctionmin(int a,int b)
{
    if(a<b)
    {
        printf("le nombre le plus petit est : %d",a);
    }
    else
    {
        printf("le nombre le plus petit est : %d",b);
    }
    return 0;
}
int main()
{
 
     printf("entrer la valeur de a :");
    scanf("%d",&a);
    printf("entrer la valeur de b :");
    scanf("%d",&b);
    fonctionmin(a,b);
    return 0;
    
}