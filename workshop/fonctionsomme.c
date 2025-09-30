#include<stdio.h>

int a;
int b;

void fonctionsomme(int a,int b)
{
int somme;
somme=a+b;
}

int main()
{
printf("entrer la valeur de a : ");
scanf("%d",&a);
printf("entrer la valeur de b : ");
scanf("%d",&b);
fonctionsomme(a,b);
printf("le resultat de la somme est : %d",a+b);
return 0;
}