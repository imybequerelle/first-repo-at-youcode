#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Déclaration globale des élèments d'un tableau pour stocker les informations d'un livre
    char titre[100];
    char auteur[100];
    float prix[100];
    int quantite_de_stock[100];
    int N,i;

int main() 
{ 
    int choix;
    printf("Entrez un nombre entre 1 et 6 : ");
    scanf("%d", &choix);
    getchar(); // Pour consommer le caractère de nouvelle ligne après scanf

    switch (choix) {
        case 1:
        printf("Vous avez choisi 1 \n");

    // Saisir les informations du livre
    printf("Entrez le titre du livre : ");

    fgets(titre, sizeof(titre), stdin);         // Lecture du titre

    printf("Entrez le nom de l'auteur : ");
    fgets(auteur, sizeof(auteur), stdin);        // Lecture de l'auteur

    printf("Entrez le prix : ");
    scanf("%f", &prix);             // Lecture du prix

     printf("Entrez la quantite de stock  : ");
    scanf("%d", &quantite_de_stock);          // Lecture de la quantite du stock
    break;

      case 2:
    printf("Vous avez choisi 2 \n");

    // Affichage des informations du livre 
    printf("Informations du Livre : \n");
    printf("Titre : %s \n", titre);
    printf("Auteur : %s \n", auteur);
    printf("prix : %f \n", prix);
    printf("quantite de stock : %d \n",quantite_de_stock);
    break;

  case 3:
     printf("Vous avez choisi 3 \n");

char Recherche_livre_disponible(char titres[100][100], int N)
{
    char recherche[100];
    // Demander à l'utilisateur d'entrer la chaîne à rechercher
    printf("Entrez la chaîne à rechercher : ");
    scanf("%s", recherche);

    int trouve = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(titres[i], recherche) == 0) {
            printf("La chaîne '%s' a été trouvée à l'indice %d.\n", recherche, i);
            trouve = 1;
            break; }}

    if (!trouve) {
        printf("La chaîne '%s' n'a pas été trouvée dans le tableau.\n", recherche);}

    return 0;}
break;

  case 4:
       printf("Vous avez choisi 4 \n");
         // Vérifier si le livre est en stock
            if (quantite_de_stock > 0) {
                printf("Le livre est en stock \n");     
            } else {
                printf("Le livre n'est pas en stock \n");
            }
         // Mettre à jour la quantite du livre et modifier la quantite de stock
            int nouvelle_quantite;    //variable locale
            printf("Entrez la nouvelle quantite de stock : ");
            scanf("%d", &nouvelle_quantite);
            quantite_de_stock[0] = nouvelle_quantite;
            printf("La quantite de stock a ete mise a jour : %d \n", quantite_de_stock[0]);
            break;

    case 5:
         printf("Vous avez choisi 5 \n");
         //supprimer un livre du stock
            titre[0] = '\0'; // Effacer le titre
            auteur[0] = '\0'; // Effacer l'auteur
            prix[0] = 0.0; // Réinitialiser le prix
            quantite_de_stock[0] = 0; // Réinitialiser la quantité de stock
            printf("Le livre a ete supprime du stock.\n"); 
            break;

 case 6:
        printf("Vous avez choisi 6 \n");
 //Afficher le nombre total des livres dans le stock
            printf("Le nombre total des livres dans le stock est : %d \n", N);
            break;          
      default:
      printf("votre Choix est invalide ! Veuillez entrer un nombre entre 1 et 5  \n");}
return 0;}