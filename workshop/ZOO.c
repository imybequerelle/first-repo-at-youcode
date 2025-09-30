#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include<time.h>

typedef enum {
    CARNIVORE,
    HERBIVORE,
    OMNIVORE,
} RegimeAlimentaire;

// Structure de l'animal
typedef struct {
    int id;
    char nom[50];
    char espece[50];
    int age;
    char habitat[50];
    float poids;          // Poids (réel, optionnel)
    char date_arrivee[50];   // Bonus: Date d'arrivée
    RegimeAlimentaire regime; // Bonus: Régime alimentaire
} Animal;

// Variables Globales pour le Zoo
Animal zoo[200];
int nb_animaux = 0;
int next_id = 1;  // Prochain ID unique à attribuer

//Génère un ID unique et incrémental.
 
int generer_id() {
    return next_id++;
}

// Trouve l'index d'un animal dans le tableau par son ID.

int trouver_index_par_id(int id) {
    for (int i = 0; i < nb_animaux; i++) {
        if (zoo[i].id == id) {
            return i;
        }
    }
    return -1;
}

//stockage des donnees des animaux du zoo

   struct zoo_animaux[200] = 
   {
    {1, "Simba", "Lion", 5, "Savane", 190.5},
    {2, "Nala", "Lion", 4, "Savane", 175.0},
    {3, "ShereKhan", "Tigre", 8, "Jungle", 220.3},
    {4, "Baloo", "Ours", 12, "Forêt", 310.0},
    {5, "Raja", "Éléphant", 15, "Savane", 540.7},
    {6, "Marty", "Zèbre", 6, "Savane", 300.2},
    {7, "Gloria", "Hippopotame", 10, "Rivière", 450.0},
    {8, "Alex", "Lion", 7, "Savane", 200.0},
    {9, "Julien", "Lémurien", 3, "Jungle", 12.5},
    {10, "Melman", "Girafe", 9, "Savane", 390.8},
    {11, "Timon", "Suricate", 2, "Désert", 1.2},
    {12, "Pumbaa", "Phacochère", 5, "Savane", 120.0},
    {13, "Scar", "Lion", 11, "Savane", 210.4},
    {14, "Kaa", "Serpent", 6, "Jungle", 45.0},
    {15, "Iko", "Perroquet", 4, "Jungle", 2.1},
    {16, "Dumbo", "Éléphant", 3, "Savane", 320.0},
    {17, "Kiki", "Chien sauvage", 7, "Savane", 25.0},
    {18, "Donatello", "Tortue", 40, "Rivière", 90.5},
    {19, "Polly", "Oiseau", 5, "Jungle", 1.5},
    {20, "Kong", "Gorille", 13, "Jungle", 180.0}
   };




//fonction ajouter un animal
void ajouter_animal_interactif() 
   {
    int nb_a_ajouter = 1;
    char choix_multi;

    printf("\n--- Ajout d'Animal ---\n");
    printf("Voulez-vous ajouter plusieurs animaux (O/N) ? ");
    scanf(" %c", &choix_multi);
    if (choix_multi == 'O' || choix_multi == 'o') {
        printf("Combien d'animaux voulez-vous ajouter ? ");
        scanf("%d", &nb_a_ajouter);
        while (getchar() != '\n'); // Nettoyer le buffer
    } else {
        while (getchar() != '\n'); // Nettoyer le buffer
    }

    for (int i = 0; i < nb_a_ajouter; i++) {
        if (nb_animaux >= 200) {
            printf(" Limite maximale de %d animaux atteinte. Arrêt de l'ajout.\n", 200);
            break;
        }




















//fonction qui affiche le menu 
void affiche_menu()
{
printf("\n ******* Gestion de ZOO ******* \n");
    printf("1. Ajouter un animal \n");
    printf("2. ");
    printf("3. ");
    printf("4. ");
    printf("5. ");
    printf("6. ");
    printf("7. ");
    printf("6. ");
    printf("6. ");
    printf("6. ");
    printf("6. ");
    printf("6. ");
    printf("6. ");
    printf("0. Quitter ");
    printf("Choix : ");




}














/*************************************************** MAIN : ******************************************************/

int main()

{
    do{
        affiche_menu();
        scanf("%d", &choix);
         switch (choix) 
         {
        case 1 : ;break;
        case 2 :
        case 3 : 
        case 4 : 
        case 5 :
        case 5 : 
        case 6 :
        case 0: printf(" Au revoir ! \n"); break;
        default: printf(" Choix invalide! \n "); 
         }
        return 0; 
    }}