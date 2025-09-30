#include <stdio.h>
#include <string.h>

//fonction qui inverse une chaine de caracteres
void inverser_chaine(char str[]) {
    int debut = 0;
    int fin = strlen(str) - 1;
    char temp;

    while(debut < fin) {
        //echanger les caracteres
        temp = str[debut];
        str[debut] = str[fin];
        str[fin] = temp;
        debut++;
        fin--;
    }
}
int main() 
{
    char str[100];
    printf("Entrer une chaine : ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; // enlever le saut de ligne

    inverser_chaine(str);
    printf("Chaine inversee : %s\n", str);

    return 0;
}
