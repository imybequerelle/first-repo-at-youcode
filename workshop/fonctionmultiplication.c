#include<stdio.h>
int a;
int b;

int fonctionmultiplication(int a, int b)
{  
   int multiplication;
   multiplication = a * b;
   return multiplication;
}
int main()

{
     printf("entrer la valeur de a :");
    scanf("%d",&a);
    printf("entrer la valeur de b :");
     scanf("%d",&b);
    int resultat = fonctionmultiplication(a, b);
    printf("le resultat de la multiplication est : %d", resultat);
         return 0;
}      