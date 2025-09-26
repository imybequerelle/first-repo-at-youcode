#include<stdio.h>
#include<stdlib.h>

int a;
int fact(int a)
{
    if(a==0)
    {
        return 1;
    }
    else
    {
        return a*fact(a-1);
    }
}
int main()
{
 
     printf("entrer la valeur de a :");
    scanf("%d",&a);
    printf("la factorielle de %d est : %d",a,fact(a));
    return 0;
    
}   
