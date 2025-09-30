#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LENGTH 50
#define PHONE_LENGTH 15

// Structure représentant un contact
typedef struct {
    char nom[NAME_LENGTH];
    char telephone[PHONE_LENGTH];
    char email[100];
} Contact;

// Structure représentant le carnet de contacts
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int nombreContacts;
} Carnet;

// Fonction pour ajouter un contact
void ajouterContact(Carnet *carnet) {
    if (carnet->nombreContacts>= MAX_CONTACTS) {
        printf("Carnet plein!\n");
        return;
}

    Contact nouveau;
    printf("Nom: ");
    scanf(" %[^\n]", nouveau.nom);
    printf("Téléphone: ");
    scanf(" %[^\n]", nouveau.telephone);
    printf("Email: ");
    scanf(" %[^\n]", nouveau.email);

    carnet->contacts[carnet->nombreContacts++] = nouveau;
    printf("Contact ajouté avec succès.\n");
}

// Fonction pour afficher tous les contacts
void afficherContacts(const Carnet *carnet) {
    printf("\n--- Liste des contacts ---\n");
    for (int i = 0; i < carnet->nombreContacts; i++) {
        printf("%d. %s - %s\n", i + 1, carnet->contacts[i].nom, carnet->contacts[i].telephone, carnet->contacts[i].email);
}
    printf("--------------------------\n");
}

// Fonction pour rechercher un contact par nom
void rechercherContact(const Carnet *carnet) {
    char nomRecherche[NAME_LENGTH];
    printf("Nom à rechercher: ");
    scanf(" %[^\n]", nomRecherche);

    int trouve = 0;
    for (int i = 0; i < carnet->nombreContacts; i++) {
        if (strcmp(carnet->contacts[i].nom, nomRecherche) == 0) {
            printf("Contact trouvé: %s - %s\n", carnet->contacts[i].nom, carnet->contacts[i].telephone);
            trouve = 1;
            break;
}
}

    if (!trouve) {
        printf("Aucun contact trouvé avec ce nom.\n");
}
}

// Menu principal
int main() {
    Carnet monCarnet;
    monCarnet.nombreContacts = 0;

    int choix;
    do {
        printf("\n--- Carnet de contacts ---\n");
        printf("1. Ajouter un contact\n");
        printf("2. Afficher les contacts\n");
        printf("3. Rechercher un contact\n");
        printf("0. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterContact(&monCarnet);
                break;
            case 2:
                afficherContacts(&monCarnet);
                break;
            case 3:
                rechercherContact(&monCarnet);
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide.\n");
}
} while (choix!= 0);

    return 0;
}
